// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Models/SessionModel.cpp
//! @brief     Implements class SessionModel.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "SessionModel.h"
#include "ItemFactory.h"
#include "GUIHelpers.h"
#include "MaterialEditor.h"
#include "ComboProperty.h"
#include "ScientificDoubleProperty.h"
#include "IconProvider.h"
#include "FancyGroupProperty.h"
#include "MaterialUtils.h"
#include "MaterialProperty.h"
#include "AngleProperty.h"

#include <QFile>
#include <QMimeData>
#include <QDebug>

namespace {
const int MaxCompression = 9;
enum Column {
    ItemName,
    ModelType,
    MaxColumns
};
}

SessionModel::SessionModel(QString model_tag, QObject *parent)
    : QAbstractItemModel(parent)
    , m_root_item(0)
    , m_name("DefaultName")
    , m_model_tag(model_tag)
    , m_iconProvider(0)
{
}

SessionModel::~SessionModel()
{
    delete m_root_item;
    delete m_iconProvider;
}

Qt::ItemFlags SessionModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags result_flags = QAbstractItemModel::flags(index);
    if (index.isValid()) {
        result_flags |= Qt::ItemIsSelectable|Qt::ItemIsEnabled
                     |Qt::ItemIsEditable|Qt::ItemIsDragEnabled;
        QList<QString> acceptable_child_items = getAcceptableChildItems(index);
        if (acceptable_child_items.contains(m_dragged_item_type)) {
            result_flags |= Qt::ItemIsDropEnabled;
        }
    }
    else {
        result_flags |= Qt::ItemIsDropEnabled;
    }
    return result_flags;
}

QVariant SessionModel::data(const QModelIndex &index, int role) const
{
    if (!m_root_item || !index.isValid() || index.column() < 0
            || index.column() >= MaxColumns) {
        return QVariant();
    }
    if (ParameterizedItem *item = itemForIndex(index)) {
        if (role == Qt::DisplayRole || role == Qt::EditRole) {
            switch (index.column()) {
            case ItemName: return item->itemName();
            case ModelType: return item->modelType();
            default: return QVariant();
            }
        }
        else if(role == Qt::DecorationRole && m_iconProvider) {
            return m_iconProvider->icon(item->modelType());
        }
    }
    return QVariant();
}

QVariant SessionModel::headerData(int section, Qt::Orientation orientation,
                                  int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        switch (section) {
        case ItemName: return tr("Name");
        case ModelType: return tr("Model Type");
        }
    }
    return QVariant();
}

int SessionModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid() && parent.column() != 0) return 0;
    ParameterizedItem *parent_item = itemForIndex(parent);
    return parent_item ? parent_item->childItemCount() : 0;
}

int SessionModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid() && parent.column() != 0) return 0;
    return MaxColumns;
}

QModelIndex SessionModel::index(int row, int column,
                                const QModelIndex &parent) const
{
    if (!m_root_item || row < 0 || column < 0 || column >= MaxColumns
            || (parent.isValid() && parent.column() != 0))
        return QModelIndex();
    ParameterizedItem *parent_item = itemForIndex(parent);
    if (ParameterizedItem *item = parent_item->childAt(row)) {
        return createIndex(row, column, item);
    }
    return QModelIndex();
}

QModelIndex SessionModel::parent(const QModelIndex &child) const
{
    if (!child.isValid()) return QModelIndex();
    if (ParameterizedItem *child_item = itemForIndex(child)) {
        if (ParameterizedItem *parent_item = child_item->parent()) {
            if (parent_item == m_root_item) return QModelIndex();
            if (ParameterizedItem *grandparent_item = parent_item->parent())
            {
                int row = grandparent_item->rowOfChild(parent_item);
                return createIndex(row, 0, parent_item);
            }
        }
    }
    return QModelIndex();
}

