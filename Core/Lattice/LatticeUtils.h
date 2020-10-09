// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Lattice/LatticeUtils.h
//! @brief     Defines factory functions for different types of lattices and orientations.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_LATTICE_LATTICEUTILS_H
#define BORNAGAIN_CORE_LATTICE_LATTICEUTILS_H

#include "Base/Vector/Vectors3D.h"
#include "Core/Lattice/Lattice.h"

class ILatticeOrientation;

namespace LatticeUtils
{
Lattice createFCCLattice(double lattice_constant, const ILatticeOrientation& orientation);
Lattice createHCPLattice(double a, double c, const ILatticeOrientation& orientation);
Lattice createBCTLattice(double a, double c, const ILatticeOrientation& orientation);
} // namespace LatticeUtils

#endif // BORNAGAIN_CORE_LATTICE_LATTICEUTILS_H
