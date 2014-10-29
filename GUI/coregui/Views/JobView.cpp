#include "JobView.h"
#include "TestView.h"
#include "JobSelectorWidget.h"
#include "JobOutputDataWidget.h"
#include "JobQueueModel.h"
#include "JobRealTimeWidget.h"
#include "projectmanager.h"
#include "mainwindow.h"
#include "progressbar.h"
#include <QFrame>
#include <QDockWidget>
#include <QAbstractItemView>


struct JobViewPrivate
{
    JobViewPrivate(JobQueueModel *jobQueueModel, ProjectManager *projectManager);
    QWidget *m_subWindows[JobView::NumberOfDocks];
    QDockWidget *m_dockWidgets[JobView::NumberOfDocks];
    JobQueueModel *m_jobQueueModel;
    JobSelectorWidget *m_jobSelector;
    JobOutputDataWidget *m_jobOutputDataWidget;
    JobRealTimeWidget *m_jobRealTimeWidget;
    Manhattan::ProgressBar *m_progressBar; //!< general progress bar
    ProjectManager *m_projectManager;
};


JobViewPrivate::JobViewPrivate(JobQueueModel *jobQueueModel, ProjectManager *projectManager)
    : m_jobQueueModel(jobQueueModel)
    , m_jobSelector(0)
    , m_jobOutputDataWidget(0)
    , m_progressBar(0)
    , m_projectManager(projectManager)
{
    qFill(m_subWindows, m_subWindows + JobView::NumberOfDocks,
          static_cast<QWidget*>(0));
    qFill(m_dockWidgets, m_dockWidgets + JobView::NumberOfDocks,
          static_cast<QDockWidget*>(0));
}


JobView::JobView(JobQueueModel *jobQueueModel, ProjectManager *projectManager, QWidget *parent)
    : Manhattan::FancyMainWindow(parent)
    , m_d(new JobViewPrivate(jobQueueModel, projectManager))
{
    setObjectName("JobView");

    initWindows();

    setDocumentMode(true);
    setTabPosition(Qt::AllDockWidgetAreas, QTabWidget::South);
    setCorner(Qt::BottomLeftCorner, Qt::LeftDockWidgetArea);
    setCorner(Qt::BottomRightCorner, Qt::RightDockWidgetArea);

    for (int i = 0; i < NumberOfDocks; i++) {
        QWidget *subWindow = m_d->m_subWindows[i];
        m_d->m_dockWidgets[i] = addDockForWidget(subWindow);

        // Since we have 1-pixel splitters, we generally want to remove
        // frames around item views. So we apply this hack for now.
        QList<QAbstractItemView*> frames =
                subWindow->findChildren<QAbstractItemView*>();
        for (int i = 0 ; i< frames.count(); ++i)
            frames[i]->setFrameStyle(QFrame::NoFrame);

    }

    resetToDefaultLayout();

    connectSignals();
}


JobView::~JobView()
{
    delete m_d;
}


void JobView::setProgressBar(Manhattan::ProgressBar *progressBar)
{
    if(m_d->m_progressBar != progressBar) {
        m_d->m_progressBar = progressBar;
        m_d->m_progressBar->hide();
        connect(m_d->m_progressBar, SIGNAL(clicked()), m_d->m_jobQueueModel->getJobQueueData(), SLOT(onCancelAllJobs()));
    }
}


void JobView::updateGlobalProgressBar(int progress)
{
    Q_ASSERT(m_d->m_progressBar);
    if(progress<0 || progress >= 100) {
        m_d->m_progressBar->setFinished(true);
        m_d->m_progressBar->hide();
    } else {
        m_d->m_progressBar->show();
        m_d->m_progressBar->setFinished(false);
        m_d->m_progressBar->setValue(progress);
    }
}


void JobView::onFocusRequest(JobItem *item)
{
    m_d->m_jobSelector->makeJobItemSelected(item);
    emit focusRequest(MainWindow::JobTab);
}


void JobView::resetToDefaultLayout()
{
    setTrackingEnabled(false);
    QList<QDockWidget *> dockWidgetList = dockWidgets();
    foreach (QDockWidget *dockWidget, dockWidgetList) {
        dockWidget->setFloating(false);
        removeDockWidget(dockWidget);
    }

    addDockWidget(Qt::LeftDockWidgetArea,
                  m_d->m_dockWidgets[JobListDock]);
    addDockWidget(Qt::RightDockWidgetArea,
                  m_d->m_dockWidgets[RealTimeDock]);

    foreach (QDockWidget *dockWidget, dockWidgetList)
        dockWidget->show();

    setTrackingEnabled(true);

    setActivity(JobViewActivity);
}


void JobView::setActivity(int activity)
{
    if(activity == JobViewActivity) {
        m_d->m_dockWidgets[JobListDock]->show();
        m_d->m_dockWidgets[RealTimeDock]->hide();
        emit activityChanged(activity);
    } else if(activity == RealTimeActivity) {
        m_d->m_dockWidgets[JobListDock]->hide();
        m_d->m_dockWidgets[RealTimeDock]->show();
        m_d->m_jobRealTimeWidget->updateCurrentItem();
        emit activityChanged(activity);
    }
}


void JobView::initWindows()
{
    // central widget
    m_d->m_jobOutputDataWidget = new JobOutputDataWidget(m_d->m_jobQueueModel, m_d->m_projectManager, this);
    setCentralWidget(m_d->m_jobOutputDataWidget);

    m_d->m_jobSelector = new JobSelectorWidget(m_d->m_jobQueueModel, this);
    m_d->m_subWindows[JobListDock] = m_d->m_jobSelector;

    m_d->m_jobRealTimeWidget = new JobRealTimeWidget(m_d->m_jobQueueModel, this);
    m_d->m_subWindows[RealTimeDock] = m_d->m_jobRealTimeWidget;
}


void JobView::connectSignals()
{
    connect(this, SIGNAL(resetLayout()), this, SLOT(resetToDefaultLayout()));
    connect(m_d->m_jobQueueModel->getJobQueueData(), SIGNAL(globalProgress(int)), this, SLOT(updateGlobalProgressBar(int)));
    connect(m_d->m_jobQueueModel->getJobQueueData(), SIGNAL(focusRequest(JobItem*)), this, SLOT(onFocusRequest(JobItem*)));
    connect(m_d->m_jobOutputDataWidget, SIGNAL(jobViewActivityRequest(int)), this, SLOT(setActivity(int)));
    connect(this, SIGNAL(activityChanged(int)),  m_d->m_jobOutputDataWidget, SLOT(onActivityChanged(int)));
}


