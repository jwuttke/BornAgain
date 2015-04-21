// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/IntensityDataWidgets/IntensityDataPlotWidget.cpp
//! @brief     Implements class IntensityDataPlotWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "IntensityDataPlotWidget.h"
#include "ColorMapPlot.h"
#include "HorizontalSlicePlot.h"
#include "VerticalSlicePlot.h"
#include "IntensityDataItem.h"
#include "qcustomplot.h"
#include <QSplitter>
#include <QVBoxLayout>
#include <QLabel>
#include <QDebug>

IntensityDataPlotWidget::IntensityDataPlotWidget(QWidget *parent)
    : QWidget(parent)
    , m_splitter(new QSplitter(this))
    , m_splitterTop(new QSplitter(this))
    , m_splitterBottom(new QSplitter(this))
    , m_propertyPanelAction(0)
    , m_projectionsAction(0)
    , m_resetAction(0)
    , m_saveAction(0)
    , m_centralPlot(new ColorMapPlot(this))
    , m_verticalPlot(new VerticalSlicePlot(this))
    , m_horizontalPlot(new HorizontalSlicePlot(this))
    , m_statusLabel(new QLabel(this))
    , m_leftHistogramArea(150)
    , m_bottomHistogramArea(150)
    , m_item(0)
{
    setObjectName(QStringLiteral("IntensityDataPlotWidget"));
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    m_splitterTop->addWidget(m_verticalPlot);
    m_splitterTop->addWidget(m_centralPlot);
    m_splitterTop->setStyleSheet("background-color:white;");

    m_splitterBottom->addWidget(new QWidget());
    m_splitterBottom->addWidget(m_horizontalPlot);
    m_splitterBottom->setStyleSheet("background-color:white;");
    m_splitterBottom->setHandleWidth(0);

    m_splitter->setOrientation(Qt::Vertical);
    m_splitter->addWidget(m_splitterTop);
    m_splitter->addWidget(m_splitterBottom);
    m_splitter->setStyleSheet("background-color:white;");

    m_statusLabel->setAlignment(Qt::AlignVCenter| Qt::AlignLeft);
    m_statusLabel->setStyleSheet("background-color:white;");
    m_statusLabel->setMargin(3);

    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->setMargin(0);
    vlayout->setSpacing(0);
    vlayout->addWidget(m_splitter);
    vlayout->addWidget(m_statusLabel);
    this->setLayout(vlayout);

    initLeftRightAreaSize(0, 600);
    initTopBottomAreaSize(500, 0);

    connect(m_splitterTop, SIGNAL(splitterMoved(int,int)), this, SLOT(onSplitterMoved(int,int)));
    connect(m_splitterBottom, SIGNAL(splitterMoved(int,int)), this, SLOT(onSplitterMoved(int,int)));
    connect(m_centralPlot, SIGNAL(validMousMove()), this, SLOT(onMouseMove()));
    connect(m_centralPlot->getCustomPlot(), SIGNAL(mousePress(QMouseEvent*)), this, SLOT(onMousePress(QMouseEvent*)), Qt::UniqueConnection);

    setupContextMenuActions();
}

//! initializes the class with NIntensityDataItem
void IntensityDataPlotWidget::setItem(IntensityDataItem *item)
{
    //qDebug() << "IntensityDataPlotWidget::setItem(NIntensityDataItem *item)";

    m_centralPlot->setItem(item);
    m_horizontalPlot->setItem(item);
    m_verticalPlot->setItem(item);

    if (m_item == item) return;

    if (m_item) {
        disconnect(m_item, SIGNAL(propertyChanged(QString)),
                this, SLOT(onPropertyChanged(QString)));
        disconnect(m_item, SIGNAL(intensityModified()), this, SLOT(onIntensityModified()));
    }

    m_item = item;

    if (!m_item) return;

    updateItem(m_item);

    connect(m_item, SIGNAL(propertyChanged(QString)),
            this, SLOT(onPropertyChanged(QString)));
    connect(m_item, SIGNAL(intensityModified()), this, SLOT(onIntensityModified()));
}

