#include "FunctionalTestRegistry.h"
#include "FileSystem.h"
#include "IntensityDataFunctions.h"
#include "IntensityDataIOFactory.h"
#include "SimulationRegistry.h"
#include <boost/scoped_ptr.hpp>

int main(int argc, char **argv)
{
    if(argc == 2) Utils::FileSystem::SetReferenceDataDir(argv[1]);

    SimulationRegistry sim_registry;
    Simulation* simulation = sim_registry.createSimulation("polmagcylinders2");
    simulation->runSimulation();
    simulation->normalize();

    boost::scoped_ptr<OutputData<double> > reference00(IntensityDataIOFactory::readIntensityData(
        Utils::FileSystem::GetReferenceDataDir()+ "polmagcylinders2_reference_00.int.gz"));
    boost::scoped_ptr<OutputData<double> > reference01(IntensityDataIOFactory::readIntensityData(
        Utils::FileSystem::GetReferenceDataDir()+ "polmagcylinders2_reference_01.int.gz"));
    boost::scoped_ptr<OutputData<double> > reference10(IntensityDataIOFactory::readIntensityData(
        Utils::FileSystem::GetReferenceDataDir()+ "polmagcylinders2_reference_10.int.gz"));
    boost::scoped_ptr<OutputData<double> > reference11(IntensityDataIOFactory::readIntensityData(
        Utils::FileSystem::GetReferenceDataDir()+ "polmagcylinders2_reference_11.int.gz"));

    boost::scoped_ptr<OutputData<double> > data00(simulation->getPolarizedIntensityData(0,0));
    boost::scoped_ptr<OutputData<double> > data01(simulation->getPolarizedIntensityData(0,1));
    boost::scoped_ptr<OutputData<double> > data10(simulation->getPolarizedIntensityData(1,0));
    boost::scoped_ptr<OutputData<double> > data11(simulation->getPolarizedIntensityData(1,1));

    const double threshold(2e-10);
    double diff(0);
    diff += IntensityDataFunctions::getRelativeDifference(*data00, *reference00);
    diff += IntensityDataFunctions::getRelativeDifference(*data01, *reference01);
    diff += IntensityDataFunctions::getRelativeDifference(*data10, *reference10);
    diff += IntensityDataFunctions::getRelativeDifference(*data11, *reference11);
    diff /= 4.;

    delete simulation;

    // Assess result.
    bool status_ok(true);
    if( diff > threshold ) status_ok=false;

    std::cout << " diff " << diff << std::endl;
    std::cout << "polmagcylinders2" << " " << "Magnetic cylinders with non-zero magnetic field" << " " <<
            (status_ok ? "[OK]" : "[FAILED]") << std::endl;
    return (status_ok ? 0 : 1);
}
