// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/FTDistributionItems.h
//! @brief     Defines FTDistribution1DItem's classes
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FTDISTRIBUTIONITEMS_H
#define FTDISTRIBUTIONITEMS_H


#include "ParameterizedItem.h"
#include "FTDistributions.h"


class BA_CORE_API_ FTDistribution1DItem : public ParameterizedItem
{
    Q_OBJECT
public:
    static const QString P_CORR_LENGTH;
    explicit FTDistribution1DItem(const QString name)
        : ParameterizedItem(name){}
    virtual IFTDistribution1D *createFTDistribution() const { return 0;}
    virtual ~FTDistribution1DItem(){}
};

class BA_CORE_API_ FTDistribution1DCauchyItem : public FTDistribution1DItem
{
    Q_OBJECT
public:
    explicit FTDistribution1DCauchyItem();
    virtual IFTDistribution1D *createFTDistribution() const;
};

class BA_CORE_API_ FTDistribution1DGaussItem : public FTDistribution1DItem
{
    Q_OBJECT
public:
    explicit FTDistribution1DGaussItem();
    virtual IFTDistribution1D *createFTDistribution() const;
};

class BA_CORE_API_ FTDistribution1DGateItem : public FTDistribution1DItem
{
    Q_OBJECT
public:
    explicit FTDistribution1DGateItem();
    virtual IFTDistribution1D *createFTDistribution() const;
};

class BA_CORE_API_ FTDistribution1DTriangleItem : public FTDistribution1DItem
{
    Q_OBJECT
public:
    explicit FTDistribution1DTriangleItem();
    virtual IFTDistribution1D *createFTDistribution() const;
};

class BA_CORE_API_ FTDistribution1DCosineItem : public FTDistribution1DItem
{
    Q_OBJECT
public:
    explicit FTDistribution1DCosineItem();
    virtual IFTDistribution1D *createFTDistribution() const;
};

class BA_CORE_API_ FTDistribution1DVoigtItem : public FTDistribution1DItem
{
    Q_OBJECT
public:
    static const QString P_ETA;
    explicit FTDistribution1DVoigtItem();
    virtual IFTDistribution1D *createFTDistribution() const;
};

class BA_CORE_API_ FTDistribution2DItem : public ParameterizedItem
{
    Q_OBJECT
public:
    static const QString P_CORR_LENGTH_X;
    static const QString P_CORR_LENGTH_Y;
    static const QString P_GAMMA;
    explicit FTDistribution2DItem(const QString name)
        : ParameterizedItem(name) {
        registerProperty(P_GAMMA, 0.0);
    }
    virtual IFTDistribution2D *createFTDistribution() const { return 0;}
    virtual ~FTDistribution2DItem(){}
};


class BA_CORE_API_ FTDistribution2DCauchyItem : public FTDistribution2DItem
{
    Q_OBJECT
public:
    explicit FTDistribution2DCauchyItem();
    virtual IFTDistribution2D *createFTDistribution() const;
};


class BA_CORE_API_ FTDistribution2DGaussItem : public FTDistribution2DItem
{
    Q_OBJECT
public:
    explicit FTDistribution2DGaussItem();
    virtual IFTDistribution2D *createFTDistribution() const;
};


class BA_CORE_API_ FTDistribution2DGateItem : public FTDistribution2DItem
{
    Q_OBJECT
public:
    explicit FTDistribution2DGateItem();
    virtual IFTDistribution2D *createFTDistribution() const;
};


class BA_CORE_API_ FTDistribution2DConeItem : public FTDistribution2DItem
{
    Q_OBJECT
public:
    explicit FTDistribution2DConeItem();
    virtual IFTDistribution2D *createFTDistribution() const;
};


class BA_CORE_API_ FTDistribution2DVoigtItem : public FTDistribution2DItem
{
    Q_OBJECT
public:
    static const QString P_ETA;
    explicit FTDistribution2DVoigtItem();
    virtual IFTDistribution2D *createFTDistribution() const;
};


#endif