bool SessionModel::setData(const QModelIndex &index,
                           const QVariant &value, int role)
{
    if (!index.isValid() || index.column()!=ItemName) return false;
    if (ParameterizedItem *item = itemForIndex(index)) {
        if (role==Qt::EditRole) {
            qDebug() << "SessionModel::setData ";
            item->setItemName(value.toString());
        }
        else return false;
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

bool SessionModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if (!m_root_item) return false;
    ParameterizedItem *item = parent.isValid() ? itemForIndex(parent)
                                               : m_root_item;
    beginRemoveRows(parent, row, row + count - 1);
    for (int i=0; i<count; ++i) {
        delete item->takeChildItem(row);
    }
    endRemoveRows();
    return true;
}

QStringList SessionModel::mimeTypes() const
{
    return QStringList() << SessionXML::MimeType;
}

QMimeData *SessionModel::mimeData(const QModelIndexList &indices) const
{
    if (indices.count() != 2) return 0;
    if (ParameterizedItem *item = itemForIndex(indices.at(0))) {
        QMimeData *mime_data = new QMimeData;
        QByteArray xml_data;
        QXmlStreamWriter writer(&xml_data);
        writeItemAndChildItems(&writer, item);
        mime_data->setData(SessionXML::MimeType,
                           qCompress(xml_data, MaxCompression));
        return mime_data;
    }
    return 0;
}

bool SessionModel::canDropMimeData(const QMimeData *data, Qt::DropAction action,
                                   int row, int column,
                                   const QModelIndex &parent) const
{
    (void)row;
    if (action == Qt::IgnoreAction) return true;
    if (action != Qt::MoveAction || column > 0 || !data
            || !data->hasFormat(SessionXML::MimeType)) return false;
    if (!parent.isValid()) return true;
    QList<QString> acceptable_child_items = getAcceptableChildItems(parent);
    QByteArray xml_data = qUncompress(data->data(SessionXML::MimeType));
    QXmlStreamReader reader(xml_data);
    while (!reader.atEnd()) {
        reader.readNext();
        if (reader.isStartElement()) {
            if (reader.name() == SessionXML::ItemTag) {
                const QString model_type = reader.attributes()
                        .value(SessionXML::ModelTypeAttribute).toString();
                return acceptable_child_items.contains(model_type);
            }
        }
    }
    return false;
}

bool SessionModel::dropMimeData(const QMimeData *data, Qt::DropAction action,
                                int row, int column, const QModelIndex &parent)
{
    if (action == Qt::IgnoreAction) return true;
    if (action != Qt::MoveAction || column > 0 || !data
            || !data->hasFormat(SessionXML::MimeType)) return false;
    if (!canDropMimeData(data, action, row, column, parent)) return false;
    if (ParameterizedItem *item = itemForIndex(parent)) {
        QByteArray xml_data = qUncompress(data->data(SessionXML::MimeType));
        QXmlStreamReader reader(xml_data);
        if (row == -1) row = item->childItemCount();
        beginInsertRows(parent, row, row);
        readItems(&reader, item, row);
        endInsertRows();
        return true;
    }
    return false;
}

QModelIndex SessionModel::indexOfItem(ParameterizedItem *item) const
{
    if (!item || item == m_root_item) return QModelIndex();
    ParameterizedItem *parent_item = item->parent();
    int row = parent_item->rowOfChild(item);
    return createIndex(row, 0, item);
}

ParameterizedItem *SessionModel::insertNewItem(QString model_type,
                                               const QModelIndex &parent,
                                               int row,
                                               ParameterizedItem::PortInfo::Keys port)
{
    if (!m_root_item) {
        m_root_item = ItemFactory::createEmptyItem();
    }
    ParameterizedItem *parent_item = itemForIndex(parent);
    if (row==-1) row = parent_item->childItemCount();
    beginInsertRows(parent, row, row);
    ParameterizedItem *new_item = insertNewItem(model_type, parent_item, row, port);
    endInsertRows();

    cleanItem(indexOfItem(parent_item), row, row);
    return new_item;
}

QList<QString> SessionModel::getAcceptableChildItems(
        const QModelIndex &parent) const
{
    QList<QString> result;
    if (ParameterizedItem *parent_item = itemForIndex(parent)) {
        result = parent_item->acceptableChildItems();
    }
    return result;
}

void SessionModel::clear()
{
    beginResetModel();
    delete m_root_item;
    m_root_item = 0;
    endResetModel();
}

void SessionModel::load(const QString &filename)
{
    beginResetModel();
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly))
        throw GUIHelpers::Error(file.errorString());
    clear();
    m_root_item = ItemFactory::createEmptyItem();
    QXmlStreamReader reader(&file);
    readItems(&reader, m_root_item);
    if (reader.hasError())
        throw GUIHelpers::Error(reader.errorString());
    endResetModel();
}


