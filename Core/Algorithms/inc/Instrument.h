// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/inc/Instrument.h
//! @brief     Defines class Instrument.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef INSTRUMENT_H_
#define INSTRUMENT_H_

#include "Beam.h"
#include "Detector.h"
#include "IResolutionFunction2D.h"

//! @class Instrument
//! @ingroup simulation_internal
//! @brief Assembles beam, detector and their relative positions wrt the sample.

class BA_CORE_API_ Instrument : public IParameterized
{
public:
    Instrument();
    Instrument(const Instrument& other);

    ~Instrument() {}

    //! Returns the beam data
    Beam getBeam() const;

    //! Sets the beam data
    void setBeam(const Beam &beam);

    //! Sets the beam wavelength and incoming angles
    void setBeamParameters(double wavelength, double alpha_i, double phi_i);

    //! Sets the beam's intensity
    void setBeamIntensity(double intensity) { m_beam.setIntensity(intensity); }

    //! Returns the beam's intensity
    double getIntensity() const { return m_beam.getIntensity(); }

    //! Returns the detector data
    Detector getDetector() const;

    //! Returns a detector axis
    const IAxis& getDetectorAxis(size_t index) const;

    //! Returns the detector's dimension
    size_t getDetectorDimension() const { return m_detector.getDimension(); }

    //! Sets detector parameters using axes of output data
    void matchDetectorParameters(const OutputData<double >& output_data);

    //! Sets detector parameters using angle ranges
    void setDetectorParameters(size_t n_phi, double phi_f_min, double phi_f_max,
            size_t n_alpha, double alpha_f_min, double alpha_f_max, bool isgisaxs_style=false);

    //! Sets detector parameters using parameter object
    void setDetectorParameters(const DetectorParameters& params);

    //! Sets detector parameters using axes
    void setDetectorAxes(const IAxis &axis0, const IAxis &axis1);

    //! Sets detector resolution function
    void setDetectorResolutionFunction(IResolutionFunction2D *p_resolution_function);
    void setDetectorResolutionFunction(const IResolutionFunction2D &p_resolution_function);

#ifndef GCCXML_SKIP_THIS
    //! apply the detector resolution to the given intensity map
    void applyDetectorResolution(OutputData<double> *p_intensity_map,
            OutputData<Eigen::Matrix2d> *p_matrix_intensity=0) const;
#endif
    //! Adds parameters from local pool to external pool and call recursion over direct children
    virtual std::string addParametersToExternalPool(std::string path, ParameterPool *external_pool, int copy_number=-1) const;

#ifndef GCCXML_SKIP_THIS
    //! normalize a detector image
    void normalize(OutputData<double> *p_intensity,
            OutputData<Eigen::Matrix2d> *p_polarized_intensity = 0) const;
#endif

protected:
    virtual void print(std::ostream& ostr) const;

    //! Registers some class members for later access via parameter pool
    virtual void init_parameters();

    Detector m_detector;
    Beam m_beam;

};

inline Beam Instrument::getBeam() const
{
    return m_beam;
}

inline void Instrument::setBeam(const Beam &beam)
{
    m_beam = beam;
}

inline void Instrument::setBeamParameters(double wavelength, double alpha_i, double phi_i)
{
    m_beam.setCentralK(wavelength, alpha_i, phi_i);
}

inline Detector Instrument::getDetector() const
{
    return m_detector;
}

inline const IAxis& Instrument::getDetectorAxis(size_t index) const
{
    return m_detector.getAxis(index);
}

#endif /* INSTRUMENT_H_ */
