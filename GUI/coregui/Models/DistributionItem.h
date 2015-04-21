// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/DistributionItem.h
//! @brief     Defines class DistributionItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef DISTRIBUTIONITEM_H
#define DISTRIBUTIONITEM_H

#include "ParameterizedItem.h"
#include "Distributions.h"


class BA_CORE_API_ DistributionItem : public ParameterizedItem
{
    Q_OBJECT
public:
    static const QString P_NUMBER_OF_SAMPLES;
    static const QString P_SIGMA_FACTOR;
    explicit DistributionItem(const QString name, ParameterizedItem *parent=0);
    virtual ~DistributionItem() {}

    virtual IDistribution1D *createDistribution() const=0;

    virtual void init_parameters(double, PropertyAttribute){}
protected:
    void register_number_of_samples();
    void register_sigma_factor();
};

class BA_CORE_API_ DistributionNoneItem : public DistributionItem
{
    Q_OBJECT
public:
    static const QString P_VALUE;
    explicit DistributionNoneItem(ParameterizedItem *parent=0);
    virtual IDistribution1D *createDistribution() const;
    virtual void init_parameters(double value, PropertyAttribute attribute);
};


class BA_CORE_API_ DistributionGateItem : public DistributionItem
{
    Q_OBJECT
public:
    static const QString P_MIN;
    static const QString P_MAX;
    explicit DistributionGateItem(ParameterizedItem *parent=0);

    virtual IDistribution1D *createDistribution() const;
    virtual void init_parameters(double value, PropertyAttribute attribute);
};


class BA_CORE_API_ DistributionLorentzItem : public DistributionItem
{
    Q_OBJECT
public:
    static const QString P_MEAN;
    static const QString P_HWHM;
    explicit DistributionLorentzItem(ParameterizedItem *parent=0);

    virtual IDistribution1D *createDistribution() const;
    virtual void init_parameters(double value, PropertyAttribute attribute);
};


class BA_CORE_API_ DistributionGaussianItem : public DistributionItem
{
    Q_OBJECT
public:
    static const QString P_MEAN;
    static const QString P_STD_DEV;
    explicit DistributionGaussianItem(ParameterizedItem *parent=0);

    virtual IDistribution1D *createDistribution() const;
    virtual void init_parameters(double value, PropertyAttribute attribute);
};


class BA_CORE_API_ DistributionLogNormalItem : public DistributionItem
{
    Q_OBJECT
public:
    static const QString P_MEDIAN;
    static const QString P_SCALE_PAR;
    explicit DistributionLogNormalItem(ParameterizedItem *parent=0);

    virtual IDistribution1D *createDistribution() const;
    virtual void init_parameters(double value, PropertyAttribute attribute);
};


class BA_CORE_API_ DistributionCosineItem : public DistributionItem
{
    Q_OBJECT
public:
    static const QString P_MEAN;
    static const QString P_SIGMA;
    explicit DistributionCosineItem(ParameterizedItem *parent=0);

    virtual IDistribution1D *createDistribution() const;
    virtual void init_parameters(double value, PropertyAttribute attribute);
};

#endif // DISTRIBUTIONITEM_H