void SessionModel::save(const QString &filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly|QIODevice::Text))
        throw GUIHelpers::Error(file.errorString());

    QXmlStreamWriter writer(&file);
    writer.setAutoFormatting(true);
    writer.writeStartDocument();
    writer.writeStartElement("BornAgain");
    writer.writeAttribute("Version", "1.9");
    writeItemAndChildItems(&writer, m_root_item);
    writer.writeEndElement(); // BornAgain
    writer.writeEndDocument();
}


ParameterizedItem *SessionModel::itemForIndex(const QModelIndex &index) const
{
    if (index.isValid()) {
        if (ParameterizedItem *item = static_cast<ParameterizedItem *>(
                    index.internalPointer()))
            return item;
    }
    return m_root_item;
}

void SessionModel::readFrom(QXmlStreamReader *reader)
{
    Q_ASSERT(reader);

    qDebug() << "SessionModel::readFrom()" << m_model_tag << reader->name() << m_root_item;

    if(reader->name() != m_model_tag) {
        throw GUIHelpers::Error("SessionModel::readFrom() -> Format error in p1");
    }

    beginResetModel();
    clear();

    m_name = reader->attributes()
            .value(SessionXML::ModelNameAttribute).toString();

    m_root_item = ItemFactory::createEmptyItem();

    readItems(reader, m_root_item);
    if (reader->hasError())
        throw GUIHelpers::Error(reader->errorString());
    endResetModel();

}


void SessionModel::writeTo(QXmlStreamWriter *writer, ParameterizedItem *parent)
{
    writer->writeStartElement(m_model_tag);
    writer->writeAttribute(SessionXML::ModelNameAttribute, m_name);

    qDebug() << "SessionModel::writeTo";
    if(!parent) parent = m_root_item;
    writeItemAndChildItems(writer, parent);

    writer->writeEndElement(); // m_model_tag
}


void SessionModel::moveParameterizedItem(ParameterizedItem *item, ParameterizedItem *new_parent, int row)
{
    qDebug() << "";
    qDebug() << "";
    qDebug() << "SessionModel::moveParameterizedItem() " << item << new_parent << row;

    if(new_parent) {
        if(!new_parent->acceptsAsChild(item->modelType())) return;
    } else {
        new_parent = m_root_item;
    }

    if(item->parent() == new_parent && indexOfItem(item).row() == row) {
        qDebug() << "SessionModel::moveParameterizedItem() -> no need to move, same parent, same raw. ";
        return;
    }

    QByteArray xml_data;
    QXmlStreamWriter writer(&xml_data);
    writeItemAndChildItems(&writer, item);

    QXmlStreamReader reader(xml_data);
    if (row == -1) row = new_parent->childItemCount();

    qDebug() << "   SessionModel::moveParameterizedItem()  >>> Beginning to insert indexOfItem(new_parent)" << indexOfItem(new_parent);
    beginInsertRows(indexOfItem(new_parent), row, row);
    readItems(&reader, new_parent, row);
    endInsertRows();

    qDebug() << " ";
    qDebug() << "    SessionModel::moveParameterizedItem() >>> Now deleting indexOfItem(item).row()" << indexOfItem(item).row();

    removeRows(indexOfItem(item).row(), 1, indexOfItem(item->parent()));

    cleanItem(indexOfItem(new_parent), row, row);
}


SessionModel *SessionModel::createCopy(ParameterizedItem *parent)
{
    (void)parent;
    throw GUIHelpers::Error("SessionModel::createCopy() -> Error. Not implemented.");
}



ParameterizedItem *SessionModel::insertNewItem(QString model_type,
                                               ParameterizedItem *parent,
                                               int row,
                                               ParameterizedItem::PortInfo::Keys port)
{
    if (!m_root_item) {
        m_root_item = ItemFactory::createEmptyItem();
    }
    if (!parent) parent = m_root_item;
    if (row == -1) row = parent->childItemCount();
    if (row < 0 || row > parent->childItemCount()) return 0;
    if (parent != m_root_item) {
        if (!parent->acceptsAsChild(model_type))
            return 0;
    }

    ParameterizedItem *new_item = ItemFactory::createItem(model_type);
    if(port != ParameterizedItem::PortInfo::PortDef)
        new_item->setItemPort(port);

    if(!new_item)
        throw GUIHelpers::Error("SessionModel::insertNewItem() -> Wrong model type "+ model_type);

    connect(new_item, SIGNAL(propertyChanged(const QString &)), this, SLOT(onItemPropertyChange(const QString &)));
    parent->insertChildItem(row, new_item);

    return new_item;
}

