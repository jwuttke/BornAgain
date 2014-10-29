// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/src/FormFactorDWBAConstZ.cpp
//! @brief     Implements class FormFactorDWBAConstZ.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorDWBAConstZ.h"

#include <boost/scoped_ptr.hpp>

FormFactorDWBAConstZ::FormFactorDWBAConstZ(
    IFormFactor* p_form_factor, double depth)
  : FormFactorDWBA(p_form_factor)
  , m_depth(depth)
{
    setName("FormFactorDWBAConstZ");
}

complex_t FormFactorDWBAConstZ::evaluate(
    const cvector_t& k_i, const Bin1DCVector& k_f_bin, const Bin1D &alpha_f_bin) const
{
    calculateTerms(k_i, k_f_bin, alpha_f_bin);

    complex_t k_iz = k_i.z();
    complex_t k_fz = mp_out_coeffs->getScalarKz();
    m_term_S *= getDepthPhase(k_iz-k_fz);
    m_term_RS *= getDepthPhase(-k_iz-k_fz);
    m_term_SR *= getDepthPhase(k_iz+k_fz);
    m_term_RSR *= getDepthPhase(-k_iz+k_fz);

    return m_term_S + m_term_RS + m_term_SR + m_term_RSR;
}

FormFactorDWBAConstZ* FormFactorDWBAConstZ::clone() const
{
    FormFactorDWBAConstZ *p_clone =
        new FormFactorDWBAConstZ(mp_form_factor->clone(), m_depth);
    p_clone->setSpecularInfo(mp_in_coeffs, mp_out_coeffs);
    return p_clone;
}


