// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Particle/ParticleCoreShell.h
//! @brief     Defines ParticleCoreShell.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef PARTICLECORESHELL_H
#define PARTICLECORESHELL_H

#include "IParticle.h"

class IMaterial;
class Particle;

//! A particle with a core/shell geometry.
//! @ingroup samples

class BA_CORE_API_ ParticleCoreShell : public IParticle
{
public:
    ParticleCoreShell(const Particle& shell, const Particle& core,
                      kvector_t relative_core_position=kvector_t(0.0, 0.0, 0.0));
    ~ParticleCoreShell();

    ParticleCoreShell* clone() const override final;
    ParticleCoreShell* cloneInvertB() const override final;

    void accept(INodeVisitor* visitor) const override final { visitor->visit(this); }

    IFormFactor* createSlicedFormFactor(ZLimits limits) const override final;

    IFormFactor* createTransformedFormFactor(
        const IRotation* p_rotation, kvector_t translation) const override final;

    const Particle* coreParticle() const;

    const Particle* shellParticle() const;

    std::vector<const INode*> getChildren() const override final;

protected:
    void addAndRegisterCore(const Particle& core, kvector_t relative_core_position);
    void addAndRegisterShell(const Particle& shell);
    ParticleCoreShell();

    std::unique_ptr<Particle> mp_shell;
    std::unique_ptr<Particle> mp_core;
};

inline const Particle* ParticleCoreShell::coreParticle() const
{
    return mp_core.get();
}

inline const Particle* ParticleCoreShell::shellParticle() const
{
    return mp_shell.get();
}

#endif // PARTICLECORESHELL_H
