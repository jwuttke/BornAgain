// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/IntensityDataWidgets/IntensityDataWidget.h
//! @brief     Defines class IntensityDataWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef INTENSITYDATAWIDGET_H
#define INTENSITYDATAWIDGET_H

#include "WinDllMacros.h"
#include <QWidget>

class IntensityDataPropertyWidget;
class IntensityDataItem;
class IntensityDataPlotWidget;

//! The widget presents IntensityData color map and property editor.
//! Belongs to the stack handled by JobOutputDataWidget
class BA_CORE_API_ IntensityDataWidget : public QWidget
{
    Q_OBJECT
public:
    explicit IntensityDataWidget(QWidget *parent = 0);

    void setItem(IntensityDataItem *item);

    QSize sizeHint() const { return QSize(500, 400); }
    QSize minimumSizeHint() const { return QSize(128, 128); }

signals:
    void savePlotRequest();

public slots:
    void onResetView();
    void togglePropertyPanel();
    void savePlot(const QString &dirname);
    void toggleProjections();
    void setPropertyPanelVisible(bool visible);

private slots:
    void onPropertyChanged(const QString &property_name);

private:
    void updateItem(IntensityDataItem *item);

    IntensityDataPlotWidget *m_plotWidget;
    IntensityDataPropertyWidget *m_propertyWidget;
    IntensityDataItem *m_currentItem;
};




#endif
