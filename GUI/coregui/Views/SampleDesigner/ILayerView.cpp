// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/SampleDesigner/ILayerView.cpp
//! @brief     Implements class ILayerView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ILayerView.h"
#include "DesignerScene.h"
#include "DesignerHelper.h"
#include "MultiLayerView.h"
#include "ParameterizedItem.h"
#include "SampleModel.h"
#include "LayerItem.h"
#include "GUIHelpers.h"
#include "MaterialProperty.h"
#include <QGraphicsSceneMouseEvent>
#include <QDebug>


QLineF MultiLayerCandidate::getInterfaceToScene()
{
    Q_ASSERT(multilayer);
    QLineF line = multilayer->getInterfaceLine(row);
    return QLineF(multilayer->mapToScene(line.p1()), multilayer->mapToScene(line.p2()));
}


bool MultiLayerCandidate::operator< (const MultiLayerCandidate& cmp) const
{
    return cmp.distance <  distance;
}


ILayerView::ILayerView(QGraphicsItem *parent)
    : ConnectableView(parent)
{
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
}


//! Propagates change of 'Thickness' dynamic property to screen thickness of ILayerView.
void ILayerView::onPropertyChange(const QString &propertyName)
{
    Q_ASSERT(m_item);
    if(propertyName == LayerItem::P_THICKNESS) {
        m_rect.setHeight(DesignerHelper::nanometerToScreen(m_item->getRegisteredProperty(LayerItem::P_THICKNESS).toDouble()));
        setPortCoordinates();
        update();
        emit heightChanged();
    }else if(propertyName == "Material") {
        qDebug() << " ------------- > ILayerView::onPropertyChange Material";
        MaterialProperty mp = getParameterizedItem()->property("Material").value<MaterialProperty>();
        setColor(mp.getColor());
        update();
    } else {
        IView::onPropertyChange(propertyName);
    }
}


void ILayerView::setParameterizedItem(ParameterizedItem *item)
{
    QVariant v = item->property(LayerItem::P_MATERIAL.toUtf8().constData());
    if(v.isValid()) {
        MaterialProperty mp = v.value<MaterialProperty>();
        setColor(mp.getColor());
    }
    ConnectableView::setParameterizedItem(item);
}




//! Detects movement of the ILayerView and sends possible drop areas to GraphicsScene
//! for visualization.
QVariant ILayerView::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemPositionChange && scene()) {

        MultiLayerCandidate multilayerCandidate = getMultiLayerCandidate();
        if(multilayerCandidate) {
            DesignerScene *designerScene = dynamic_cast<DesignerScene *>(scene());
            designerScene->setLayerInterfaceLine(multilayerCandidate.getInterfaceToScene());
        }

    }
    return QGraphicsItem::itemChange(change, value);
}


void ILayerView::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton) {
        m_drag_start_position = pos();
    }
    QGraphicsItem::mousePressEvent(event);
}


