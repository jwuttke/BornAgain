// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Simulation/MultiLayerRoughnessDWBASimulation.h
//! @brief     Defines class MultiLayerRoughnessDWBASimulation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef MULTILAYERROUGHNESSDWBASIMULATION_H
#define MULTILAYERROUGHNESSDWBASIMULATION_H

#include "DWBASimulation.h"
#include "Complex.h"

class LayerSpecularInfo;
class MultiLayer;

//! Computes the diffuse reflection from the rough interfaces of a multilayer.
//! Controlled by MultiLayerDWBASimulation.
//! @ingroup algorithms_internal

class BA_CORE_API_ MultiLayerRoughnessDWBASimulation : public DWBASimulation
{
public:
    MultiLayerRoughnessDWBASimulation(const MultiLayer* p_multi_layer);
    ~MultiLayerRoughnessDWBASimulation() final;
    MultiLayerRoughnessDWBASimulation* clone() const final;

    void run() final;

    //! Sets magnetic reflection/transmission info for specific layer
    void setSpecularInfo(size_t i_layer, const LayerSpecularInfo& specular_info);

    // evaluate
    double evaluate(const SimulationElement& sim_element);

protected:
    void runProtected() final;

    complex_t get_refractive_term(size_t ilayer) const;
    complex_t get_sum8terms(size_t ilayer, const SimulationElement& sim_element);

    MultiLayer* mp_multi_layer;
    std::vector<LayerSpecularInfo*> mp_specular_info_vector;
};

#endif // MULTILAYERROUGHNESSDWBASIMULATION_H
