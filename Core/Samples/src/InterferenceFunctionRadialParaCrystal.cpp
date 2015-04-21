// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/src/InterferenceFunctionRadialParaCrystal.cpp
//! @brief     Implements class InterferenceFunctionRadialParaCrystal.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "InterferenceFunctionRadialParaCrystal.h"
#include "MathFunctions.h"

InterferenceFunctionRadialParaCrystal::InterferenceFunctionRadialParaCrystal(
        double peak_distance, double damping_length)
    : m_peak_distance(peak_distance)
    , m_damping_length(damping_length)
    , m_use_damping_length(true)
    , m_kappa(0.0)
    , m_domain_size(0.0)
{
    setName("InterferenceFunctionRadialParaCrystal");
    if (m_damping_length==0.0) {
        m_use_damping_length = false;
    }
    init_parameters();
}

void InterferenceFunctionRadialParaCrystal::init_parameters()
{
    clearParameterPool();
    registerParameter("peak_distance", &m_peak_distance);
    registerParameter("damping_length", &m_damping_length);
    registerParameter("size_spacing_coupling", &m_kappa);
    registerParameter("domain_size", &m_domain_size);
}


InterferenceFunctionRadialParaCrystal *InterferenceFunctionRadialParaCrystal::clone() const {
    InterferenceFunctionRadialParaCrystal *result =
        new InterferenceFunctionRadialParaCrystal(
            m_peak_distance, m_damping_length);
    result->setName(getName());
    result->setDomainSize(getDomainSize());
    result->setKappa(m_kappa);
    if (mP_pdf.get()) {
        result->setProbabilityDistribution(*mP_pdf);
    }
    return result;
}


double InterferenceFunctionRadialParaCrystal::evaluate(const cvector_t& q) const
{
    if (!mP_pdf.get()) {
        throw NullPointerException("InterferenceFunctionRadialParaCrystal::"
                "evaluate() -> Error! Probability distribution for "
                "interference funtion not properly initialized");
    }
    double result=0.0;
    double qxr = q.x().real();
    double qyr = q.y().real();
    double qpar = std::sqrt(qxr*qxr + qyr*qyr);
    int n = (int)std::abs(m_domain_size/m_peak_distance);
    double nd = (double)n;
    complex_t fp = FTPDF(qpar);
    if (n<1) {
        result = ((1.0 + fp)/(1.0 - fp)).real();
    } else {
        if (std::abs(1.0-fp) < Numeric::double_epsilon ) {
            result = nd;
        }
        else if (std::abs(1.0-fp)*nd < 2e-4) {
            double intermediate = MathFunctions::geometricSum(fp, n).real()/nd;
            result = 1.0 + 2.0*intermediate;
        }
        else {
            complex_t tmp;
            double double_min = std::numeric_limits<double>::min();
            if (std::log(std::abs(fp)+double_min)*nd < std::log(double_min)) {
                tmp = complex_t(0.0, 0.0);
            } else {
            tmp = std::pow(fp,n-1);
            }
            double intermediate = ((1.0-1.0/nd)*fp/(1.0-fp)
                    - fp*fp*(1.0-tmp)/nd/(1.0-fp)/(1.0-fp)).real();
            result = 1.0 + 2.0*intermediate;
        }
    }
    return result;
}

complex_t InterferenceFunctionRadialParaCrystal::FTPDF(
    double qpar) const
{
    complex_t phase = std::exp(complex_t(0.0, 1.0)*qpar*m_peak_distance);
    double amplitude = mP_pdf->evaluate(qpar);
    complex_t result = phase*amplitude;
    if (m_use_damping_length) {
        result *= std::exp(-m_peak_distance/m_damping_length);
    }
    return result;
}

void InterferenceFunctionRadialParaCrystal::setProbabilityDistribution(
        const IFTDistribution1D &pdf)
{
    if (mP_pdf.get() != &pdf) {
        mP_pdf.reset(pdf.clone());
    }
}

const IFTDistribution1D
    *InterferenceFunctionRadialParaCrystal::getPropabilityDistribution() const
{
    return mP_pdf.get();
}


