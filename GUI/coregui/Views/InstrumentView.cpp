// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/InstrumentView.cpp
//! @brief     Implements class InstrumentView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "InstrumentView.h"
#include "InstrumentModel.h"
#include "InstrumentSelectorWidget.h"
#include "InstrumentEditorWidget.h"
#include "InstrumentItem.h"
#include "styledbar.h"
#include "minisplitter.h"
#include <QBoxLayout>
#include <QListView>
#include <QStackedWidget>
#include <QPushButton>
#include <QToolButton>
#include <QMenu>
#include <QAction>
#include <QDebug>
#include <QComboBox>
#include <QToolBar>
#include <QRegExp>


InstrumentView::InstrumentView(InstrumentModel *model, QWidget *parent)
    : QWidget(parent)
    , m_instrumentModel(model)
    , m_toolBar(new QToolBar(this))
    , m_instrumentSelector(new InstrumentSelectorWidget(m_instrumentModel, this))
    , m_stackWidget(new QStackedWidget)
    , m_addInstrumentAction(0)
    , m_removeInstrumentAction(0)
    , m_addInstrumentButton(0)
    , m_removeInstrumentButton(0)
{
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);

    QHBoxLayout *horizontalLayout = new QHBoxLayout;
    horizontalLayout->addWidget(m_instrumentSelector);
    horizontalLayout->addWidget(m_stackWidget, 1);

    mainLayout->addWidget(m_toolBar);
    mainLayout->addLayout(horizontalLayout);
    setLayout(mainLayout);

    connect(m_instrumentSelector,
        SIGNAL( selectionChanged(const QItemSelection&, const QItemSelection&) ),
        this,
        SLOT( onSelectionChanged(const QItemSelection&, const QItemSelection&) )
        );

    connect(m_instrumentModel, SIGNAL(modelAboutToBeReset()), this, SLOT(resetView()));
    connect(m_instrumentModel, SIGNAL(rowsAboutToBeRemoved(QModelIndex, int,int)), this, SLOT(onRowsAboutToBeRemoved(QModelIndex,int,int)));

    createActions();

    if(m_instrumentModel->rowCount(QModelIndex()) == 0)
        onAddInstrument();

    updateView();
}


void InstrumentView::updateView()
{
    qDebug() << "InstrumentView::updateView()";
    m_instrumentSelector->updateSelection();
}


void InstrumentView::resetView()
{
    qDebug() << "InstrumentView::resetView()";

    QMap<ParameterizedItem *, InstrumentEditorWidget *>::iterator it = m_instrumentToEditor.begin();
    while(it!=m_instrumentToEditor.end()) {
        m_stackWidget->removeWidget(it.value());
        delete it.value();
        ++it;
    }
    m_instrumentToEditor.clear();
    m_name_to_copy.clear();
}


void InstrumentView::onSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected )
{
    qDebug() << "InstrumentView::onSelectionChanged()" << selected << deselected;
    if(selected.indexes().isEmpty()) {
        qDebug() << "       InstrumentView::onSelectionChanged() -> no selected" << selected << deselected;
        return;
    }

    ParameterizedItem *instrument = m_instrumentModel->itemForIndex(selected.indexes().back());
    qDebug() << "InstrumentView::onSelectionChanged()" << instrument->itemName();

    InstrumentEditorWidget *widget = m_instrumentToEditor[instrument];

    if( !widget) {
        widget = new InstrumentEditorWidget();
        widget->setInstrumentItem(instrument);
        m_stackWidget->addWidget(widget);
        m_instrumentToEditor[instrument] = widget;
    }
    m_stackWidget->setCurrentWidget(widget);

}


void InstrumentView::onAddInstrument()
{
    qDebug() << "InstrumentView::onAddInstrument()";
    ParameterizedItem *instrument = m_instrumentModel->insertNewItem(Constants::InstrumentType);
    instrument->setItemName(getNewInstrumentName("Default GISAS"));
    m_instrumentModel->insertNewItem(Constants::DetectorType, m_instrumentModel->indexOfItem(instrument));
    m_instrumentModel->insertNewItem(Constants::BeamType, m_instrumentModel->indexOfItem(instrument));
    QModelIndex itemIndex = m_instrumentModel->indexOfItem(instrument);
    qDebug() << "       InstrumentView::onAddInstrument() -> clearing selection";
    m_instrumentSelector->getSelectionModel()->clearSelection();
    qDebug() << "       InstrumentView::onAddInstrument() -> clearing selection -> done.";
    m_instrumentSelector->getSelectionModel()->select(itemIndex, QItemSelectionModel::Select);
}