void SessionModel::readItems(QXmlStreamReader *reader, ParameterizedItem *item,
                             int row)
{
    qDebug() << "SessionModel::readItems() ";
    bool inside_parameter_tag = false;
    QString parent_parameter_name;
    while (!reader->atEnd()) {
        reader->readNext();
        if (reader->isStartElement()) {
            if (reader->name() == SessionXML::ItemTag) {
                const QString model_type = reader->attributes()
                        .value(SessionXML::ModelTypeAttribute).toString();
                const QString item_name = reader->attributes()
                        .value(SessionXML::ItemNameAttribute).toString();
                if (inside_parameter_tag) {
                    Q_ASSERT(item);
                    ParameterizedItem *parent = item;
                    item = parent->getSubItems()[parent_parameter_name];
                }
                else {
                    item = insertNewItem(model_type, item, row);
                }
                item->setItemName(item_name);
                row = -1; // all but the first item should be appended
            }
            else if (reader->name() == SessionXML::ParameterTag) {
                parent_parameter_name = readProperty(reader, item);
                inside_parameter_tag = true;
            }
        }
        else if (reader->isEndElement()) {
            if (reader->name() == SessionXML::ItemTag) {
                item = item->parent();
            }
            if (reader->name() == m_model_tag) {
                break;
            }
            if (reader->name() == SessionXML::ParameterTag) {
                inside_parameter_tag = false;
            }
        }
    }
}


QString SessionModel::readProperty(QXmlStreamReader *reader, ParameterizedItem *item)
{
    qDebug() << "SessionModel::readProperty() for" << item;
    if(item) qDebug() << item->modelType();
    const QString parameter_name = reader->attributes()
            .value(SessionXML::ParameterNameAttribute)
            .toString();
    const QString parameter_type = reader->attributes()
            .value(SessionXML::ParameterTypeAttribute)
            .toString();
    //qDebug() << "           SessionModel::readProperty " << item->itemName() << item->modelType() << parameter_name << parameter_type << parameter_name.toUtf8().constData();
    if (parameter_type == "double") {
        double parameter_value = reader->attributes()
                .value(SessionXML::ParameterValueAttribute)
                .toDouble();
        item->setRegisteredProperty(parameter_name, parameter_value);

    }
    else if (parameter_type == "int") {
            int parameter_value = reader->attributes()
                    .value(SessionXML::ParameterValueAttribute)
                    .toInt();
            item->setRegisteredProperty(parameter_name, parameter_value);
    }
    else if (parameter_type == "bool") {
        bool parameter_value = reader->attributes()
                .value(SessionXML::ParameterValueAttribute)
                .toInt();
        item->setRegisteredProperty(parameter_name, parameter_value);

    }
    else if (parameter_type == "QString") {
        QString parameter_value = reader->attributes()
                .value(SessionXML::ParameterValueAttribute)
                .toString();
        item->setRegisteredProperty(parameter_name, parameter_value);

    }
    else if (parameter_type == "MaterialProperty") {
        QString identifier = reader->attributes()
                .value(SessionXML::IdentifierAttribute)
                .toString();

        MaterialProperty material_property(identifier);
        item->setProperty(parameter_name.toUtf8().constData(), material_property.getVariant());
    }
    else if (parameter_type == "ComboProperty") {
        QString parameter_value = reader->attributes()
                .value(SessionXML::ParameterValueAttribute)
                .toString();

        ComboProperty combo_property = item->getRegisteredProperty(parameter_name).value<ComboProperty>();
        combo_property.setValue(parameter_value);
        item->setRegisteredProperty(parameter_name, combo_property.getVariant());
    }
    else if (parameter_type == "ScientificDoubleProperty") {
        double parameter_value = reader->attributes()
                .value(SessionXML::ParameterValueAttribute)
                .toDouble();

        ScientificDoubleProperty scdouble_property(parameter_value);
        QVariant v;
        v.setValue(scdouble_property);
        item->setRegisteredProperty(parameter_name, v);
    }
    else if (parameter_type == "FancyGroupProperty_t") {
        QString parameter_value = reader->attributes()
                .value(SessionXML::ParameterValueAttribute)
                .toString();

        FancyGroupProperty_t group_property = item->getRegisteredProperty(parameter_name).value<FancyGroupProperty_t>();
        group_property->setValue(parameter_value);
    }
    else if (parameter_type == "ColorProperty") {
        int r = reader->attributes().value(SessionXML::ColorRedAttribute).toInt();
        int g = reader->attributes().value(SessionXML::ColorGreenAttribute).toInt();
        int b = reader->attributes().value(SessionXML::ColorBlueAttribute).toInt();
        int a = reader->attributes().value(SessionXML::ColorAlphaAttribute).toInt();
        ColorProperty color(QColor(r, g, b, a));
        item->setRegisteredProperty(parameter_name, color.getVariant());
    }
    else if (parameter_type == "AngleProperty") {
        double parameter_value = reader->attributes()
                .value(SessionXML::ParameterValueAttribute).toDouble();
        QString units = reader->attributes().value(SessionXML::AngleUnitsAttribute).toString();
        AngleProperty angle_property(parameter_value, Constants::UnitsRadians);
        angle_property.setUnits(units);
        item->setRegisteredProperty(parameter_name, angle_property.getVariant());
    }

    else {
        throw GUIHelpers::Error("SessionModel::readProperty: "
                                   "Parameter type not supported"+parameter_type);
    }
    return parameter_name;
}

