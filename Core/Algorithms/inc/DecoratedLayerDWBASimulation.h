// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/inc/DecoratedLayerDWBASimulation.h
//! @brief     Defines class DecoratedLayerDWBASimulation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef DECORATEDLAYERDWBASIMULATION_H_
#define DECORATEDLAYERDWBASIMULATION_H_

#include "LayerDWBASimulation.h"
#include "IInterferenceFunctionStrategy.h"

class Layer;

//! @class DecoratedLayerDWBASimulation
//! @ingroup algorithms_internal
//! @brief Calculates scattering cross sections in DWBA for a layer with particles in/on it

class BA_CORE_API_ DecoratedLayerDWBASimulation : public LayerDWBASimulation
{
public:
    DecoratedLayerDWBASimulation(const Layer *p_layer, size_t layout_index=0);
    virtual ~DecoratedLayerDWBASimulation();

    DecoratedLayerDWBASimulation *clone() const
    {
        throw NotImplementedException("DecoratedLayerDWBASimulation::clone() -> "
                                      "Error: not implemented.");
    }

    virtual void init(const Simulation& simulation);

    virtual void run();
protected:
    virtual void runProtected();

private:
    IInterferenceFunctionStrategy *createAndInitStrategy() const;
    void calculateCoherentIntensity(const IInterferenceFunctionStrategy *p_strategy);
    size_t m_layout_index;

};

#endif /* DECORATEDLAYERDWBASIMULATION_H_ */
