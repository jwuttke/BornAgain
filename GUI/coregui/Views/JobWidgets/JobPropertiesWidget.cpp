// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/JobWidgets/JobPropertiesWidget.cpp
//! @brief     Implements class JobPropertiesWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "JobPropertiesWidget.h"
#include "AwesomePropertyEditor.h"
#include "JobModel.h"
#include "JobItem.h"
#include <QVBoxLayout>
#include <QTabBar>
#include <QTextEdit>
#include <QTabWidget>
#include <QDebug>

JobPropertiesWidget::JobPropertiesWidget(QWidget *parent)
    : QWidget(parent)
    , m_jobModel(0)
    , m_currentItem(0)
    , m_tabWidget(new QTabWidget)
    , m_propertyEditor(0)
    , m_commentsEditor(0)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    setWindowTitle(QLatin1String("Job Properties"));
    setObjectName(QLatin1String("Job Properties"));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);

    m_propertyEditor = new AwesomePropertyEditor(this);
    //m_propertyEditor->setCreateGroupProperty(false);

    m_commentsEditor = new QTextEdit();

    QWidget *commentsWidget = new QWidget();
    QVBoxLayout * vlayout = new QVBoxLayout;
    vlayout->setMargin(8);
    vlayout->addWidget(m_commentsEditor);
    commentsWidget->setLayout(vlayout);

    m_tabWidget->setTabPosition(QTabWidget::South);
    m_tabWidget->insertTab(JOB_PROPERTIES, m_propertyEditor, "Job Properties");
    m_tabWidget->insertTab(JOB_COMMENTS, commentsWidget, "Details");

    mainLayout->addWidget(m_tabWidget);

    setLayout(mainLayout);
}

void JobPropertiesWidget::setModel(JobModel *model)
{
    Q_ASSERT(model);
    if(model != m_jobModel) {
        if(m_jobModel)
            disconnect(m_jobModel,
                SIGNAL( selectionChanged(JobItem *) ),
                this,
                SLOT( setItem(JobItem *) )
                );

        m_jobModel = model;
        connect(m_jobModel,
            SIGNAL( selectionChanged(JobItem *) ),
            this,
            SLOT( setItem(JobItem *) )
            );
    }
}

void JobPropertiesWidget::setItem(JobItem *jobItem)
{
    m_propertyEditor->setItem(jobItem);

    if (m_currentItem == jobItem) return;

    if (m_currentItem) {
        disconnect(m_currentItem, SIGNAL(propertyChanged(QString)),
                this, SLOT(onPropertyChanged(QString)));
    }

    m_currentItem = jobItem;

    if (!m_currentItem) return;

    updateItem(m_currentItem);

    connect(m_currentItem, SIGNAL(propertyChanged(QString)),
            this, SLOT(onPropertyChanged(QString)));
}

void JobPropertiesWidget::onPropertyChanged(const QString &property_name)
{
    if(property_name == JobItem::P_COMMENTS) {
        updateItem(m_currentItem);
    }
}

void JobPropertiesWidget::updateItem(JobItem *jobItem)
{
    if(jobItem) {
        if(jobItem->getStatus() == Constants::STATUS_FAILED) {
            m_tabWidget->tabBar()->setTabTextColor(JOB_COMMENTS, Qt::red);
        } else {
            m_tabWidget->tabBar()->setTabTextColor(JOB_COMMENTS, Qt::black);
        }
        m_commentsEditor->setText(jobItem->getComments());
    }

}




