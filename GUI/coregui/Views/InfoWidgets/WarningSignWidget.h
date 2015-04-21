// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/InfoWidgets/WarningSignWidget.h
//! @brief     Defines class WarningSignWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef WARNINGSIGNWIDGET_H
#define WARNINGSIGNWIDGET_H

#include "WinDllMacros.h"
#include <QWidget>
#include <QPixmap>
#include <QString>

//! The WarningSignWidget is an transparent widget with warning sign pixmap intended to be
//! overlayed onto other widget at some arbitrary position.
class WarningSignWidget : public QWidget
{
public:
    WarningSignWidget(QWidget *parent = 0);

    void setPosition(int x, int y);

    void setWarningMessage(const QString &message) {m_warning_message = message;}

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);

private:
    QPixmap m_pixmap;
    QString m_warning_message;
};

#endif
