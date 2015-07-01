// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/src/Crystal.cpp
//! @brief     Implements class Crystal.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "Crystal.h"
#include "FormFactors.h"
#include "Units.h"
#include "MathFunctions.h"

Crystal::Crystal(const ParticleComposition &lattice_basis, const Lattice &lattice)
    : m_lattice(lattice), m_dw_factor(0.0)
{
    setName("Crystal");
    mp_lattice_basis = lattice_basis.clone();
    registerChild(mp_lattice_basis);
}

Crystal::~Crystal()
{
    delete mp_lattice_basis;
}

Crystal *Crystal::clone() const
{
    Crystal *p_new = new Crystal(*mp_lattice_basis, m_lattice);
    p_new->setDWFactor(m_dw_factor);
    return p_new;
}

Crystal *Crystal::cloneInvertB() const
{
    Crystal *p_new = new Crystal(mp_lattice_basis->cloneInvertB(), m_lattice);
    p_new->setDWFactor(m_dw_factor);
    p_new->setName(getName() + "_inv");
    return p_new;
}

IFormFactor *Crystal::createTotalFormFactor(const IFormFactor &meso_crystal_form_factor,
                                            complex_t wavevector_scattering_factor,
                                            const IRotation *p_rotation,
                                            kvector_t translation) const
{
    Lattice transformed_lattice = getTransformedLattice(p_rotation);
    boost::scoped_ptr<IFormFactor> P_basis_ff(mp_lattice_basis->createTransformedFormFactor(
        wavevector_scattering_factor, p_rotation, translation));
    boost::scoped_ptr<FormFactorCrystal> P_ff_crystal(
        new FormFactorCrystal(transformed_lattice, *P_basis_ff, meso_crystal_form_factor));
    if (m_dw_factor > 0.0) {
        return new FormFactorDecoratorDebyeWaller(*P_ff_crystal, m_dw_factor);
    }
    return P_ff_crystal->clone();
}

Lattice Crystal::getTransformedLattice(const IRotation *p_rotation) const
{
    if (p_rotation) {
        return m_lattice.createTransformedLattice(*p_rotation);
    } else {
        return m_lattice;
    }
}

Crystal::Crystal(ParticleComposition *p_lattice_basis, const Lattice &lattice)
    : m_lattice(lattice), m_dw_factor(0.0)
{
    setName("Crystal");
    mp_lattice_basis = p_lattice_basis;
    registerChild(mp_lattice_basis);
}
