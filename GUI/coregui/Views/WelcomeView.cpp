// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/WelcomeView.cpp
//! @brief     Implements class WelcomeView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "WelcomeView.h"
#include "DesignerHelper.h"
#include "FancyLabel.h"
#include "mainwindow.h"
#include "mainwindow_constants.h"
#include "projectdocument.h"
#include "projectmanager.h"
#include "stringutils.h"
#include <QGroupBox>
#include <QLabel>
#include <QComboBox>
#include <QVBoxLayout>
#include <QDesktopServices>
#include <QUrl>
#include <QSizePolicy>
#include <QCommandLinkButton>
#include <QSignalMapper>
#include <QDebug>
#include <QPushButton>

WelcomeView::WelcomeView(MainWindow *parent)
    : m_mainWindow(parent)
{
    QColor bgColor(240,240,240,255);
    QPalette palette;
    palette.setColor(QPalette::Background, bgColor);
    setAutoFillBackground(true);
    setPalette(palette);

    m_projectManager = m_mainWindow->getProjectManager();
    Q_ASSERT(m_projectManager);

    // button layout
    QFont buttonFont;
    buttonFont.setPointSize(DesignerHelper::getLabelFontSize());
    buttonFont.setBold(false);
    const int buttonHeight = 45;
    const int buttonWidth = 140;

    m_newProjectButton = new QPushButton(tr("New Project"));
    m_newProjectButton->setMinimumWidth(buttonWidth);
    m_newProjectButton->setMinimumHeight(buttonHeight);
    m_newProjectButton->setFont(buttonFont);
//    QPalette button_palette = m_newProjectButton->palette();
//    button_palette.setColor(QPalette::Button, QColor(Constants::BUTTON_COLOR));
//    button_palette.setColor(QPalette::ButtonText, QColor(Constants::BUTTON_TEXT_COLOR));
//    m_newProjectButton->setPalette(button_palette);
    m_newProjectButton->setToolTip("Create new project");

    m_openProjectButton = new QPushButton(tr("Open Project"));
    m_openProjectButton->setMinimumWidth(buttonWidth);
    m_openProjectButton->setMinimumHeight(buttonHeight);
    m_openProjectButton->setFont(buttonFont);
//    m_openProjectButton->setPalette(button_palette);
    m_openProjectButton->setToolTip("Open existing project");

    m_newUsertButton = new QPushButton(tr("New to BornAgain?"));
    m_newUsertButton->setMinimumWidth(buttonWidth);
    m_newUsertButton->setMinimumHeight(buttonHeight);
    m_newUsertButton->setFont(buttonFont);
//    m_newUsertButton->setPalette(button_palette);
    m_newUsertButton->setToolTip("Open BornAgain web site");

    QVBoxLayout *buttonLayout = new QVBoxLayout;

    buttonLayout->addWidget(m_newProjectButton);
    buttonLayout->addWidget(m_openProjectButton);
    buttonLayout->addStretch(1);
    buttonLayout->addWidget(m_newUsertButton);

    QHBoxLayout *buttonPanel = new QHBoxLayout;
    buttonPanel->setContentsMargins(30,0,30,0);
    buttonPanel->addLayout(buttonLayout);

    // current project layout
    QVBoxLayout *currentProjectLayout = new QVBoxLayout;
    currentProjectLayout->setContentsMargins(30,0,0,0);
    QFont titleFont;
    titleFont.setPointSize(DesignerHelper::getSectionFontSize());
    titleFont.setBold(true);

    QLabel *currentProLabel = new QLabel("Current Project:");
    currentProLabel->setFont(titleFont);

    m_currentProName = new FancyLabel("Untitled");
    currentProjectLayout->addWidget(currentProLabel);
    currentProjectLayout->addWidget(m_currentProName);

    // recent project layout
    m_recentProjectLayout = new QVBoxLayout;
    m_recentProjectLayout->setContentsMargins(30,0,0,0);

    // project layout
    QVBoxLayout *projectLayout = new QVBoxLayout;
    projectLayout->addLayout(currentProjectLayout);
    projectLayout->addSpacing(15);
    projectLayout->addLayout(m_recentProjectLayout);

    // assembling all together
    QFrame* line = new QFrame();
    line->setFrameShape(QFrame::VLine);
    line->setFrameShadow(QFrame::Sunken);

    QHBoxLayout *itemContainerLayout = new QHBoxLayout;
    itemContainerLayout->addLayout(buttonPanel);
    itemContainerLayout->addWidget(line);
//    itemContainerLayout->addLayout(m_recentProjectLayout);
    itemContainerLayout->addLayout(projectLayout);
    itemContainerLayout->addStretch(1);

    QWidget *itemContainerWidget = new QWidget;
    itemContainerWidget->setLayout(itemContainerLayout);
    itemContainerWidget->setFixedHeight(430);

    QVBoxLayout *containerLayout = new QVBoxLayout;
    containerLayout->setMargin(0);
    containerLayout->addWidget(itemContainerWidget);
    containerLayout->addStretch(1);

    QWidget *containerWidget = new QWidget;
    containerWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    containerWidget->setObjectName("containerWidget");
    containerWidget->setMaximumWidth(800);
    containerWidget->setContentsMargins(0,30,0,0);
    containerWidget->setStyleSheet(QString::fromUtf8("QWidget#containerWidget\n"
    "{\n"
    "    border-left: 1px solid gray;\n"
    "    border-right: 1px solid gray;\n"
    "    background-color:white;\n"
    "}\n"
    ""));
    containerWidget->setLayout(containerLayout);

    // main layout
    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->addWidget(new QWidget);
    mainLayout->addWidget(containerWidget);
    mainLayout->addWidget(new QWidget);
    setLayout(mainLayout);

    connect(m_newProjectButton, SIGNAL(clicked()), m_projectManager, SLOT(newProject()));
    connect(m_openProjectButton, SIGNAL(clicked()), m_projectManager, SLOT(openProject()));
    connect(m_newUsertButton, SIGNAL(clicked()), this, SLOT(onNewUser()));

    connect(m_projectManager, SIGNAL(modified()), this, SLOT(updateRecentProjectPanel()));

    updateRecentProjectPanel();
}

