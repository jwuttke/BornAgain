// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/SoftParticle/FormFactorSphereGaussianRadius.cpp
//! @brief     Implements class FormFactorSphereGaussianRadius.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/SoftParticle/FormFactorSphereGaussianRadius.h"
#include "Core/Basics/BornAgainNamespace.h"
#include "Fit/Tools/RealLimits.h"
#include "Core/Parametrization/RealParameter.h"
#include "Core/Shapes/TruncatedEllipsoid.h"

FormFactorSphereGaussianRadius::FormFactorSphereGaussianRadius(double mean, double sigma)
    : m_mean(mean), m_sigma(sigma), m_mean_r3(0.0)
{
    setName(BornAgain::FormFactorSphereGaussianRadiusType);
    m_mean_r3 = calculateMeanR3();
    P_ff_sphere.reset(new FormFactorFullSphere(m_mean_r3));
    registerParameter(BornAgain::MeanRadius, &m_mean).setUnit(BornAgain::UnitsNm).setNonnegative();
    registerParameter(BornAgain::SigmaRadius, &m_sigma)
        .setUnit(BornAgain::UnitsNm)
        .setNonnegative();
    onChange();
}

complex_t FormFactorSphereGaussianRadius::evaluate_for_q(cvector_t q) const
{
    double q2 = std::norm(q.x()) + std::norm(q.y()) + std::norm(q.z());
    double dw = std::exp(-q2 * m_sigma * m_sigma / 2.0);
    return dw * P_ff_sphere->evaluate_for_q(q);
}

void FormFactorSphereGaussianRadius::onChange()
{
    mP_shape.reset(new TruncatedEllipsoid(m_mean, m_mean, m_mean, 2.0 * m_mean, 0.0));
}

double FormFactorSphereGaussianRadius::calculateMeanR3() const
{
    return std::pow(m_mean * (m_mean * m_mean + 3.0 * m_sigma * m_sigma), 1.0 / 3.0);
}
