// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Beam/Beam.cpp
//! @brief     Implements class Beam.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Beam/Beam.h"
#include "Core/Basics/BornAgainNamespace.h"
#include "Core/Basics/Complex.h"
#include "Core/Basics/Exceptions.h"
#include "Core/Basics/MathConstants.h"
#include "Core/Beam/FootprintFactorGaussian.h"
#include "Core/Parametrization/RealParameter.h"

// Allow for 90 degrees by adding a relatively small constant to pi/2
static constexpr double INCLINATION_LIMIT = M_PI_2 + 1e-10;

Beam::Beam() : m_wavelength(1.0), m_alpha(0.0), m_phi(0.0), m_intensity(1.0)
{
    setName(BornAgain::BeamType);
    init_parameters();
}

Beam::Beam(const Beam& other)
    : m_wavelength(other.m_wavelength), m_alpha(other.m_alpha), m_phi(other.m_phi),
      m_intensity(other.m_intensity), m_bloch_vector(other.m_bloch_vector)
{
    setName(other.getName());
    if (other.m_shape_factor)
        m_shape_factor.reset(other.m_shape_factor->clone());
    init_parameters();
    registerChildren();
}

Beam& Beam::operator=(const Beam& other)
{
    if (this != &other) {
        Beam tmp(other);
        tmp.swapContent(*this);
    }
    return *this;
}

Beam::~Beam() = default;

kvector_t Beam::getCentralK() const
{
    return vecOfLambdaAlphaPhi(m_wavelength, -m_alpha, m_phi);
}

void Beam::setCentralK(double wavelength, double alpha_i, double phi_i)
{
    if (wavelength <= 0.0)
        throw Exceptions::ClassInitializationException(
            "Beam::setCentralK() -> Error. Wavelength can't be negative or zero.");
    if (alpha_i < 0.0)
        throw Exceptions::ClassInitializationException(
            "Beam::setCentralK() -> Error. Inclination angle alpha_i can't be negative.");
    m_wavelength = wavelength;
    m_alpha = alpha_i;
    m_phi = phi_i;
}

const IFootprintFactor* Beam::footprintFactor() const
{
    return m_shape_factor.get();
}

void Beam::setFootprintFactor(const IFootprintFactor& shape_factor)
{
    m_shape_factor.reset(shape_factor.clone());
    registerChild(m_shape_factor.get());
}

void Beam::setWidthRatio(double width_ratio)
{
    if (!m_shape_factor)
        throw std::runtime_error("Error in Beam::setWidthRatio: footprint factor is nullptr. "
                                 "Probably, you have forgotten to initialize it.");
    m_shape_factor->setWidthRatio(width_ratio);
}

void Beam::setPolarization(const kvector_t bloch_vector)
{
    if (bloch_vector.mag() > 1.0) {
        throw Exceptions::ClassInitializationException(
            "Beam::setPolarization: "
            "The given Bloch vector cannot represent a real physical ensemble");
    }
    m_bloch_vector = bloch_vector;
}

kvector_t Beam::getBlochVector() const
{
    return m_bloch_vector;
}

Eigen::Matrix2cd Beam::getPolarization() const
{
    Eigen::Matrix2cd result;
    double x = m_bloch_vector.x();
    double y = m_bloch_vector.y();
    double z = m_bloch_vector.z();
    result(0, 0) = (1.0 + z) / 2.0;
    result(0, 1) = complex_t(x, -y) / 2.0;
    result(1, 0) = complex_t(x, y) / 2.0;
    result(1, 1) = (1.0 - z) / 2.0;
    return result;
}

std::vector<const INode*> Beam::getChildren() const
{
    if (m_shape_factor)
        return {m_shape_factor.get()};
    else
        return {};
}

void Beam::init_parameters()
{
    registerParameter(BornAgain::Intensity, &m_intensity).setNonnegative();
    registerParameter(BornAgain::Wavelength, &m_wavelength)
        .setUnit(BornAgain::UnitsNm)
        .setNonnegative();
    registerParameter(BornAgain::Inclination, &m_alpha)
        .setUnit(BornAgain::UnitsRad)
        .setLimited(0, INCLINATION_LIMIT);
    registerParameter(BornAgain::Azimuth, &m_phi)
        .setUnit(BornAgain::UnitsRad)
        .setLimited(-M_PI_2, M_PI_2);
    registerVector(BornAgain::BlochVector, &m_bloch_vector, BornAgain::UnitsNone);
}

void Beam::registerChildren()
{
    if (m_shape_factor)
        registerChild(m_shape_factor.get());
}

void Beam::swapContent(Beam& other)
{
    std::swap(m_wavelength, other.m_wavelength);
    std::swap(m_alpha, other.m_alpha);
    std::swap(m_phi, other.m_phi);
    std::swap(m_intensity, other.m_intensity);
    std::swap(m_shape_factor, other.m_shape_factor);
    std::swap(m_bloch_vector, other.m_bloch_vector);

    registerChildren();
    other.registerChildren();
}
