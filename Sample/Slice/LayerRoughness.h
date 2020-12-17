//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      Sample/Slice/LayerRoughness.h
//! @brief     Defines class LayerRoughness.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_SAMPLE_SLICE_LAYERROUGHNESS_H
#define BORNAGAIN_SAMPLE_SLICE_LAYERROUGHNESS_H

#include "Sample/Scattering/ISampleNode.h"

//! A roughness of interface between two layers.
//!
//! Based on the article
//! D.K.G. de Boer, Physical review B, Volume 51, Number 8, 15 February 1995
//! "X-ray reflection and transmission by rough surfaces"
//!
//! @ingroup samples

class LayerRoughness : public ISampleNode {
public:
    LayerRoughness(double sigma, double hurstParameter, double lateralCorrLength);
    LayerRoughness();

    LayerRoughness* clone() const
    {
        return new LayerRoughness(m_sigma, m_hurstParameter, m_lateralCorrLength);
    }
    virtual void accept(INodeVisitor* visitor) const { visitor->visit(this); }

    //! Returns power spectral density of the surface roughness
    double getSpectralFun(const kvector_t kvec) const;

    double getCorrFun(const kvector_t k) const;

    //! Sets rms of roughness
    void setSigma(double sigma) { m_sigma = sigma; }
    //! Returns rms of roughness
    double getSigma() const { return m_sigma; }

    //! Sets hurst parameter. It describes how jagged the surface is.
    void setHurstParameter(double hurstParameter) { m_hurstParameter = hurstParameter; }
    //! Returns hurst parameter
    double getHurstParameter() const { return m_hurstParameter; }

    //! Sets lateral correlation length
    void setLatteralCorrLength(double lateralCorrLength)
    {
        m_lateralCorrLength = lateralCorrLength;
    }
    //! Returns lateral correlation length
    double getLatteralCorrLength() const { return m_lateralCorrLength; }

private:
    double m_sigma;          //!< rms of roughness
    double m_hurstParameter; //!< Hurst parameter which describes how jagged the interface, 0<H<=1
    double m_lateralCorrLength; //!< lateral correlation length of the roughness
};

#endif // BORNAGAIN_SAMPLE_SLICE_LAYERROUGHNESS_H
