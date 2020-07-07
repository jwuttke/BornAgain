// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SampleDesigner/MesoCrystalView.cpp
//! @brief     Implements class MesoCrystalView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/SampleDesigner/MesoCrystalView.h"
#include "GUI/coregui/Models/MesoCrystalItem.h"
#include "GUI/coregui/Models/ParticleItem.h"
#include "GUI/coregui/Models/SessionItem.h"
#include "GUI/coregui/Views/SampleDesigner/DesignerHelper.h"
#include "GUI/coregui/utils/StyleUtils.h"

MesoCrystalView::MesoCrystalView(QGraphicsItem* parent) : ConnectableView(parent)
{
    setName(Constants::MesoCrystalType);
    setColor(DesignerHelper::getDefaultParticleColor());
    setRectangle(DesignerHelper::getDefaultBoundingRect(Constants::ParticleCoreShellType));
    addPort("out", NodeEditorPort::OUTPUT, NodeEditorPort::FORM_FACTOR)
        ->setToolTip(QStringLiteral("Connect to the ParticleLayout"));
    addPort("basis", NodeEditorPort::INPUT, NodeEditorPort::FORM_FACTOR)
        ->setToolTip(QStringLiteral("Connect basis particles"));
    addPort("transformation", NodeEditorPort::INPUT, NodeEditorPort::TRANSFORMATION)
        ->setToolTip(QStringLiteral("Connect rotation to this port, if necessary"));
    m_label_vspace = StyleUtils::SizeOfLetterM().height()*2.5;
}

void MesoCrystalView::addView(IView* childView, int /* row */)
{
    int index = 0;
    if (this->getItem()->tagFromItem(childView->getItem()) == ParticleItem::T_TRANSFORMATION)
        index = 1;
    connectInputPort(dynamic_cast<ConnectableView*>(childView), index);
}
