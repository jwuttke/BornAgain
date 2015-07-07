// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/InfoWidgets/ProjectLoadWarningDialog.cpp
//! @brief     Implements class ProjectLoadWarningDialog
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ProjectLoadWarningDialog.h"
#include "DesignerHelper.h"
#include "WarningMessageService.h"
#include "MessageContainer.h"
#include "GUIMessage.h"
#include <QBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QFrame>
#include <QTextEdit>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>

namespace {
const int top_panel_height = 80;
}

ProjectLoadWarningDialog::ProjectLoadWarningDialog(QWidget *parent, const WarningMessageService *messageService)
    : QDialog(parent)
    , m_messageService(messageService)
{
    setMinimumSize(256, 256);
    resize(480, 640);
    setWindowTitle("Problems encountered while loading project");
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setModal(true);

    QVBoxLayout *mainLayout = new QVBoxLayout;

    mainLayout->addWidget(createTopPanel());
    mainLayout->addWidget(createModelInfoPanel());
    mainLayout->addWidget(createExplanationPanel());
    mainLayout->addWidget(createDetailsPanel());

//    QPushButton *button = new QPushButton("Close", this);
//    button->setAutoDefault(false);
//    connect(button, SIGNAL(clicked()), this, SLOT(close()));

//    QHBoxLayout *buttonLayout = new QHBoxLayout;
//    buttonLayout->addStretch(1);
//    buttonLayout->setContentsMargins(4, 4, 4, 4);
//    buttonLayout->addWidget(button);


//    layout->setContentsMargins(0, 0, 0, 0);
    setLayout(mainLayout);
}

QWidget *ProjectLoadWarningDialog::createTopPanel()
{
    QWidget *result = new QWidget(this);
    QHBoxLayout *layout = new QHBoxLayout;

    // ---
    QLabel *warningLabel = new QLabel;
    warningLabel->setPixmap(QPixmap(":/images/warning_64x64.png"));

    QWidget *warningWidget = new QWidget;
    warningWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    warningWidget->resize(top_panel_height,top_panel_height);
    QHBoxLayout *warningWidgetLayout = new QHBoxLayout;
    warningWidgetLayout->addWidget(warningLabel);
    warningWidget->setLayout(warningWidgetLayout);

    QFont titleFont;
    titleFont.setPointSize(DesignerHelper::getSectionFontSize());
    titleFont.setBold(true);

    QLabel *messageLabel = new QLabel();
    messageLabel->setFont(titleFont);
    messageLabel->setText("Some parts of the project were not loaded correctly.");
    messageLabel->setWordWrap(true);

    layout->addWidget(warningWidget);
    layout->addWidget(messageLabel);

    result->setLayout(layout);
    return result;
}

QWidget *ProjectLoadWarningDialog::createModelInfoPanel()
{
    QWidget *result = new QWidget(this);
    QHBoxLayout *layout = new QHBoxLayout;

    QFrame* line = new QFrame();
    line->setFrameShape(QFrame::VLine);
    line->setFrameShadow(QFrame::Sunken);


    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->addWidget(new QLabel("Material Model"), 0, 0);
    gridLayout->addWidget(new QLabel("OK"), 0, 1);
    gridLayout->addWidget(new QLabel("Instrument Model"), 1, 0);
    gridLayout->addWidget(new QLabel("OK"), 1, 1);
    gridLayout->addWidget(new QLabel("Sample Model"), 2, 0);
    gridLayout->addWidget(new QLabel("OK"), 2, 1);
    gridLayout->addWidget(new QLabel("Job Model"), 3, 0);
    gridLayout->addWidget(new QLabel("OK"), 3, 1);

    layout->addWidget(line);
    layout->addLayout(gridLayout);
    layout->addWidget(new QWidget);

    result->setLayout(layout);
    return result;
}

QWidget *ProjectLoadWarningDialog::createExplanationPanel()
{
    QWidget *result = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout;

    QFont titleFont;
    titleFont.setPointSize(DesignerHelper::getSectionFontSize());
    titleFont.setBold(true);

    QLabel *whyLabel = new QLabel;
    whyLabel->setFont(titleFont);
    whyLabel->setText("Why did this happen to me?");

    QLabel *explanationLabel = new QLabel;
    QString explanationText("Given project was created using BornAgain version 1.0 ");
    explanationText.append("which is different from version 2.0 you are currently using. ");
    explanationText.append("At the moment we provide only limited support for import from older versions. ");
    explanationLabel->setText(explanationText);
    explanationLabel->setWordWrap(true);

    QLabel *whatLabel = new QLabel;
    whatLabel->setFont(titleFont);
    whatLabel->setText("What to do?");

    QLabel *adviceLabel = new QLabel;
    QString adviceText("Check parameters of your items and re-enter uninitialized values. ");
    adviceText.append("Use detailed log below to get a hint what went wrong.");
    adviceText.append("When save you project and work as normal.");
    adviceLabel->setText(adviceText);
    adviceLabel->setWordWrap(true);

    layout->addWidget(whyLabel);
    layout->addWidget(explanationLabel);
    layout->addWidget(whatLabel);
    layout->addWidget(adviceLabel);

    result->setLayout(layout);
    return result;
}

QWidget *ProjectLoadWarningDialog::createDetailsPanel()
{
    QWidget *result = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout;

    QFont titleFont;
    titleFont.setPointSize(DesignerHelper::getSectionFontSize());
    titleFont.setBold(true);

    QLabel *detailsLabel = new QLabel;
    detailsLabel->setFont(titleFont);
    detailsLabel->setText("Details");

    layout->addWidget(detailsLabel);
    layout->addWidget(createTableWidget());

    result->setLayout(layout);
    return result;


}

//! Creates QTableWidget and fills it with error messages
QTableWidget *ProjectLoadWarningDialog::createTableWidget()
{
    Q_ASSERT(m_messageService);
    QTableWidget *result = new QTableWidget;

    result->setRowCount(getNumberOfRows());
    result->setColumnCount(getHeaderLabels().size());
    result->setHorizontalHeaderLabels(getHeaderLabels());
    result->verticalHeader()->setVisible(false);
    result->horizontalHeader()->setStretchLastSection(true);

    int rowCount(0);
    for(WarningMessageService::container_t::const_iterator it=m_messageService->begin(); it!=m_messageService->end(); ++it) {
        const MessageContainer *messageContainer = it.value();
        for(MessageContainer::const_iterator it=messageContainer->begin(); it!=messageContainer->end(); ++it) {
            const GUIMessage *guiMessage = (*it);

            result->setItem(rowCount, 0, new QTableWidgetItem(guiMessage->getSenderName()));
            result->setItem(rowCount, 1, new QTableWidgetItem(guiMessage->getMessageType()));
            result->setItem(rowCount, 2, new QTableWidgetItem(guiMessage->getMessageDescription()));
            ++rowCount;

        }
    }

    return result;
}

//! Returns number of rows in table with error messages, each row represents an error message
int ProjectLoadWarningDialog::getNumberOfRows() const
{
    Q_ASSERT(m_messageService);
    int result(0);
    for(WarningMessageService::container_t::const_iterator it=m_messageService->begin(); it!=m_messageService->end(); ++it) {
        result += it.value()->size();
    }
    return result;
}

//! Returns labels for table header
QStringList ProjectLoadWarningDialog::getHeaderLabels() const
{
    QStringList result;
    result << "Sender" << "Warning" << "Description";
    return result;
}


