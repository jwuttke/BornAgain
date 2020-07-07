// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/SoftParticle/FormFactorGauss.h
//! @brief     Defines class FormFactorGauss.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_SOFTPARTICLE_FORMFACTORGAUSS_H
#define BORNAGAIN_CORE_SOFTPARTICLE_FORMFACTORGAUSS_H

#include "Core/Scattering/IFormFactorBorn.h"

//! The form factor of a gaussian.
//! @ingroup softParticle

class BA_CORE_API_ FormFactorGauss : public IFormFactorBorn
{
public:
    FormFactorGauss(double length);
    FormFactorGauss(double width, double height);

    FormFactorGauss* clone() const override final { return new FormFactorGauss(m_width, m_height); }
    void accept(INodeVisitor* visitor) const override final { visitor->visit(this); }

    double getWidth() const { return m_width; }
    double getHeight() const { return m_height; }

    double radialExtension() const override final { return m_width; }

    complex_t evaluate_for_q(cvector_t q) const override final;

protected:
    void onChange() override final;

private:
    double m_width;
    double m_height;
    double m_max_ql;
    void initialize();
};

#endif // BORNAGAIN_CORE_SOFTPARTICLE_FORMFACTORGAUSS_H
