// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/inc/FormFactorGauss.h
//! @brief     Defines class FormFactorGauss.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORGAUSS_H_
#define FORMFACTORGAUSS_H_

#include "IFormFactorBorn.h"

//! @class FormFactorGauss
//! @ingroup formfactors
//! @brief The formfactor of a gaussian.

class BA_CORE_API_ FormFactorGauss : public IFormFactorBorn
{
public:
    FormFactorGauss(double volume);
    FormFactorGauss(double width, double height);
    ~FormFactorGauss() {}
    virtual FormFactorGauss *clone() const;

    virtual void accept(ISampleVisitor *visitor) const { visitor->visit(this); }

    virtual int getNumberOfStochasticParameters() const { return 2; }

    virtual complex_t evaluate_for_q(const cvector_t& q) const;

    //! Returns volume
    virtual double getVolume() const {
        return m_width*m_width*m_height;
    }

    //! Returns height
    double getHeight() const { return m_height; }

    //! Returns radius of Box
    double getRadius() const { return m_width; }

protected:
    virtual bool check_initialization() const;
    virtual void init_parameters();

private:
    double m_width;
    double m_height;
    double m_max_ql;
};

#endif /* FORMFACTORGAUSS_H_ */


