// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/InstrumentWidgets/InstrumentSelectorWidget.cpp
//! @brief     Implements class InstrumentSelectorWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "InstrumentSelectorWidget.h"
#include "InstrumentModel.h"
#include "ParameterizedItem.h"
#include <QListView>
#include <QVBoxLayout>
#include <QPushButton>
#include <QMenu>
#include <QAction>
#include <QDebug>

InstrumentSelectorWidget::InstrumentSelectorWidget(InstrumentModel *model, QWidget *parent)
    : QWidget(parent)
    , m_instrumentModel(0)
    , m_listView(0)
{
    setMinimumSize(128, 400);
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);

    m_listView = new QListView;
    m_listView->setViewMode(QListView::IconMode);
    m_listView->setIconSize(QSize(96, 84));
    m_listView->setMovement(QListView::Static);
    m_listView->setMaximumWidth(200);
    m_listView->setSpacing(12);
    //m_listView->setModel(m_instrumentModel);

    m_listView->setObjectName("listView");
    m_listView->setStyleSheet(QString::fromUtf8("QListView#listView\n"
    "{\n"
    "   selection-background-color : rgb(98,100,105); \n"
    "   selection-color: rgb(255,255,255);\n"
    "   border: 1px solid rgb(98,100,105);\n"
    "}\n"
    ""));

    QVBoxLayout *verticaLayout = new QVBoxLayout;
    verticaLayout->setMargin(10);
    verticaLayout->setSpacing(10);
    verticaLayout->addWidget(m_listView, 3);

    setLayout(verticaLayout);

    setInstrumentModel(model);
}


void InstrumentSelectorWidget::setInstrumentModel(InstrumentModel *model)
{
    Q_ASSERT(model);
    Q_ASSERT(m_listView);

    if(model != m_instrumentModel) {
        if(m_instrumentModel) {
            disconnect(m_instrumentModel, SIGNAL(rowsInserted(const QModelIndex &, int, int)), this, SLOT(onRowsInserted(const QModelIndex &,int,int)));
        }
        m_instrumentModel = model;
        m_listView->setModel(model);

        connect(m_listView->selectionModel(),
            SIGNAL( selectionChanged(const QItemSelection&, const QItemSelection&) ),
            this,
            SIGNAL( selectionChanged(const QItemSelection&, const QItemSelection&) )
        );

    }
}


QItemSelectionModel *InstrumentSelectorWidget::getSelectionModel()
{
    return m_listView->selectionModel();
}


//! select last item if no selection exists
void InstrumentSelectorWidget::updateSelection()
{
    qDebug() << "InstrumentSelectorWidget::updateSelection()" << m_instrumentModel->rowCount(QModelIndex());
    if(!getSelectionModel()->hasSelection()) {
        QModelIndex itemIndex = m_instrumentModel->index(m_instrumentModel->rowCount(QModelIndex()) - 1,0,QModelIndex());
        qDebug() << "       InstrumentSelectorWidget::updateSelection()" << itemIndex;
        getSelectionModel()->select(itemIndex, QItemSelectionModel::Select);
    }
}


