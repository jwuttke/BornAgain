// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/PyCore/suite/PyCoreTest.cpp
//! @brief     Implements class PyCoreTest
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "PyCoreTest.h"
#include "BAPython.h"
#include "FileSystem.h"
#include "GISASSimulation.h"
#include "IntensityDataFunctions.h"
#include "IntensityDataIOFactory.h"
#include "PythonFormatting.h"
#include "SimulationFactory.h"
#include "TestConfig.h"
#include "Utils.h"
#include <cstdio>
#include <cstdlib>
#include <fstream>

PyCoreTest::PyCoreTest(
    const std::string& name, const std::string& description,
    GISASSimulation* reference_simulation, double threshold)
    : IFunctionalTest(name, description)
    , m_reference_simulation(reference_simulation)
    , m_domain_simulation(0)
    , m_threshold(threshold)
    , m_difference(0)
    , m_pyscript_filename( BUILD_TMP_DIR + "/pysuite_" + name + ".py" )
    , m_output_filename( BUILD_TMP_DIR + "/pysuite_" + name + ".int" )
{
}

PyCoreTest::~PyCoreTest()
{
    delete m_reference_simulation;
    delete m_domain_simulation;
}

void PyCoreTest::runTest()
{
    // Generate Python script
    std::ostringstream ostr;
    ostr << "# Functional test settings, generated by PyCoreTest::runTest():\n"
         << "import sys, os\n"
         << "sys.path.append('" << BUILD_LIB_DIR << "')\n\n"
         << "# Simulation script, generated by PythonFormatting::simulationToPython(..):\n"
         << PythonFormatting::simulationToPython(m_reference_simulation);
    std::ofstream pythonFile(m_pyscript_filename);
    pythonFile << ostr.str();
    pythonFile.close();
    std::cout << "Generated Python script " << m_pyscript_filename <<"." << std::endl/*sic*/;
        // Here we are using std::endl instead of "\n" in order to flush because otherwise
        // the system calls 'remove' and 'system' may break the order of output lines.

    // Run Python script
    std::remove( m_output_filename.c_str() );
    std::cout << "Removed old data set " << m_output_filename << "." << std::endl/*sic*/;
    std::string command = std::string(BORNAGAIN_PYTHON_EXE) + " " + m_pyscript_filename +
        " " + m_output_filename;
    std::cout << "Now running command '" << command << "'." << std::endl/*sic*/;
    int ret = std::system(command.c_str()); // run python script
    if (ret!=0) {
        std::cerr << "Command returned non-zero value " << ret << ".\n";
        m_result = FAILED;
        return;
    }

    // Run direct simulation
    std::cout <<
        "Now going to directly run the simulation, and to compare with result from Py script.\n";
    assert(m_reference_simulation);
    m_reference_simulation->runSimulation();
    const std::unique_ptr<OutputData<double> > P_reference_data(
        m_reference_simulation->getDetectorIntensity());

    // Compare results
    const std::unique_ptr<OutputData<double> > P_domain_data(
        IntensityDataIOFactory::readOutputData(m_output_filename));
    m_difference = IntensityDataFunctions::getRelativeDifference(*P_domain_data, *P_reference_data);
    m_result = m_difference > m_threshold ? FAILED_DIFF : SUCCESS;
    if (m_result != SUCCESS) {
        // Move failed Python script to failed tests directory
        Utils::FileSystem::CreateDirectory(FAILED_TESTS_DIR);
        std::rename( m_pyscript_filename.c_str(), getPySuiteFileNameAndPath().c_str());
    }
}

void PyCoreTest::printResults(std::ostream& ostr) const
{
    ostr << getFormattedInfoString();
    ostr << Utils::String::getScientificDoubleString(m_difference);
    if (m_result != SUCCESS)
        ostr << "--> " << getPySuiteFileNameAndPath();
}

std::string PyCoreTest::getPySuiteFileNameAndPath() const
{
    std::string result = Utils::FileSystem::GetJoinPath(FAILED_TESTS_DIR, m_pyscript_filename);
    return result;
}
