// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/inc/FormFactorTruncatedSpheroid.h
//! @brief     Defines class FormFactorTruncatedSpheroid.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORTRUNCATEDSPHEROID_H
#define FORMFACTORTRUNCATEDSPHEROID_H

#include "IFormFactorBorn.h"
#include "MemberComplexFunctionIntegrator.h"

//! @class FormFactorTruncatedSpheroid
//! @ingroup formfactors
//! @brief The formfactor of a truncated spheroid.

class BA_CORE_API_ FormFactorTruncatedSpheroid : public IFormFactorBorn
{
public:
    //! @brief TruncatedSpheroid constructor
    //! @param radius of Truncated Spheroid
    //! @param height of Truncated Spheroid
    //! @param flattening parameter in vertical direction (full height: 2 x flattening x radius)

    FormFactorTruncatedSpheroid(double radius, double height, double height_flattening);

    ~FormFactorTruncatedSpheroid() {delete m_integrator;}

    virtual FormFactorTruncatedSpheroid *clone() const;

    virtual void accept(ISampleVisitor *visitor) const { visitor->visit(this); }

    virtual int getNumberOfStochasticParameters() const { return 3; }

    virtual double getHeight() const { return m_height; }

    virtual double getHeightFlattening() const { return m_height_flattening; }

    virtual double getRadius() const { return m_radius; }

    virtual double getHeightFullSpheroid() const
    { return 2.*m_height_flattening*m_radius; }

    virtual complex_t evaluate_for_q(const cvector_t& q) const;

protected:
    virtual bool check_initialization() const;
    virtual void init_parameters();

private:

    complex_t Integrand(double Z, void* params) const;

    double m_radius;
    double m_height;
    double m_height_flattening;
    mutable cvector_t m_q;

    MemberComplexFunctionIntegrator<FormFactorTruncatedSpheroid> *m_integrator;
};


#endif // FORMFACTORTRUNCATEDSPHEROID_H
