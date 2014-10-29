#include "SimulationSetupWidget.h"
#include "Simulation.h"
#include "mainwindow.h"
#include "PythonScriptSampleBuilder.h"
#include "JobQueueModel.h"
#include "SampleModel.h"
#include "InstrumentModel.h"
#include "JobItem.h"
#include "SampleValidator.h"
#include "Utils.h"
#include <QGroupBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QComboBox>
#include <QLabel>
#include <QGridLayout>
#include <QMessageBox>
#include <QFileDialog>
#include <QDir>
#include <QtCore>
#include <QMenu>

SimulationSetupWidget::SimulationSetupWidget(QWidget *parent)
    : QWidget(parent)
    , m_jobQueueModel(0)
    , m_sampleModel(0)
    , m_instrumentModel(0)
{
    // selection of input parameters
    QGroupBox *inputDataGroup = new QGroupBox(tr("Data selection"));
      // instrument selection
    QLabel *instrumentSelectionLabel = new QLabel(tr("Select Instrument:"));
    instrumentSelectionBox = new QComboBox;
      // sample selection
    QLabel *sampleSelectionLabel = new QLabel(tr("Select Sample:"));
    sampleSelectionBox = new QComboBox;
      // layout
    QGridLayout *dataSelectionLayout = new QGridLayout;
    dataSelectionLayout->addWidget(instrumentSelectionLabel, 0, 0);
    dataSelectionLayout->addWidget(instrumentSelectionBox, 0, 1);
    dataSelectionLayout->addWidget(sampleSelectionLabel, 1, 0);
    dataSelectionLayout->addWidget(sampleSelectionBox, 1, 1);
    inputDataGroup->setLayout(dataSelectionLayout);
    //updateViewElements();

    // selection of simulation parameters
    QGroupBox *simulationParametersGroup = new QGroupBox(tr("Simulation Parameters"));
    // run policy
    QLabel *runPolicyLabel = new QLabel(tr("Run Policy:"));
    runPolicyLabel->setToolTip("Defines run policy for the simulation");
    runPolicySelectionBox = new QComboBox;
    runPolicySelectionBox->setToolTip("Defines run policy for the simulation");
    runPolicySelectionBox->addItems(JobItem::getRunPolicies().keys());
    int index(0);
    foreach(QString descr, JobItem::getRunPolicies().values())
        runPolicySelectionBox->setItemData(index++, descr, Qt::ToolTipRole);

    // selection of number of threads
    QLabel *cpuUsageLabel = new QLabel(tr("CPU Usage:"));
    cpuUsageLabel->setToolTip("Defines number of threads to use for the simulation.");
    cpuUsageSelectionBox = new QComboBox;
    cpuUsageSelectionBox->setToolTip("Defines number of threads to use for the simulation.");
    cpuUsageSelectionBox->addItems(getCPUUsageOptions());

      // layout
    QGridLayout *simulationParametersLayout = new QGridLayout;
    simulationParametersLayout->addWidget(runPolicyLabel, 0, 0);
    simulationParametersLayout->addWidget(runPolicySelectionBox, 0, 1);
    simulationParametersLayout->addWidget(cpuUsageLabel, 1, 0);
    simulationParametersLayout->addWidget(cpuUsageSelectionBox, 1, 1);
    simulationParametersGroup->setLayout(simulationParametersLayout);

    QHBoxLayout *simButtonLayout = new QHBoxLayout;
    // run simulation button
    runSimulationButton = new QPushButton(tr("Run Simulation"));
    runSimulationButton->setIcon(QIcon(":/images/main_simulation.png"));
    runSimulationButton->setMinimumWidth(100);
    runSimulationButton->setMinimumHeight(50);
    runSimulationButton->setToolTip("Run the simulation using settings above.\n Global shortcut ctrl-r can be used to run from sample view.");

    simButtonLayout->addStretch();
    simButtonLayout->addWidget(runSimulationButton);
    simButtonLayout->addStretch();


    // run simulation with python script sample builder
    //runPyScriptSimulation = new QPushButton(tr("Run Simulation with Python Sample"));

    // main layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(inputDataGroup);
    mainLayout->addWidget(simulationParametersGroup);
    //mainLayout->addWidget(runSimulationButton);
    //mainLayout->addWidget(runPyScriptSimulation);
    mainLayout->addLayout(simButtonLayout);
    mainLayout->addStretch();
    setLayout(mainLayout);

    // signal and slots
    connect(runSimulationButton, SIGNAL(clicked()), this, SLOT(onRunSimulation()));
    //connect(runPyScriptSimulation, SIGNAL(clicked()), this, SLOT(onPythonJobLaunched()));
}


void SimulationSetupWidget::setJobQueueModel(JobQueueModel *model)
{
    Q_ASSERT(model);
    if(model != m_jobQueueModel) {
        m_jobQueueModel = model;
    }
}


void SimulationSetupWidget::setSampleModel(SampleModel *model)
{
    Q_ASSERT(model);
    if(model != m_sampleModel) {
        m_sampleModel = model;
        updateSelectionBox(sampleSelectionBox, m_sampleModel->getSampleMap().keys());
    }
}


