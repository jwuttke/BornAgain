// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/inc/ParticleDistribution.h
//! @brief     Defines class ParticleDistribution.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef PARTICLEDISTRIBUTION_H
#define PARTICLEDISTRIBUTION_H

#include "IParticle.h"
#include "ParticleInfo.h"
#include "ParameterDistribution.h"

class ParticleInfo;

//! @class ParticleDistribution
//! @ingroup samples
//! @brief A particle with a form factor and refractive index

class BA_CORE_API_ ParticleDistribution : public IParticle
{
public:
    ParticleDistribution(const IParticle &prototype, const ParameterDistribution &par_distr);

    ParticleDistribution(const IParticle &prototype, const ParameterDistribution &par_distr,
                         kvector_t position);

    virtual ~ParticleDistribution()
    {
    }
    virtual ParticleDistribution *clone() const;

    //! Returns a clone with inverted magnetic fields
    virtual ParticleDistribution *cloneInvertB() const;

    //! calls the ISampleVisitor's visit method
    virtual void accept(ISampleVisitor *visitor) const
    {
        visitor->visit(this);
    }

    //! Sets the refractive index of the ambient material (which influences its
    //! scattering power)
    virtual void setAmbientMaterial(const IMaterial &material)
    {
        m_particle.setAmbientMaterial(material);
    }

    //! Returns particle's material.
    virtual const IMaterial *getAmbientMaterial() const
    {
        return m_particle.getParticle()->getAmbientMaterial();
    }

    //! Should not be called for objects of this class:
    //! The object should spawn particles that will create the
    //! required form factors
    virtual IFormFactor *createFormFactor(complex_t wavevector_scattering_factor) const;

    //! Returns list of new particles generated according to a distribution
    std::vector<ParticleInfo *> generateParticleInfos(kvector_t position, double abundance) const;

    //! Returns the distributed parameter data
    ParameterDistribution getParameterDistribution() const
    {
        return m_par_distribution;
    }

    //! Returns the parameter pool that can be used for parameter distributions
    ParameterPool *createDistributedParameterPool() const {
        return m_particle.createParameterTree();
    }

    //! Returns particle.
    const IParticle *getParticle() const
    {
        return m_particle.getParticle();
    }

protected:
    ParticleInfo m_particle;
    ParameterDistribution m_par_distribution;
    //! Propagates a transformation to child particles
    virtual void applyTransformationToSubParticles(const IRotation& rotation);
};

#endif // PARTICLEDISTRIBUTION_H
