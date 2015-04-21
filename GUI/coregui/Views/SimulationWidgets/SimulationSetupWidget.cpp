// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/SimulationWidgets/SimulationSetupWidget.cpp
//! @brief     Implements class SimulationSetupWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "SimulationSetupWidget.h"
#include "Simulation.h"
#include "mainwindow.h"
#include "PythonScriptSampleBuilder.h"
#include "JobModel.h"
#include "SampleModel.h"
#include "InstrumentModel.h"
#include "JobItem.h"
#include "SampleValidator.h"
#include "Utils.h"
#include "PyGenTools.h"
#include "mainwindow_constants.h"
#include "PythonScriptWidget.h"
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
#include <DomainSimulationBuilder.h>

SimulationSetupWidget::SimulationSetupWidget(QWidget *parent)
    : QWidget(parent)
    , m_jobModel(0)
    , m_sampleModel(0)
    , m_instrumentModel(0)
    , m_projectManager(0)
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
    runSimulationButton->setToolTip("Run the simulation using settings above.\n"
                                    " Global shortcut ctrl-r can be used to run from sample view.");
//    QPalette palette = runSimulationButton->palette();
//    palette.setColor(QPalette::Button, QColor(Constants::BUTTON_COLOR));
//    palette.setColor(QPalette::ButtonText, QColor(Constants::BUTTON_TEXT_COLOR));
//    runSimulationButton->setPalette(palette);

    // export simulation to a python script
    exportToPyScriptButton = new QPushButton(tr("Export to Python Script"));
    exportToPyScriptButton->setIcon(QIcon(":/images/mode_script.png"));
    exportToPyScriptButton->setMinimumWidth(100);
    exportToPyScriptButton->setMinimumHeight(50);
    exportToPyScriptButton->setToolTip("Export the simulation using settings above to "
                                       "a python script.\n");
//    exportToPyScriptButton->setPalette(palette);

    simButtonLayout->addStretch();
    simButtonLayout->addWidget(runSimulationButton);
    simButtonLayout->addWidget(exportToPyScriptButton);
    simButtonLayout->addStretch();

    // main layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(inputDataGroup);
    mainLayout->addWidget(simulationParametersGroup);
    mainLayout->addLayout(simButtonLayout);
    mainLayout->addStretch();
    setLayout(mainLayout);

    // signal and slots
    connect(runSimulationButton, SIGNAL(clicked()), this, SLOT(onRunSimulation()));
    connect(exportToPyScriptButton, SIGNAL(clicked()), this, SLOT(onExportToPythonScript()));
}

void SimulationSetupWidget::setJobModel(JobModel *model)
{
    Q_ASSERT(model);
    if(model != m_jobModel) {
        m_jobModel = model;
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

int SimulationSetupWidget::getInstrumentCurrentIndex() const
{
    return instrumentSelectionBox->currentIndex();
}

QString SimulationSetupWidget::getSampleSelection() const
{
    return sampleSelectionBox->currentText();
}

int SimulationSetupWidget::getSampleCurrentIndex() const
{
    return sampleSelectionBox->currentIndex();
}

void SimulationSetupWidget::setProjectManager(ProjectManager *projectManager)
{
    m_projectManager = projectManager;
}

void SimulationSetupWidget::updateViewElements()
{
    updateSelectionBox(instrumentSelectionBox, m_instrumentModel->getInstrumentMap().keys());
    updateSelectionBox(sampleSelectionBox, m_sampleModel->getSampleMap().keys());
}

void SimulationSetupWidget::onRunSimulation()
{
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

    m_jobModel->addJob(jobSampleModel, jobInstrumentModel, runPolicySelectionBox->currentText(), getNumberOfThreads());
}

void SimulationSetupWidget::onExportToPythonScript()
{
    InstrumentModel *instrumentModel = getJobInstrumentModel();
    if(!instrumentModel) {
        QMessageBox::warning(this, tr("No Instrument Selected"),
                             tr("You must select an instrument first."));
        return;
    }

    SampleModel *sampleModel = getJobSampleModel();
    if(!sampleModel) {
        QMessageBox::warning(this, tr("No Sample Selected"),
                             tr("You must select a sample first."));
        return;
    }

    SampleValidator sampleValidator;
    if(!sampleValidator.isVaildSampleModel(sampleModel)) {
        QMessageBox::warning(this, tr("Not suitable MultiLayer"),
                             sampleValidator.getValidationMessage());
        return;
    }

    PythonScriptWidget *pythonWidget = new PythonScriptWidget(this, m_projectManager);
    pythonWidget->show();
    pythonWidget->raise();
    pythonWidget->generatePythonScript(sampleModel, instrumentModel);
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
//    if(instruments[getInstrumentSelection()]) {
//        result = m_instrumentModel->createCopy(instruments[getInstrumentSelection()]);
//    }
    // there can be several instruments with same name
    if(instruments[getInstrumentSelection()]) {
        int index = getInstrumentCurrentIndex();
        QMap<QString, ParameterizedItem *>::iterator it = instruments.begin()+index;
        result = m_instrumentModel->createCopy(it.value());
    }

    return result;
}

//! Returns copy of SampleModel containing a single MultiLayer according to the text selection
SampleModel *SimulationSetupWidget::getJobSampleModel()
{
    SampleModel *result(0);
    QMap<QString, ParameterizedItem *> samples = m_sampleModel->getSampleMap();
//    if(samples[getSampleSelection()]) {
//        result = m_sampleModel->createCopy(samples[getSampleSelection()]);
//    }
    // there can be several samples with same name
    if(samples[getSampleSelection()]) {
        int index = getSampleCurrentIndex();
        QMap<QString, ParameterizedItem *>::iterator it = samples.begin()+index;
        result = m_sampleModel->createCopy(it.value());
    }
    return result;
}

