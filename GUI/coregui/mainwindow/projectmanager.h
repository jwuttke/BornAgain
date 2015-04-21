// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/mainwindow/projectmanager.h
//! @brief     Defines class ProjectManager
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef PROJECTMANAGER_H
#define PROJECTMANAGER_H

#include "WinDllMacros.h"
#include <QObject>
#include <QString>
#include <QStringList>
class MainWindow;
class ProjectDocument;
class QSettings;

//! handles activity related to opening/save projects
class BA_CORE_API_ ProjectManager : public QObject
{
    Q_OBJECT
public:
    ProjectManager(MainWindow *parent);
    ~ProjectManager();

    void createNewProject();
    bool closeCurrentProject();

    void readSettings(QSettings *settings);
    void writeSettings(QSettings *settings);

    QStringList getRecentProjects();

    ProjectDocument *getDocument() { return m_project_document; }

signals:
    void modified();

public slots:
    void clearRecentProjects();
    void onDocumentModified();
    bool saveProject();
    bool saveProjectAs();
    void openProject(QString fileName = QString());
    void newProject();

//    bool saveModifiedProject();

private:
//    ProjectDocument *createNewProject();
    void addToRecentProjects();

    QString getDefaultProjectPath();
    QString getUntitledProjectName();

    MainWindow *m_mainWindow;

    ProjectDocument *m_project_document;

    QString m_defaultProjectPath;
    QStringList m_recentProjects;

};


#endif
