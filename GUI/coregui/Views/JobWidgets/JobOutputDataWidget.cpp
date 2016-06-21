// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/JobWidgets/JobOutputDataWidget.cpp
//! @brief     Implements class JobOutputDataWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "JobOutputDataWidget.h"
#include "JobModel.h"
#include "JobItem.h"
#include "IntensityDataWidget.h"
#include "JobOutputDataToolBar.h"
#include "JobResultsPresenter.h"
#include "StyledToolBar.h"
#include "AppSvc.h"
#include "projectmanager.h"
#include "JobViewFlags.h"
#include <QVBoxLayout>

JobOutputDataWidget::JobOutputDataWidget(JobModel *jobModel, QWidget *parent)
    : QWidget(parent)
//    , m_stackedWidget(new ItemStackPresenter<IntensityDataWidget>)
    , m_stackedWidget(new ItemStackPresenter<JobResultsPresenter>)
//    , m_toolBar(new JobOutputDataToolBar)
//    , m_toolBar(new StyledToolBar)
{
    setWindowTitle(QLatin1String("Job OutputData"));

    setMinimumSize(400, 400);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);

//    mainLayout->addWidget(m_toolBar);
    mainLayout->addWidget(m_stackedWidget);

    m_stackedWidget->setMinimumSize(600, 600);
    m_stackedWidget->setModel(jobModel);

    setLayout(mainLayout);

    connectSignals();
}


void JobOutputDataWidget::setItem(JobItem * jobItem)
{
    if(!isValidJobItem(jobItem)) {
        m_stackedWidget->hideWidgets();
        return;
    }

    bool isNew(false);
    m_stackedWidget->setItem(jobItem, isNew);

    if(isNew) {
//        IntensityDataWidget *widget = m_stackedWidget->currentWidget();
        JobResultsPresenter *widget = m_stackedWidget->currentWidget();
        Q_ASSERT(widget);
        widget->setItem(jobItem);
//        widget->setToolBar(m_toolBar);
//        widget->setItem(jobItem->getIntensityDataItem());
//        connect(widget, SIGNAL(savePlotRequest()), this, SLOT(onSavePlot()));
    }
}

void JobOutputDataWidget::togglePropertyPanel()
{
//    if(auto widget = currentOutputDataWidget())
//        widget->togglePropertyPanel();
}

void JobOutputDataWidget::toggleProjections()
{
//    if(auto widget = currentOutputDataWidget())
//        widget->toggleProjections();
}

void JobOutputDataWidget::onResetView()
{
//    if(auto widget = currentOutputDataWidget())
//        widget->onResetView();
}

void JobOutputDataWidget::onSavePlot()
{
//    if(auto widget = currentOutputDataWidget())
//        widget->savePlot(AppSvc::projectManager()->userExportDir());
}

void JobOutputDataWidget::onActivityChanged(int activity)
{
    Q_UNUSED(activity);
//    if(activity == JobViewFlags::REAL_TIME_ACTIVITY) {
//        if(auto widget = currentOutputDataWidget())
//            widget->setPropertyPanelVisible(false);
//    }
}

bool JobOutputDataWidget::isValidJobItem(JobItem *item)
{
    if(!item) return false;
    if(item->isCompleted() || item->isCanceled()) return true;
    return false;
}

void JobOutputDataWidget::connectSignals()
{
//    connect(m_toolBar, SIGNAL(togglePropertyPanel()), this, SLOT(togglePropertyPanel()));
//    connect(m_toolBar, SIGNAL(toggleProjections()), this, SLOT(toggleProjections()));
//    connect(m_toolBar, SIGNAL(resetView()), this, SLOT(onResetView()));
//    connect(m_toolBar, SIGNAL(savePlot()), this, SLOT(onSavePlot()));
}

IntensityDataWidget *JobOutputDataWidget::currentOutputDataWidget()
{
//    return m_stackedWidget->currentWidget();
    return 0;
}

