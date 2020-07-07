// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/TestMachinery/TestUtils.h
//! @brief     Defines TestUtils namespace.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef TESTUTILS_H
#define TESTUTILS_H

#include "Core/Instrument/OutputData.h"
#include "Tests/Functional/TestMachinery/StandardTestInfo.h"
#include "Wrap/WinDllMacros.h"

namespace TestUtils
{

//! Returns test info for given set of command line parameters.
BA_CORE_API_ StandardTestInfo testInfo(int argc, char** argv);

//! Returns true if intensity maps are the same within given threshold.
BA_CORE_API_ bool isTheSame(const OutputData<double>& dat, const OutputData<double>& ref,
                            double threshold);

//! Executes script in external (system) Python interpreter
BA_CORE_API_ bool runPython(const std::string& py_command);

} // namespace TestUtils

#endif
