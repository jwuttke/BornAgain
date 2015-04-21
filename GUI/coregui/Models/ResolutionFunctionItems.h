// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/ResolutionFunctionItems.h
//! @brief     Defines family of ResolutionFunctionItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef RESOLUTIONFUNCTIONITEMS_H
#define RESOLUTIONFUNCTIONITEMS_H

#include "ParameterizedItem.h"
#include "ResolutionFunction2DGaussian.h"


class BA_CORE_API_ ResolutionFunctionItem : public ParameterizedItem
{
    Q_OBJECT
public:
    explicit ResolutionFunctionItem(const QString name, ParameterizedItem *parent=0);
    virtual ~ResolutionFunctionItem() {}

    virtual IResolutionFunction2D *createResolutionFunction() const=0;
};

class BA_CORE_API_ ResolutionFunctionNoneItem : public ResolutionFunctionItem
{
    Q_OBJECT
public:
    explicit ResolutionFunctionNoneItem(ParameterizedItem *parent=0);
    virtual IResolutionFunction2D *createResolutionFunction() const;
};

class BA_CORE_API_ ResolutionFunction2DGaussianItem : public ResolutionFunctionItem
{
    Q_OBJECT
public:
    static const QString P_SIGMA_X;
    static const QString P_SIGMA_Y;
    explicit ResolutionFunction2DGaussianItem(ParameterizedItem *parent=0);
    virtual IResolutionFunction2D *createResolutionFunction() const;
};



#endif // DISTRIBUTIONITEM_H

