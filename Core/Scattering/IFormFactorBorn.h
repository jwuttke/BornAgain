// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Scattering/IFormFactorBorn.h
//! @brief     Defines pure virtual interface class IFormFactorBorn.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef IFORMFACTORBORN_H
#define IFORMFACTORBORN_H

#include "IFormFactor.h"
#include "Vectors3D.h"

//! Pure virtual base class for Born form factors.
//! In contrast to the generic IFormFactor, a Born form factor does not depend
//! on the incoming and outgoing wave vectors ki and kf, except through their
//! difference, the scattering vector q=ki-kf.

//! @ingroup formfactors_internal

class BA_CORE_API_ IFormFactorBorn : public IFormFactor
{
public:
    IFormFactorBorn() {}
    virtual ~IFormFactorBorn() {}

    virtual IFormFactorBorn* clone() const=0;

    virtual complex_t evaluate(const WavevectorInfo& wavevectors) const;

    //! Returns scattering amplitude for complex scattering wavevector q=k_i-k_f.
    virtual complex_t evaluate_for_q(const cvector_t q) const=0;
};

#ifdef POLYHEDRAL_DIAGNOSTIC
//! Information about the latest form factor evaluation. Not thread-safe.
//! Used only by external test program.
class Diagnosis {
public:
    int maxOrder;
    int nExpandedFaces;
    int debmsg;
    bool request_convergence;
    bool operator!=( const Diagnosis& other ) const {
        return maxOrder!=other.maxOrder || nExpandedFaces!=other.nExpandedFaces; }
    friend std::ostream& operator<< (std::ostream& stream, const Diagnosis& diag) {
        return stream<<" ["<<diag.nExpandedFaces<<":"<<diag.maxOrder<<"]";
    }
};
#endif

#endif // IFORMFACTORBORN_H
