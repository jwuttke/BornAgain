// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/src/InterferenceFunction1DLattice.cpp
//! @brief     Implements class InterferenceFunction1DLattice.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "InterferenceFunction1DLattice.h"
#include <cassert>

InterferenceFunction1DLattice::InterferenceFunction1DLattice(double length,
                                                             double xi)
: mp_pdf(0)
, m_prefactor(1.0)
, m_na(0)
{
    m_lattice_params.m_length = length;
    m_lattice_params.m_xi = xi;
    setName("InterferenceFunction1DLattice");
    init_parameters();
}

InterferenceFunction1DLattice::~InterferenceFunction1DLattice()
{
    delete mp_pdf;
}

InterferenceFunction1DLattice *InterferenceFunction1DLattice::clone() const {
    InterferenceFunction1DLattice *result =
            new InterferenceFunction1DLattice(m_lattice_params);
    if(mp_pdf) result->setProbabilityDistribution(*mp_pdf);
    result->setName(getName());
    return result;
}


void InterferenceFunction1DLattice::setProbabilityDistribution(
        const IFTDistribution1D& pdf)
{
    if (mp_pdf != &pdf) delete mp_pdf;
    mp_pdf = pdf.clone();
    double omega = mp_pdf->getOmega();
//     initialize_calc_factors(omega):
    m_prefactor = Units::PI*omega;
    double qa_max = (m_lattice_params.m_length/Units::PI2)*nmax/omega;
    m_na = (int) (std::abs(qa_max) + 0.5);
}

double InterferenceFunction1DLattice::evaluate(const cvector_t& q) const
{
    if(!mp_pdf) {
        throw NullPointerException("InterferenceFunction1DLattice::evaluate"
                " -> Error! No probability distribution function defined.");
    }
    double result = 0.0;
    double qxr = q.x().real();
    double qyr = q.y().real();
    double qx_frac;
    double xi = m_lattice_params.m_xi;
    double a = m_lattice_params.m_length;
    double a_rec = Units::PI2/a;

    // rotate the q vector to xi angle
    // so that qx_prime is along the a axis of lattice
    double qx_prime = qxr*std::cos(xi) + qyr*std::sin(xi);

    // calculate reciprocal vector fraction
    int qa_int = (int) (qx_prime/a_rec);
    qx_frac = qx_prime - qa_int*a_rec;

    for (int i=-m_na-1; i<m_na+2; ++i)
    {
        double qx = qx_frac + i*a_rec;
        result += mp_pdf->evaluate(qx);
    }
    return m_prefactor*result;
}

InterferenceFunction1DLattice::InterferenceFunction1DLattice(
        const Lattice1DIFParameters& lattice_params)
: m_lattice_params(lattice_params)
, mp_pdf(0)
, m_prefactor(1.0)
, m_na(0)
{
    setName("InterferenceFunction1DLattice");
    init_parameters();
}

void InterferenceFunction1DLattice::init_parameters()
{
    clearParameterPool();
    registerParameter("length", &m_lattice_params.m_length);
    registerParameter("xi", &m_lattice_params.m_xi);
}


