// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/BeamWavelengthItem.cpp
//! @brief     Implements class BeamWavelengthItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "BeamAngleItems.h"
#include "item_constants.h"
#include "Distributions.h"
#include "Units.h"


BeamInclinationAngleItem::BeamInclinationAngleItem(ParameterizedItem *parent)
    : BeamDistributionItem(Constants::BeamInclinationAngleType, parent)
{
    setItemName(Constants::BeamInclinationAngleType);
    setPropertyAttribute(BeamDistributionItem::P_CACHED_VALUE, PropertyAttribute(PropertyAttribute::HIDDEN, AttLimits::limited(0.0, 90.0), 2));
    setRegisteredProperty(BeamDistributionItem::P_CACHED_VALUE, 0.2);

    ParameterizedItem *distribution = dynamic_cast<DistributionNoneItem *>(getSubItems()[P_DISTRIBUTION]);
    Q_ASSERT(distribution);
    distribution->setPropertyAttribute(DistributionNoneItem::P_VALUE, PropertyAttribute(AttLimits::limited(0.0, 90.0), 2));
}

IDistribution1D *BeamInclinationAngleItem::createDistribution1D()
{
    IDistribution1D *result(0);
    if(DistributionItem *distributionItem = dynamic_cast<DistributionItem *>(getSubItems()[P_DISTRIBUTION])) {
        result = BeamAngleHelper::creatAngleDistribution(distributionItem);
    }
    return result;
}

// -------------------------------------------------------------------------- //

BeamAzimuthalAngleItem::BeamAzimuthalAngleItem(ParameterizedItem *parent)
    : BeamDistributionItem(Constants::BeamAzimuthalAngleType, parent)
{
    setItemName(Constants::BeamAzimuthalAngleType);
    setRegisteredProperty(BeamDistributionItem::P_CACHED_VALUE, 0.0);
    setPropertyAttribute(BeamDistributionItem::P_CACHED_VALUE, PropertyAttribute(PropertyAttribute::HIDDEN, AttLimits::limited(-90.0, 90.0), 2));
    ParameterizedItem *distribution = dynamic_cast<DistributionNoneItem *>(getSubItems()[P_DISTRIBUTION]);
    Q_ASSERT(distribution);
    distribution->setPropertyAttribute(DistributionNoneItem::P_VALUE, PropertyAttribute(AttLimits::limited(-90.0, 90.0), 2));
}

IDistribution1D *BeamAzimuthalAngleItem::createDistribution1D()
{
    IDistribution1D *result(0);
    if(DistributionItem *distributionItem = dynamic_cast<DistributionItem *>(getSubItems()[P_DISTRIBUTION])) {
        result = BeamAngleHelper::creatAngleDistribution(distributionItem);
    }
    return result;
}

// -------------------------------------------------------------------------- //

IDistribution1D *BeamAngleHelper::creatAngleDistribution(DistributionItem *distributionItem)
{

    IDistribution1D *result(0);
    if(distributionItem->modelType() == Constants::DistributionGateType) {
        double min = distributionItem->getRegisteredProperty(DistributionGateItem::P_MIN).toDouble();
        double max = distributionItem->getRegisteredProperty(DistributionGateItem::P_MAX).toDouble();
        result = new DistributionGate(Units::deg2rad(min), Units::deg2rad(max));
    }
    else if(distributionItem->modelType() == Constants::DistributionLorentzType) {
        double mean = distributionItem->getRegisteredProperty(DistributionLorentzItem::P_MEAN).toDouble();
        double hwhm = distributionItem->getRegisteredProperty(DistributionLorentzItem::P_HWHM).toDouble();
        result = new DistributionLorentz(Units::deg2rad(mean), Units::deg2rad(hwhm));
    }
    else if(distributionItem->modelType() == Constants::DistributionGaussianType) {
        double mean = distributionItem->getRegisteredProperty(DistributionGaussianItem::P_MEAN).toDouble();
        double std_dev = distributionItem->getRegisteredProperty(DistributionGaussianItem::P_STD_DEV).toDouble();
        result = new DistributionGaussian(Units::deg2rad(mean), Units::deg2rad(std_dev));
    }
    else if(distributionItem->modelType() == Constants::DistributionLogNormalType) {
        double median = distributionItem->getRegisteredProperty(DistributionLogNormalItem::P_MEDIAN).toDouble();
        double scale_par = distributionItem->getRegisteredProperty(DistributionLogNormalItem::P_SCALE_PAR).toDouble();
        return new DistributionLogNormal(Units::deg2rad(median), scale_par);
    }
    else if(distributionItem->modelType() == Constants::DistributionCosineType) {
        double mean = distributionItem->getRegisteredProperty(DistributionCosineItem::P_MEAN).toDouble();
        double sigma = distributionItem->getRegisteredProperty(DistributionCosineItem::P_SIGMA).toDouble();
        return new DistributionCosine(Units::deg2rad(mean), Units::deg2rad(sigma));
    }
    return result;
}