//! Detects possible MultiLayerView's to drop given ILayerView and propagate
//! request to SessionModel.
void ILayerView::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "ILayerView::mouseReleaseEvent()  this:" << this << getParameterizedItem()->itemName() << " parentItem: " << parentItem();

    DesignerScene *designerScene = dynamic_cast<DesignerScene *>(scene());
    Q_ASSERT(designerScene);
    designerScene->setLayerInterfaceLine(); // removing drop area hint from the scene

    if(QLineF(m_drag_start_position, pos()).length() == 0) {
        QGraphicsItem::mouseReleaseEvent(event);
        return;
    }

    MultiLayerCandidate candidate = getMultiLayerCandidate();
    MultiLayerView *requested_parent = candidate.multilayer;
    int requested_row = candidate.row;

    qDebug() << "ILayerView::mouseReleaseEvent()  requested_parent:" << requested_parent << " requested_row:" << requested_row;

    // Simple move of lonely layer across the scene: let it be.
    if(requested_parent == 0 && parentItem() == 0) {
        qDebug() << "ILayerView::mouseReleaseEvent() simple move of lonely layer";
        QGraphicsItem::mouseReleaseEvent(event);
        return;
    }

    // Layer was moved on top of MultiLayer but not in the right drop area:
    // returning layer back to starting position.
    if(requested_parent && requested_row == -1) {
        qDebug() << "1.1 Layer->MultiLayer, wrong drop area.";
        setPos(m_drag_start_position);
        QGraphicsItem::mouseReleaseEvent(event);
        return;
    }

    SampleModel *model = designerScene->getSampleModel();

    // Layer was moved only slightly, to the same row of his own MultiLayer: returning back.
    if(requested_parent == parentItem() && requested_row == model->indexOfItem(getParameterizedItem()).row()) {
        qDebug() << "1.2 Layer->MultiLayer (same), same drop area";
        setPos(m_drag_start_position);
        QGraphicsItem::mouseReleaseEvent(event);
        return;
    }

    // Layer was moved from MultiLayer he belong's to, to the empty place of
    // the scene: changing ownership.
    if(parentItem() && !requested_parent) {
        qDebug() << "1.3 Layer->Scene";
        setPos( mapToScene(event->pos()) - event->pos());
        model->moveParameterizedItem(this->getParameterizedItem(), 0);
        QGraphicsItem::mouseReleaseEvent(event);
        return;
    }

    // Layer was moved either from one MultiLayer to another, or is moved inside
    // one multilayer: changing ownership or row within same ownership.
    if(requested_parent) {
        qDebug() << "1.4 ILayerView->MultiLayer";
        model->moveParameterizedItem(this->getParameterizedItem(), requested_parent->getParameterizedItem(), requested_row);
        QGraphicsItem::mouseReleaseEvent(event);
        return;
    }

    // should not be here
    throw GUIHelpers::Error(tr("LayerView::mouseReleaseEvent() -> Loggic error."));
}


//! Finds candidate (another MultiLayer) into which we will move our ILayerView.
//!
//! To become the candidate, the bounding rectangles of MultiLayerView and given
//! ILayerView should intersects and ILayerView center should be near appropriate
//! drop area. If more than one candidate is found, they will be sorted according
//! to the distance between drop area and ILayerVIew center
MultiLayerCandidate ILayerView::getMultiLayerCandidate()
{
    //qDebug() << "ILayerView::getMultiLayerCandidate()";

    QVector<MultiLayerCandidate > candidates;

    QRectF layerRect = mapRectToScene(boundingRect());
    foreach(QGraphicsItem *item, scene()->items()) {
        if(item->type() == DesignerHelper::MULTILAYER
                && item != this
                && !childItems().contains(item)
                )
        {
            MultiLayerView *multilayer = qgraphicsitem_cast<MultiLayerView *>(item);
            if(multilayer->mapRectToScene(multilayer->boundingRect()).intersects(layerRect)) {
                MultiLayerCandidate candidate;

                // calculate row number to drop ILayerView and distance to the nearest droping area
                int row = multilayer->getDropArea(multilayer->mapFromScene(layerRect.center()));
                QRectF droparea = multilayer->mapRectToScene(multilayer->getDropAreaRectangle(row));
                int distance = std::abs(droparea.center().y() - layerRect.center().y());

                candidate.multilayer = multilayer;
                candidate.row = row;
                candidate.distance = distance;
                candidates.push_back(candidate);
            }
        }
    }

    // sorting MultiLayerView candidates to find one whose drop area is closer
    if(candidates.size()) {
        qSort(candidates.begin(), candidates.end());
        //foreach(MultiLayerCandidate candidate, candidates) {
        //    qDebug() << "ILayerView::getMultiLayerCandidate() -> " << candidate.multilayer << candidate.distance << candidate.row;
        //}

        return candidates.back();
    }
    return MultiLayerCandidate();
}

