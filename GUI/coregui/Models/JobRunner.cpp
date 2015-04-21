// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/JobRunner.cpp
//! @brief     Implements class JobRunner
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "JobRunner.h"
#include "Simulation.h"
#include "ProgressHandler.h"
#include "ThreadInfo.h"
#include "item_constants.h"
#include <boost/bind.hpp>
#include <QTimer>
#include <QDebug>


JobRunner::JobRunner(QString identifier, Simulation *simulation)
    : m_identifier(identifier)
    , m_simulation(simulation)
    , m_progress(0)
    , m_job_status(Constants::STATUS_IDLE)
    , m_terminate_request_flag(false)
{

}

JobRunner::~JobRunner()
{
    qDebug() << "JobRunner::~JobRunner()";
}

int JobRunner::getProgress() const
{
    // sometimes simulation underestimate the number of iterations required
    // and progress can be greater than 100
    return m_progress < 100 ? m_progress : 100;
}

void JobRunner::start()
{
    qDebug() << "JobRunner::start() " << m_simulation;
    m_terminate_request_flag = false;
    emit started();

    if(m_simulation) {
        ProgressHandler_t progressHandler(new ProgressHandler());
        ProgressHandler::Callback_t callback = boost::bind(&JobRunner::similationProgressCallback, this, _1);
        progressHandler->setCallback(callback);
        m_simulation->setProgressHandler(progressHandler);

        m_job_status = Constants::STATUS_RUNNING;

        try {
            m_simulation->runSimulation();
            if(m_job_status != Constants::STATUS_CANCELED)
                m_job_status = Constants::STATUS_COMPLETED;
        }
        catch(const std::exception &ex)
        {
            m_job_status = Constants::STATUS_FAILED;
            m_progress=100;
            m_failure_message = QString("JobRunner::start() -> Simulation failed with exception throw:\n\n");

            m_failure_message.append(QString(ex.what()));
        }

    } else {
        m_job_status = Constants::STATUS_FAILED;
        m_progress=100;
        m_failure_message = QString("JobRunner::start() -> Error. Simulation doesn't exist.");
    }
    emit progressUpdate();
    emit finished();
}

//! Fake simulation function to mimic some hard work going on
void JobRunner::runFakeSimulation()
{
    qDebug() << "JobItem::runFakeSimulation()" << m_progress;
    if(m_progress < 100) {
        m_progress++;
        emit progressUpdate();
        QTimer::singleShot(100, this, SLOT(runFakeSimulation()));
    }
    if(m_progress >=100 || m_terminate_request_flag) {
        emit progressUpdate();
        emit finished();
    }
}

//! function which is called by the Simulation to report its progress
bool JobRunner::similationProgressCallback(int progress)
{
    if(progress >= m_progress) {
        m_progress = progress;
        emit progressUpdate();
    }

    return !m_terminate_request_flag;
}

//! set request for JobRunner to terminate underlying domain simulation
void JobRunner::terminate()
{
    qDebug() << "JobRunner::terminate()";
    m_terminate_request_flag = true;
    m_job_status = Constants::STATUS_CANCELED;
}
