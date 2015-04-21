// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/inc/FormFactorRipple1.h
//! @brief     Defines class FormFactorRipple1.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORRIPPLE1_H
#define FORMFACTORRIPPLE1_H

#include "IFormFactorBorn.h"
#include "MemberComplexFunctionIntegrator.h"

//! @class FormFactorRipple1
//! @ingroup formfactors
//! @brief The formfactor for a cosine ripple.

class BA_CORE_API_ FormFactorRipple1 : public IFormFactorBorn
{
public:
    //! @brief Ripple1 constructor
    //! @param length of Ripple1
    //! @param width of cosine cross section
    //! @param height of cosine cross section
    FormFactorRipple1(double length, double width, double height);

    virtual ~FormFactorRipple1() { delete m_integrator; }

    virtual FormFactorRipple1 *clone() const;

    virtual void accept(ISampleVisitor *visitor) const { visitor->visit(this); }

    virtual int getNumberOfStochasticParameters() const { return 3; }

    virtual double getHeight() const { return m_height; }
    virtual double getWidth() const { return m_width; }
    virtual double getLength() const { return m_length; }

    virtual complex_t evaluate_for_q(const cvector_t& q) const;

protected:
    virtual bool check_initialization() const;
    virtual void init_parameters();

private:
    complex_t Integrand(double Z, void* params) const;

    double m_width;
    double m_height;
    double m_length;
    mutable cvector_t m_q;

    MemberComplexFunctionIntegrator<FormFactorRipple1> *m_integrator;
};

#endif // FORMFACTORRIPPLE1_H


