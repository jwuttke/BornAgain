// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Particle/ParticleDistribution.cpp
//! @brief     Implements class ParticleDistribution.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ParticleDistribution.h"
#include "BornAgainNamespace.h"
#include "Exceptions.h"
#include "IParticle.h"
#include "ParameterPool.h"
#include "ParameterSample.h"
#include "RealParameter.h"
#include <map>

ParticleDistribution::ParticleDistribution(const IParticle& prototype,
                                           const ParameterDistribution& par_distr)
    : m_par_distribution(par_distr)
{
    setName(BornAgain::ParticleDistributionType);
    mP_particle.reset(prototype.clone());
    registerChild(mP_particle.get());
}

ParticleDistribution* ParticleDistribution::clone() const
{
    ParticleDistribution* p_result
        = new ParticleDistribution(*mP_particle, m_par_distribution);
    p_result->setAbundance(m_abundance);
    return p_result;
}

ParticleDistribution* ParticleDistribution::cloneInvertB() const
{
    throw Exceptions::NotImplementedException("ParticleDistribution::"
                                              "cloneInvertB: should never be called");
}

void ParticleDistribution::accept(ISampleVisitor* visitor) const
{
    visitor->visit(this);
}

std::string ParticleDistribution::to_str(int indent) const
{
    std::stringstream ss;
    ss << std::string(4*indent, '.') << " " << getName() << "\n";
    for( const ISample* child: getChildren() )
        ss << child->to_str(indent+1);
    return ss.str();
}
void ParticleDistribution::setAmbientMaterial(const IMaterial& material)
{
    mP_particle->setAmbientMaterial(material);
}

const IMaterial* ParticleDistribution::getAmbientMaterial() const
{
    return mP_particle->getAmbientMaterial();
}

//! Initializes list of new particles generated according to a distribution.
std::vector<const IParticle*> ParticleDistribution::generateParticles() const
{
    std::unique_ptr<ParameterPool> P_pool(createDistributedParameterPool());
    std::string main_par_name = m_par_distribution.getName();
    std::vector<RealParameter*> matched_pars
        = P_pool->getMatchedParameters(main_par_name);
    if (matched_pars.size() != 1)
        throw Exceptions::RuntimeErrorException(
            "ParticleDistribution::generateParticles: "
            "main parameter name matches nothing or more than one parameter");
    RealParameter* main_par = matched_pars[0];
    double main_par_value = main_par->getValue();
    std::vector<std::string> linked_par_names = m_par_distribution.getLinkedParameterNames();
    std::map<std::string, double> linked_par_ratio_map;
    for (const std::string& name: linked_par_names) {
        std::vector<RealParameter*> linked_par_matches
            = P_pool->getMatchedParameters(name);
        if (linked_par_matches.size() != 1)
            throw Exceptions::RuntimeErrorException(
                "ParticleDistribution::generateParticles: "
                "linked parameter name matches nothing or more than one parameter");
        RealParameter* linked_par = linked_par_matches[0];
        double linked_par_value = linked_par->getValue();
        double linked_ratio = main_par_value == 0 ? 1.0 : linked_par_value / main_par_value;
        linked_par_ratio_map[name] = linked_ratio;
    }
    std::vector<ParameterSample> main_par_samples = m_par_distribution.generateSamples();
    std::vector<const IParticle*> result;
    for (const ParameterSample& main_sample: main_par_samples ) {
        double particle_abundance = getAbundance() * main_sample.weight;
        IParticle* p_particle_clone = mP_particle->clone();
        std::unique_ptr<ParameterPool> P_new_pool(p_particle_clone->createParameterTree());
        int changed = P_new_pool->setMatchedParametersValue(main_par_name, main_sample.value);
        if (changed != 1)
            throw Exceptions::RuntimeErrorException(
                "ParticleDistribution::generateParticles: "
                "main parameter name matches nothing or more than one parameter");
        for (std::map<std::string, double>::const_iterator it = linked_par_ratio_map.begin();
             it != linked_par_ratio_map.end(); ++it) {
            double new_linked_value = main_sample.value * it->second;
            changed = P_new_pool->setMatchedParametersValue(it->first, new_linked_value);
            if (changed != 1)
                throw Exceptions::RuntimeErrorException(
                    "ParticleDistribution::generateParticles: "
                    "linked parameter name matches nothing or more than one parameter");
        }
        p_particle_clone->setAbundance(particle_abundance);
        result.push_back(p_particle_clone);
    }
    return result;
}

ParameterPool* ParticleDistribution::createDistributedParameterPool() const
{
    return mP_particle->createParameterTree();
}

const IParticle* ParticleDistribution::getParticle() const
{
    return mP_particle.get();
}
