// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/src/LayerStrategyBuilder.cpp
//! @brief     Implements classes LayerStrategyBuilder and
//!              FormFactorInfo
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "LayerStrategyBuilder.h"
#include "Layer.h"
#include "Simulation.h"
#include "InterferenceFunctions.h"
#include "InterferenceFunctionStrategies.h"
#include "FormFactors.h"
#include "FormFactorTools.h"
#include "PositionParticleInfo.h"

#include <cmath>
#include <boost/scoped_ptr.hpp>

LayerStrategyBuilder::LayerStrategyBuilder(
        const Layer& decorated_layer, const Simulation& simulation,
        const SimulationParameters& sim_params, size_t layout_index)
: mp_layer(decorated_layer.clone())
, mp_simulation(simulation.clone())
, m_sim_params(sim_params)
, mp_specular_info(0)
, m_layout_index(layout_index)
{
    assert(mp_layer->getNumberOfLayouts()>0);
}

LayerStrategyBuilder::~LayerStrategyBuilder()
{
    delete mp_layer;
    delete mp_simulation;
    delete mp_specular_info;
}


void LayerStrategyBuilder::setRTInfo(const LayerSpecularInfo& specular_info)
{
    if (mp_specular_info != &specular_info) {
        delete mp_specular_info;
        mp_specular_info = specular_info.clone();
    }
}

IInterferenceFunctionStrategy* LayerStrategyBuilder::createStrategy()
{
    collectFormFactorInfos();
    collectInterferenceFunctions();
    size_t n_ifs = m_ifs.size();
    IInterferenceFunctionStrategy *p_result(0);
    switch (mp_layer->getLayout(m_layout_index)->getApproximation())
    {
    case ILayout::DA:
        p_result = new DecouplingApproximationStrategy(m_sim_params);
        break;
    case ILayout::SSCA:
    {
        if (n_ifs<1) {
            throw Exceptions::ClassInitializationException(
                    "SSCA requires an interference function");
        }
        double kappa = m_ifs[0]->getKappa();
        if (kappa<=0.0) {
            throw Exceptions::ClassInitializationException(
                    "SSCA requires a strictly positive coupling value");
        }
        p_result = new SizeSpacingCorrelationApproximationStrategy(
            m_sim_params, kappa);
        break;
    }
    case ILayout::ISGISAXSMOR:
        p_result = new IsGISAXSMorphologyFileStrategy(m_sim_params);
        break;
    default:
        throw Exceptions::ClassInitializationException(
                "Unknown interference function approximation");
    }
    if (!p_result) {
        throw Exceptions::ClassInitializationException(
                "Could not create appropriate strategy");
    }
    p_result->init(m_ff_infos, m_ifs);
    p_result->setSpecularInfo(*mp_specular_info);
    return p_result;
}

bool LayerStrategyBuilder::requiresMatrixFFs() const
{
    return mp_simulation->getSample()->containsMagneticMaterial();
}

void LayerStrategyBuilder::collectFormFactorInfos()
{
    assert(mp_layer->getNumberOfLayouts()>0);
    m_ff_infos.clear();
    const ILayout *p_decoration = mp_layer->getLayout(m_layout_index);
    const IMaterial *p_layer_material = mp_layer->getMaterial();
    double wavelength = getWavelength();
    complex_t wavevector_scattering_factor = M_PI/wavelength/wavelength;
    size_t number_of_particles = p_decoration->getNumberOfParticles();
    for (size_t particle_index =
             0; particle_index<number_of_particles; ++particle_index) {
        const ParticleInfo *p_particle_info =
            p_decoration->getParticleInfo(particle_index);
        FormFactorInfo *p_ff_info;
        p_ff_info = createFormFactorInfo(p_particle_info, p_layer_material,
                wavevector_scattering_factor);
        p_ff_info->m_abundance =
            p_decoration->getAbundanceFractionOfParticle(particle_index);
        m_ff_infos.push_back(p_ff_info);
    }
    return;
}

void LayerStrategyBuilder::collectInterferenceFunctions()
{
    assert(mp_layer->getNumberOfLayouts()>0);
    m_ifs.clear();
    if (mp_layer->getLayout(m_layout_index)->getNumberOfInterferenceFunctions()) {
        m_ifs = mp_layer->getLayout(m_layout_index)->getInterferenceFunctions();
    }
    else m_ifs.push_back(new InterferenceFunctionNone);
}

double LayerStrategyBuilder::getWavelength()
{
    cvector_t ki = mp_simulation->getInstrument().getBeam().getCentralK();
    kvector_t ki_real(ki.x().real(), ki.y().real(), ki.z().real());
    return 2*M_PI/ki_real.mag();
}

FormFactorInfo *LayerStrategyBuilder::createFormFactorInfo(
        const ParticleInfo *p_particle_info,
        const IMaterial *p_ambient_material,
        complex_t factor) const
{
    FormFactorInfo *p_result = new FormFactorInfo;
    boost::scoped_ptr<Particle> P_particle_clone(p_particle_info->
            getParticle()->clone());
    P_particle_clone->setAmbientMaterial(p_ambient_material);

    // formfactor
    IFormFactor *p_ff_particle = P_particle_clone->createFormFactor(factor);
    IFormFactor *p_ff_framework(p_ff_particle);
    size_t n_layers = mp_layer->getNumberOfLayers();
    if (n_layers>1) {
        double depth = p_particle_info->getDepth();
        if (requiresMatrixFFs()) {
            p_ff_framework = FormFactorTools::createDWBAMatrixFormFactor(
                    p_ff_particle, depth);
        }
        else {
            p_ff_framework = FormFactorTools::createDWBAScalarFormFactor(
                    p_ff_particle, depth);
        }
    }
    p_result->mp_ff = p_ff_framework;
    // Other info (position and abundance
    const PositionParticleInfo *p_pos_particle_info =
        dynamic_cast<const PositionParticleInfo *>(p_particle_info);
    if (p_pos_particle_info) {
        kvector_t position = p_pos_particle_info->getPosition();
        p_result->m_pos_x = position.x();
        p_result->m_pos_y = position.y();
    }
    p_result->m_abundance = p_particle_info->getAbundance();
    return p_result;
}

// =============================================================================
// Implementation of FormFactorInfo
// =============================================================================

FormFactorInfo::~FormFactorInfo() { delete mp_ff; }

FormFactorInfo* FormFactorInfo::clone() const
{
    FormFactorInfo *p_result = new FormFactorInfo();
    p_result->m_abundance = m_abundance;
    p_result->m_pos_x = m_pos_x;
    p_result->m_pos_y = m_pos_y;
    p_result->mp_ff = mp_ff->clone();
    return p_result;
}

