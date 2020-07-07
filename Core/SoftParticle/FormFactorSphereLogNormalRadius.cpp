// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/SoftParticle/FormFactorSphereLogNormalRadius.cpp
//! @brief     Implements class FormFactorSphereGaussianRadius.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/SoftParticle/FormFactorSphereLogNormalRadius.h"
#include "Core/Basics/BornAgainNamespace.h"
#include "Core/Parametrization/Distributions.h"
#include "Core/Parametrization/ParameterSample.h"
#include "Core/Parametrization/RealParameter.h"
#include "Core/Shapes/TruncatedEllipsoid.h"

FormFactorSphereLogNormalRadius::FormFactorSphereLogNormalRadius(double mean, double scale_param,
                                                                 size_t n_samples)
    : m_mean(mean), m_scale_param(scale_param), m_n_samples(n_samples)
{
    setName(BornAgain::FormFactorSphereLogNormalRadiusType);
    mP_distribution.reset(new DistributionLogNormal(mean, scale_param));
    registerParameter(BornAgain::MeanRadius, &m_mean).setUnit(BornAgain::UnitsNm).setNonnegative();
    registerParameter(BornAgain::ScaleParameter, &m_scale_param);
    if (!mP_distribution)
        return;
    // Init vectors:
    m_form_factors.clear();
    m_probabilities.clear();
    for (ParameterSample& sample : mP_distribution->equidistantSamples(m_n_samples)) {
        double radius = sample.value;
        m_form_factors.push_back(new FormFactorFullSphere(radius));
        m_probabilities.push_back(sample.weight);
    }
    onChange();
}

complex_t FormFactorSphereLogNormalRadius::evaluate_for_q(cvector_t q) const
{
    if (m_form_factors.size() < 1)
        return 0.0;
    complex_t result(0.0);
    for (size_t i = 0; i < m_form_factors.size(); ++i)
        result += m_form_factors[i]->evaluate_for_q(q) * m_probabilities[i];
    return result;
}

void FormFactorSphereLogNormalRadius::onChange()
{
    mP_shape.reset(new TruncatedEllipsoid(m_mean, m_mean, m_mean, 2.0 * m_mean, 0.0));
}
