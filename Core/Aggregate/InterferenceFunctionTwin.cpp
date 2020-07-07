// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Aggregate/InterferenceFunctionTwin.cpp
//! @brief     Implements class InterferenceFunctionTwin.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Aggregate/InterferenceFunctionTwin.h"
#include "Core/Basics/BornAgainNamespace.h"
#include "Core/Parametrization/RealParameter.h"
#include <cmath>

InterferenceFunctionTwin::InterferenceFunctionTwin(const kvector_t& direction, double mean_distance,
                                                   double std_dev)
    : m_direction(direction), m_distance(mean_distance), m_std_dev(std_dev)
{
    setName(BornAgain::InterferenceFunctionTwinType);
    validateParameters();
    init_parameters();
}

InterferenceFunctionTwin* InterferenceFunctionTwin::clone() const
{
    return new InterferenceFunctionTwin(*this);
}

kvector_t InterferenceFunctionTwin::direction() const
{
    return m_direction;
}

double InterferenceFunctionTwin::meanDistance() const
{
    return m_distance;
}

double InterferenceFunctionTwin::stdDev() const
{
    return m_std_dev;
}

InterferenceFunctionTwin::InterferenceFunctionTwin(const InterferenceFunctionTwin& other)
    : IInterferenceFunction(other), m_direction(other.m_direction), m_distance(other.m_distance),
      m_std_dev(other.m_std_dev)
{
    setName(BornAgain::InterferenceFunctionTwinType);
    validateParameters();
    init_parameters();
}

double InterferenceFunctionTwin::iff_without_dw(const kvector_t q) const
{
    double q_proj = q.dot(m_direction.unit());
    return 1.0
           + std::exp(-q_proj * q_proj * m_std_dev * m_std_dev / 2.0)
                 * std::cos(q_proj * m_distance);
}

void InterferenceFunctionTwin::validateParameters() const
{
    if (m_direction.mag2() <= 0.0 || m_distance < 0.0 || m_std_dev < 0.0)
        throw std::runtime_error(
            "InterferenceFunctionTwin::validateParameters: mean distance, standard deviation and "
            "length of direction vector should be positive");
}

void InterferenceFunctionTwin::init_parameters()
{
    registerVector(BornAgain::Direction, &m_direction, BornAgain::UnitsNone);
    registerParameter(BornAgain::Mean, &m_distance).setUnit(BornAgain::UnitsNm).setNonnegative();
    registerParameter(BornAgain::StdDeviation, &m_std_dev)
        .setUnit(BornAgain::UnitsNm)
        .setNonnegative();
}
