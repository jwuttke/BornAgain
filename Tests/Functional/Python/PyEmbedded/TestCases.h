// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Python/PyEmbedded/TestCases.h
//! @brief     Defines TestCases class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef TESTCASES_H
#define TESTCASES_H

#include "Tests/Functional/TestMachinery/IFunctionalTest.h"

//! Checks system path for embedded enterpreter.

class SysPath : public IFunctionalTest
{
protected:
    bool runTest();
};

//! Tries to import numpy and access its version string.

class ImportNumpy : public IFunctionalTest
{
protected:
    bool runTest();
};

//! Checks function call in embeded Python interpreter.

class FunctionCall : public IFunctionalTest
{
protected:
    bool runTest();
};

//! Checks method call in embedded Python interpreter.

class MethodCall : public IFunctionalTest
{
protected:
    bool runTest();
};

//! Compiling function from multi line string.

class CompiledFunction : public IFunctionalTest
{
protected:
    bool runTest();
};

//! Extracting object created in Python into C++.

class ObjectExtract : public IFunctionalTest
{
protected:
    bool runTest();
};

//! Building embedding MultiLayer.

class EmbeddedMultiLayer : public IFunctionalTest
{
protected:
    bool runTest();
};

//! Export of standard multilayer to Python code and casting back.

class ExportToPythonAndBack : public IFunctionalTest
{
protected:
    bool runTest();
};

//! Explores the content of imported module for the list of defined functions.

class ModuleFunctionsList : public IFunctionalTest
{
protected:
    bool runTest();
};

#endif