//! provide syncronious move of top and bottom splitters
void IntensityDataPlotWidget::onSplitterMoved(int pos, int index)
{
    Q_UNUSED(index);
    QSplitter *splitter = qobject_cast<QSplitter *>(sender());
    QList<int> sizes = QList<int>() << pos << (this->size().width()-pos);
    if(splitter == m_splitterTop) {
        m_splitterBottom->setSizes(sizes);
    } else if(splitter == m_splitterBottom) {
        m_splitterTop->setSizes(sizes);
    }
}

//! reset views to original axes min and max
void IntensityDataPlotWidget::resetView()
{
    m_centralPlot->resetView();
}

//! updates status string, line cross and projections on mouse move
void IntensityDataPlotWidget::onMouseMove()
{
    m_statusLabel->setText(m_centralPlot->getStatusString());

    bool bottom_is_visible = isBottomAreaVisible();
    if(bottom_is_visible) {
        QVector<double> x, y;
        m_centralPlot->getHorizontalSlice(x, y);
        m_horizontalPlot->plotData(x,y);
    }

    bool left_is_visible = isLeftAreaVisible();
    if(left_is_visible) {
        QVector<double> x, y;
        m_centralPlot->getVerticalSlice(x, y);
        m_verticalPlot->plotData(x,y);
    }

    if(bottom_is_visible || left_is_visible)
        m_centralPlot->drawLinesOverTheMap();
}

//! provides context menu on right mouse button
void IntensityDataPlotWidget::onMousePress(QMouseEvent *event)
{
    if(event->button() == Qt::RightButton) {
        //showContextMenu(event->pos());
        showContextMenu(event->globalPos());
    }
}

//! saves plot into proposed directory
void IntensityDataPlotWidget::savePlot(const QString &dirname)
{
    //qDebug() << "IntensityDataPlotWidget::savePlot(const QString &dirname)" << dirname;
    Q_ASSERT(m_item);

    bool projections_flag = m_item->getRegisteredProperty(IntensityDataItem::P_PROJECTIONS_FLAG).toBool();
    if(projections_flag)
        m_centralPlot->showLinesOverTheMap(false);

    QString filters("*.png;;*.jpg;;*.pdf");
    QString defaultFilter("*.png");
    QString defaultName = dirname + QString("/untitled");
    QString fileName =QFileDialog::getSaveFileName(0, "Save Plot", defaultName,
        filters, &defaultFilter);
    QString extension =  defaultFilter.mid(1);

    if (!fileName.isEmpty() && !defaultFilter.isEmpty()) {

        if(fileName.endsWith(tr(".pdf"), Qt::CaseInsensitive)) {
            m_centralPlot->getCustomPlot()->savePdf(fileName, true, m_centralPlot->width(), m_centralPlot->height());
        } else if(fileName.endsWith(tr(".jpg"), Qt::CaseInsensitive)) {
            m_centralPlot->getCustomPlot()->saveJpg(fileName);
        } else if(fileName.endsWith(tr(".png"), Qt::CaseInsensitive)) {
            m_centralPlot->getCustomPlot()->savePng(fileName);
        } else if(defaultFilter == "*.pdf") {
            m_centralPlot->getCustomPlot()->savePdf(fileName+extension, true, m_centralPlot->width(), m_centralPlot->height());
        } else if(defaultFilter == "*.jpg") {
            m_centralPlot->getCustomPlot()->saveJpg(fileName+extension);
        } else {
            m_centralPlot->getCustomPlot()->savePng(fileName+extension);
        }
    }
    m_centralPlot->showLinesOverTheMap(projections_flag);
}

//! updates itself if item properties changed
void IntensityDataPlotWidget::onPropertyChanged(const QString &property_name)
{
    //qDebug() << "IntensityDataPlotWidget::onPropertyChanged(const QString &property_name)" << property_name;
    if(property_name == IntensityDataItem::P_PROJECTIONS_FLAG) {
        showProjections(m_item->getRegisteredProperty(IntensityDataItem::P_PROJECTIONS_FLAG).toBool());
    }
}

