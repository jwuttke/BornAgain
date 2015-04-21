// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/inc/FormFactorDecoratorDebyeWaller.h
//! @brief     Defines and implements class FormFactorDecoratorDebyeWaller.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORDECORATORDEBYEWALLER_H_
#define FORMFACTORDECORATORDEBYEWALLER_H_

#include "IFormFactorDecorator.h"

//! @class FormFactorDecoratorDebyeWaller
//! @ingroup formfactors_internal
//! @brief Debye-Waller factors in radial and z directions.

class BA_CORE_API_ FormFactorDecoratorDebyeWaller : public IFormFactorDecorator
{
public:
    //! Isotropic Debye-Waller factor.
    FormFactorDecoratorDebyeWaller(IFormFactor *p_form_factor,
            double dw_factor);

    //! Anisotropic Debye-Waller factor.
    FormFactorDecoratorDebyeWaller(IFormFactor *p_form_factor,
            double dw_h_factor, double dw_r_factor);

    //! Why the hell do we need this alternative form?
    FormFactorDecoratorDebyeWaller(const IFormFactor& p_form_factor,
        double dw_h_factor, double dw_r_factor);

    virtual ~FormFactorDecoratorDebyeWaller() {}

    virtual FormFactorDecoratorDebyeWaller *clone() const;

    virtual void accept(ISampleVisitor *visitor) const { visitor->visit(this); }

    virtual complex_t evaluate(const cvector_t& k_i,
            const Bin1DCVector& k_f_bin, const Bin1D &alpha_f_bin) const;

    virtual int getNumberOfStochasticParameters() const {
        return mp_form_factor->getNumberOfStochasticParameters();
    }

protected:
    virtual bool check_initialization() const;
    virtual void init_parameters();

private:
    double m_h_dw_factor; //!< the Debye-Waller factor in the z-direction
    double m_r_dw_factor; //!< the Debye-Waller factor in the radial direction
};

#endif /* FORMFACTORDECORATORDEBYEWALLER_H_ */