void WelcomeView::generateRecentProjectList()
{
    QFont titleFont;
    titleFont.setPointSize(DesignerHelper::getSectionFontSize());
    titleFont.setBold(true);


//    QLabel *currentProLabel = new QLabel("Current Project:");
//    currentProLabel->setFont(titleFont);

    QLabel *recentProLabel = new QLabel("Recent Projects:");
    recentProLabel->setFont(titleFont);

    setCurrentProjectName(getCurrentProjectFancyName());
//    QLabel *currentProName = new QLabel("Untitled");
//    ProjectDocument *projectDocument = m_projectManager->getDocument();
//    if(projectDocument) {
//        if(projectDocument->hasValidNameAndPath()) {
//           m_currentProName->setText(Utils::withTildeHomePath(m_projectManager->getDocument()->getProjectFileName()));
//        } else {
//            m_currentProName->setText(m_projectManager->getDocument()->getProjectName());
//        }
//    }

//    m_recentProjectLayout->addWidget(currentProLabel);
//    m_recentProjectLayout->addWidget(currentProName);
//    m_recentProjectLayout->addSpacing(15);

    m_recentProjectLayout->addWidget(recentProLabel);

    QCommandLinkButton *slotButtons[Constants::MAX_RECENT_PROJECTS];
    //QLabel *myLabel[count];
    m_signalMapper = new QSignalMapper(this);

    int i(0);
    foreach(QString file, m_projectManager->getRecentProjects() ) {
        //hasRecentProjects = true;

        QFont font;
        //font.setPointSize(9);
        font.setPointSize(DesignerHelper::getLabelFontSize());
        font.setBold(false);
        //font.underline();

        QPalette palette;
        palette.setColor(QPalette::ButtonText,QColor(41,73,150));

        slotButtons[i] = new QCommandLinkButton;
        slotButtons[i]->setText(Utils::withTildeHomePath(file));
        slotButtons[i]->setFont(font);
        slotButtons[i]->setPalette(palette);
        //slotButtons[i]->setDescription("Recent description");
        slotButtons[i]->setFixedHeight(30);
        m_signalMapper->setMapping(slotButtons[i], file);
        connect(slotButtons[i], SIGNAL(clicked()), m_signalMapper, SLOT (map()));
        m_recentProjectLayout->addWidget(slotButtons[i]);

        i++;

        if(i == Constants::MAX_RECENT_PROJECTS) break;
    }

    m_recentProjectLayout->addStretch();

    connect(m_signalMapper, SIGNAL(mapped(QString)),
            m_projectManager, SLOT(openProject(QString)));
}

//! returns current project name suited for displaying on current project layout
QString WelcomeView::getCurrentProjectFancyName()
{
    QString result("Untitled");
    if(ProjectDocument *projectDocument = m_projectManager->getDocument()) {
        if(projectDocument->hasValidNameAndPath()) {
           result = Utils::withTildeHomePath(projectDocument->getProjectFileName());
        } else {
           result = projectDocument->getProjectName();
        }
    }
    return result;
}

//! updates label with current project name in picturesque manner
void WelcomeView::setCurrentProjectName(const QString &name)
{
    m_currentProName->setTextAnimated(name);
//    m_currentProName->setText(name);
}

void WelcomeView::onWebLinkClicked(const QUrl &url)
{
    QDesktopServices::openUrl(url);
}

void WelcomeView::onNewUser()
{
    QUrl url(tr("http://www.bornagainproject.org"));
    QDesktopServices::openUrl(url);
}

void WelcomeView::updateRecentProjectPanel()
{
    qDebug() << "WelcomeView::updateRecentProjectPanel called";
    this->clearLayout(m_recentProjectLayout);
    this->generateRecentProjectList();
    update();
}

void WelcomeView::clearLayout(QLayout* layout, bool deleteWidgets)
{
    if(layout) {
        while (QLayoutItem* item = layout->takeAt(0)) {
            if (deleteWidgets) {
                if (QWidget* widget = item->widget())
                    delete widget;
            }
            if (QLayout* childLayout = item->layout()) clearLayout(childLayout, deleteWidgets);
            delete item;
        }
    }
}
