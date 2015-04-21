// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/SampleDesigner/SampleToolBar.cpp
//! @brief     Implements class SampleToolBar
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "SampleToolBar.h"
#include "MaterialEditor.h"
#include "MaterialProperty.h"
#include "DesignerView.h"
#include <QIcon>
#include <QAction>
#include <QToolButton>
#include <QToolBar>
#include <QStyle>
#include <QComboBox>
#include <QButtonGroup>
#include <QLabel>
#include <QDebug>
#include <QPushButton>
#include <QMenu>


#include "styledbar.h"

//! main tool bar on top of SampleView window
SampleToolBar::SampleToolBar(QWidget *parent)
    : QToolBar(parent)
{
    setMovable(false);

    const int size = style()->pixelMetric(QStyle::PM_SmallIconSize);
    setIconSize(QSize(size, size));
    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

    // Select & Pan
    QToolButton *selectionPointerButton = new QToolButton;
    selectionPointerButton->setCheckable(true);
    selectionPointerButton->setChecked(true);
    selectionPointerButton->setIcon(QIcon(":/SampleDesigner/images/toolbar_pointer.png"));
    selectionPointerButton->setToolTip("Edit mode.");
    QToolButton *handPointerButton = new QToolButton;
    handPointerButton->setCheckable(true);
    handPointerButton->setIcon(QIcon(":/SampleDesigner/images/toolbar_hand.png"));
    handPointerButton->setToolTip("Pan mode (space).");

    m_pointerModeGroup = new QButtonGroup(this);
    m_pointerModeGroup->addButton(selectionPointerButton, DesignerView::RUBBER_SELECTION);
    m_pointerModeGroup->addButton(handPointerButton, DesignerView::HAND_DRAG);
    connect(m_pointerModeGroup, SIGNAL(buttonClicked(int)),
            this, SIGNAL(selectionMode(int)));
    addWidget(selectionPointerButton);
    addWidget(handPointerButton);

    // unddo redo
    addWidget(new QLabel(" "));
    addSeparator();
    addWidget(new QLabel(" "));
    QToolButton *unddoButton = new QToolButton;
    unddoButton->setIcon(QIcon(":/SampleDesigner/images/toolbar_unddo.png"));
    unddoButton->setToolTip("Unddo last action (not implemented yet).");
    addWidget(unddoButton);
    QToolButton *redoButton = new QToolButton;
    redoButton->setIcon(QIcon(":/SampleDesigner/images/toolbar_redo.png"));
    redoButton->setToolTip("Do again the last undone action (not implemented yet).");
    addWidget(redoButton);

    // Remove item
    addWidget(new QLabel(" "));
    addSeparator();
    addWidget(new QLabel(" "));
    m_removeButton = new QToolButton;
    m_removeButton->setText("Remove item");
    m_removeButton->setIcon(QIcon(":/SampleDesigner/images/toolbar_recycle.png"));
    m_removeButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    m_removeButton->setToolTip("Remove selected items and they child items (del).");
    connect(m_removeButton, SIGNAL(clicked()), this, SIGNAL(deleteItems()));
    addWidget(m_removeButton);

    // Center view
    addWidget(new QLabel(" "));
    addSeparator();
    addWidget(new QLabel(" "));
    m_centerViewButton = new QToolButton;
    m_centerViewButton->setIcon(QIcon(":/SampleDesigner/images/toolbar_center.png"));
    m_centerViewButton->setToolTip("Center view.");
    addWidget(m_centerViewButton);
    connect(m_centerViewButton, SIGNAL(clicked()), this, SIGNAL(centerView()));

    // align sample
    m_alignItemsButton = new QToolButton;
    m_alignItemsButton->setIcon(QIcon(":/SampleDesigner/images/toolbar_align.png"));
    m_alignItemsButton->setToolTip("Try to align items.");
    connect(m_alignItemsButton, SIGNAL(clicked()), this, SIGNAL(smartAlign()));
    addWidget(m_alignItemsButton);


    // Zoom
    addWidget(new QLabel(" "));
    addSeparator();
    addWidget(new QLabel(" Zoom "));
    m_scaleCombo = new QComboBox;
    QStringList scales;
    scales << tr("25%")<< tr("50%") << tr("75%") << tr("100%") << tr("125%") << tr("150%");
    m_scaleCombo->addItems(scales);
    m_scaleCombo->setCurrentIndex(3);
    connect(m_scaleCombo, SIGNAL(currentIndexChanged(QString)),
            this, SLOT(onScaleComboChanged(QString)));
    addWidget(m_scaleCombo);


    // MaterialEditor
    addWidget(new QLabel(" "));
    m_materialEditorButton = new QToolButton;
    m_materialEditorButton->setText("Material Editor");
    m_materialEditorButton->setIcon(QIcon(":/SampleDesigner/images/toolbar_materialeditor.png"));
    m_materialEditorButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    m_materialEditorButton->setToolTip("Open material editor (m).");
    m_materialEditorButton->setShortcut(Qt::Key_M);
    connect(m_materialEditorButton, SIGNAL(clicked()), this, SLOT(onMaterialEditorCall()));
    addWidget(m_materialEditorButton);

    // Additional actions
    m_zoomOutAction = new QAction(this);
    m_zoomOutAction->setShortcut(QKeySequence(Qt::Key_Minus));
    connect(m_zoomOutAction, SIGNAL(triggered()), this, SIGNAL(zoomOut()));
    addAction(m_zoomOutAction);

    m_zoomInAction = new QAction(this);
    m_zoomInAction->setShortcut(QKeySequence(Qt::Key_Equal));
    connect(m_zoomInAction, SIGNAL(triggered()), this, SIGNAL(zoomIn()));
    addAction(m_zoomInAction);
}


void SampleToolBar::onViewSelectionMode(int mode)
{
    qDebug() << "SampleToolBar::onViewSelectionMode" << mode;
    if(mode == DesignerView::RUBBER_SELECTION || mode == DesignerView::HAND_DRAG)
        m_pointerModeGroup->button(mode)->setChecked(true);
}

void SampleToolBar::onScaleComboChanged(const QString &scale_string)
{
    double scale = scale_string.left(scale_string.indexOf(tr("%"))).toDouble() / 100.0;
    emit changeScale(scale);
}

void SampleToolBar::onMaterialEditorCall()
{
    MaterialProperty mp = MaterialEditor::selectMaterialProperty();
    qDebug() << "SampleToolBar::materialBrowserCall()" << mp.getName() << mp.getColor();

}
