// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/src/FormFactorFullSphere.cpp
//! @brief     Implements class FormFactorFullSphere.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorFullSphere.h"
#include "MathFunctions.h"

FormFactorFullSphere::FormFactorFullSphere(double radius)
: m_radius(radius)
{
    setName("FormFactorFullSphere");
    check_initialization();
    init_parameters();
}

bool FormFactorFullSphere::check_initialization() const
{
    return true;
}

void FormFactorFullSphere::init_parameters()
{
    clearParameterPool();
    registerParameter("radius", &m_radius, AttLimits::n_positive());
}


FormFactorFullSphere* FormFactorFullSphere::clone() const
{
    FormFactorFullSphere *result = new FormFactorFullSphere(m_radius);
    result->setName(getName());
    return result;
}

complex_t FormFactorFullSphere::evaluate_for_q(const cvector_t& q) const
{
    complex_t qz = q.z();
    double R = m_radius;

    complex_t iqzR = complex_t(0.0, 1.0)*qz*R;
    complex_t z_part = std::exp(iqzR);

    complex_t qR = std::sqrt( std::norm(q.x()) + std::norm(q.y()) + std::norm(qz) )*R;
    double volume = 4*Units::PI*R*R*R/3;
    complex_t radial;
    if (std::abs(qR) < Numeric::double_epsilon) {
        radial = volume;
    }
    else {
        // way1 (standard)
        //radial = 3*volume*(std::sin(qR) - qR*std::cos(qR))/(qR*qR*qR);

        // way2 (fast)
        radial = 3*volume*(MathFunctions::FastSin(qR) - qR*MathFunctions::FastCos(qR))/(qR*qR*qR);

        // way3 (experimental)
        // complex_t xsin, xcos;
        // MathFunctions::FastSinCos(qR, xsin, xcos);
        // radial = 3*volume*(xsin - qR*xcos)/(qR*qR*qR);
    }

    return radial*z_part;
}



