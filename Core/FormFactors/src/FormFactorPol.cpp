// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/src/FormFactorPol.cpp
//! @brief     Implements class FormFactorPol.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorPol.h"

FormFactorPol* FormFactorPol::clone() const
{
    FormFactorPol *p_result = new FormFactorPol(mp_form_factor->clone());
    p_result->setSpecularInfo(*mp_specular_info);
    p_result->setName(getName());
    p_result->setMaterial(mp_material);
    p_result->setAmbientMaterial(mp_ambient_material);
    return p_result;
}

FormFactorPol::~FormFactorPol()
{
    delete mp_specular_info;
}

complex_t FormFactorPol::evaluate(const cvector_t& k_i,
        const Bin1DCVector& k_f_bin, double alpha_i, double alpha_f) const
{
    (void)k_i;
    (void)k_f_bin;
    (void)alpha_i;
    (void)alpha_f;
    throw Exceptions::NotImplementedException("FormFactorPol::evaluate:"
            " scalar evaluate should never be called for matrix ff");
}

Eigen::Matrix2cd FormFactorPol::evaluatePol(const cvector_t& k_i,
        const Bin1DCVector& k_f1_bin, const Bin1DCVector& k_f2_bin,
        double alpha_i, double alpha_f, double phi_f) const
{
    (void)k_f2_bin;
    (void)phi_f;
    // the conjugated linear part of time reversal operator T
    // (T=UK with K complex conjugate operator and U is linear)
    Eigen::Matrix2cd time_reverse_conj = Eigen::Matrix2cd::Zero();
    time_reverse_conj(0,1) = 1.0;
    time_reverse_conj(1,0) = -1.0;
    // the interaction and time reversal taken together:
    double k_mag2 = std::abs(k_i.magxy2())/std::cos(alpha_i)/std::cos(alpha_i);
    Eigen::Matrix2cd V_eff = time_reverse_conj *
            (mp_material->getScatteringMatrix(k_mag2) -
             mp_ambient_material->getScatteringMatrix(k_mag2));
    return mp_form_factor->evaluate(k_i, k_f1_bin, alpha_i, alpha_f) * V_eff;
}

void FormFactorPol::setSpecularInfo(const LayerSpecularInfo& layer_specular_info)
{
    delete mp_specular_info;
    mp_specular_info = layer_specular_info.clone();
}