void SessionModel::writeItemAndChildItems(QXmlStreamWriter *writer,
                                          ParameterizedItem *item) const
{
    if(!m_root_item) return;
    qDebug() << "SessionModel::writeItemAndChildItems " << item << m_root_item;
    Q_ASSERT(item);
    if (item != m_root_item) {
        writer->writeStartElement(SessionXML::ItemTag);
        writer->writeAttribute(SessionXML::ModelTypeAttribute,
                               item->modelType());
        writer->writeAttribute(SessionXML::ItemNameAttribute,
                               item->itemName());
        QListIterator<QByteArray> it(item->dynamicPropertyNames());
        while (it.hasNext()) {
            const char *name = it.next().constData();
            writeProperty(writer, item, name);
        }
    }
    foreach (ParameterizedItem *child_item, item->childItems()) {
        writeItemAndChildItems(writer, child_item);
    }
    if (item != m_root_item) {
        writer->writeEndElement(); // ItemTag
    }
}

void SessionModel::writeProperty(QXmlStreamWriter *writer,
                                 ParameterizedItem *item,
                                 const char *property_name) const
{
    QMap<QString, ParameterizedItem *> sub_items = item->getSubItems();
    QVariant variant = item->property(property_name);
    if (variant.isValid()) {
        writer->writeStartElement(SessionXML::ParameterTag);
        writer->writeAttribute(SessionXML::ParameterNameAttribute,
                               QString(property_name));
        QString type_name = variant.typeName();
        writer->writeAttribute(SessionXML::ParameterTypeAttribute,
                               type_name );
        if (type_name == QString("double")) {
            writer->writeAttribute(SessionXML::ParameterValueAttribute,
                                QString::number(variant.toDouble(), 'e', 12));
        }
        else if (type_name == QString("int")) {
            writer->writeAttribute(SessionXML::ParameterValueAttribute,
                                QString::number(variant.toInt()));
        }
        else if (type_name == QString("bool")) {
            writer->writeAttribute(SessionXML::ParameterValueAttribute,
                                QString::number(variant.toBool()));
        }
        else if (type_name == QString("QString")) {
            writer->writeAttribute(SessionXML::ParameterValueAttribute,
                                variant.toString());
        }
        else if (type_name == QString("MaterialProperty")) {
            MaterialProperty material_property = variant.value<MaterialProperty>();
            writer->writeAttribute(SessionXML::ParameterValueAttribute,
                                material_property.getName());
            writer->writeAttribute(SessionXML::IdentifierAttribute,
                                material_property.getIdentifier());

        }
        else if (type_name == QString("ComboProperty")) {
            writer->writeAttribute(SessionXML::ParameterValueAttribute,
                                variant.value<ComboProperty>().getValue());
        }
        else if (type_name == QString("ScientificDoubleProperty")) {
            writer->writeAttribute(SessionXML::ParameterValueAttribute,
                                variant.value<ScientificDoubleProperty>().getText());

        }
        else if (type_name == QString("FancyGroupProperty_t")) {
            QString ff_name =
                    variant.value<FancyGroupProperty_t>()->getValue();
            writer->writeAttribute(SessionXML::ParameterValueAttribute,
                                ff_name);
        }
        else if (type_name == QString("ColorProperty")) {
            int r, g, b, a;
            QColor material_color = variant.value<ColorProperty>().getColor();
            material_color.getRgb(&r, &g, &b, &a);
            writer->writeAttribute(SessionXML::ColorRedAttribute, QString::number(r));
            writer->writeAttribute(SessionXML::ColorGreenAttribute, QString::number(g));
            writer->writeAttribute(SessionXML::ColorBlueAttribute, QString::number(b));
            writer->writeAttribute(SessionXML::ColorAlphaAttribute, QString::number(a));
        }
        else if (type_name == QString("AngleProperty")) {
            double value = variant.value<AngleProperty>().getValueInRadians();
            writer->writeAttribute(SessionXML::ParameterValueAttribute,
                                QString::number(value,'g'));
            writer->writeAttribute(SessionXML::AngleUnitsAttribute,
                                variant.value<AngleProperty>().getUnits());
        }
        else {
            throw GUIHelpers::Error(tr("SessionModel::writeProperty: "
                                       "Parameter type not supported ")+type_name);
        }
        if (sub_items.contains(QString(property_name))) {
            writePropertyItem(writer, sub_items[QString(property_name)]);
        }
        writer->writeEndElement(); // end ParameterTag
    }
}