void InstrumentView::onRemoveInstrument()
{
    qDebug() << "InstrumentView::onRemoveInstrument()";
    QModelIndex currentIndex = m_instrumentSelector->getSelectionModel()->currentIndex();
    qDebug() << "InstrumentView::onRemoveInstrument()" <<  currentIndex;
    if(currentIndex.isValid())
        m_instrumentModel->removeRows(currentIndex.row(), 1, QModelIndex());
}


void InstrumentView::onRowsAboutToBeRemoved(QModelIndex parent, int first, int /* last */)
{
    qDebug() << "InstrumentView::onRowsAboutToBeRemoved()";
    ParameterizedItem *item = m_instrumentModel->itemForIndex(m_instrumentModel->index(first,0, parent));
    Q_ASSERT(item);
    InstrumentEditorWidget *widget = m_instrumentToEditor[item];
    Q_ASSERT(widget);

    QMap<ParameterizedItem *, InstrumentEditorWidget *>::iterator it = m_instrumentToEditor.begin();
    while(it!=m_instrumentToEditor.end()) {
        if(it.value() == widget) {
            it = m_instrumentToEditor.erase(it);
        } else {
            ++it;
        }
    }

    m_stackWidget->removeWidget(widget);
    delete widget;
}


void InstrumentView::createActions()
{
    m_addInstrumentButton = new QToolButton;
    m_addInstrumentButton->setText("Add instrument");
    m_addInstrumentButton->setIcon(QIcon(":/images/toolbar_newitem.png"));
    m_addInstrumentButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    m_addInstrumentButton->setToolTip("Add new instrument");
    connect(m_addInstrumentButton, SIGNAL(clicked()), this, SLOT(onAddInstrument()));
    m_toolBar->addWidget(m_addInstrumentButton);

    m_toolBar->addWidget(new QLabel(" "));
    m_toolBar->addSeparator();
    m_toolBar->addWidget(new QLabel(" "));

    m_removeInstrumentButton = new QToolButton;
    m_removeInstrumentButton->setText("Remove instrument");
    m_removeInstrumentButton->setIcon(QIcon(":/SampleDesigner/images/toolbar_recycle.png"));
    m_removeInstrumentButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    m_removeInstrumentButton->setToolTip("Remove currently selected instrument");
    connect(m_removeInstrumentButton, SIGNAL(clicked()), this, SLOT(onRemoveInstrument()));
    m_toolBar->addWidget(m_removeInstrumentButton);

    m_toolBar->addWidget(new QLabel(" "));
    m_toolBar->addSeparator();
    m_toolBar->addWidget(new QLabel(" "));

    m_addInstrumentAction = new QAction(QIcon(":/images/toolbar_newitem_dark.png"), tr("Add new instrument"), this);
    connect(m_addInstrumentAction, SIGNAL(triggered()), this, SLOT(onAddInstrument()));

    m_removeInstrumentAction = new QAction(QIcon(":/SampleDesigner/images/toolbar_recycle_dark.png"), tr("Remove currently selected instrument"), this);
    connect(m_removeInstrumentAction, SIGNAL(triggered()), this, SLOT(onRemoveInstrument()));

    Q_ASSERT(m_instrumentSelector->getListView());
    m_instrumentSelector->getListView()->setContextMenuPolicy(Qt::ActionsContextMenu);
    m_instrumentSelector->getListView()->addAction(m_addInstrumentAction);
    m_instrumentSelector->getListView()->addAction(m_removeInstrumentAction);
}


//! returns name of instrument which is based on suggested name
//! If "Default GISAS" name already exists, then "Default GISAS (2)" will be proposed.
QString InstrumentView::getNewInstrumentName(const QString &name)
{
    updateMapOfNames();

    int ncopies = m_name_to_copy[name];
    qDebug() << "   InstrumentView::getNewInstrumentName()" << ncopies;
    if(ncopies == 0) {
        m_name_to_copy[name]=1;
        return name;
    }
    else {
        m_name_to_copy[name]++;
        return QString("%1 (%2)").arg(name).arg(m_name_to_copy[name]);
    }
}


//! construct map of instrument names defined in the model together with number
//! of copies
void InstrumentView::updateMapOfNames()
{

    m_name_to_copy.clear();
    QModelIndex parentIndex;
    for( int i_row = 0; i_row < m_instrumentModel->rowCount( parentIndex ); ++i_row) {
        QModelIndex itemIndex = m_instrumentModel->index( i_row, 0, parentIndex );
        QString name =  m_instrumentModel->itemForIndex(itemIndex)->itemName();
        int ncopy(1);
        QRegExp regexp("\\((.*)\\)");
        if(regexp.indexIn(name) >= 0) {
            ncopy = regexp.cap(1).toInt();
        }
        name.replace(regexp.cap(0),"");
        name = name.trimmed();
        m_name_to_copy[name] = ncopy;
//        qDebug() << " ";
//        qDebug() << "XXXXXXXXXXXXXXXX" << name << ncopy << regexp.cap(0);
    }
}

