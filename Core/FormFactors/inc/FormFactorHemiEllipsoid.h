// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/inc/FormFactorHemiEllipsoid.h
//! @brief     Defines class FormFactorHemiEllipsoid.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORHEMIELLIPSOID_H
#define FORMFACTORHEMIELLIPSOID_H

#include "IFormFactorBorn.h"
#include "MemberComplexFunctionIntegrator.h"

//! @class FormFactorHemiEllipsoid
//! @ingroup formfactors
//! @brief The formfactor of an hemi ellipsoid.

class BA_CORE_API_ FormFactorHemiEllipsoid : public IFormFactorBorn
{
public:
    //! @brief Hemi Ellipsoid constructor
    //! @param radius_a half length of one horizontal main axes
    //! @param radius_b half length of the other horizontal main axes
    //! @param height of Hemi Ellipsoid

    FormFactorHemiEllipsoid(double radius_a, double radius_b, double height);

    ~FormFactorHemiEllipsoid() {delete m_integrator;}

    virtual FormFactorHemiEllipsoid* clone() const;

    virtual void accept(ISampleVisitor *visitor) const { visitor->visit(this); }

    virtual int getNumberOfStochasticParameters() const { return 3; }

    virtual double getHeight() const { return m_height; }

    virtual double getRadiusA() const { return m_radius_a; }

    virtual double getRadiusB() const { return m_radius_b; }

    virtual complex_t evaluate_for_q (const cvector_t& q) const;

protected:
    virtual bool check_initialization() const;
    virtual void init_parameters();

private:

    complex_t Integrand(double Z, void* params) const;

    double m_radius_a;
    double m_radius_b;
    double m_height;
    mutable cvector_t m_q;

    MemberComplexFunctionIntegrator<FormFactorHemiEllipsoid> *m_integrator;

};

#endif // FORMFACTORHEMIELLIPSOID_H


