// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/IntensityDataWidgets/VerticalSlicePlot.cpp
//! @brief     Implements class VerticalSlicePlot
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "VerticalSlicePlot.h"
#include "IntensityDataItem.h"
#include "AxesItems.h"
#include "qcustomplot.h"
#include "Units.h"
#include <QVBoxLayout>

VerticalSlicePlot::VerticalSlicePlot(QWidget *parent)
    : QWidget(parent)
    , m_customPlot(0)
    , m_bars(0)
    , m_item(0)
{
    m_customPlot = new QCustomPlot();
    m_bars = new QCPBars(m_customPlot->yAxis, m_customPlot->xAxis);
    m_customPlot->addPlottable(m_bars);

    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->setMargin(0);
    vlayout->setSpacing(0);
    vlayout->addWidget(m_customPlot);
    setLayout(vlayout);

}

void VerticalSlicePlot::setItem(IntensityDataItem *item)
{
    if (m_item == item) return;

    if (m_item) {
//        disconnect(m_item, SIGNAL(propertyChanged(QString)),
//                this, SLOT(onPropertyChanged(QString)));
        disconnect(m_item, SIGNAL(subItemPropertyChanged(QString,QString)),
                this, SLOT(onSubItemPropertyChanged(QString,QString)));
    }

    m_item = item;

    if (!m_item) return;

    plotItem(m_item);

//    connect(m_item, SIGNAL(propertyChanged(QString)),
//            this, SLOT(onPropertyChanged(QString)));

    connect(m_item, SIGNAL(subItemPropertyChanged(QString,QString)),
            this, SLOT(onSubItemPropertyChanged(QString,QString)));

}

void VerticalSlicePlot::plotData(const QVector<double> &x, const QVector<double> &y)
{
    //qDebug() << "NHistogramPlot::plotData(const QVector<double> &x, const QVector<double> &y)";
    m_bars->setData(x, y);
    m_customPlot->replot();
}

void VerticalSlicePlot::onSubItemPropertyChanged(const QString &property_group, const QString &property_name)
{
    qDebug() << "HorizontalSlicePlot::onSubItemPropertyChanged(const QString &property_name)" << property_group << property_name;
    if(property_group == IntensityDataItem::P_XAXIS) {
        if(property_name == BasicAxisItem::P_MIN) {
            setXmin(m_item->getLowerX());
        }
        else if(property_name == BasicAxisItem::P_MAX) {
            setXmax(m_item->getUpperX());
        }
    }
    else if(property_group == IntensityDataItem::P_YAXIS) {
        if(property_name == BasicAxisItem::P_MIN) {
            setYmin(m_item->getLowerY());
        }
        else if(property_name == BasicAxisItem::P_MAX) {
            setYmax(m_item->getUpperY());
        }
    }
    else if(property_group == IntensityDataItem::P_ZAXIS) {
        if(property_name == BasicAxisItem::P_MIN) {
            setZmin(m_item->getLowerZ());
        }
        else if(property_name == BasicAxisItem::P_MAX) {
            setZmax(m_item->getUpperZ());
        }
        else if(property_name == AmplitudeAxisItem::P_IS_LOGSCALE) {
            setLogz(m_item->isLogz(), true);
        }
    }
}


void VerticalSlicePlot::plotItem(IntensityDataItem *intensityItem)
{
    //qDebug() << "NHistogramPlot::plotItem(NIntensityDataItem *intensityItem)";
    Q_ASSERT(intensityItem);

    const OutputData<double> *data = intensityItem->getOutputData();
    Q_ASSERT(data);

    if(data->getRank() != 2) {
        throw NullPointerException("NHistogramPlot::plotItem::Draw() -> Error. Zero pointer to the data to draw");
    }

    m_customPlot->axisRect()->setupFullAxesBox(true);

    m_customPlot->xAxis->setRange(intensityItem->getLowerZ(), intensityItem->getUpperZ());
    m_customPlot->yAxis->setRange(intensityItem->getLowerY(), intensityItem->getUpperY());

    const IAxis *axis = data->getAxis(1);
    double bin_size(0);
    if(intensityItem->axesInRadians()) {
        bin_size = (axis->getMax() - axis->getMin())/axis->getSize();
    } else {
        bin_size = (Units::rad2deg(axis->getMax()) - Units::rad2deg((axis->getMin())))/axis->getSize();
    }

    m_bars->setWidth(bin_size);
    m_bars->setPen(Qt::NoPen);
    m_bars->setBrush(Qt::blue);

    setLogz(intensityItem->isLogz());

    const QMargins margins(0,0,0,0);
    m_customPlot->axisRect()->setMargins(margins);
    m_customPlot->axisRect()->layout()->setMargins(margins);

    m_customPlot->replot();
}


void VerticalSlicePlot::setLogz(bool logz, bool isReplot)
{
    if(logz) {
        m_customPlot->xAxis->setScaleType(QCPAxis::stLogarithmic);
        m_customPlot->xAxis->setNumberFormat("eb");
        m_customPlot->xAxis->setNumberPrecision(0);
    } else {
        m_customPlot->xAxis->setScaleType(QCPAxis::stLinear);
        m_customPlot->xAxis->setNumberFormat("f");
    }

    if(isReplot) m_customPlot->replot();
}

void VerticalSlicePlot::setXmin(double value)
{
    Q_UNUSED(value);
}

void VerticalSlicePlot::setXmax(double value)
{
    Q_UNUSED(value);
}

void VerticalSlicePlot::setYmin(double value)
{
    QCPRange range = m_customPlot->yAxis->range();
    range.lower = value;
    m_customPlot->yAxis->setRange(range);
    m_customPlot->replot();
}

void VerticalSlicePlot::setYmax(double value)
{
    QCPRange range = m_customPlot->yAxis->range();
    range.upper = value;
    m_customPlot->yAxis->setRange(range);
    m_customPlot->replot();
}

void VerticalSlicePlot::setZmin(double value)
{
    QCPRange range = m_customPlot->xAxis->range();
    range.lower = value;
    m_customPlot->xAxis->setRange(range);
    m_customPlot->replot();
}

void VerticalSlicePlot::setZmax(double value)
{
    QCPRange range = m_customPlot->xAxis->range();
    range.upper = value;
    m_customPlot->xAxis->setRange(range);
    m_customPlot->replot();
}

