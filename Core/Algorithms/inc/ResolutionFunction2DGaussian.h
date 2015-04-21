// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/inc/ResolutionFunction2DGaussian.h
//! @brief     Defines class ResolutionFunction2DGaussian.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef RESOLUTIONFUNCTION2DGAUSSIAN_H
#define RESOLUTIONFUNCTION2DGAUSSIAN_H

#include "IResolutionFunction2D.h"

//! @class ResolutionFunction2DGaussian
//! @ingroup algorithms_internal
//! @brief Simple gaussian two-dimensional resolution function.

class BA_CORE_API_ ResolutionFunction2DGaussian : public IResolutionFunction2D
{
public:
    ResolutionFunction2DGaussian(double sigma_x, double sigma_y);
    virtual ~ResolutionFunction2DGaussian();

    virtual double evaluateCDF(double x, double y) const;

    ResolutionFunction2DGaussian *clone() const;

    double getSigmaX() const { return m_sigma_x; }
    double getSigmaY() const { return m_sigma_y; }

protected:
    virtual void init_parameters();
private:
    ResolutionFunction2DGaussian(const ResolutionFunction2DGaussian& other);
    ResolutionFunction2DGaussian& operator=(const ResolutionFunction2DGaussian& );

    double m_sigma_x;
    double m_sigma_y;
};

#endif /* RESOLUTIONFUNCTION2DGAUSSIAN_H */
