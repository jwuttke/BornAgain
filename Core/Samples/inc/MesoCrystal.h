// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/inc/MesoCrystal.h
//! @brief     Defines class MesoCrystal.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef MESOCRYSTAL_H_
#define MESOCRYSTAL_H_

#include "IClusteredParticles.h"
#include "IFormFactor.h"
#include "IParticle.h"

//! @class MesoCrystal
//! @ingroup samples
//! @brief A particle with an internal structure of smaller particles

class BA_CORE_API_ MesoCrystal : public IParticle
{
public:
    MesoCrystal(IClusteredParticles *p_particle_structure,
            IFormFactor *p_form_factor);
    MesoCrystal(const IClusteredParticles& particle_structure,
            IFormFactor& form_factor);

    virtual ~MesoCrystal();
    virtual MesoCrystal *clone() const;

    //! Returns a clone with inverted magnetic fields
    virtual MesoCrystal *cloneInvertB() const;

    //! Calls the ISampleVisitor's visit method
    virtual void accept(ISampleVisitor *visitor) const { visitor->visit(this); }

    virtual void setAmbientMaterial(const IMaterial& material);
    virtual const IMaterial* getAmbientMaterial() const;

    virtual IFormFactor* createFormFactor(
            complex_t wavevector_scattering_factor) const;

    //! @brief get the internal structure, which is in principle unbounded in
    //! space (eg.  an infinite crystal)
    const IClusteredParticles *getClusteredParticles() const {
        return mp_particle_structure;
    }

protected:
    //! Propagates a transformation to child particles
    virtual void applyTransformationToSubParticles(const IRotation& rotation);

private:
    IClusteredParticles *mp_particle_structure;
    IFormFactor *mp_meso_form_factor;
};

#endif /* MESOCRYSTAL_H_ */


