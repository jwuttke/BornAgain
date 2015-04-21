// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/InfoWidgets/PySampleWidget.cpp
//! @brief     Implements class PySampleWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "PythonScriptWidget.h"
#include "PythonSyntaxHighlighter.h"
#include "SampleModel.h"
#include "InstrumentModel.h"
#include "DesignerHelper.h"
#include "Simulation.h"
#include "PyGenTools.h"
#include "DomainSimulationBuilder.h"
#include "WarningSignWidget.h"
#include "projectdocument.h"
#include "projectmanager.h"
#include <QScrollBar>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QToolBar>
#include <QToolButton>
#include <QTextEdit>
#include <QStyle>
#include <QPushButton>
#include <QDir>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QStandardPaths>
#include <boost/scoped_ptr.hpp>


PythonScriptWidget::PythonScriptWidget(QWidget *parent, ProjectManager *projectManager)
    : QDialog(parent)
    , m_toolBar(0)
    , m_textEdit(0)
    , m_sampleModel(0)
    , m_instrumentModel(0)
    , m_warningSign(0)
    , m_projectManager(projectManager)
{
    setWindowTitle("Python Script View");
    setMinimumSize(128, 128);
    resize(512, 400);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    m_toolBar = new QToolBar;
    m_toolBar->setFixedHeight(28);
    m_toolBar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    const int size = style()->pixelMetric(QStyle::PM_SmallIconSize);
    m_toolBar->setIconSize(QSize(size, size));
    m_toolBar->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

    QPushButton *exportToFileButton = new QPushButton;
    exportToFileButton->setText("Save to file");
    exportToFileButton->setToolTip("Opens dialog to save given script into the file");
    connect(exportToFileButton, SIGNAL(clicked()), this, SLOT(onExportToFileButton()));
    exportToFileButton->setAutoDefault(false);
    m_toolBar->addWidget(exportToFileButton);

    m_textEdit = new QTextEdit;
    m_textEdit->setReadOnly(true);
    QFont textFont("Monospace");
    m_textEdit->setFont(textFont);
    m_textEdit->setFontPointSize(DesignerHelper::getPythonEditorFontSize());
    m_textEdit->setLineWrapMode(QTextEdit::NoWrap);
    PythonSyntaxHighlighter *highlighter = new PythonSyntaxHighlighter(m_textEdit->document());
    Q_UNUSED(highlighter);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(m_toolBar);
    mainLayout->addWidget(m_textEdit);

    setLayout(mainLayout);

    setAttribute(Qt::WA_DeleteOnClose, true);
}

PythonScriptWidget::~PythonScriptWidget()
{
    qDebug() << "PythonScriptWidget::~PythonScriptWidget()";
    delete m_sampleModel;
    delete m_instrumentModel;
}

void PythonScriptWidget::generatePythonScript(SampleModel *sampleModel, InstrumentModel *instrumentModel)
{
    delete m_sampleModel;
    m_sampleModel = sampleModel;

    delete m_instrumentModel;
    m_instrumentModel = instrumentModel;

    delete m_warningSign;
    m_warningSign = 0;

    try{
        boost::scoped_ptr<Simulation> simulation(
            DomainSimulationBuilder::getSimulation(sampleModel, instrumentModel));
        QString code = QString::fromStdString(PyGenTools::genPyScript(simulation.get()));
        m_textEdit->clear();
        m_textEdit->setText(code);
    } catch(const std::exception &ex) {
        m_warningSign = new WarningSignWidget(this);
        m_warningSign->setWarningMessage(QString::fromStdString(ex.what()));
        QPoint pos = getPositionForWarningSign();
        m_warningSign->setPosition(pos.x(), pos.y());
        m_warningSign->show();
    }
}

//! adjusts position of warning label on widget move
void PythonScriptWidget::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    if(m_warningSign) {
        QPoint pos = getPositionForWarningSign();
        m_warningSign->setPosition(pos.x(),pos.y());
    }
}

void PythonScriptWidget::onExportToFileButton()
{
    QString dirname = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);

    if(m_projectManager) {
        ProjectDocument *document  = m_projectManager->getDocument();
        if(document->hasValidNameAndPath()) {
            dirname = document->getProjectDir();
        }
    }

    QString file_name = QFileDialog::getSaveFileName(this, tr("Select file"), dirname,
                            tr("Python scipts (*.py)"), 0,
                            QFileDialog::DontResolveSymlinks);

    if(file_name.isEmpty()) return;

    QFile file(file_name);
    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << "PythonScriptWidget::onExportToFileButton: Error! Can't save file";
        QMessageBox warning_dialog(this);
        warning_dialog.setIcon(QMessageBox::Warning);
        warning_dialog.setText(tr("File could not be opened for writing!"));
        warning_dialog.exec();
        return;
    }
    QTextStream out(&file);
    out << m_textEdit->toPlainText();
    file.close();
    raise();
}

//! Returns position for warning sign at the bottom left corner of the editor. The position will
//! be adjusted according to the visibility of scroll bars
QPoint PythonScriptWidget::getPositionForWarningSign()
{
    const int warning_sign_xpos = 38;
    const int warning_sign_ypos = 38;

    int x = width()-warning_sign_xpos;
    int y = height()-warning_sign_ypos;

    if(QScrollBar *horizontal = m_textEdit->horizontalScrollBar()) {
        if(horizontal->isVisible())
            y -= horizontal->height();
    }

    if(QScrollBar *vertical = m_textEdit->verticalScrollBar()) {
        if(vertical->isVisible())
            x -= vertical->width();
    }

    return QPoint(x, y);
}

