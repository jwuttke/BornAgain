// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Minimizer/KernelTypes.h
//! @brief     Defines common types for fitting library.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef KERNELTYPES_H
#define KERNELTYPES_H

#include <functional>
#include <vector>

namespace Fit { class Parameters; }

using scalar_function_t = std::function<double(const std::vector<double>&)>;

using gradient_function_t
    = std::function<double(const std::vector<double>&, unsigned int, std::vector<double>&)>;

using root_objective_t = std::function<double(const double*)>;

using root_gradient_t = std::function<double(const double*, unsigned int, double*)>;

using fcn_scalar_t = std::function<double(const Fit::Parameters&)>;
using fcn_residual_t = std::function<std::vector<double>(const Fit::Parameters&)>;

#endif // KERNELTYPES_H
