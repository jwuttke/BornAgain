// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/Slice/SpecularSimulationElement.cpp
//! @brief     Implements the class SpecularSimulationElement.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Sample/Slice/SpecularSimulationElement.h"
#include "Sample/Slice/KzComputation.h"

SpecularSimulationElement::SpecularSimulationElement(double kz, bool computable)
    : m_intensity(0.0), m_computable(computable),
      m_kz_computation([kz](const std::vector<Slice>& slices) {
          return KzComputation::computeKzFromSLDs(slices, kz);
      })
{
}

SpecularSimulationElement::SpecularSimulationElement(double wavelength, double alpha, bool computable)
    : m_intensity(0.0), m_computable(computable),
      m_kz_computation(
          [k = vecOfLambdaAlphaPhi(wavelength, alpha, 0.0)](const std::vector<Slice>& slices) {
              return KzComputation::computeKzFromRefIndices(slices, k);
          })
{
}

SpecularSimulationElement::SpecularSimulationElement(const SpecularSimulationElement& other)
    : m_polarization(other.m_polarization), m_intensity(other.m_intensity),
      m_computable(other.m_computable), m_kz_computation(other.m_kz_computation)
{
}

SpecularSimulationElement::SpecularSimulationElement(SpecularSimulationElement&& other) noexcept
    : m_polarization(std::move(other.m_polarization)), m_intensity(other.m_intensity),
      m_computable(other.m_computable),
      m_kz_computation(std::move(other.m_kz_computation))
{
}

SpecularSimulationElement::~SpecularSimulationElement() = default;

SpecularSimulationElement& SpecularSimulationElement::
operator=(const SpecularSimulationElement& other)
{
    if (this != &other) {
        SpecularSimulationElement tmp(other);
        tmp.swapContent(*this);
    }
    return *this;
}

void SpecularSimulationElement::setPolarizationHandler(const PolarizationHandler& handler)
{
    m_polarization = handler;
}

std::vector<complex_t> SpecularSimulationElement::produceKz(const std::vector<Slice>& slices)
{
    return m_kz_computation(slices);
}

void SpecularSimulationElement::swapContent(SpecularSimulationElement& other)
{
    m_polarization.swapContent(other.m_polarization);
    std::swap(m_intensity, other.m_intensity);
    m_kz_computation.swap(other.m_kz_computation);
}
