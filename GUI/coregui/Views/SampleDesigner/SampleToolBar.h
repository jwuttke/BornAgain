// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/SampleDesigner/SampleToolBar.h
//! @brief     Defines class SampleToolBar
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef SAMPLETOOLBAR_H
#define SAMPLETOOLBAR_H

#include "WinDllMacros.h"
#include <QToolBar>

class QAction;
class QToolButton;
class QToolBar;
class QComboBox;
class QString;
class QButtonGroup;

//! main tool bar on top of SampleView window
class BA_CORE_API_ SampleToolBar : public QToolBar
{
    Q_OBJECT

public:
    explicit SampleToolBar(QWidget *parent = 0);

signals:
    void deleteItems();
    void selectionMode(int);
    void centerView();
    void smartAlign();
    void changeScale(double);
    void zoomIn();
    void zoomOut();

public slots:
    void onViewSelectionMode(int);
    void onScaleComboChanged(const QString &);
    void onMaterialEditorCall();

private:
    QButtonGroup *m_pointerModeGroup;
    QToolButton *m_removeButton;
    QToolButton *m_centerViewButton;
    QToolButton *m_alignItemsButton;
    QComboBox *m_scaleCombo;
    QToolButton *m_materialEditorButton;
    QAction *m_zoomInAction;
    QAction *m_zoomOutAction;
};


#endif // SAMPLETOOLBAR_H
