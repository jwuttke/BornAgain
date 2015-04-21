// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/WelcomeView.h
//! @brief     Defines class WelcomeView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef WELCOMEVIEW_H
#define WELCOMEVIEW_H

#include "WinDllMacros.h"
#include <QWidget>

class QPushButton;
class MainWindow;
class ProjectManager;
class QSignalMapper;
class QVBoxLayout;
class FancyLabel;

class BA_CORE_API_ WelcomeView : public QWidget
{
    Q_OBJECT
public:
    WelcomeView(MainWindow *parent);

public slots:
    void onWebLinkClicked(const QUrl &url);
    void onNewUser();
    void updateRecentProjectPanel();

private:
    void clearLayout(QLayout* layout, bool deleteWidgets = true);
    void generateRecentProjectList();
    QString getCurrentProjectFancyName();
    void setCurrentProjectName(const QString &name);

    QPushButton *m_newProjectButton;
    QPushButton *m_openProjectButton;
    QPushButton *m_newUsertButton;
    MainWindow *m_mainWindow;
    ProjectManager *m_projectManager;
    QSignalMapper *m_signalMapper;
    QVBoxLayout *m_recentProjectLayout;
    FancyLabel *m_currentProName;
};

#endif // WELCOMEVIEW_H
