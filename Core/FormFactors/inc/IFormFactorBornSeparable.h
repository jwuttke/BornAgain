// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/inc/IFormFactorBornSeparable.h
//! @brief     Defines pure virtual interface class IFormFactorBornSeparable.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef IFORMFACTORBORNSEPARABLE_H_
#define IFORMFACTORBORNSEPARABLE_H_

#include "IFormFactorBorn.h"

//! @class IFormFactorBornSeparable
//! @ingroup formfactors_internal
//! @brief Separable Born formfactor interface. Scattering amplitude only
//! depends on q, and separates into a radial and a z-dependent part.

class BA_CORE_API_ IFormFactorBornSeparable : public IFormFactorBorn
{
public:
    IFormFactorBornSeparable();
    virtual ~IFormFactorBornSeparable() {}
    virtual IFormFactorBornSeparable *clone() const=0;

    virtual complex_t evaluate(const cvector_t& k_i, const Bin1DCVector& k_f_bin, double alpha_i, double alpha_f) const;

    virtual complex_t evaluate_for_q(const cvector_t& q) const;

protected:
    //! evaluate radial part of scattering amplitude for complex wavevector
    virtual complex_t evaluate_for_q_radial(const cvector_t& q) const=0;

    //! evaluate z-part of scattering amplitude for complex wavevector
    virtual complex_t evaluate_for_q_z(const cvector_t& q) const=0;
};

inline complex_t IFormFactorBornSeparable::evaluate(const cvector_t& k_i,
        const Bin1DCVector& k_f_bin, double alpha_i, double alpha_f) const
{
    (void)alpha_i;
    (void)alpha_f;
    complex_t radial, zpart;
    Bin1DCVector q_bin(k_i - k_f_bin.m_q_lower, k_i - k_f_bin.m_q_upper);
    double delta_qr = std::abs( q_bin.getDelta().magxy() );
    if ( delta_qr > Units::PID2/getRadius() ) {
        radial = bigRadialPart(q_bin);
    } else {
    radial = evaluate_for_q_radial(q_bin.getMidPoint());
    }
    double delta_qz = std::abs( q_bin.getDelta().z() );
    if ( delta_qz > Units::PID2/getHeight() ) {
        zpart = bigZPart(q_bin);
    } else {
        zpart = evaluate_for_q_z(q_bin.getMidPoint());
    }
    return getVolume()*radial*zpart;
}

inline complex_t IFormFactorBornSeparable::evaluate_for_q(const cvector_t& q) const
{
    return getVolume()*evaluate_for_q_radial(q)*evaluate_for_q_z(q);
}

#endif /* IFORMFACTORBORNSEPARABLE_H_ */


