// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Python/PyStandard/main.cpp
//! @brief     Implements program PyStandardTest, to run functional tests
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Tests/Functional/Python/PyStandard/PyStandardTest.h"
#include "Tests/Functional/TestMachinery/StandardTestService.h"

//! Runs PyStandardTest on a standard simulation indicated by argv[1].

int main(int argc, char** argv)
{
    return StandardTestService<PyStandardTest>().execute(argc, argv) ? 0 : 1;
}
