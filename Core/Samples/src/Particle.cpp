// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/src/Particle.cpp
//! @brief     Implements class Particle.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "Particle.h"
#include "ParticleInfo.h"
#include "Materials.h"
#include <boost/scoped_ptr.hpp>

Particle::Particle()
{
    setName("Particle");
}

Particle::Particle(const IMaterial &p_material) : mP_material(p_material.clone())
{
    setName("Particle");
}

Particle::Particle(const IMaterial &p_material, const IFormFactor &form_factor)
    : mP_material(p_material.clone()), mP_form_factor(form_factor.clone())
{
    setName("Particle");
    registerChild(mP_form_factor.get());
}

Particle::Particle(const IMaterial &p_material, const IFormFactor &form_factor,
                   const IRotation &rotation)
    : mP_material(p_material.clone()), mP_form_factor(form_factor.clone())
{
    setName("Particle");
    mP_rotation.reset(rotation.clone());
    registerChild(mP_form_factor.get());
}

Particle::~Particle()
{
}

Particle *Particle::clone() const
{
    Particle *result = new Particle();

    if (mP_form_factor.get())
        result->setFormFactor(*mP_form_factor);
    if (mP_material.get())
        result->setMaterial(*mP_material);
    if (mP_ambient_material.get())
        result->setAmbientMaterial(*mP_ambient_material);
    if (mP_rotation.get())
        result->setTransformation(*mP_rotation);
    result->setName(getName());

    return result;
}

Particle *Particle::cloneInvertB() const
{
    Particle *result = new Particle();
    if (mP_form_factor.get())
        result->setFormFactor(*mP_form_factor);

    if (mP_material.get())
        result->mP_material.reset(Materials::createInvertedMaterial(mP_material.get()));
    if (mP_ambient_material.get())
        result->mP_ambient_material.reset(
            Materials::createInvertedMaterial(mP_ambient_material.get()));

    if (mP_rotation.get())
        result->mP_rotation.reset(mP_rotation->clone());

    result->setName(getName() + "_inv");
    return result;
}

IFormFactor *Particle::createFormFactor(complex_t wavevector_scattering_factor) const
{
    IFormFactor *p_transformed_ff = createTransformedFormFactor();
    if (!p_transformed_ff) {
        return 0;
    }
    FormFactorDecoratorMaterial *p_ff
        = new FormFactorDecoratorMaterial(p_transformed_ff, wavevector_scattering_factor);
    if (mP_material.get()) {
        if (mP_rotation.get()) {
            boost::scoped_ptr<const IMaterial> transformed_material(
                        mP_material->createTransformedMaterial(*mP_rotation));
            p_ff->setMaterial(*transformed_material);
        } else {
            p_ff->setMaterial(*mP_material);
        }
    }
    if (mP_ambient_material.get()) p_ff->setAmbientMaterial(*mP_ambient_material);
    return p_ff;
}

void Particle::setFormFactor(const IFormFactor &form_factor)
{
    if (&form_factor != mP_form_factor.get()) {
        if (mP_form_factor.get()) deregisterChild(mP_form_factor.get());
        mP_form_factor.reset(form_factor.clone());
        registerChild(mP_form_factor.get());
    }
}

IFormFactor *Particle::createTransformedFormFactor() const
{
    if (!mP_form_factor.get())
        return 0;
    IFormFactor *p_result;
    if (mP_rotation.get()) {
        p_result = new FormFactorDecoratorTransformation(mP_form_factor->clone(), *mP_rotation);
    } else {
        p_result = mP_form_factor->clone();
    }
    return p_result;
}

void Particle::applyTransformationToSubParticles(const IRotation &rotation)
{
    (void)rotation;
    return;
}
