// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/SampleDesigner/SamplePropertyWidget.h
//! @brief     Defines class SamplePropertyWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef SAMPLEPROPERTYWIDGET_H
#define SAMPLEPROPERTYWIDGET_H

#include "WinDllMacros.h"
#include <QWidget>

class QItemSelectionModel;
class QItemSelection;
class AwesomePropertyEditor;

//! Property editor to modify property of the objectcurrently selected on the
//! graphics scene, located in the bottom right corner of SampleView.
class BA_CORE_API_ SamplePropertyWidget : public QWidget
{
    Q_OBJECT
public:
    SamplePropertyWidget(QItemSelectionModel *selection_model,
                         QWidget *parent = 0);

    QSize sizeHint() const { return QSize(230, 256); }
    QSize minimumSizeHint() const { return QSize(230, 64); }

    void setSelectionModel(QItemSelectionModel *selection_model);

public slots:
    //! show property of currently selected object (triggered by graphics scene)
    void selectionChanged(const QItemSelection & selected,
                          const QItemSelection & deselected);

private:
    QItemSelectionModel *m_selection_model;
    AwesomePropertyEditor *m_propertyEditor;
};

#endif
