// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/ResolutionFunctionItems.cpp
//! @brief     Implements family of ResolutionFunctionItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ResolutionFunctionItems.h"
#include "ComboProperty.h"
#include "Units.h"
#include <QDebug>

ResolutionFunctionItem::ResolutionFunctionItem(const QString name, ParameterizedItem *parent)
    : ParameterizedItem(name, parent)
{

}

/* ------------------------------------------------ */

ResolutionFunctionNoneItem::ResolutionFunctionNoneItem(ParameterizedItem *parent)
    : ResolutionFunctionItem(Constants::ResolutionFunctionNoneType, parent)
{
    setItemName(Constants::ResolutionFunctionNoneType);
}

IResolutionFunction2D *ResolutionFunctionNoneItem::createResolutionFunction() const
{
    return 0;
}

/* ------------------------------------------------ */

const QString ResolutionFunction2DGaussianItem::P_SIGMA_X = "Sigma phi";
const QString ResolutionFunction2DGaussianItem::P_SIGMA_Y = "Sigma alpha";

ResolutionFunction2DGaussianItem::ResolutionFunction2DGaussianItem(ParameterizedItem *parent)
    : ResolutionFunctionItem(Constants::ResolutionFunction2DGaussianType, parent)
{
    setItemName(Constants::ResolutionFunction2DGaussianType);
    registerProperty(P_SIGMA_X, 0.02, PropertyAttribute(AttLimits::lowerLimited(0.0), 3));
    registerProperty(P_SIGMA_Y, 0.02, PropertyAttribute(AttLimits::lowerLimited(0.0), 3));
}

IResolutionFunction2D *ResolutionFunction2DGaussianItem::createResolutionFunction() const
{
    double sigma_x = Units::deg2rad(getRegisteredProperty(P_SIGMA_X).toDouble());
    double sigma_y = Units::deg2rad(getRegisteredProperty(P_SIGMA_Y).toDouble());
    return new ResolutionFunction2DGaussian(sigma_x, sigma_y);
}
