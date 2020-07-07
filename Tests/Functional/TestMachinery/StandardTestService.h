// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/TestMachinery/StandardTestService.h
//! @brief     Defines class StandardTestService.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef STANDARDTESTSERVICE_H
#define STANDARDTESTSERVICE_H

#include "Wrap/WinDllMacros.h"
#include <memory>
#include <string>
class IFunctionalTest;
class Simulation;

//! @class StandardTestServiceBase
//! @ingroup standard_samples
//! @brief Main class to run standard functional test from standalone executable.

class BA_CORE_API_ StandardTestServiceBase
{
public:
    virtual ~StandardTestServiceBase() = default;
    bool execute(int argc, char** argv);

private:
    virtual IFunctionalTest* createTest(const std::string& name, const std::string& description,
                                        const Simulation& simulation, double threshold) = 0;
};

//! @class StandardTestService
//! @ingroup standard_samples
//! @brief Extends main class to run standard functional test from standalone executable.
//! Concrete test type is templated.

template <typename T> class StandardTestService : public StandardTestServiceBase
{

private:
    IFunctionalTest* createTest(const std::string& name, const std::string& description,
                                const Simulation& simulation, double threshold) override
    {
        return new T(name, description, simulation, threshold);
    }
};

#endif // STANDARDTESTSERVICE_H
