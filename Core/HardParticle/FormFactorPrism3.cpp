// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/FormFactorPrism3.cpp
//! @brief     Implements class FormFactorPrism3.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/HardParticle/FormFactorPrism3.h"
#include "Core/Basics/BornAgainNamespace.h"
#include "Core/Parametrization/RealParameter.h"
#include <iostream>

//! Constructor of a prism with an equilaterial triangle base.
//! @param base_edge: length of the base edge in nanometers
//! @param height: height in nanometers
FormFactorPrism3::FormFactorPrism3(double base_edge, double height)
    : FormFactorPolygonalPrism(height), m_base_edge(base_edge)
{
    setName(BornAgain::FFPrism3Type);
    registerParameter(BornAgain::BaseEdge, &m_base_edge)
        .setUnit(BornAgain::UnitsNm)
        .setNonnegative();
    registerParameter(BornAgain::Height, &m_height).setUnit(BornAgain::UnitsNm).setNonnegative();
    onChange();
}

IFormFactor* FormFactorPrism3::sliceFormFactor(ZLimits limits, const IRotation& rot,
                                               kvector_t translation) const
{
    auto effects = computeSlicingEffects(limits, translation, m_height);
    FormFactorPrism3 slicedff(m_base_edge, m_height - effects.dz_bottom - effects.dz_top);
    return CreateTransformedFormFactor(slicedff, rot, effects.position);
}

void FormFactorPrism3::onChange()
{
    double a = m_base_edge;
    double as = a / 2;
    double ac = a / sqrt(3) / 2;
    double ah = a / sqrt(3);
    std::vector<kvector_t> V{{-ac, as, 0.}, {-ac, -as, 0.}, {ah, 0., 0.}};
    setPrism(false, V);
}
