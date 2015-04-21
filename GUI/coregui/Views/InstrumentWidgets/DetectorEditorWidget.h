// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/InstrumentWidgets/DetectorEditorWidget.h
//! @brief     Defines class DetectorEditorWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef DETECTOREDITORWIDGET_H
#define DETECTOREDITORWIDGET_H

#include "WinDllMacros.h"
#include <QWidget>

class DetectorItem;
class AwesomePropertyEditor;
class QGridLayout;

class BA_CORE_API_ DetectorEditorWidget : public QWidget
{
    Q_OBJECT
public:
    DetectorEditorWidget(QWidget *parent = 0);

    void setDetectorItem(DetectorItem *detectorItem);

    QGridLayout *getGridLayout() { return m_gridLayout;}

private:
    AwesomePropertyEditor *m_binningEditor;
    AwesomePropertyEditor *m_phiAxisEditor;
    AwesomePropertyEditor *m_alphaAxisEditor;
    AwesomePropertyEditor *m_resolutionFunctionEditor;
    QGridLayout *m_gridLayout;
    DetectorItem *m_detectorItem;
};

#endif
