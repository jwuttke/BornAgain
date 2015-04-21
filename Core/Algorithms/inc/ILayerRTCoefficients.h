// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/inc/ILayerRTCoefficients.h
//! @brief     Defines class ILayerRTCoefficients.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ILAYERRTCOEFFICIENTS_H_
#define ILAYERRTCOEFFICIENTS_H_

#include "Types.h"
#include "EigenCore.h"


//! @class ILayerRTCoefficients
//! @ingroup algorithms_internal
//! @brief Interface to access reflection/transmition coefficients

class BA_CORE_API_ ILayerRTCoefficients
{
public:
    virtual ~ILayerRTCoefficients() {}

    virtual ILayerRTCoefficients* clone() const=0;

#ifndef GCCXML_SKIP_THIS
    //! The following functions return the transmitted and reflected amplitudes
    //! for different incoming beam polarizations and eigenmodes
    virtual Eigen::Vector2cd T1plus() const=0;
    virtual Eigen::Vector2cd R1plus() const=0;
    virtual Eigen::Vector2cd T2plus() const=0;
    virtual Eigen::Vector2cd R2plus() const=0;
    virtual Eigen::Vector2cd T1min() const=0;
    virtual Eigen::Vector2cd R1min() const=0;
    virtual Eigen::Vector2cd T2min() const=0;
    virtual Eigen::Vector2cd R2min() const=0;
    //! Returns z-part of the two wavevector eigenmodes
    virtual Eigen::Vector2cd getKz() const=0;
    //! Scalar value getters; these throw errors by default as they should only
    //! be used when the derived object is really scalar
#endif
    virtual complex_t getScalarT() const {
        throw Exceptions::NotImplementedException("ILayerRTCoefficients::"
                "getScalarT(): coefficients are not scalar.");
    }
    virtual complex_t getScalarR() const {
        throw Exceptions::NotImplementedException("ILayerRTCoefficients::"
                "getScalarR(): coefficients are not scalar.");
    }
    virtual complex_t getScalarKz() const {
        throw Exceptions::NotImplementedException("ILayerRTCoefficients::"
                "getScalarKz(): coefficients are not scalar.");
    }
};


#endif /* ILAYERRTCOEFFICIENTS_H_ */
