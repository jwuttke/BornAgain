// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/mainwindow/mainwindow.cpp
//! @brief     Implements class MainWindow
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "mainwindow.h"
#include "fancytabwidget.h"
#include "manhattanstyle.h"
#include "actionmanager.h"
#include "WelcomeView.h"
#include "SampleView.h"
#include "InstrumentView.h"
#include "SimulationView.h"
#include "MaterialEditorWidget.h"
#include "stylehelper.h"
#include "JobModel.h"
#include "MaterialModel.h"
#include "InstrumentModel.h"
#include "MaterialEditor.h"
#include "Instrument.h"
#include "Units.h"
#include "Samples.h"
#include "IconProvider.h"
#include "InterferenceFunctions.h"
#include "FormFactors.h"
#include "ParticleItem.h"
#include "FormFactorItems.h"
#include "InstrumentItem.h"
#include "BeamItem.h"
#include "DetectorItems.h"
#include "mainwindow_constants.h"
#include "hostosinfo.h"
#include "projectmanager.h"
#include "progressbar.h"
#include "SimulationRegistry.h"
#include "DomainObjectBuilder.h"
#include "GUIObjectBuilder.h"
#include "SampleBuilderFactory.h"
#include "GUIObjectBuilder.h"
#include "tooltipdatabase.h"
#include "mainwindow_constants.h"
#include "ParticleCoreShellItem.h"
#include "FancyGroupProperty.h"
#include "ScientificDoubleProperty.h"
#include "SampleModel.h"
#include "JobView.h"
#include "aboutapplicationdialog.h"
#include "FitModel.h"
#include "FitProxyModel.h"
#include "FitView.h"
#include "TestView.h"
#include <boost/scoped_ptr.hpp>

#include <QApplication>
#include <QStatusBar>
#include <QSettings>
#include <QCloseEvent>
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : Manhattan::FancyMainWindow(parent)
    , m_tabWidget(0)
    , m_welcomeView(0)
    , m_instrumentView(0)
    , m_sampleView(0)
    , m_simulationView(0)
    , m_jobView(0)
    , m_fitView(0)
    , m_progressBar(0)
    , m_actionManager(0)
    , m_projectManager(0)
    , m_settings(new QSettings(Constants::APPLICATION_NAME, Constants::APPLICATION_NAME, this))
    , m_jobModel(0)
    , m_sampleModel(0)
    , m_instrumentModel(0)
    , m_materialModel(0)
    , m_materialEditor(0)
    , m_toolTipDataBase(new ToolTipDataBase(this))
    , m_fitProxyModel(0)
{
//    QCoreApplication::setApplicationName(QLatin1String(Constants::APPLICATION_NAME));
//    QCoreApplication::setApplicationVersion(QLatin1String(Constants::APPLICATION_VERSION));
//    QCoreApplication::setOrganizationName(QLatin1String(Constants::APPLICATION_NAME));

    createModels();

    if (!Utils::HostOsInfo::isMacHost())
        QApplication::setWindowIcon(QIcon(":/images/BornAgain.ico"));

    QString baseName = QApplication::style()->objectName();
    qApp->setStyle(new ManhattanStyle(baseName));
    Manhattan::Utils::StyleHelper::setBaseColor(QColor(Constants::MAIN_THEME_COLOR));

    setDockNestingEnabled(true);

    setCorner(Qt::BottomLeftCorner, Qt::LeftDockWidgetArea);
    setCorner(Qt::BottomRightCorner, Qt::BottomDockWidgetArea);

    m_projectManager = new ProjectManager(this);
    m_actionManager = new ActionManager(this);
    readSettings();

    m_tabWidget = new Manhattan::FancyTabWidget(this);
    m_welcomeView = new WelcomeView(this);
    m_instrumentView = new InstrumentView(m_instrumentModel);
    m_sampleView = new SampleView(m_sampleModel, m_instrumentModel);
    m_simulationView = new SimulationView(this);

//    m_testView = new TestView(m_sampleModel, this);
    //m_fitView = new FitView(m_fitProxyModel, this);

    m_jobView = new JobView(m_jobModel, m_projectManager);


    m_tabWidget->insertTab(WELCOME, m_welcomeView, QIcon(":/images/main_home.png"), "Welcome");
    m_tabWidget->insertTab(INSTRUMENT, m_instrumentView, QIcon(":/images/main_instrument.png"), "Instrument");
    m_tabWidget->insertTab(SAMPLE, m_sampleView, QIcon(":/images/main_sample.png"), "Sample");
    //m_tabWidget->insertTab(3, m_scriptView, QIcon(":/images/mode_script.png"), "Python scripts");
    m_tabWidget->insertTab(SIMULATION, m_simulationView, QIcon(":/images/main_simulation.png"), "Simulation");
    m_tabWidget->insertTab(JOB, m_jobView, QIcon(":/images/main_jobqueue.png"), "Jobs");
    //m_tabWidget->insertTab(TestViewTab, m_testView, QIcon(":/images/main_simulation.png"), "Test");
    //m_tabWidget->insertTab(FitViewTab, m_fitView, QIcon(":/images/main_simulation.png"), "Fit");
    //m_tabWidget->insertTab(FIT_VIEW, new TestView(this), QIcon(":/images/main_simulation.png"), "Test");

    m_tabWidget->setCurrentIndex(WELCOME);

    m_progressBar = new Manhattan::ProgressBar(this);
    m_tabWidget->addBottomCornerWidget(m_progressBar);
    m_progressBar->hide();
    m_jobView->setProgressBar(m_progressBar);

    setCentralWidget(m_tabWidget);

    setAcceptDrops(true);

    // signals/slots
    connect(m_tabWidget, SIGNAL(currentChanged(int)), this, SLOT(onChangeTabWidget(int)));
    connect(m_jobView, SIGNAL(focusRequest(int)), this, SLOT(onFocusRequest(int)));

    m_projectManager->createNewProject();

    //testGUIObjectBuilder();
}

