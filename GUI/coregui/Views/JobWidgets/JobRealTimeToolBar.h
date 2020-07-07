// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/JobWidgets/JobRealTimeToolBar.h
//! @brief     Defines class JobRealTimeToolBar
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef JOBREALTIMETOOLBAR_H
#define JOBREALTIMETOOLBAR_H

#include "GUI/coregui/mainwindow/StyledToolBar.h"

class QToolButton;

//! Represents a toolbar with buttons for ParameterTuningWidget.

class BA_CORE_API_ JobRealTimeToolBar : public StyledToolBar
{
    Q_OBJECT

public:
    explicit JobRealTimeToolBar(QWidget* parent = nullptr);

signals:
    void resetParameters();

private:
    QToolButton* m_resetParametersButton;
};

#endif // JOBREALTIMETOOLBAR_H
