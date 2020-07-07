// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Tools/PyImport.h
//! @brief     Defines PyImport namespace
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_TOOLS_PYIMPORT_H
#define BORNAGAIN_CORE_TOOLS_PYIMPORT_H

#include "Wrap/WinDllMacros.h"
#include <memory>
#include <string>
#include <vector>

class MultiLayer;

namespace PyImport
{

////! Returns directory name
// std::string bornagainPythonDir();

//! Creates a multi layer by running python code in embedded interpreter.
//! @param script: Python script
//! @param functionName: A function name in this script which produces a MultiLayer
//! @param path: A path to import BornAgain library. If empty, relies on PYTHONPATH
BA_CORE_API_ std::unique_ptr<MultiLayer> createFromPython(const std::string& script,
                                                          const std::string& functionName,
                                                          const std::string& path = std::string());

//! Returns list of functions defined in the script.
//! @param script: Python script
//! @param path: A path to import BornAgain library. If empty, relies on PYTHONPATH
BA_CORE_API_ std::vector<std::string> listOfFunctions(const std::string& script,
                                                      const std::string& path = std::string());
} // namespace PyImport

#endif // BORNAGAIN_CORE_TOOLS_PYIMPORT_H
