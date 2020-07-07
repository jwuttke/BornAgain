// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Python/PyEmbedded/PyEmbeddedTestFactory.cpp
//! @brief     Implements PyEmbeddedTestFactory class.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Tests/Functional/Python/PyEmbedded/PyEmbeddedTestFactory.h"
#include "Tests/Functional/Python/PyEmbedded/TestCases.h"

PyEmbeddedTestFactory::PyEmbeddedTestFactory()
{
    registerItem("SysPath", create_new<SysPath>, "Content of sys.path variable");
    registerItem("ImportNumpy", create_new<ImportNumpy>, "Import numpy and check its version");
    registerItem("FunctionCall", create_new<FunctionCall>, "Calling function from embedded Python");
    registerItem("MethodCall", create_new<MethodCall>,
                 "Creating object embedded and calling its methods.");
    registerItem("CompiledFunction", create_new<CompiledFunction>,
                 "Compiling function from multi line string.");
    registerItem("ObjectExtract", create_new<ObjectExtract>,
                 "Extracting object created in Python into C++.");
    registerItem("EmbeddedMultiLayer", create_new<EmbeddedMultiLayer>,
                 "Building embedding MultiLayer.");
    registerItem("ExportToPythonAndBack", create_new<ExportToPythonAndBack>,
                 "Export of standard multilayer to Python code and casting back.");
    registerItem("ModuleFunctionsList", create_new<ModuleFunctionsList>,
                 "Explores the content of imported module for the list of defined functions.");
}
