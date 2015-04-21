// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/SampleDesigner/DesignerMimeData.cpp
//! @brief     Implements class DesignerMimeData
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "DesignerMimeData.h"
#include <QWidget>
#include <QDrag>
#include <QByteArray>
#include <QDataStream>
#include <QPixmap>

#include <QXmlStreamReader>
#include <QPainter>
#include <QBitmap>

#include <iostream>

#include "DesignerHelper.h"

#if QT_VERSION < 0x050000
#define QStringLiteral QString
#endif


DesignerMimeData::DesignerMimeData(const QString &entryname, const QString &xmldescr, QDrag *drag)
    : m_entryname(entryname)
    , m_xmldescr(xmldescr)
{
    drag->setMimeData(this);

    read_xmldescr(m_xmldescr);

    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    dataStream << xmldescr;
    setData("bornagain/widget", itemData);

    drag->setPixmap(getPixmap(m_classname));
    drag->setHotSpot(QPoint(drag->pixmap().width()/2, drag->pixmap().height()/2));

}


void DesignerMimeData::read_xmldescr(const QString &xmldescr)
{
    QXmlStreamReader reader(xmldescr);

    bool widget_found = false;
    while (!reader.atEnd()) {
        if (reader.readNext() == QXmlStreamReader::StartElement) {
            const QStringRef name = reader.name();
            if(widget_found) {
                reader.raiseError(tr("Unexpected element <%1>").arg(name.toString()));
            }
            if (name.compare(QStringLiteral("widget"), Qt::CaseInsensitive) == 0) {
                read_widget(reader);
            } else {
                reader.raiseError(tr("Unexpected element <%1>").arg(name.toString()));
            }
        }
    }

    if (reader.hasError()) {
        QString errorMessage = tr("A parse error occurred at line %1, column %2 of the XML code "
                                   "specified for the widget %3: %4\n%5")
                                   .arg(reader.lineNumber()).arg(reader.columnNumber()).arg(m_entryname)
                                   .arg(reader.errorString()).arg(xmldescr);
        std::cout << "DesignerMimeData::read_xmldescr() -> Error during parse." << std::endl;
        std::cout << errorMessage.toStdString() << std::endl;
    }
}


// extract class name and skip the rest
void DesignerMimeData::read_widget(QXmlStreamReader &reader)
{
    foreach (const QXmlStreamAttribute &attribute, reader.attributes()) {
        QStringRef name = attribute.name();
        if (name == QStringLiteral("class")) {
            m_classname = attribute.value().toString();
            continue;
        }
        reader.raiseError(QStringLiteral("Unexpected attribute ") + name.toString());
    }
    reader.skipCurrentElement();
}


// Execute a drag and drop operation.
Qt::DropAction DesignerMimeData::execDrag(const QString &name, const QString &xmldescr, QWidget *dragSource)
{
    if ( !xmldescr.size() ) return Qt::IgnoreAction;

    QDrag *drag = new QDrag(dragSource);
    DesignerMimeData *mimeData = new DesignerMimeData(name, xmldescr, drag);
    Q_UNUSED(mimeData);

    const Qt::DropAction executedAction = drag->exec(Qt::CopyAction);

    return executedAction;
}


QPixmap DesignerMimeData::getPixmap(const QString &name)
{
    return DesignerHelper::getMimePixmap(name);
}

