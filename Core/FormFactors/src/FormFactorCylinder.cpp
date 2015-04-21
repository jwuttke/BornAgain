// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/src/FormFactorCylinder.cpp
//! @brief     Implements class FormFactorCylinder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorCylinder.h"

#include "MathFunctions.h"
#include "Numeric.h"

FormFactorCylinder::FormFactorCylinder(double radius, double height)
{
    setName("FormFactorCylinder");
    m_radius = radius;
    m_height = height;
    check_initialization();
    init_parameters();
}

bool FormFactorCylinder::check_initialization() const
{
    return true;
}

void FormFactorCylinder::init_parameters()
{
    clearParameterPool();
    registerParameter("radius", &m_radius, AttLimits::n_positive());
    registerParameter("height", &m_height, AttLimits::n_positive());
}

FormFactorCylinder* FormFactorCylinder::clone() const
{
    FormFactorCylinder *result = new FormFactorCylinder(m_radius, m_height);
    result->setName(getName());
    return result;
}

complex_t FormFactorCylinder::evaluate_for_q(const cvector_t& q) const
{
    double R = m_radius;
    double H = m_height;

    complex_t qzH_half = q.z()*H/2.0;
    complex_t z_part = H*MathFunctions::Sinc(qzH_half) *
        std::exp(complex_t(0.0, 1.0)*qzH_half);

    complex_t qrR = q.magxy()*R;
    complex_t J1_qrR_div_qrR = std::abs(qrR) > Numeric::double_epsilon ?
        MathFunctions::Bessel_C1(qrR) :
        0.5;
    complex_t radial_part = Units::PI2*R*R*J1_qrR_div_qrR;

    complex_t result = radial_part*z_part;

    return result;
}



