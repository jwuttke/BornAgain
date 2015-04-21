// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/NJobModel.h
//! @brief     Defines class NJobModel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //
#ifndef JOBMODEL_H
#define JOBMODEL_H

#include "SessionModel.h"
#include "JobQueueData.h"
class JobItem;
class SampleModel;
class InstrumentModel;
class QItemSelection;

class BA_CORE_API_ JobModel : public SessionModel
{
    Q_OBJECT

public:
    explicit JobModel(QObject *parent = 0);
    ~JobModel();

    JobQueueData *getJobQueueData() { return m_queue_data; }

    const JobItem *getJobItemForIndex(const QModelIndex &index) const;
    JobItem *getJobItemForIndex(const QModelIndex &index);

    JobItem *getJobItemForIdentifier(const QString &identifier);

    JobItem *addJob(SampleModel *sampleModel, InstrumentModel *instrumentModel,
            const QString &run_policy = QString(), int numberOfThreads=-1);

signals:
    void selectionChanged(JobItem *item);
    void aboutToDeleteJobItem(JobItem *item);
    void focusRequest(JobItem *item);
    void globalProgress(int);

public slots:
    void runJob(const QModelIndex &index);
    void cancelJob(const QModelIndex &index);
    void removeJob(const QModelIndex &index);
    void onSelectionChanged( const QItemSelection &selected, const QItemSelection &deselected);
    void onFocusRequest(const QString &identifier);

private:
    QString generateJobName();
    QString generateJobIdentifier();

    JobQueueData *m_queue_data;
};

#endif
