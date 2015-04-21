// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/inc/Beam.h
//! @brief     Defines class Beam.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef BEAM_H_
#define BEAM_H_

#include "Types.h"
#include "IParameterized.h"
#include "EigenCore.h"

//! @class Beam
//! @ingroup simulation
//! @brief Ideal collimated beam defined by wavelength, direction and intensity.

class BA_CORE_API_ Beam : public IParameterized
{
public:
    Beam();
    Beam(const Beam& other);
    Beam& operator=(const Beam& other);

    virtual ~Beam() {}

    //! Get the value of the wavevector
    cvector_t getCentralK() const;

    //! Sets the value of the incoming wavevector in terms of wavelength
    //! and incoming angles
    void setCentralK(double wavelength, double alpha_i, double phi_i);

    //! Gets the beam intensity in neutrons/sec
    double getIntensity() const { return m_intensity; }

    //! Sets the beam intensity in neutrons/sec
    void setIntensity(double intensity) { m_intensity = intensity; }

#ifndef GCCXML_SKIP_THIS
    //! Gets the polarization density matrix (in spin basis along z-axis)
    Eigen::Matrix2cd getPolarization() const { return m_polarization; }
#endif

#ifndef GCCXML_SKIP_THIS
    //! Sets the polarization density matrix (in spin basis along z-axis)
    void setPolarization(const Eigen::Matrix2cd &polarization);
#endif

    //! Sets the polarization density matrix to a value representing
    //! a mixed ensemble with the given fraction of positive z spin
    void SetSpinUpFraction(double up_fraction);

#ifndef GCCXML_SKIP_THIS
    //! Checks if the given matrix can represent a physical density matrix
    bool checkPolarization(const Eigen::Matrix2cd &polarization) const;
#endif

    double getWavelength() const { return m_wavelength; }
    double getAlpha() const { return m_alpha; }
    double getPhi() const { return m_phi;}

protected:
    virtual void print(std::ostream& ostr) const;
    //! Registers some class members for later access via parameter pool
    virtual void init_parameters();

private:
    //! swap function
    void swapContent(Beam& other);

    //! Initialize polarization (for constructors)
    void initPolarization();

    double m_wavelength, m_alpha, m_phi; //!< wavelength and angles of beam
    double m_intensity;     //!< beam intensity (neutrons/sec)
#ifndef GCCXML_SKIP_THIS
    Eigen::Matrix2cd m_polarization; //!< polarization density matrix
#endif
};

#endif /* BEAM_H_ */
