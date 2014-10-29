// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/inc/FormFactorDWBA.h
//! @brief     Defines class FormFactorDWBA.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORDWBA_H_
#define FORMFACTORDWBA_H_

#include "IFormFactorDecorator.h"
#include "LayerSpecularInfo.h"

#include <boost/scoped_ptr.hpp>

//! @class FormFactorDWBA
//! @ingroup formfactors_internal
//! @brief Evaluates a coherent sum of the four DWBA terms in a scalar formfactor.

class BA_CORE_API_ FormFactorDWBA: public IFormFactorDecorator
{
public:
    FormFactorDWBA(IFormFactor* p_form_factor);
    virtual ~FormFactorDWBA();

    virtual FormFactorDWBA *clone() const;

    virtual void accept(ISampleVisitor *visitor) const { visitor->visit(this); }

    //! Sets reflection/transmission info for scalar DWBA simulation
    virtual void setSpecularInfo(const ILayerRTCoefficients *p_in_coeffs,
                         const ILayerRTCoefficients *p_out_coeffs);

    virtual complex_t evaluate(const cvector_t& k_i,
            const Bin1DCVector& k_f_bin, const Bin1D &alpha_f_bin) const;

    friend class TestPolarizedDWBATerms;

protected:
    void calculateTerms(const cvector_t& k_i, const Bin1DCVector& k_f_bin,
            const Bin1D &alpha_f_bin) const;

    mutable complex_t m_term_S, m_term_RS, m_term_SR, m_term_RSR;
    const ILayerRTCoefficients *mp_in_coeffs;
    const ILayerRTCoefficients *mp_out_coeffs;
};

#endif /* FORMFACTORDWBA_H_ */


