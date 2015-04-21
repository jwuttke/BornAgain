// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/SampleView.h
//! @brief     Defines class SampleView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef SAMPLEMANAGER_H
#define SAMPLEMANAGER_H

#include "WinDllMacros.h"
#include "fancymainwindow.h"
#include <QWidget>
#include <QMainWindow>
#include <QDockWidget>
#include <QTreeView>
#include <QAction>
#include <QSignalMapper>
#include <QItemSelectionModel>


class SampleModel;
class InstrumentModel;
class SampleDesignerInterface;
class SampleDesigner;
class SampleToolBar;
class MaterialBrowser;


class BA_CORE_API_ SampleView : public Manhattan::FancyMainWindow
{
    Q_OBJECT

public:
    enum ESubWindows
    {
        WIDGET_BOX,         // drag & drop items
        SAMPLE_TREE,             // a tree view
        PROPERTY_EDITOR,    // property editor
        INFO,              // status/info display
        NUMBER_OF_SUB_WINDOWS
    };

    SampleView(SampleModel *sampleModel, InstrumentModel *instrumentModel, QWidget *parent = 0);
    virtual ~SampleView();

public slots:
    void resetToDefaultLayout();
    void addItem(const QString &item_name);
    void deleteItem();
    void setDockHeightForWidget(int height);
    void onWidgetCloseRequest();

protected slots:
    void showContextMenu(const QPoint &pnt);
    void setDirty(bool dirty=true) { setWindowModified(dirty); }
    void dockToMinMaxSizes();
    void onDockVisibilityChangeV2(bool status);

private:
    //! Stores sizes of dock widget
    struct DockSizeInfo {
        DockSizeInfo():m_dock(0){}
        QDockWidget *m_dock;
        QSize m_min_size;
        QSize m_max_size;
    };

    void initSubWindows();
    void initSelectionModel();
    void createActions();
    void connectSignals();
    void clearSignalMapper();
    void setCurrentIndex(const QModelIndex &index);

    SampleModel *getSampleModel();
    QTreeView *getTreeView();

   // MaterialBrowser *m_materialBrowser;  // material editor
    SampleDesigner *m_sampleDesigner;    // main sample view
    SampleToolBar *m_toolBar;            // toolbar
    QWidget *m_subWindows[NUMBER_OF_SUB_WINDOWS];
    QDockWidget *m_dockWidgets[NUMBER_OF_SUB_WINDOWS];

    QMap<QWidget *, QDockWidget *> m_widget_to_dock;
    QMap<QDockWidget *, QWidget *> m_dock_to_widget;

    QSignalMapper *m_add_item_mapper;
    QMap<QString, QAction *> m_add_action_map;
    QAction *m_delete_item_action;

    SampleModel *m_sampleModel;
    InstrumentModel *m_instrumentModel;
    QTreeView *m_tree_view;

    QItemSelectionModel *m_selection_model;

    DockSizeInfo m_dock_info;
};


#endif // SAMPLEMANAGER_H
