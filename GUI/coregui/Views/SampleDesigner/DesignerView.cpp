// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/SampleDesigner/DesignerView.cpp
//! @brief     Implements class DesignerView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "DesignerView.h"
#include "DesignerMimeData.h"
#include "DesignerScene.h"
#include "GUIHelpers.h"
#include "DesignerHelper.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QVBoxLayout>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QShortcut>
#include <QDebug>


DesignerView::DesignerView(QGraphicsScene *scene, QWidget *parent)
    : QGraphicsView(scene, parent)
{
    setAcceptDrops(true);
    setRenderHint(QPainter::Antialiasing);
    setMouseTracking(true);
    setDragMode(QGraphicsView::RubberBandDrag);
}


int DesignerView::getSelectionMode() const
{
    if (dragMode() == QGraphicsView::NoDrag) {
        return SIMPLE_SELECTION;
    }
    else if(dragMode() == QGraphicsView::RubberBandDrag) {
        return RUBBER_SELECTION;
    }
    else if(dragMode() == QGraphicsView::ScrollHandDrag) {
        return HAND_DRAG;
    }
    else {
        throw GUIHelpers::Error("DesignerView::getSelectionMode() -> Error.");
    }
}


void DesignerView::onSelectionMode(int mode)
{
    switch(mode) {
    case SIMPLE_SELECTION:
        setDragMode(QGraphicsView::NoDrag);
        setInteractive(true);
        emit selectionModeChanged(SIMPLE_SELECTION);
        break;
    case RUBBER_SELECTION:
        setDragMode(QGraphicsView::RubberBandDrag);
        setInteractive(true);
        emit selectionModeChanged(RUBBER_SELECTION);
        break;
    case HAND_DRAG:
        setDragMode(QGraphicsView::ScrollHandDrag);
        setInteractive(false);
        emit selectionModeChanged(HAND_DRAG);
        break;
     default:
        break;
    }
}


void DesignerView::onCenterView()
{
    //fitInView(scene()->itemsBoundingRect() ,Qt::KeepAspectRatio);
    centerOn(scene()->itemsBoundingRect().center());
}


void DesignerView::onChangeScale(double new_scale)
{
    qDebug() << "DesignerView::onScaleChanged()" << new_scale;
    QMatrix oldMatrix = matrix();
    resetMatrix();
    translate(oldMatrix.dx(), oldMatrix.dy());
    scale(new_scale, new_scale);
    DesignerHelper::setZoomLevel(new_scale);
}


void DesignerView::deleteSelectedItems()
{
    DesignerScene *designerScene = dynamic_cast<DesignerScene *>(scene());
    Q_ASSERT(designerScene);
    designerScene->deleteSelectedItems();
}


void DesignerView::zoomIn()
{
    qDebug() << "DesignerView::zoomIn() -> Not implemented";
}


void DesignerView::zoomOut()
{
    qDebug() << "DesignerView::zoomOut() -> Not implemented";
}


//void SampleEditorView::wheelEvent(QWheelEvent *event)
//{
//    scaleView(std::pow((double)2, -event->delta() / 240.0));
//}


//void DesignerView::scaleView(qreal scaleFactor)
//{
//    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
//    if (factor < 0.07 || factor > 100)
//        return;

//    //m_graphicsView->scale(scaleFactor, scaleFactor);
//    scale(scaleFactor, scaleFactor);
//}


void DesignerView::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Left:
        break;
    case Qt::Key_Space:
        if( getSelectionMode() != HAND_DRAG && !event->isAutoRepeat()) {
            onSelectionMode(HAND_DRAG);
            qDebug() << "  space pressed" << event->isAutoRepeat();
        }
        break;
    case Qt::Key_Delete:
        deleteSelectedItems();
        break;
    case Qt::Key_Backspace:
        deleteSelectedItems();
        break;
    default:
        QWidget::keyPressEvent(event);
    }
}


void DesignerView::keyReleaseEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Space:

        if( getSelectionMode() != RUBBER_SELECTION && !event->isAutoRepeat()) {
            onSelectionMode(RUBBER_SELECTION);
            qDebug() << "  space released" << event->isAutoRepeat();
        }
        break;
    default:
        QWidget::keyPressEvent(event);
    }

}



