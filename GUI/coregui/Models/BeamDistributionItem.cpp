// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/BeamDistributionItem.cpp
//! @brief     Implements class BeamDistributionItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "BeamDistributionItem.h"
#include "DistributionItem.h"
#include "ParameterDistribution.h"
#include "Units.h"
#include <QDebug>
#include <boost/scoped_ptr.hpp>


const QString BeamDistributionItem::P_DISTRIBUTION = "Distribution";
const QString BeamDistributionItem::P_CACHED_VALUE = "Cached value";

BeamDistributionItem::BeamDistributionItem(const QString name, ParameterizedItem *parent)
    : ParameterizedItem(name, parent)
{
    setItemName(Constants::BeamDistributionType);
    registerProperty(P_CACHED_VALUE, 0.0, PropertyAttribute(PropertyAttribute::HIDDEN));
    registerGroupProperty(P_DISTRIBUTION, Constants::DistributionExtendedGroup);
    setGroupProperty(P_DISTRIBUTION, Constants::DistributionNoneType);
}

void BeamDistributionItem::onPropertyChange(const QString &name)
{
    if(name == P_CACHED_VALUE) {
        DistributionItem *distribution = dynamic_cast<DistributionItem *>(getSubItems()[P_DISTRIBUTION]);
        if(distribution) {
            double cached_value = getRegisteredProperty(P_CACHED_VALUE).toDouble();
            PropertyAttribute cached_attribute = getPropertyAttribute(P_CACHED_VALUE);
            cached_attribute.setAppearance(PropertyAttribute::VISIBLE);
            // do not propagate this change back to me, or I will enter an infinite
            // signal-slot loop
            disconnect(getSubItems()[P_DISTRIBUTION], SIGNAL(propertyChanged(QString)),
                    this, SLOT(processSubItemPropertyChanged(QString)) );
            distribution->init_parameters(cached_value, cached_attribute);
            connect(getSubItems()[P_DISTRIBUTION], SIGNAL(propertyChanged(QString)),
                    this, SLOT(processSubItemPropertyChanged(QString)), Qt::UniqueConnection);
        }
    }
}

//! returns parameter distribution to add into the Simulation
ParameterDistribution *BeamDistributionItem::getParameterDistributionForName(const QString &parameter_name)
{
    ParameterDistribution *result(0);
    if(DistributionItem *distributionItem = dynamic_cast<DistributionItem *>(getSubItems()[P_DISTRIBUTION])) {
        boost::scoped_ptr<IDistribution1D> distribution(createDistribution1D());

        if(distribution) {
            int nbr_samples = distributionItem->getRegisteredProperty(DistributionItem::P_NUMBER_OF_SAMPLES).toInt();
            double sigma_factor(0);
            if(distributionItem->isRegisteredProperty(DistributionItem::P_SIGMA_FACTOR)) {
                sigma_factor = distributionItem->getRegisteredProperty(DistributionItem::P_SIGMA_FACTOR).toInt();
            }

            PropertyAttribute cached_attribute = getPropertyAttribute(P_CACHED_VALUE);
            AttLimits limits;
            if(modelType() == Constants::BeamWavelengthType) {
                limits = cached_attribute.getLimits();
            } else {
                AttLimits orig = cached_attribute.getLimits();
                if(orig.hasLowerLimit()) limits.setLowerLimit(Units::deg2rad(orig.getLowerLimit()));
                if(orig.hasUpperLimit()) limits.setUpperLimit(Units::deg2rad(orig.getUpperLimit()));
            }
            result = new ParameterDistribution(parameter_name.toStdString(), *distribution, nbr_samples, sigma_factor, limits);
        }
    }
    return result;
}

//! updates new DistributionItem with cached_value
void BeamDistributionItem::onSubItemChanged(const QString &propertyName)
{
    qDebug() << "BeamWavelengthItem::onSubItemChanged(const QString &propertyName)" << propertyName;
    if(propertyName == P_DISTRIBUTION) {
        DistributionItem *distribution = dynamic_cast<DistributionItem *>(getSubItems()[P_DISTRIBUTION]);
        Q_ASSERT(distribution);
        double cached_value = getRegisteredProperty(P_CACHED_VALUE).toDouble();
        PropertyAttribute cached_attribute = getPropertyAttribute(P_CACHED_VALUE);
        cached_attribute.setAppearance(PropertyAttribute::VISIBLE);
        distribution->init_parameters(cached_value, cached_attribute);
    }
    ParameterizedItem::onSubItemChanged(propertyName);
}

void BeamDistributionItem::onSubItemPropertyChanged(const QString &property_group, const QString &property_name)
{
    qDebug() << "BeamWavelengthItem::onSubItemPropertyChanged(const QString &property_group, const QString &property_name)" << property_group << property_name;
    if(property_group == P_DISTRIBUTION && property_name == DistributionNoneItem::P_VALUE) {
        double value_to_cache = getSubItems()[P_DISTRIBUTION]->
                getRegisteredProperty(DistributionNoneItem::P_VALUE).toDouble();
        setRegisteredProperty(P_CACHED_VALUE, value_to_cache);
    }
    ParameterizedItem::onSubItemPropertyChanged(property_group, property_name);
}

IDistribution1D *BeamDistributionItem::createDistribution1D()
{
    IDistribution1D *result(0);
    if(DistributionItem *distributionItem = dynamic_cast<DistributionItem *>(getSubItems()[P_DISTRIBUTION])) {
        result = distributionItem->createDistribution();
    }
    return result;
}
