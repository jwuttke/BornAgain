// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/inc/FormFactorDecoratorMaterial.h
//! @brief     Defines class FormFactorDecoratorMaterial.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORDECORATORMATERIAL_H_
#define FORMFACTORDECORATORMATERIAL_H_

#include "FormFactorDecoratorFactor.h"
#include "HomogeneousMaterial.h"
#include <boost/scoped_ptr.hpp>

//! @class FormFactorDecoratorMaterial
//! @ingroup formfactors_decorations
//! @brief Decorates a scalar formfactor with the correct factor for the material's
//! refractive index and that of its surrounding material.

class BA_CORE_API_  FormFactorDecoratorMaterial : public FormFactorDecoratorFactor
{
public:
    FormFactorDecoratorMaterial(IFormFactor *p_form_factor,
            complex_t wavevector_scattering_factor=1.0);
    virtual ~FormFactorDecoratorMaterial();

    virtual FormFactorDecoratorMaterial *clone() const;

    virtual void accept(ISampleVisitor *visitor) const { visitor->visit(this); }

    //! Sets the material of the scatterer
    virtual void setMaterial(const IMaterial& material);

    //! Sets the ambient material
    virtual void setAmbientMaterial(const IMaterial& material);

    //! Retrieves the refractive index of the ambient material
    virtual complex_t getAmbientRefractiveIndex() const;

#ifndef GCCXML_SKIP_THIS
    //! Returns scattering amplitude for matrix interactions
    virtual Eigen::Matrix2cd evaluatePol(const cvector_t& k_i,
            const Bin1DCVector& k_f_bin, const Bin1D &alpha_f_bin,
            const Bin1D &phi_f_bin) const;
#endif

private:
    complex_t getRefractiveIndexFactor() const;

    complex_t m_wavevector_scattering_factor;
    boost::scoped_ptr<IMaterial> mP_material;
    boost::scoped_ptr<IMaterial> mP_ambient_material;
};

#endif /* FORMFACTORDECORATORMATERIAL_H_ */


