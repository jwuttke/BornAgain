// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/CommonWidgets/ItemComboToolBar.h
//! @brief     Declares class ItemComboToolBar
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef ITEMCOLBOTOOLBAR_H
#define ITEMCOLBOTOOLBAR_H

#include "StyledToolBar.h"

//! The ItemComboToolBar class is a styled toolbar on top of ItemComboWidget. Contains
//! ComboBox to switch ItemComboWidget, and dynamic list of actions, which are updated
//! according to current state of ItemComboWidget.

class BA_CORE_API_ ItemComboToolBar : public StyledToolBar
{
    Q_OBJECT

public:
    explicit ItemComboToolBar(QWidget *parent = 0);

    void addPresentationType(const QString &name);

    QString currentPresentation() const;

signals:
    void comboChanged(const QString &presentation);

private:
    class QComboBox *m_comboBox;
};

#endif

