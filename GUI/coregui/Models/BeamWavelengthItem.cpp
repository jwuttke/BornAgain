// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/BeamWavelengthItem.cpp
//! @brief     Implements class BeamWavelengthItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "BeamWavelengthItem.h"

BeamWavelengthItem::BeamWavelengthItem(ParameterizedItem *parent)
    : BeamDistributionItem(Constants::BeamWavelengthType, parent)
{
    setItemName(Constants::BeamWavelengthType);
    setPropertyAttribute(BeamDistributionItem::P_CACHED_VALUE, PropertyAttribute(PropertyAttribute::HIDDEN, AttLimits::lowerLimited(1e-4), 4));
    setRegisteredProperty(BeamDistributionItem::P_CACHED_VALUE, 0.1);
}
