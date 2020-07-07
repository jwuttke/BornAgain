// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/FormFactorPyramid.h
//! @brief     Defines class FormFactorPyramid
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef FORMFACTORPYRAMID_H
#define FORMFACTORPYRAMID_H

#include "Core/HardParticle/FormFactorPolyhedron.h"

//! A frustum with a quadratic base.
//! @ingroup hardParticle

class BA_CORE_API_ FormFactorPyramid : public FormFactorPolyhedron
{
public:
    FormFactorPyramid(double base_edge, double height, double alpha);

    FormFactorPyramid* clone() const override final
    {
        return new FormFactorPyramid(m_base_edge, m_height, m_alpha);
    }
    void accept(INodeVisitor* visitor) const override final { visitor->visit(this); }

    double getHeight() const { return m_height; }
    double getBaseEdge() const { return m_base_edge; }
    double getAlpha() const { return m_alpha; }

protected:
    IFormFactor* sliceFormFactor(ZLimits limits, const IRotation& rot,
                                 kvector_t translation) const override final;

    void onChange() override final;

private:
    static const PolyhedralTopology topology;

    double m_base_edge;
    double m_height;
    double m_alpha;
};

#endif // FORMFACTORPYRAMID_H
