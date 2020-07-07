// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Tools/PyEmbeddedUtils.h
//! @brief     Defines PyEmbeddedUtils namespace
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef PYEMBEDDEDUTILS_H
#define PYEMBEDDEDUTILS_H

#include "Core/Tools/PyObject.h"
#include "Wrap/WinDllMacros.h"
#include <memory>
#include <string>
#include <vector>

class MultiLayer;

namespace PyEmbeddedUtils
{

//! Converts PyObject into string, if possible, or throws exception.
BA_CORE_API_ std::string toString(PyObject* obj);

//! Converts PyObject into vector of strings, if possible, or throws exception.
BA_CORE_API_ std::vector<std::string> toVectorString(PyObject* obj);

//! Converts char to string. In the case of nullptr will return an empty string.
BA_CORE_API_ std::string toString(char* c);
BA_CORE_API_ std::string toString(wchar_t* c);

//! Imports BornAgain from given location. If path is empty, tries to rely on PYTHONPATH.
BA_CORE_API_ void import_bornagain(const std::string& path = std::string());

//! Returns multi-line string representing PATH, PYTHONPATH, sys.path and other info.
BA_CORE_API_ std::string pythonRuntimeInfo();

//! Returns string representing python stack trace.
BA_CORE_API_ std::string pythonStackTrace();
} // namespace PyEmbeddedUtils

#endif
