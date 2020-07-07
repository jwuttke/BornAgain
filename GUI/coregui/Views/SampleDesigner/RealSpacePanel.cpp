// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SampleDesigner/RealSpacePanel.cpp
//! @brief     Implements class RealSpacePanel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/SampleDesigner/RealSpacePanel.h"
#ifdef BORNAGAIN_OPENGL
#include "GUI/coregui/Views/RealSpaceWidgets/RealSpaceWidget.h"
#endif
#include <QVBoxLayout>

RealSpacePanel::RealSpacePanel(SampleModel* sampleModel, QItemSelectionModel* selectionModel,
                               QWidget* parent)
    : QWidget(parent), m_realSpaceWidget(nullptr)
{
    setWindowTitle("Real Space");
    setObjectName("Sample3DPanel");

    auto layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);

#ifdef BORNAGAIN_OPENGL
    m_realSpaceWidget = new RealSpaceWidget(sampleModel, selectionModel, this);
    layout->addWidget(m_realSpaceWidget);
#endif

    setLayout(layout);
}

QSize RealSpacePanel::sizeHint() const
{
    return QSize(300, 300);
}