void SimulationSetupWidget::setInstrumentModel(InstrumentModel *model)
{
    Q_ASSERT(model);
    if(model != m_instrumentModel) {
        m_instrumentModel = model;
        updateSelectionBox(instrumentSelectionBox, m_instrumentModel->getInstrumentMap().keys());
    }
}


QString SimulationSetupWidget::getInstrumentSelection() const
{
    return instrumentSelectionBox->currentText();
}


QString SimulationSetupWidget::getSampleSelection() const
{
    return sampleSelectionBox->currentText();
}


void SimulationSetupWidget::updateViewElements()
{
    updateSelectionBox(instrumentSelectionBox, m_instrumentModel->getInstrumentMap().keys());
    updateSelectionBox(sampleSelectionBox, m_sampleModel->getSampleMap().keys());
}


void SimulationSetupWidget::onRunSimulation()
{
    qDebug() << "SimulationView::onRunSimulation()";

    InstrumentModel *jobInstrumentModel = getJobInstrumentModel();
    if(!jobInstrumentModel) {
        QMessageBox::warning(this, tr("No Instrument Selected"),
                             tr("You must select an instrument first."));
        return;
    }

    SampleModel *jobSampleModel = getJobSampleModel();
    if(!jobSampleModel) {
        QMessageBox::warning(this, tr("No Sample Selected"),
                             tr("You must select a sample first."));
        return;
    }

    SampleValidator sampleValidator;
    if(!sampleValidator.isVaildSampleModel(jobSampleModel)) {
        QMessageBox::warning(this, tr("Not suitable MultiLayer"),
                             sampleValidator.getValidationMessage());
        return;
    }

    JobItem *jobItem = new JobItem(jobSampleModel, jobInstrumentModel, runPolicySelectionBox->currentText());
    jobItem->setNumberOfThreads(getNumberOfThreads());
    m_jobQueueModel->addJob(jobItem);
}


void SimulationSetupWidget::onPythonJobLaunched()
{
//    Instrument *p_instrument = mp_simulation_data_model->getInstrumentList().value(
//                instrumentSelectionBox->currentText(), 0);
//    if (!p_instrument) {
//        QMessageBox::warning(this, tr("No Instrument Selected"),
//                             tr("You must select an instrument first."));
//        return;
//    }
//    QString file_name = QFileDialog::getOpenFileName(this, tr("Select Python Script"),
//                            QDir::homePath(), tr("Python scripts (*.py)"),
//                            0, QFileDialog::ReadOnly | QFileDialog::DontUseNativeDialog);
//    if (file_name.isNull()) {
//        return;
//    }
//    PythonScriptSampleBuilder builder(file_name);
//    ISample *p_sample = builder.buildSample();
//    Simulation *p_sim = new Simulation;
//    p_sim->setSample(*p_sample);
//    p_sim->setInstrument(*p_instrument);

//    QString identifier = m_jobQueueModel->addJob("PythonScript", p_sim);
//    m_jobQueueModel->runJob(identifier);
}



void SimulationSetupWidget::updateSelectionBox(QComboBox *comboBox, QStringList itemList)
{
    QString previousItem = comboBox->currentText();

    comboBox->clear();
    if(itemList.isEmpty()) {
        comboBox->setEnabled(false);
        comboBox->addItem("Not yet defined");
    } else {
        comboBox->setEnabled(true);
        qSort(itemList.begin(), itemList.end());
        comboBox->addItems(itemList);
        if(itemList.contains(previousItem))
            comboBox->setCurrentIndex(itemList.indexOf(previousItem));
    }
}

//! returns list with number of threads to select
QStringList SimulationSetupWidget::getCPUUsageOptions()
{
    QStringList result;
    int nthreads = Utils::System::getThreadHardwareConcurrency();
    for(int i = nthreads; i>0; i--){
        if(i == nthreads) {
            result.append(QString("Max (%1 threads)").arg(QString::number(i)));
        } else if(i == 1) {
            result.append(QString("%1 thread").arg(QString::number(i)));
        } else {
            result.append(QString("%1 threads").arg(QString::number(i)));
        }
    }
    return result;
}


int SimulationSetupWidget::getNumberOfThreads()
{
    foreach(QChar ch, cpuUsageSelectionBox->currentText()) {
        if(ch.isDigit()) return ch.digitValue();
    }
    return 0;
}


//! Returns copy of InstrumentModel containing a single instrument according to the text selection
InstrumentModel *SimulationSetupWidget::getJobInstrumentModel()
{
    InstrumentModel *result(0);
    QMap<QString, ParameterizedItem *> instruments = m_instrumentModel->getInstrumentMap();
    if(instruments[getInstrumentSelection()]) {
        result = m_instrumentModel->createCopy(instruments[getInstrumentSelection()]);
    }
    return result;
}


//! Returns copy of SampleModel containing a single MultiLayer according to the text selection
SampleModel *SimulationSetupWidget::getJobSampleModel()
{
    SampleModel *result(0);
    QMap<QString, ParameterizedItem *> samples = m_sampleModel->getSampleMap();
    if(samples[getSampleSelection()]) {
        result = m_sampleModel->createCopy(samples[getSampleSelection()]);
    }
    return result;

}


