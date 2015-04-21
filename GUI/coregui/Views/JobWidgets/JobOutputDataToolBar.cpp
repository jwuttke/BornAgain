// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/JobWidgets/JobOutputDataToolBar.cpp
//! @brief     Implements class JobOutputDataToolBar
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "JobOutputDataToolBar.h"
#include "JobView.h"
#include <QIcon>
#include <QComboBox>
#include <QToolButton>
#include <QToolBar>
#include <QStyle>
#include <QLabel>
#include <QDebug>
#include "styledbar.h"

namespace
{
const QString JobViewActivityName = "Job View Activity";
const QString RealTimeActivityName = "Real Time Activity";
}

//! main tool bar on top of SampleView window
JobOutputDataToolBar::JobOutputDataToolBar(QWidget *parent)
    : QToolBar(parent)
    , m_activityCombo(0)
    , m_toggleProjectionsButton(0)
    , m_togglePropertyPanelButton(0)
    , m_resetViewButton(0)
    , m_savePlotButton(0)
{
    setMovable(false);

    const int size = style()->pixelMetric(QStyle::PM_SmallIconSize);
    setIconSize(QSize(size, size));
    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);

    setContentsMargins(0,0,0,0);

    // projections button
    m_toggleProjectionsButton = new QToolButton;
    m_toggleProjectionsButton->setText("Projections");
    m_toggleProjectionsButton->setIcon(QIcon(":/images/toolbar_projections.png"));
    m_toggleProjectionsButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    m_toggleProjectionsButton->setToolTip("Toggle Projections, Ctrl+O");
    m_toggleProjectionsButton->setShortcut(Qt::CTRL + Qt::Key_O);
    connect(m_toggleProjectionsButton, SIGNAL(clicked()), this, SIGNAL(toggleProjections()));
    addWidget(m_toggleProjectionsButton);

    addWidget(new QLabel(" "));
    addSeparator();
    addWidget(new QLabel(" "));

    // plot properties button
    m_togglePropertyPanelButton = new QToolButton;
    m_togglePropertyPanelButton->setText("Plot Properties");
    m_togglePropertyPanelButton->setIcon(QIcon(":/images/toolbar_propertypanel.png"));
    m_togglePropertyPanelButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    m_togglePropertyPanelButton->setToolTip("Toggle Property Panel, Ctrl+P");
    m_togglePropertyPanelButton->setShortcut(Qt::CTRL + Qt::Key_P);
    connect(m_togglePropertyPanelButton, SIGNAL(clicked()), this, SIGNAL(togglePropertyPanel()));
    addWidget(m_togglePropertyPanelButton);

    addWidget(new QLabel(" "));
    addSeparator();
    addWidget(new QLabel(" "));

    // reset view button
    m_resetViewButton = new QToolButton;
    m_resetViewButton->setText("Reset View");
    m_resetViewButton->setIcon(QIcon(":/images/toolbar_refresh.png"));
    m_resetViewButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    m_resetViewButton->setToolTip("Reset View, Ctrl+R");
    m_resetViewButton->setShortcut(Qt::CTRL + Qt::Key_R);
    connect(m_resetViewButton, SIGNAL(clicked()), this, SIGNAL(resetView()));
    addWidget(m_resetViewButton);

    addWidget(new QLabel(" "));
    addSeparator();
    addWidget(new QLabel(" "));

    // save plot button
    m_savePlotButton = new QToolButton;
    m_savePlotButton->setText("Save Plot");
    m_savePlotButton->setIcon(QIcon(":/images/toolbar_save.png"));
    m_savePlotButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    m_savePlotButton->setToolTip("Save Plot, Ctrl+S");
    m_savePlotButton->setShortcut(Qt::CTRL + Qt::Key_S);
    connect(m_savePlotButton, SIGNAL(clicked()), this, SIGNAL(savePlot()));
    addWidget(m_savePlotButton);

    addWidget(new QLabel(" "));
    addSeparator();
    addWidget(new QLabel(" "));

    // activity combo
    QWidget* empty = new QWidget();
    empty->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    addWidget(empty);

    m_activityCombo = new QComboBox();
    m_activityCombo->setToolTip("Main Activity Selector");
    m_activityCombo->addItem(JobViewActivityName);
    m_activityCombo->addItem(RealTimeActivityName);
    connect(m_activityCombo, SIGNAL(currentIndexChanged(QString)), this, SLOT(onActivityChangeRequest(QString)));

    // attempts to tune style of activity combo
//    QString stylesheet = QString::fromUtf8(
//                "QComboBox:!on\n"
//                "{\n"
//                "   color: rgba(201,218,255,255); \n"
//                "   padding: 0px 0px 0px 0px;\n" // Qt bug we need padding to make color work
//                "}\n\n"
//                "QComboBox:on\n"
//                "{\n"
//                "   color: black; \n"
//                "}\n\n"
//        "QComboBox QListView\n"
//        "{\n"
//                "   color: black;\n"
//                "   selection-color: black;\n"
//        "}\n"
//        );
//    m_activityCombo->setStyleSheet(stylesheet);

    addWidget(m_activityCombo);

}

void JobOutputDataToolBar::onActivityChangeRequest(const QString &name)
{
    if(name == JobViewActivityName) {
        emit jobViewActivityRequest(JobView::JOB_VIEW_ACTIVITY);
    } else if(name == RealTimeActivityName) {
        emit jobViewActivityRequest(JobView::REAL_TIME_ACTIVITY);
    }
}

void JobOutputDataToolBar::onActivityChanged(int activity)
{
    disconnect(m_activityCombo, SIGNAL(currentIndexChanged(QString)), this, SLOT(onActivityChangeRequest(QString)));

    m_activityCombo->setCurrentIndex(activity);

    connect(m_activityCombo, SIGNAL(currentIndexChanged(QString)), this, SLOT(onActivityChangeRequest(QString)));
}
