// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/inc/LayerStrategyBuilder.h
//! @brief     Defines classes LayerStrategyBuilder, FormFactorInfo.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef LAYERSTRATEGYBUILDER_H_
#define LAYERSTRATEGYBUILDER_H_

#include "SimulationParameters.h"
#include "SafePointerVector.h"
#include "ICloneable.h"
#include "Types.h"
#include "IMaterial.h"

class FormFactorInfo;
class IInterferenceFunction;
class IInterferenceFunctionStrategy;
class Layer;
class Simulation;
class ParticleInfo;
class IFormFactor;
class LayerSpecularInfo;



//! @class LayerStrategyBuilder
//! @ingroup algorithms_internal
//! @brief Methods to generate a simulation strategy for decorated Layer SimulationParameters

class BA_CORE_API_ LayerStrategyBuilder
{
public:
    LayerStrategyBuilder(
        const Layer& decorated_layer,
        const Simulation& simulation,
        const SimulationParameters& sim_params,
        size_t layout_index);

    virtual ~LayerStrategyBuilder();

    //! Sets reflection/transmission map for DWBA calculation
    void setRTInfo(const LayerSpecularInfo &specular_info);

    //! Creates a strategy object which is able to calculate the scattering for fixed k_f
    virtual IInterferenceFunctionStrategy *createStrategy();

protected:
    Layer *mp_layer;                            //!< decorated layer
    Simulation *mp_simulation;                  //!< simulation
    SimulationParameters m_sim_params;          //!< simulation parameters
    LayerSpecularInfo *mp_specular_info; //!< R and T coefficients for DWBA
    size_t m_layout_index; //!< index for the layout to be used in the layer

private:
    //! determines if the form factors need to be matrix valued
    bool requiresMatrixFFs() const;
    //! collect the formfactor info of all particles in the decoration and decorate
    //! these for DWBA when needed
    void collectFormFactorInfos();
    //! collect the interference functions
    void collectInterferenceFunctions();
    //! retrieve wavelength from simulation
    double getWavelength();
    //! Creates formfactor info for single particle
    FormFactorInfo *createFormFactorInfo(
        const ParticleInfo *p_particle_info,
        const IMaterial *p_ambient_material,
        complex_t factor) const;

    SafePointerVector<FormFactorInfo> m_ff_infos;
    SafePointerVector<IInterferenceFunction> m_ifs;
};


//! @class FormFactorInfo
//! @ingroup formfactors_internal
//! @brief The %FormFactorInfo holds information about particle position and abundance

class BA_CORE_API_ FormFactorInfo : public ICloneable
{
public:
    FormFactorInfo()
        : mp_ff(0), m_pos_x(0.0), m_pos_y(0.0), m_abundance(0.0) {}
    ~FormFactorInfo();
    /* out-of-place implementation required due to IFormFactor */
    virtual FormFactorInfo *clone() const;
    IFormFactor *mp_ff;
    double m_pos_x, m_pos_y;
    double m_abundance;
};

#endif /* LAYERSTRATEGYBUILDER_H_ */


