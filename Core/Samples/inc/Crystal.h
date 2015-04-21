// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/inc/Crystal.h
//! @brief     Defines class Crystal.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef CRYSTAL_H_
#define CRYSTAL_H_

#include "IClusteredParticles.h"
#include "Particle.h"
#include "Lattice.h"
#include "ParticleComposition.h"


//! @class Crystal
//! @ingroup samples
//! @brief A crystal structure with a form factor as a basis.

class BA_CORE_API_ Crystal : public IClusteredParticles
{
public:
    Crystal(const ParticleComposition& lattice_basis, const Lattice& lattice);
    ~Crystal();

    Crystal *clone() const;

    //! Returns a clone with inverted magnetic fields
    Crystal *cloneInvertB() const;

    //! Calls the ISampleVisitor's visit method
    void accept(ISampleVisitor *visitor) const { visitor->visit(this); }

    void setAmbientMaterial(const IMaterial& material) {
        mp_lattice_basis->setAmbientMaterial(material);
    }

    const IMaterial* getAmbientMaterial() const {
        return mp_lattice_basis->getAmbientMaterial();
    }

    IFormFactor *createTotalFormFactor(
        const IFormFactor& meso_crystal_form_factor,
        const IMaterial &p_ambient_material,
        complex_t wavevector_scattering_factor) const;

    Lattice getTransformedLattice() const;

    const ParticleComposition *getLatticeBasis() const { return mp_lattice_basis; }

    void setDWFactor(double dw_factor) { m_dw_factor = dw_factor; }

    //! Composes transformation with existing one
    void applyTransformation(const IRotation& rotation);

    //! Gets transformation
    const IRotation* getRotation() const {
        return mP_rotation.get();
    }


private:
    //! Private constructor
    Crystal(ParticleComposition *p_lattice_basis, const Lattice& lattice);

    //! Propagates a transformation to child particles
    void applyTransformationToSubParticles(const IRotation& rotation);

    Lattice m_lattice;
    std::auto_ptr<IRotation> mP_rotation;
    ParticleComposition *mp_lattice_basis;
    double m_dw_factor;
};

#endif /* CRYSTAL_H_ */


