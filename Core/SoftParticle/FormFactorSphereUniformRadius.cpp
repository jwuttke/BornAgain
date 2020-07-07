// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/SoftParticle/FormFactorSphereUniformRadius.cpp
//! @brief     Implements class FormFactorSphereUniformRadius.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/SoftParticle/FormFactorSphereUniformRadius.h"
#include "Core/Basics/BornAgainNamespace.h"
#include "Core/Basics/Exceptions.h"
#include "Core/Basics/MathConstants.h"
#include "Core/Parametrization/RealParameter.h"
#include "Core/Shapes/TruncatedEllipsoid.h"
#include <limits>

FormFactorSphereUniformRadius::FormFactorSphereUniformRadius(double mean, double full_width)
    : m_mean(mean), m_full_width(full_width)
{
    if (!checkParameters())
        throw Exceptions::ClassInitializationException(
            "FormFactorSphereUniformRadius::FormFactorSphereUniformRadius:"
            " mean radius must be bigger than the half width");
    setName(BornAgain::FormFactorSphereUniformRadiusType);
    registerParameter(BornAgain::MeanRadius, &m_mean).setUnit(BornAgain::UnitsNm).setNonnegative();
    registerParameter(BornAgain::FullWidth, &m_full_width)
        .setUnit(BornAgain::UnitsNm)
        .setNonnegative();
    onChange();
}

complex_t FormFactorSphereUniformRadius::evaluate_for_q(cvector_t q) const
{
    double R = m_mean;
    double W = m_full_width;
    double q2 = std::norm(q.x()) + std::norm(q.y()) + std::norm(q.z());
    double q_r = std::sqrt(q2);
    if (q_r * R < std::numeric_limits<double>::epsilon())
        return (4.0 * M_PI * R * R * R + M_PI * R * W * W) / 3.0;
    double qR = q_r * R;
    double qW = q_r * W;
    double nominator =
        4 * M_PI
        * (4 * std::sin(qR) * std::sin(qW / 2.0) - qW * std::cos(qW / 2.0) * std::sin(qR)
           - 2.0 * qR * std::cos(qR) * std::sin(qW / 2.0));
    return nominator / (q2 * q2 * W);
}

void FormFactorSphereUniformRadius::onChange()
{
    mP_shape.reset(new TruncatedEllipsoid(m_mean, m_mean, m_mean, 2.0 * m_mean, 0.0));
}

bool FormFactorSphereUniformRadius::checkParameters() const
{
    if (m_full_width <= 0.0)
        return false;
    if (2.0 * m_mean < m_full_width)
        return false;
    return true;
}
