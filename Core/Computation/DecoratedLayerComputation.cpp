// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/DecoratedLayerComputation.cpp
//! @brief     Implements class DecoratedLayerComputation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "DecoratedLayerComputation.h"
#include "Exceptions.h"
#include "IInterferenceFunctionStrategy.h"
#include "Layer.h"
#include "LayerSpecularInfo.h"
#include "LayerStrategyBuilder.h"
#include "Logger.h"
#include "MultiLayer.h"
#include "ProgressHandler.h"
#include "SimulationElement.h"

DecoratedLayerComputation::DecoratedLayerComputation(const Layer* p_layer, size_t layout_index)
    : mp_layer(p_layer), m_layout_index(layout_index)
{}

void DecoratedLayerComputation::setSpecularInfo(const LayerSpecularInfo& specular_info)
{
    if (&specular_info != mP_specular_info.get())
        mP_specular_info.reset(specular_info.clone());
}

//! Computes scattering intensity for given range of simulation elements.
void DecoratedLayerComputation::eval(
    const SimulationOptions& options,
    ProgressHandler* progress,
    bool polarized,
    const MultiLayer& sample,
    const std::vector<SimulationElement>::iterator& begin_it,
    const std::vector<SimulationElement>::iterator& end_it) const
{
    LayerStrategyBuilder builder(*mp_layer, sample, options, m_layout_index,
                                 mP_specular_info.get());
    const std::unique_ptr<const IInterferenceFunctionStrategy> p_strategy(builder.createStrategy());
    double total_surface_density = mp_layer->getTotalParticleSurfaceDensity(m_layout_index);

    for (std::vector<SimulationElement>::iterator it = begin_it; it != end_it; ++it) {
        if (!progress->alive())
            return;
        double alpha_f = it->getAlphaMean();
        size_t n_layers = mp_layer->getNumberOfLayers();
        if (n_layers > 1 && alpha_f < 0)
            continue;
        // each ffdwba: one call to getOutCoeffs
        if (polarized)
            it->setIntensity(p_strategy->evaluatePol(*it) * total_surface_density);
        else
            it->setIntensity(p_strategy->evaluate(*it) * total_surface_density);
        stepProgress(progress);
    }
}
