#include "JobListToolBar.h"
#include <QStyle>
#include <QToolButton>
#include <QLabel>

//! main tool bar on top of SampleView window
JobListToolBar::JobListToolBar(QWidget *parent)
    : QToolBar(parent)
    , m_runJobButton(0)
    , m_removeJobButton(0)
{
    setMovable(false);

    const int size = style()->pixelMetric(QStyle::PM_SmallIconSize);
    setIconSize(QSize(size, size));
    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
    setMinimumSize(25, 25);

    setContentsMargins(0,0,0,0);

    // projections button
    m_runJobButton = new QToolButton;
    m_runJobButton->setText("Run Job");
    m_runJobButton->setIcon(QIcon(":/images/main_simulation.png"));
    m_runJobButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    m_runJobButton->setToolTip("Run currently selected job");
    connect(m_runJobButton, SIGNAL(clicked()), this, SIGNAL(runJob()));
    addWidget(m_runJobButton);

    // plot properties button
    m_removeJobButton = new QToolButton;
    m_removeJobButton->setText("Remove Job");
    m_removeJobButton->setIcon(QIcon(":/SampleDesigner/images/toolbar_recycle.png"));
    m_removeJobButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    m_removeJobButton->setToolTip("Remove currently selected job.");
    connect(m_removeJobButton, SIGNAL(clicked()), this, SIGNAL(removeJob()));
    addWidget(m_removeJobButton);
}