MainWindow::~MainWindow()
{
    delete m_materialEditor;
}

void MainWindow::readSettings()
{
    if(m_settings->childGroups().contains("MainWindow")) {
        m_settings->beginGroup("MainWindow");
        resize(m_settings->value("size", QSize(400, 400)).toSize());
        move(m_settings->value("pos", QPoint(200, 200)).toPoint());
        m_settings->endGroup();
    }
    assert(m_projectManager);
    m_projectManager->readSettings(m_settings);
}

void MainWindow::writeSettings()
{
    m_settings->beginGroup("MainWindow");
    m_settings->setValue("size", size());
    m_settings->setValue("pos", pos());
    m_settings->endGroup();

    m_projectManager->writeSettings(m_settings);

    m_settings->sync();
}

void MainWindow::onRunSimulationShortcut()
{
    m_simulationView->onRunSimulationShortcut();
}

void MainWindow::openRecentProject()
{
    if (const QAction *action = qobject_cast<const QAction*>(sender())) {
        QString file = action->data().value<QString>();
        qDebug() << "MainWindow::openRecentProject() -> " << file;
        m_projectManager->openProject(file);
    }
}

void MainWindow::onChangeTabWidget(int index)
{
    // update views which depend on others
    (void)index;

    if(index == WELCOME)
    {
        m_welcomeView->updateRecentProjectPanel();
    }
    else if (index == INSTRUMENT) {
        m_instrumentView->updateView();
    }
    else if(index == SIMULATION) {
        m_simulationView->updateSimulationViewElements();
    }
}

void MainWindow::onFocusRequest(int index)
{
    m_tabWidget->setCurrentIndex(index);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(m_jobModel->getJobQueueData()->hasUnfinishedJobs()) {
        QMessageBox::warning(this, tr("Can't quite the application."),
                             "Can't quite the application while jobs are running.\nCancel running jobs or wait until they are completed.");
        event->ignore();
        return;
    }

    if(m_projectManager->closeCurrentProject())
    {
        writeSettings();
        event->accept();
    }
    else
    {
        event->ignore();
    }
}

//! creates and initializes models
void MainWindow::createModels()
{
    createMaterialModel(); // should be first

    createSampleModel();

    createJobModel();

    createInstrumentModel();

    //createFitModel();

    resetModels();
}

void MainWindow::createMaterialModel()
{
    delete m_materialModel;
    m_materialModel = new MaterialModel(this);
//    m_materialModel->addMaterial("Default", 1e-3, 1e-5);
//    m_materialModel->addMaterial("Air", 0.0, 0.0);
//    m_materialModel->addMaterial("Particle", 6e-4, 2e-8);
//    m_materialModel->addMaterial("Substrate", 6e-6, 2e-8);
    m_materialEditor = new MaterialEditor(m_materialModel);
}

void MainWindow::createSampleModel()
{
    Q_ASSERT(m_materialModel);
    delete m_sampleModel;
    m_sampleModel = new SampleModel(this);
    connect(m_materialModel, SIGNAL(dataChanged(QModelIndex,QModelIndex)),
            m_sampleModel, SLOT(onMaterialModelChanged(QModelIndex,QModelIndex)));
}

void MainWindow::createJobModel()
{
    delete m_jobModel;
    m_jobModel = new JobModel(this);
}

void MainWindow::createInstrumentModel()
{
    delete m_instrumentModel;
    m_instrumentModel = new InstrumentModel(this);
    m_instrumentModel->setIconProvider(new IconProvider());
}

void MainWindow::createFitModel()
{
    m_fitProxyModel = new FitProxyModel;
}

//! reset all models to initial state
void MainWindow::resetModels()
{
    m_materialModel->clear();
    m_materialModel->addMaterial("Default", 1e-3, 1e-5);
    m_materialModel->addMaterial("Air", 0.0, 0.0);
    m_materialModel->addMaterial("Particle", 6e-4, 2e-8);
    m_materialModel->addMaterial("Substrate", 6e-6, 2e-8);

    m_sampleModel->clear();

    m_jobModel->clear();

    m_instrumentModel->clear();
    ParameterizedItem *instrument = m_instrumentModel->insertNewItem(Constants::InstrumentType);
    instrument->setItemName("Default GISAS");
    m_instrumentModel->insertNewItem(Constants::DetectorType, m_instrumentModel->indexOfItem(instrument));
    m_instrumentModel->insertNewItem(Constants::BeamType, m_instrumentModel->indexOfItem(instrument));
}

void MainWindow::testGUIObjectBuilder()
{
    SampleBuilderFactory factory;
    boost::scoped_ptr<ISample> sample(factory.createSample("isgisaxs01"));

    GUIObjectBuilder guiBuilder;
    guiBuilder.populateSampleModel(m_sampleModel, *sample);
}

void MainWindow::onAboutApplication()
{
    AboutApplicationDialog dialog(this);
    dialog.exec();
}

