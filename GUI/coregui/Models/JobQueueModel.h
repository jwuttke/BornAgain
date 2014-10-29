#ifndef JOBQUEUEMODEL_H
#define JOBQUEUEMODEL_H

#include "JobQueueData.h"
#include "JobItem.h"
#include <QAbstractListModel>
#include <QList>
#include <QModelIndex>
#include <QMap>

class JobItem;
class JobQueueItem;
class Simulation;
class SampleModel;
class SimulationModel;
class QXmlStreamWriter;
class QXmlStreamReader;
class QItemSelection;
class QThread;


namespace JobQueueXML
{
    const QString ModelTag("JobQueueModel");
    const QString ModelNameAttribute("Name");
    const QString JobTag("Job");
    const QString JobNameAttribute("Name");
    const QString JobBeginTimeAttribute("BeginTime");
    const QString JobEndTimeAttribute("EndTime");
    const QString JobCommentsAttribute("Comments");
    const QString JobStatusAttribute("Status");
    const QString JobProgressAttribute("Progress");
    const QString OutputDataTag("OutputData");
    const QString OutputDataNameAttribute("Name");
    const QString OutputDataXminAttribute("Xmin");
    const QString OutputDataXmaxAttribute("Xmax");
    const QString OutputDataYminAttribute("Ymin");
    const QString OutputDataYmaxAttribute("Ymax");
    const QString OutputDataZminAttribute("Zmin");
    const QString OutputDataZmaxAttribute("Zmax");
    const QString OutputDataLogzAttribute("Logz");
    const QString OutputDataInterpolatedAttribute("Interpolated");
    const QString OutputDataXtitleAttribute("Xtitle");
    const QString OutputDataYtitleAttribute("Ytitle");
    const QString MimeType("application/org.bornagainproject.jobqueue");
}


//! The model for all jobs in a queue. Contains JobQueueItem in a list.
//! Provides interface to access real JobItem objects.
class BA_CORE_API_ JobQueueModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit JobQueueModel(QObject *parent = 0);
    virtual ~JobQueueModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);

//    bool insertRows(int position, int rows, const QModelIndex &parent);
    bool removeRows(int position, int rows, const QModelIndex &parent);

    Qt::DropActions supportedDragActions() const { return Qt::MoveAction; }
    Qt::DropActions supportedDropActions() const { return Qt::MoveAction; }
    QStringList mimeTypes() const;
    QMimeData *mimeData(const QModelIndexList &indexes) const;
    bool dropMimeData(const QMimeData *data, Qt::DropAction action,
                      int row, int column, const QModelIndex &parent);

    QString addJob(QString jobName=QString(), Simulation *simulation=0, JobItem::RunPolicy run_policy = JobItem::SubmitOnly);
    QString addJob(JobItem *jobItem);

    void clear();

    void save(const QString &filename=QString());
    void writeTo(QXmlStreamWriter *writer);

    void load(const QString &filename=QString());
    void readFrom(QXmlStreamReader *reader);

    QString getName() const { return m_name; }
    void setName(QString name) { m_name = name; }

    QString getIdentifier(const QModelIndex &index) const;

    const JobItem *getJobItemForIndex(const QModelIndex &index) const;
    JobItem *getJobItemForIndex(const QModelIndex &index);

    QModelIndex getIndexForJobItem(const JobItem *item);

    JobQueueData *getJobQueueData() { return m_queue_data; }

signals:
    void selectionChanged(JobItem *item);
    void aboutToDeleteJobItem(JobItem *item);

public slots:
    void onJobItemIsModified(JobItem *);
    void onSelectionChanged( const QItemSelection&, const QItemSelection& );
    void runJob(const QModelIndex &index);
    void runJob(const QString &identifier);
    void cancelJob(const QModelIndex &index);
    void removeJob(const QModelIndex &index);

private:
    JobQueueData *m_queue_data;
    QString m_name;
    QList <JobQueueItem *> m_jobs;
};


#endif
