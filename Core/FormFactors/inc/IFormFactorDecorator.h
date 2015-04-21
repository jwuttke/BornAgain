// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/inc/IFormFactorDecorator.h
//! @brief     Defines pure virtual interface class IFormFactorDecorator.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef IFORMFACTORDECORATOR_H_
#define IFORMFACTORDECORATOR_H_

#include "IFormFactor.h"

//! @class IFormFactorDecorator
//! @ingroup formfactors_internal
//! @brief Encapsulates another formfactor and adds extra functionality
//! (a scalar factor, a Debye-Waller factor, ...).

class BA_CORE_API_ IFormFactorDecorator : public IFormFactor
{
public:
    IFormFactorDecorator(IFormFactor *p_form_factor)
        : mp_form_factor(p_form_factor) {}
    virtual ~IFormFactorDecorator();
    virtual IFormFactorDecorator *clone() const=0;
    virtual void accept(ISampleVisitor *visitor) const = 0;

    virtual void setAmbientMaterial(const IMaterial& material);

    virtual double getVolume() const;

    virtual double getHeight() const;

    virtual double getRadius() const;

protected:
    IFormFactor *mp_form_factor;
};

inline IFormFactorDecorator::~IFormFactorDecorator()
{
    delete mp_form_factor;
}

inline void IFormFactorDecorator::setAmbientMaterial(const IMaterial& material)
{
    if (mp_form_factor) mp_form_factor->setAmbientMaterial(material);
}

inline double IFormFactorDecorator::getVolume() const
{
    if (mp_form_factor) {
        return mp_form_factor->getVolume();
    }
    return 0.0;
}

inline double IFormFactorDecorator::getHeight() const
{
    if (mp_form_factor) {
        return mp_form_factor->getHeight();
    }
    return 0.0;
}

inline double IFormFactorDecorator::getRadius() const
{
    if (mp_form_factor) {
        return mp_form_factor->getRadius();
    }
    return 0.0;
}

#endif /* IFORMFACTORDECORATOR_H_ */


