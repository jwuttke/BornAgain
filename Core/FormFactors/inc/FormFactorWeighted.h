// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/inc/FormFactorWeighted.h
//! @brief     Defines class FormFactorWeighted.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORWEIGHTED_H_
#define FORMFACTORWEIGHTED_H_

#include "IFormFactor.h"

//! @class FormFactorWeighted
//! @ingroup formfactors_internal
//! @brief Coherent sum of different form factors with different weights.
//! Acts on scalar form factors.

class BA_CORE_API_ FormFactorWeighted : public IFormFactor
{
public:
    FormFactorWeighted();
    virtual ~FormFactorWeighted();
    virtual FormFactorWeighted *clone() const;

    //! calls the ISampleVisitor's visit method
    virtual void accept(ISampleVisitor *visitor) const { visitor->visit(this); }

    void addFormFactor(const IFormFactor& form_factor, double weight=1.0);

    virtual void setAmbientMaterial(const IMaterial& material);

    virtual complex_t evaluate(const cvector_t& k_i,
            const Bin1DCVector& k_f_bin, const Bin1D &alpha_f_bin) const;

#ifndef GCCXML_SKIP_THIS
    //! Calculates and returns a polarized form factor calculation in DWBA
    virtual Eigen::Matrix2cd evaluatePol(const cvector_t& k_i,
            const Bin1DCVector& k_f_bin, const Bin1D &alpha_f_bin,
            const Bin1D &phi_f_bin) const;
#endif

    virtual int getNumberOfStochasticParameters() const;

protected:
    std::vector<IFormFactor *> m_form_factors;
    std::vector<double> m_weights;
};

#endif /* FORMFACTORWEIGHTED_H_ */


