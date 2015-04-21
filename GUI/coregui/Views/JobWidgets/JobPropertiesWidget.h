// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/JobWidgets/JobPropertiesWidget.h
//! @brief     Defines class JobPropertiesWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef JOBPROPERTIESWIDGET_H
#define JOBPROPERTIESWIDGET_H

#include "WinDllMacros.h"
#include <QWidget>
#include <QMap>

class JobModel;
class JobItem;
class QTextEdit;
class QTabWidget;
class AwesomePropertyEditor;

//! Widget to show and change properties of currently selected JobItem
//! Left buttom corner of JobView
class BA_CORE_API_ JobPropertiesWidget : public QWidget
{
    Q_OBJECT
public:
    enum ETabId { JOB_PROPERTIES, JOB_COMMENTS };
    explicit JobPropertiesWidget(QWidget *parent = 0);

    void setModel(JobModel *model);

    QSize sizeHint() const { return QSize(64, 256); }
    QSize minimumSizeHint() const { return QSize(64, 64); }

public slots:    
    void setItem(JobItem *item);

private slots:
    void onPropertyChanged(const QString &property_name);

private:
    void updateItem(JobItem *item);

    JobModel *m_jobModel;
    JobItem *m_currentItem;
    QTabWidget *m_tabWidget;
    AwesomePropertyEditor *m_propertyEditor;
    QTextEdit *m_commentsEditor;
};

#endif
