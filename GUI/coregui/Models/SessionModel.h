// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/SessionModel.h
//! @brief     Defines class SessionModel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef SESSIONMODEL_H
#define SESSIONMODEL_H

#include <QAbstractItemModel>
#include <QtCore/QXmlStreamReader>
#include <QtCore/QXmlStreamWriter>

#include "ParameterizedItem.h"

namespace SessionXML {
const QString MimeType = "application/org.bornagainproject.xml.item.z";
const QString ModelTag("SessionModel");
const QString InstrumentModelTag("InstrumentModel");
const QString SampleModelTag("SampleModel");
const QString MaterialModelTag("MaterialModel");
const QString FitModelTag("FitModel");
const QString JobModelTag("JobModel");

const QString ModelNameAttribute("Name");
const QString ItemTag("Item");
//const QString PropertyItemTag("PropertyItem");
const QString ModelTypeAttribute("ModelType");
const QString ItemNameAttribute("ItemName");
const QString ParameterTag("Parameter");
const QString ParameterNameAttribute("ParName");
const QString ParameterTypeAttribute("ParType");
const QString ParameterValueAttribute("ParValue");

const QString IdentifierAttribute("Identifier");

const QString ColorRedAttribute("Red");
const QString ColorGreenAttribute("Green");
const QString ColorBlueAttribute("Blue");
const QString ColorAlphaAttribute("Alpha");

const QString AngleUnitsAttribute("Units");

}

class IconProvider;

class BA_CORE_API_ SessionModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit SessionModel(QString model_tag, QObject *parent=0);
    ~SessionModel();

    // Begin overriden methods from QAbstractItemModel
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role) const;
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex &child) const;

    bool setHeaderData(int, Qt::Orientation, const QVariant&,
                       int=Qt::EditRole) { return false; }
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    bool removeRows(int row, int count, const QModelIndex &parent);

    Qt::DropActions supportedDragActions() const
        { return Qt::MoveAction; }
    Qt::DropActions supportedDropActions() const
        { return Qt::MoveAction; }
    QStringList mimeTypes() const;
    QMimeData *mimeData(const QModelIndexList &indexes) const;
    bool canDropMimeData(const QMimeData *data, Qt::DropAction action,
                         int row, int column, const QModelIndex &parent) const;
    bool dropMimeData(const QMimeData *data, Qt::DropAction action,
                      int row, int column, const QModelIndex &parent);
    // End overriden methods from QAbstractItemModel

    QModelIndex indexOfItem(ParameterizedItem *item) const;
    ParameterizedItem *insertNewItem(QString model_type,
                                     const QModelIndex &parent=QModelIndex(),
                                     int row=-1, ParameterizedItem::PortInfo::EPorts port = ParameterizedItem::PortInfo::DEFAULT);

    QString getModelTag() const { return m_model_tag; }
    QString getModelName() const { return m_name; }
    void setModelName(const QString &name) { m_name = name; }

    QList<QString> getAcceptableChildItems(const QModelIndex &parent) const;

    void clear();
    void load(const QString &filename=QString());
    void save(const QString &filename=QString());

    // Sets mimedata pointer of item being dragged
    void setDraggedItemType(const QString& type) {
        m_dragged_item_type = type;
    }

    ParameterizedItem *itemForIndex(const QModelIndex &index) const;

    void readFrom(QXmlStreamReader *reader);
    void writeTo(QXmlStreamWriter *writer, ParameterizedItem *parent = 0);


    void moveParameterizedItem(ParameterizedItem *item, ParameterizedItem *new_parent = 0, int row = -1);

    void setIconProvider(IconProvider *icon_provider) { m_iconProvider = icon_provider; }

//    struct ItemToInsert {
//        ParameterizedItem *child;
//        ParameterizedItem *parent;
//        int row;
//    };

    virtual SessionModel *createCopy(ParameterizedItem *parent=0);


    QMap<QString, ParameterizedItem *> getTopItemMap(const QString &model_type = QString()) const;
    ParameterizedItem *getTopItem(const QString &model_type = QString(), const QString &item_name = QString()) const;

public slots:
    void onItemPropertyChange(const QString &property_name, const QString &name = QString());


protected:
    virtual void initFrom(SessionModel *model, ParameterizedItem *parent);

private:
//    ParameterizedItem *createNewItem(QString model_type, ParameterizedItem *parent, int row = -1);

    ParameterizedItem *insertNewItem(QString model_type,
                                     ParameterizedItem *parent,
                                     int row=-1,
                                     ParameterizedItem::PortInfo::EPorts port = ParameterizedItem::PortInfo::DEFAULT);
    void readItems(QXmlStreamReader *reader, ParameterizedItem *item,
                   int row=-1);
    QString readProperty(QXmlStreamReader *reader, ParameterizedItem *item);
    void writeItemAndChildItems(QXmlStreamWriter *writer,
                                ParameterizedItem *item) const;
    void writeProperty(QXmlStreamWriter *writer, ParameterizedItem *item,
                       const char *property_name) const;
    void writePropertyItem(QXmlStreamWriter *writer,
                           ParameterizedItem *item) const;

    void cleanItem(const QModelIndex &parent, int first, int last );

    ParameterizedItem *m_root_item;
    QString m_dragged_item_type;
    QString m_name; //!< model name
    QString m_model_tag;  //!< model tag (SampleModel, InstrumentModel)
    IconProvider *m_iconProvider;
};

#endif // SESSIONMODEL_H