//! switches projections On and Off
void IntensityDataPlotWidget::showProjections(bool flag)
{
    if(flag) {
        // restoring old splitter positions
        int width = m_splitterTop->width() - m_leftHistogramArea;
        if(width < 0) width = m_leftHistogramArea*3;
        initLeftRightAreaSize(m_leftHistogramArea, width);

        int height = m_splitter->height() - m_bottomHistogramArea;
        if(height < 0) height = m_bottomHistogramArea*3;
        initTopBottomAreaSize(height, m_bottomHistogramArea);

    } else {
        // saving splitter positions, and then
        // hiding projections by setting corresponding splitter size to zero
        QList<int> horizontal_sizes = m_splitterTop->sizes();
        if(horizontal_sizes[0] > 0) m_leftHistogramArea = horizontal_sizes[0];
        initLeftRightAreaSize(0, horizontal_sizes[0]+horizontal_sizes[1]);
        QList<int> vertical_sizes = m_splitter->sizes();
        if(vertical_sizes[1] > 0) m_bottomHistogramArea = vertical_sizes[1];
        initTopBottomAreaSize(vertical_sizes[0]+vertical_sizes[1], 0);
    }
}

void IntensityDataPlotWidget::onPropertyPanelAction(bool flag)
{
    Q_ASSERT(m_item);
    m_item->setRegisteredProperty(IntensityDataItem::P_PROPERTY_PANEL_FLAG, flag);
}

void IntensityDataPlotWidget::onProjectionsAction(bool flag)
{
    Q_ASSERT(m_item);
    m_item->setRegisteredProperty(IntensityDataItem::P_PROJECTIONS_FLAG, flag);
}


void IntensityDataPlotWidget::showContextMenu(const QPoint &point)
{
    Q_ASSERT(m_item);
    QMenu menu;

    m_propertyPanelAction->setChecked(m_item->getRegisteredProperty(IntensityDataItem::P_PROPERTY_PANEL_FLAG).toBool());
    m_projectionsAction->setChecked(m_item->getRegisteredProperty(IntensityDataItem::P_PROJECTIONS_FLAG).toBool());

    menu.addAction(m_propertyPanelAction);
    menu.addAction(m_projectionsAction);
    menu.addAction(m_resetAction);
    menu.addAction(m_saveAction);

    //menu.exec(mapToGlobal(point));
    menu.exec(point);
}

void IntensityDataPlotWidget::onIntensityModified()
{
    m_centralPlot->setItem(m_item);
}

void IntensityDataPlotWidget::setupContextMenuActions()
{
    m_propertyPanelAction = new QAction(tr("&Plot Properties"), this);
    m_propertyPanelAction->setCheckable(true);
    connect(m_propertyPanelAction, SIGNAL(triggered(bool)), this, SLOT(onPropertyPanelAction(bool)));

    m_projectionsAction = new QAction(tr("Pr&ojections"), this);
    m_projectionsAction->setCheckable(true);
    connect(m_projectionsAction, SIGNAL(triggered(bool)), this, SLOT(onProjectionsAction(bool)));

    m_resetAction = new QAction(tr("&Reset View"), this);
    connect(m_resetAction, SIGNAL(triggered()), this, SLOT(resetView()));

    m_saveAction = new QAction(tr("&Save as"), this);
    connect(m_saveAction, SIGNAL(triggered()), this, SIGNAL(savePlotRequest()));

}

void IntensityDataPlotWidget::updateItem(IntensityDataItem *item)
{
    showProjections(item->getRegisteredProperty(IntensityDataItem::P_PROJECTIONS_FLAG).toBool());
}

//! sets sizes of top and bottom splitters to have correct sizes of vertical histogram (on the left) and color map
void IntensityDataPlotWidget::initLeftRightAreaSize(int left_size, int right_size)
{
    QList<int> sizes = QList<int>() << left_size << right_size;
    m_splitterTop->setSizes(sizes);
    m_splitterBottom->setSizes(sizes);
}

//! set size of main splitter to have correct sizes of horizontal histogram (at the bottom) and color map
void IntensityDataPlotWidget::initTopBottomAreaSize(int top_size, int bottom_size)
{
    QList<int> sizes = QList<int>() << top_size << bottom_size;
    m_splitter->setSizes(sizes);
}

//! returns true if bottom splitter is not collapsed
bool IntensityDataPlotWidget::isBottomAreaVisible()
{
    QList<int> sizes = m_splitter->sizes();
    return sizes[1] != 0;
}

//! returns true if left splitter is not collapsed
bool IntensityDataPlotWidget::isLeftAreaVisible()
{
    QList<int> sizes = m_splitterTop->sizes();
    return sizes[0] != 0;
}
