// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/SpecularComputationTerm.cpp
//! @brief     Implements functor SpecularComputationTerm.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "SpecularComputationTerm.h"
#include "DelayedProgressCounter.h"
#include "ScalarRTCoefficients.h"
#include "SpecularScalarStrategy.h"
#include "SpecularSimulationElement.h"
#include <iostream>

SpecularComputationTerm::SpecularComputationTerm(std::unique_ptr<ISpecularStrategy> strategy)
    : m_Strategy(std::move(strategy)){};

SpecularScalarTerm::SpecularScalarTerm(std::unique_ptr<ISpecularStrategy> strategy)
    : SpecularComputationTerm(std::move(strategy))
{
}

SpecularComputationTerm::~SpecularComputationTerm() = default;

void SpecularComputationTerm::setProgressHandler(ProgressHandler* p_progress)
{
    mP_progress_counter.reset(new DelayedProgressCounter(p_progress, 100));
}

void SpecularComputationTerm::compute(SpecularSimulationElement& elem,
                                      const std::vector<Slice>& slices) const
{
    if (!elem.isCalculated())
        return;

    eval(elem, slices);

    if (mP_progress_counter)
        mP_progress_counter->stepProgress();
}

SpecularScalarTerm::~SpecularScalarTerm() = default;

void SpecularScalarTerm::eval(SpecularSimulationElement& elem,
                              const std::vector<Slice>& slices) const
{
    auto coeff = m_Strategy->Execute(slices, elem.produceKz(slices));
    elem.setIntensity(std::norm(coeff.front()->getScalarR()));
}

SpecularMatrixTerm::SpecularMatrixTerm(std::unique_ptr<ISpecularStrategy> strategy)
    : SpecularComputationTerm(std::move(strategy))
{
}

SpecularMatrixTerm::~SpecularMatrixTerm() = default;

void SpecularMatrixTerm::eval(SpecularSimulationElement& elem,
                              const std::vector<Slice>& slices) const
{
    auto coeff = m_Strategy->Execute(slices, elem.produceKz(slices));
    elem.setIntensity(intensity(elem, coeff.front()));
}

double SpecularMatrixTerm::intensity(const SpecularSimulationElement& elem,
                                     ISpecularStrategy::single_coeff_t& coeff) const
{
    const auto& polarization = elem.polarizationHandler().getPolarization();
    const auto& analyzer = elem.polarizationHandler().getAnalyzerOperator();

    // construct the reflection operator
    auto M = coeff->getM();

//    std::cout << "M = " << M << std::endl;

    auto denominator = M(0,1) * M(1, 0) - M(0, 0) * M(1, 1);

    std::cout << "denom = " << denominator << std::endl;

    Eigen::Matrix2cd R;
    R(0, 0) = M(2, 1) * M(1, 0) - M(2, 0) * M(1, 1);
    R(0, 1) = M(2, 0) * M(0, 1) - M(0, 0) * M(2, 1);
    R(1, 1) = M(3, 0) * M(0, 1) - M(3, 1) * M(0, 0);
    R(1, 0) = M(3, 1) * M(1, 0) - M(3, 0) * M(1, 1);

    R /= denominator;

    const complex_t result = (polarization * R.adjoint() * analyzer * R).trace();

    return std::abs(result);
}
