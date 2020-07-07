// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/FormFactorPyramid.cpp
//! @brief     Implements class FormFactorPyramid.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/HardParticle/FormFactorPyramid.h"
#include "Core/Basics/BornAgainNamespace.h"
#include "Core/Basics/Exceptions.h"
#include "Core/Basics/MathConstants.h"
#include "Core/Parametrization/RealParameter.h"
#include "Core/Tools/MathFunctions.h"

const PolyhedralTopology FormFactorPyramid::topology = {{
                                                            {{3, 2, 1, 0}, true}, // TODO -> true
                                                            {{0, 1, 5, 4}, false},
                                                            {{1, 2, 6, 5}, false},
                                                            {{2, 3, 7, 6}, false},
                                                            {{3, 0, 4, 7}, false},
                                                            {{4, 5, 6, 7}, true} // TODO -> true
                                                        },
                                                        false};

//! Constructor of a truncated pyramid with a square base
//! @param base_edge: length of the square base in nanometers
//! @param height: height of the pyramid in nanometers
//! @param alpha: dihedral angle between the base and a side face in radians
FormFactorPyramid::FormFactorPyramid(double base_edge, double height, double alpha)
    : FormFactorPolyhedron(), m_base_edge(base_edge), m_height(height), m_alpha(alpha)
{
    setName(BornAgain::FFPyramidType);
    registerParameter(BornAgain::BaseEdge, &m_base_edge)
        .setUnit(BornAgain::UnitsNm)
        .setNonnegative();
    registerParameter(BornAgain::Height, &m_height).setUnit(BornAgain::UnitsNm).setNonnegative();
    registerParameter(BornAgain::Alpha, &m_alpha).setUnit(BornAgain::UnitsRad).setLimited(0., M_PI);
    onChange();
}

IFormFactor* FormFactorPyramid::sliceFormFactor(ZLimits limits, const IRotation& rot,
                                                kvector_t translation) const
{
    auto effects = computeSlicingEffects(limits, translation, m_height);
    double dbase_edge = 2 * effects.dz_bottom * MathFunctions::cot(m_alpha);
    FormFactorPyramid slicedff(m_base_edge - dbase_edge,
                               m_height - effects.dz_bottom - effects.dz_top, m_alpha);
    return CreateTransformedFormFactor(slicedff, rot, effects.position);
}

void FormFactorPyramid::onChange()
{
    double cot_alpha = MathFunctions::cot(m_alpha);
    if (!std::isfinite(cot_alpha))
        throw Exceptions::OutOfBoundsException("pyramid angle alpha out of bounds");
    double r = cot_alpha * 2 * m_height / m_base_edge; // [L(base)-L(top)]/L(base)
    if (r > 1) {
        std::ostringstream ostr;
        ostr << "FormFactorPyramid() -> Error in class initialization with parameters";
        ostr << " base_edge:" << m_base_edge;
        ostr << " height:" << m_height;
        ostr << " alpha[rad]:" << m_alpha << "\n\n";
        ostr << "Check for 'height <= base_edge*tan(alpha)' failed.";
        throw Exceptions::ClassInitializationException(ostr.str());
    }

    double a = m_base_edge / 2;
    double b = a * (1 - r);

    double zcom = m_height * (.5 - 2 * r / 3 + r * r / 4) / (1 - r + r * r / 3); // center of mass

    setPolyhedron(topology, -zcom,
                  {// base:
                   {-a, -a, -zcom},
                   {a, -a, -zcom},
                   {a, a, -zcom},
                   {-a, a, -zcom},
                   // top:
                   {-b, -b, m_height - zcom},
                   {b, -b, m_height - zcom},
                   {b, b, m_height - zcom},
                   {-b, b, m_height - zcom}});
}
