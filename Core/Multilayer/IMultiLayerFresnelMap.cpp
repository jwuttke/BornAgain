// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/IMultiLayerFresnelMap.cpp
//! @brief     Implements class IMultiLayerFresnelMap.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "IMultiLayerFresnelMap.h"
#include "MultiLayer.h"

IMultiLayerFresnelMap::IMultiLayerFresnelMap()
    : IFresnelMap{}
{}

IMultiLayerFresnelMap::~IMultiLayerFresnelMap() = default;

void IMultiLayerFresnelMap::setMultilayer(const MultiLayer& multilayer)
{
    mP_multilayer.reset(multilayer.clone());
}