void SessionModel::writePropertyItem(QXmlStreamWriter *writer,
                                     ParameterizedItem *item) const
{
    writer->writeStartElement(SessionXML::ItemTag);
    writer->writeAttribute(SessionXML::ModelTypeAttribute,
                           item->modelType());
    writer->writeAttribute(SessionXML::ItemNameAttribute,
                           item->itemName());
    QListIterator<QByteArray> it(item->dynamicPropertyNames());
    while (it.hasNext()) {
        const char *name = it.next().constData();
        writeProperty(writer, item, name);
    }
    foreach (ParameterizedItem *child_item, item->childItems()) {
        writeItemAndChildItems(writer, child_item);
    }
    writer->writeEndElement(); // ItemTag
}


void SessionModel::onItemPropertyChange(const QString & name )
{
    qDebug() << "SessionModel::onItemPropertyChange()" << name;
    ParameterizedItem *item = qobject_cast<ParameterizedItem *>(sender());
    Q_ASSERT(item);
    QModelIndex itemIndex = indexOfItem(item);
    Q_ASSERT(itemIndex.isValid());
    emit dataChanged(itemIndex, itemIndex);
}


void SessionModel::initFrom(SessionModel *model, ParameterizedItem *parent)
{
    qDebug() << "SessionModel::initFrom() -> " << model->getModelTag() << parent;
    QByteArray byte_array;
    QXmlStreamWriter writer(&byte_array);
    writer.setAutoFormatting(true);

    model->writeTo(&writer, parent);

    QXmlStreamReader reader(byte_array);

    while (!reader.atEnd()) {
        reader.readNext();
        if (reader.isStartElement()) {
            readFrom(&reader);
        }
    }

}


void SessionModel::cleanItem(const QModelIndex &parent, int first, int /* last */)
{
    ParameterizedItem *parentItem = itemForIndex(parent);
    Q_ASSERT(parentItem);
    QModelIndex childIndex = index(first, 0, parent);
    ParameterizedItem *childItem = itemForIndex(childIndex);
    Q_ASSERT(childItem);

    ParameterizedItem *candidate_for_removal = parentItem->getCandidateForRemoval(childItem);
    if(candidate_for_removal) {
        //qDebug() << " candidate_for_removal" << candidate_for_removal;
        moveParameterizedItem(candidate_for_removal, 0);
    }
}
