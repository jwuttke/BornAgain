// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/src/TestMesoCrystal2.cpp
//! @brief     Implements class TestMesoCrystal2.
//
//! Homepage:  apps.jcns.fz-juelich.de/BornAgain
//! License:   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "TestMesoCrystal2.h"
#include "AttLimits.h"
#include "Crystal.h"
#include "DrawHelper.h"
#include "FitStrategyAdjustParameters.h"
#include "FitSuite.h"
#include "FitSuiteObserverFactory.h"
#include "FormFactorDecoratorDebyeWaller.h"
#include "FormFactors.h"
#include "Simulation.h"
#include "IInterferenceFunction.h"
#include "InterferenceFunctionNone.h"
#include "IntensityDataFunctions.h"
#include "IsGISAXSTools.h"
#include "LatticeBasis.h"
#include "Materials.h"
#include "MathFunctions.h"
#include "MesoCrystal.h"
#include "MinimizerFactory.h"
#include "MultiLayer.h"
#include "FileSystem.h"
#include "IntensityDataIOFactory.h"
#include "OutputDataReader.h"
#include "OutputDataFunctions.h"
#include "ParticleLayout.h"
#include "ProgramOptions.h"
#include "ResolutionFunction2DSimple.h"
#include "SampleFactory.h"
#include "TRange.h"
#include "Units.h"
#include "Utils.h"

#include "TCanvas.h"
#include "TH2D.h"
#include <boost/assign/list_of.hpp>


/* ************************************************************************* */
// TestMesoCrystal2 member definitions
/* ************************************************************************* */
TestMesoCrystal2::TestMesoCrystal2()
    : m_real_data(0)
    , m_sample_builder(new SampleBuilder)
    , m_simulation(0)
    , m_fitSuite(0)
{
}


TestMesoCrystal2::~TestMesoCrystal2()
{
    delete m_real_data;
    delete m_simulation;
    delete m_fitSuite;
}


void TestMesoCrystal2::execute()
{

    //run_fit();
    draw_results();
}



// ----------------------------------------------------------------------------
// draw fit results
// ----------------------------------------------------------------------------
void TestMesoCrystal2::draw_results()
{
    initializeRealData();
    initializeSimulation(m_real_data);

    ParameterPool *pool = m_sample_builder->createParameterTree();
//    pool->setMatchedParametersValue("*/lattice_length_a", 6.2e+00);           // 6.2
//    pool->setMatchedParametersValue("*/lattice_length_c", 6.2e+00);           // 6.2
//    pool->setMatchedParametersValue("*/nanoparticle_radius", 5.7e+00);        // 5.7
//    pool->setMatchedParametersValue("*/sigma_nanoparticle_radius", 1.0e-01);  // 0.1
//    pool->setMatchedParametersValue("*/meso_height", 200);  // 0.1
//    pool->setMatchedParametersValue("*/meso_radius", 1000);  // 0.1
//    pool->setMatchedParametersValue("*/sigma_meso_height", 20);  // 0.1
//    pool->setMatchedParametersValue("*/sigma_meso_radius", 100);  // 0.1
//    pool->setMatchedParametersValue("*/sigma_lattice_length_a", 1.0);     // 1.5
//    pool->setMatchedParametersValue("*/surface_filling_ratio", 0.2);      // 0.25
//    pool->setMatchedParametersValue("*/roughness", 1.0);                      // 1.0
//    m_simulation->setBeamIntensity(8e+12);
//    m_simulation->runSimulation();
//    m_simulation->normalize();

//    IsGISAXSTools::drawOutputDataComparisonResults(*m_simulation->getOutputData(), *m_real_data, "initial", "initial params", 100, 1e6, 100);

    m_sample_builder->setParameterValue("lattice_length_c", 6.5677e+00);           // 6.2
    m_sample_builder->setParameterValue("lattice_length_a", 6.2091e+00);           // 6.2
    m_sample_builder->setParameterValue("nanoparticle_radius", 4.6976e+00);        // 5.7
    m_sample_builder->setParameterValue("sigma_nanoparticle_radius", 3.6720e-01);  // 0.1
    m_sample_builder->setParameterValue("meso_height", 1.1221e+02);  // 0.1
    m_sample_builder->setParameterValue("meso_radius", 9.4567e+02);  // 0.1
    m_sample_builder->setParameterValue("sigma_meso_height", 1.3310e+00);  // 0.1
    m_sample_builder->setParameterValue("sigma_meso_radius", 1.3863e+00);  // 0.1
    m_sample_builder->setParameterValue("sigma_lattice_length_a", 1.1601e+00);     // 1.5
    m_sample_builder->setParameterValue("surface_filling_ratio", 1.7286e-01);      // 0.25
    m_sample_builder->setParameterValue("roughness", 2.8746e+01);                      // 1.0
    m_simulation->setBeamIntensity(5.0090e+12);
    std::cout << *pool << std::endl;
    m_simulation->runSimulation();
    m_simulation->normalize();

//    IsGISAXSTools::drawOutputDataComparisonResults(
//            *m_simulation->getOutputData(), *m_real_data,
//            "found", "found params", 100, 1e6, 100);

//    TCanvas *c1 = new TCanvas("meso_real_data","meso_real_data",1024, 768);
//    c1->cd();
//    gPad->SetLogz();
//    gPad->SetRightMargin(0.12);
//    gPad->SetLeftMargin(0.125);
//    TH2D *hist_real = IsGISAXSTools::getOutputDataTH2D(
//            *m_real_data, "real_data");
//    hist_real->SetMinimum(100);
//    hist_real->SetMaximum(1e6);
//    hist_real->GetYaxis()->SetTitleOffset(1.35);
//    hist_real->DrawCopy("CONT4 Z");

    TCanvas *c2 = new TCanvas("meso_simul_data","meso_simul_data",1024, 768);
    c2->cd();
    gPad->SetLogz();
    gPad->SetRightMargin(0.12);
    gPad->SetLeftMargin(0.125);
    TH2D *hist_simu = IsGISAXSTools::getOutputDataTH2D(
            *m_simulation->getOutputData(), "simul_data");
//    hist_simu->SetMinimum(100);
//    hist_simu->SetMaximum(1e6);
    hist_simu->GetYaxis()->SetTitleOffset(1.35);
    hist_simu->DrawCopy("CONT4 Z");

//    OutputDataIOFactory::writeIntensityData(
//            *m_simulation->getOutputData(), "meso_simul.txt");
}




/* ************************************************************************* */
//
/* ************************************************************************* */
void TestMesoCrystal2::run_fit()
{
    initializeRealData();

    TCanvas *c1 = DrawHelper::createAndRegisterCanvas("c1_test_meso_crystal", "mesocrystal");
    c1->cd(); gPad->SetLogz();
    gPad->SetRightMargin(0.115);
    gPad->SetLeftMargin(0.115);
    IsGISAXSTools::setMinimum(100.);
    IsGISAXSTools::setMaximum(1e7);
    IsGISAXSTools::drawOutputDataInPad(*m_real_data, "CONT4 Z", "experiment");
    c1->Update();

    // initializing simulation using real data
    initializeSimulation(m_real_data);

    // setting fitSuite
    m_fitSuite = new FitSuite();
    m_fitSuite->getFitObjects()->setSimulationNormalize(true);

    int fitconfig = (*mp_options)["fitconfig"].as<int>();
    fitsuite_setup(fitconfig);

    m_fitSuite->attachObserver( FitSuiteObserverFactory::createPrintObserver() );
    m_fitSuite->attachObserver( FitSuiteObserverFactory::createDrawObserver() );
    m_fitSuite->attachObserver( FitSuiteObserverFactory::createTreeObserver() );

    m_fitSuite->runFit();

    for(FitSuiteParameters::iterator it = m_fitSuite->getFitParameters()->begin(); it!=m_fitSuite->getFitParameters()->end(); ++it) {
        std::cout << (*it) << std::endl;
    }
}


// ----------------------------------------------------------------------------
// initialize real data
// ----------------------------------------------------------------------------
void TestMesoCrystal2::initializeRealData()
{
    delete m_real_data;
    //std::string file_name = Utils::FileSystem::GetHomePath()+"Examples/MesoCrystals/ex02_fitspheres/004_230_P144_im_full_qyqz.txt.gz";
    //std::string file_name = Utils::FileSystem::GetHomePath()+"Examples/MesoCrystals/ex02_fitspheres/004_230_P144_im_full_phitheta.txt.gz";
    //std::string file_name = "dev-tools/tmp-examples/MesoCrystals/ex02_fitspheres/004_230_P144_im_full_phitheta.txt.gz";
    //std::string file_name = "../support/input/001_ElisabethJosten/2013.01.03/004_230_P144_im_full_phitheta.txt.gz";
    std::string file_name = Utils::FileSystem::GetReferenceDataDir() + "mesocrystal1_reference_v2_nphi180.txt.gz";

    m_real_data = IntensityDataIOFactory::readIntensityData(file_name);
    //Mask *mask1 = OutputDataFunctions::CreateRectangularMask(*m_real_data, 0.025, 0.003, 0.051, 0.0375);
    Mask *mask1 = OutputDataFunctions::CreateRectangularMask(*m_real_data, 0.0, 0.015, 0.09, 0.020);
    m_real_data->setMask(*mask1);


    //    OutputData<double > *real_data_half = doubleBinSize(*real_data);
    //    OutputData<double > *real_data_quarter = doubleBinSize(*real_data_half);
    //    OutputData<double > *real_data_eighth = doubleBinSize(*real_data_quarter);
}


// ----------------------------------------------------------------------------
// run appropriate FitSuite configuration
// ----------------------------------------------------------------------------
void TestMesoCrystal2::fitsuite_setup(int nconfig)
{
    switch(nconfig) {
    case 1:
        fitsuite_config1();
        break;
    case 2:
        fitsuite_config2();
        break;
    case 3:
        fitsuite_config3();
        break;
    case 4:
        fitsuite_config4();
        break;
    default:
        throw LogicErrorException("TestMesoCrystal2::fitsuite_setup() -> Error! Can't setup FitSuite");
        break;
    }
}



// ----------------------------------------------------------------------------
// FitSuite configuration #3
// * Mask on fit data
// * Several fit iterations with different set of fixed released parameters
// * ChiSquaredModule with normalizer
// ----------------------------------------------------------------------------
void TestMesoCrystal2::fitsuite_config4()
{
    m_fitSuite->setMinimizer( MinimizerFactory::createMinimizer("Minuit2", "Combined") );
//    m_fitSuite->setMinimizer( MinimizerFactory::createMinimizer("Minuit2", "Fumili") );

    m_fitSuite->getAttributes().setStepFactor(0.01);
    m_fitSuite->addFitParameter("*/lattice_length_a",          6.2091e+00*Units::nanometer,    AttLimits::limited(4.0*Units::nanometer, 8.0*Units::nanometer) );
    m_fitSuite->addFitParameter("*/lattice_length_c",          6.5677e+00*Units::nanometer,    AttLimits::limited(4.0*Units::nanometer, 8.0*Units::nanometer) );
    m_fitSuite->addFitParameter("*/nanoparticle_radius",       4.6976e+00*Units::nanometer,    AttLimits::limited(4.0*Units::nanometer, 8.0*Units::nanometer) );
    m_fitSuite->addFitParameter("*/sigma_nanoparticle_radius", 3.6720e-01*Units::nanometer,    AttLimits::limited(0.01*Units::nanometer, 2.0*Units::nanometer) );
    m_fitSuite->addFitParameter("*/meso_height",               1.1221e+02*Units::nanometer,   AttLimits::limited(10.0*Units::nanometer, 2000.0*Units::nanometer) );
    m_fitSuite->addFitParameter("*/meso_radius",               9.4567e+02*Units::nanometer,   AttLimits::limited(10.0*Units::nanometer, 5000.0*Units::nanometer) );
    m_fitSuite->addFitParameter("*/sigma_meso_height",         1.3310e+00*Units::nanometer,    AttLimits::limited(1.0*Units::nanometer, 200.0*Units::nanometer) );
    m_fitSuite->addFitParameter("*/sigma_meso_radius",         1.3863e+00*Units::nanometer,   AttLimits::limited(1.0*Units::nanometer, 500.0*Units::nanometer) );
    m_fitSuite->addFitParameter("*/sigma_lattice_length_a",    1.1601e+00*Units::nanometer,    AttLimits::limited(0.01*Units::nanometer, 4.0*Units::nanometer) );
    m_fitSuite->addFitParameter("*/surface_filling_ratio",     1.7286e-01,                      AttLimits::limited(0.05, 0.5) );
    m_fitSuite->addFitParameter("*/roughness",                 2.8746e+01*Units::nanometer,     AttLimits::limited(0.01*Units::nanometer, 50.0*Units::nanometer) );
    m_fitSuite->addFitParameter("*Beam/intensity",             5.0090e+12,                     AttLimits::limited(8e11, 8e13) );

    fixplan_t fixplan;
    fixplan.push_back(boost::assign::list_of("*Beam/intensity")("*/lattice_length_a")("*/lattice_length_c")("*/nanoparticle_radius"));
    fixplan.push_back(boost::assign::list_of("*Beam/intensity")("*/meso_height")("*/meso_radius"));
    fixplan.push_back(boost::assign::list_of("*Beam/intensity")("*/surface_filling_ratio")("*/roughness"));
    fixplan.push_back(boost::assign::list_of("*Beam/intensity")("*/sigma_lattice_length_a")("*/sigma_nanoparticle_radius")("*/sigma_meso_height")("*/sigma_meso_radius"));

    // here we are fixing specific parameters before fit
    for( size_t i_plan=0; i_plan<fixplan.size(); ++i_plan) {
        std::ostringstream ostr;
        ostr << "strategy" <<i_plan;
        FitStrategyAdjustParameters *strategy = new FitStrategyAdjustParameters(ostr.str());
        strategy->fix_all();
        for(size_t i_par=0; i_par<fixplan[i_plan].size(); ++i_par) {
            strategy->release(fixplan[i_plan][i_par]);
        }
        m_fitSuite->addFitStrategy(strategy);
    }
    FitStrategyAdjustParameters *strategy_all = new FitStrategyAdjustParameters("strategy_all");
    strategy_all->release_all();
    m_fitSuite->addFitStrategy(strategy_all);

    // fitpreserve=1 - preserve original values
    // fitpreserve=0 - return always to previous fit values
    for(FitSuiteStrategies::iterator it = m_fitSuite->getFitStrategies()->begin(); it!= m_fitSuite->getFitStrategies()->end(); ++it) {
        FitStrategyAdjustParameters *strategy = dynamic_cast<FitStrategyAdjustParameters *>( (*it) );
        assert(strategy);
        strategy->setPreserveOriginalValues( (*mp_options)["fitpreserve"].as<int>() );
    }

//    Mask *mask1 = OutputDataFunctions::CreateRectangularMask(*m_real_data, 0.041, 0.003, 0.051, 0.03);
    Mask *mask1 = OutputDataFunctions::CreateRectangularMask(*m_real_data, 0.025, 0.003, 0.051, 0.0375);
    m_real_data->setMask(*mask1);
//    IntensityDataHelper::setRectangularMask(*m_real_data, 0.025, 0.003, 0.051, 0.0375);

    ChiSquaredModule chiModule;
//    chiModule.setChiSquaredFunction( SquaredFunctionDefault() );
    //chiModule.setChiSquaredFunction( SquaredFunctionWhichOnlyWorks() ); // it works only with resolution function, without it fit doesn't converge
    chiModule.setChiSquaredFunction( new  SquaredFunctionMeanSquaredError() );
    //chiModule.setOutputDataNormalizer( OutputDataSimpleNormalizer(1.0,0) );

    m_fitSuite->addSimulationAndRealData(*m_simulation, *m_real_data, chiModule);
//    m_fitSuite->addSimulationAndRealData(*m_simulation, *m_real_data);

}


// ----------------------------------------------------------------------------
// FitSuite configuration #3
// * Mask on fit data
// * Several fit iterations with different set of fixed released parameters
// * ChiSquaredModule with normalizer
// ----------------------------------------------------------------------------
void TestMesoCrystal2::fitsuite_config3()
{
    m_fitSuite->setMinimizer( MinimizerFactory::createMinimizer("Minuit2", "Combined") );
//    m_fitSuite->setMinimizer( MinimizerFactory::createMinimizer("Minuit2", "Fumili") );

    m_fitSuite->getAttributes().setStepFactor(0.01);
    m_fitSuite->addFitParameter("*/lattice_length_a",          6.2*Units::nanometer,    AttLimits::limited(4.0*Units::nanometer, 8.0*Units::nanometer) );
    m_fitSuite->addFitParameter("*/lattice_length_c",          6.2*Units::nanometer,    AttLimits::limited(4.0*Units::nanometer, 8.0*Units::nanometer) );
    m_fitSuite->addFitParameter("*/nanoparticle_radius",       5.7*Units::nanometer,    AttLimits::limited(4.0*Units::nanometer, 8.0*Units::nanometer) );
    m_fitSuite->addFitParameter("*/sigma_nanoparticle_radius", 0.1*Units::nanometer,    AttLimits::limited(0.01*Units::nanometer, 2.0*Units::nanometer) );
    m_fitSuite->addFitParameter("*/meso_height",               200.0*Units::nanometer,   AttLimits::limited(10.0*Units::nanometer, 2000.0*Units::nanometer) );
    m_fitSuite->addFitParameter("*/meso_radius",               1000.0*Units::nanometer,   AttLimits::limited(10.0*Units::nanometer, 5000.0*Units::nanometer) );
    m_fitSuite->addFitParameter("*/sigma_meso_height",         20.0*Units::nanometer,    AttLimits::limited(1.0*Units::nanometer, 200.0*Units::nanometer) );
    m_fitSuite->addFitParameter("*/sigma_meso_radius",         100.0*Units::nanometer,   AttLimits::limited(1.0*Units::nanometer, 500.0*Units::nanometer) );
    m_fitSuite->addFitParameter("*/sigma_lattice_length_a",    1.0*Units::nanometer,    AttLimits::limited(0.01*Units::nanometer, 4.0*Units::nanometer) );
    m_fitSuite->addFitParameter("*/surface_filling_ratio",     0.2,                      AttLimits::limited(0.05, 0.5) );
    m_fitSuite->addFitParameter("*/roughness",                 1.0*Units::nanometer,     AttLimits::limited(0.01*Units::nanometer, 50.0*Units::nanometer) );
    m_fitSuite->addFitParameter("*Beam/intensity",             8e12,                     AttLimits::limited(8e11, 8e13) );

    fixplan_t fixplan;
    fixplan.push_back(boost::assign::list_of("*Beam/intensity")("*/lattice_length_a")("*/lattice_length_c")("*/nanoparticle_radius"));
    fixplan.push_back(boost::assign::list_of("*Beam/intensity")("*/meso_height")("*/meso_radius"));
    fixplan.push_back(boost::assign::list_of("*Beam/intensity")("*/surface_filling_ratio")("*/roughness"));
    fixplan.push_back(boost::assign::list_of("*Beam/intensity")("*/sigma_lattice_length_a")("*/sigma_nanoparticle_radius")("*/sigma_meso_height")("*/sigma_meso_radius"));

    // here we are fixing specific parameters before fit
    for( size_t i_plan=0; i_plan<fixplan.size(); ++i_plan) {
        std::ostringstream ostr;
        ostr << "strategy" <<i_plan;
        FitStrategyAdjustParameters *strategy = new FitStrategyAdjustParameters(ostr.str());
        strategy->fix_all();
        for(size_t i_par=0; i_par<fixplan[i_plan].size(); ++i_par) {
            strategy->release(fixplan[i_plan][i_par]);
        }
        m_fitSuite->addFitStrategy(strategy);
    }
    FitStrategyAdjustParameters *strategy_all = new FitStrategyAdjustParameters("strategy_all");
    strategy_all->release_all();
    m_fitSuite->addFitStrategy(strategy_all);

    // fitpreserve=1 - preserve original values
    // fitpreserve=0 - return always to previous fit values
    for(FitSuiteStrategies::iterator it = m_fitSuite->getFitStrategies()->begin(); it!= m_fitSuite->getFitStrategies()->end(); ++it) {
        FitStrategyAdjustParameters *strategy = dynamic_cast<FitStrategyAdjustParameters *>( (*it) );
        assert(strategy);
        strategy->setPreserveOriginalValues( (*mp_options)["fitpreserve"].as<int>() );
    }

//    Mask *mask1 = OutputDataFunctions::CreateRectangularMask(*m_real_data, 0.041, 0.003, 0.051, 0.03);
    Mask *mask1 = OutputDataFunctions::CreateRectangularMask(*m_real_data, 0.025, 0.003, 0.051, 0.0375);
    m_real_data->setMask(*mask1);

    ChiSquaredModule chiModule;
//    chiModule.setChiSquaredFunction( SquaredFunctionDefault() );
    //chiModule.setChiSquaredFunction( SquaredFunctionWhichOnlyWorks() ); // it works only with resolution function, without it fit doesn't converge
    chiModule.setChiSquaredFunction( new SquaredFunctionSystematicError() );
    //chiModule.setOutputDataNormalizer( OutputDataSimpleNormalizer(1.0,0) );

    m_fitSuite->addSimulationAndRealData(*m_simulation, *m_real_data, chiModule);
//    m_fitSuite->addSimulationAndRealData(*m_simulation, *m_real_data);

}


// ----------------------------------------------------------------------------
// FitSuite configuration #2
// * Mask on fit data
// * Several fit iterations with different set of fixed released parameters
// * ChiSquaredModule with normalizer
// ----------------------------------------------------------------------------
void TestMesoCrystal2::fitsuite_config2()
{
    m_fitSuite->setMinimizer( MinimizerFactory::createMinimizer("Minuit2", "Combined") );

    m_fitSuite->getAttributes().setStepFactor(0.01);
    m_fitSuite->addFitParameter("*/lattice_length_a",          6.2*Units::nanometer,    AttLimits::limited(4.0*Units::nanometer, 8.0*Units::nanometer) );
    m_fitSuite->addFitParameter("*/nanoparticle_radius",       5.7*Units::nanometer,    AttLimits::limited(2.0*Units::nanometer, 8.0*Units::nanometer) );
    m_fitSuite->addFitParameter("*/sigma_nanoparticle_radius", 0.1*Units::nanometer,    AttLimits::limited(0.01*Units::nanometer, 2.0*Units::nanometer) );
    m_fitSuite->addFitParameter("*/meso_height",               500.0*Units::nanometer,  AttLimits::limited(100.0*Units::nanometer, 2000.0*Units::nanometer) );
    m_fitSuite->addFitParameter("*/meso_radius",               1000.0*Units::nanometer, AttLimits::limited(100.0*Units::nanometer, 5000.0*Units::nanometer) );
    m_fitSuite->addFitParameter("*/sigma_meso_height",         5.0*Units::nanometer,    AttLimits::limited(10.0*Units::nanometer, 200.0*Units::nanometer) );
    m_fitSuite->addFitParameter("*/sigma_meso_radius",         50.0*Units::nanometer,   AttLimits::limited(10.0*Units::nanometer, 500.0*Units::nanometer) );
    m_fitSuite->addFitParameter("*/sigma_lattice_length_a",    1.5*Units::nanometer,    AttLimits::limited(0.01*Units::nanometer, 4.0*Units::nanometer) );
    m_fitSuite->addFitParameter("*/surface_filling_ratio",     0.25,                    AttLimits::limited(0.1, 0.4) );
    m_fitSuite->addFitParameter("*/roughness",                 1.0*Units::nanometer,    AttLimits::limited(0.01*Units::nanometer, 50.0*Units::nanometer) );
    m_fitSuite->addFitParameter("*Beam/intensity",             8e12,                    AttLimits::limited(8e11, 8e13) );

    fixplan_t fixplan;
    fixplan.resize(7);
    fixplan[0] = boost::assign::list_of("*/lattice_length_a")("*/nanoparticle_radius");
    fixplan[1] = boost::assign::list_of("*/meso_height")("*/meso_radius");
    fixplan[2] = boost::assign::list_of("*Beam/intensity");
    fixplan[3] = boost::assign::list_of("*/surface_filling_ratio");
    fixplan[4] = boost::assign::list_of("*/roughness");
    fixplan[5] = boost::assign::list_of("*/sigma_lattice_length_a")("*/sigma_nanoparticle_radius");
    fixplan[6] = boost::assign::list_of("*/sigma_meso_height")("*/sigma_meso_radius");

    // here we are fixing specific parameters before fit
    for( size_t i_plan=0; i_plan<fixplan.size(); ++i_plan) {
        std::ostringstream ostr;
        ostr << "strategy" <<i_plan;
        FitStrategyAdjustParameters *strategy = new FitStrategyAdjustParameters(ostr.str());
        strategy->fix_all();
        strategy->setPreserveOriginalValues(true); // initial values of parameters will be restored after each fit
        for(size_t i_par=0; i_par<fixplan[i_plan].size(); ++i_par) {
            strategy->release(fixplan[i_plan][i_par]);
        }
        m_fitSuite->addFitStrategy(strategy);
    }
    FitStrategyAdjustParameters *strategy_all = new FitStrategyAdjustParameters("strategy_all");
    strategy_all->release_all();
    m_fitSuite->addFitStrategy(strategy_all);

    // fitpreserve=1 - preserve original values
    // fitpreserve=0 - return always to previous fit values
    for(FitSuiteStrategies::iterator it = m_fitSuite->getFitStrategies()->begin(); it!= m_fitSuite->getFitStrategies()->end(); ++it) {
        FitStrategyAdjustParameters *strategy = dynamic_cast<FitStrategyAdjustParameters *>( (*it) );
        assert(strategy);
        strategy->setPreserveOriginalValues( (*mp_options)["fitpreserve"].as<int>() );
    }

    Mask *mask1 = OutputDataFunctions::CreateRectangularMask(*m_real_data, 0.041, 0.003, 0.051, 0.03);
    m_real_data->setMask(*mask1);


}


// ----------------------------------------------------------------------------
// FitSuite configuration #1
// 7 fit iterations with different sets of fixed/release parameters
// ----------------------------------------------------------------------------
void TestMesoCrystal2::fitsuite_config1()
{

    m_fitSuite->setMinimizer( MinimizerFactory::createMinimizer("Minuit2", "Combined") );

    m_fitSuite->addFitParameter("*/lattice_length_a",          6.2*Units::nanometer,    AttLimits::limited(4.0*Units::nanometer, 8.0*Units::nanometer) );
    m_fitSuite->addFitParameter("*/nanoparticle_radius",       5.7*Units::nanometer,    1.0*Units::nanometer,   AttLimits::limited(2.0*Units::nanometer, 8.0*Units::nanometer) );
    m_fitSuite->addFitParameter("*/sigma_nanoparticle_radius", 0.1*Units::nanometer,    0.05*Units::nanometer,  AttLimits::limited(0.01*Units::nanometer, 2.0*Units::nanometer) );
    m_fitSuite->addFitParameter("*/meso_height",               500.0*Units::nanometer,  100.0*Units::nanometer, AttLimits::limited(100.0*Units::nanometer, 2000.0*Units::nanometer) );
    m_fitSuite->addFitParameter("*/meso_radius",               1000.0*Units::nanometer, 100.0*Units::nanometer, AttLimits::limited(100.0*Units::nanometer, 5000.0*Units::nanometer) );
    m_fitSuite->addFitParameter("*/sigma_meso_height",         5.0*Units::nanometer,    1.0*Units::nanometer,   AttLimits::limited(10.0*Units::nanometer, 200.0*Units::nanometer) );
    m_fitSuite->addFitParameter("*/sigma_meso_radius",         50.0*Units::nanometer,   10.0*Units::nanometer,  AttLimits::limited(10.0*Units::nanometer, 500.0*Units::nanometer) );
    m_fitSuite->addFitParameter("*/sigma_lattice_length_a",    1.5*Units::nanometer,    0.5*Units::nanometer,   AttLimits::limited(0.01*Units::nanometer, 4.0*Units::nanometer) );
    m_fitSuite->addFitParameter("*/surface_filling_ratio",     0.25,                    0.1,                    AttLimits::limited(0.1, 0.4) );
    m_fitSuite->addFitParameter("*/roughness",                 1.0*Units::nanometer,    0.1*Units::nanometer,   AttLimits::limited(0.01*Units::nanometer, 50.0*Units::nanometer) );
    m_fitSuite->addFitParameter("*Beam/intensity",             8e12,                    100,                    AttLimits::limited(8e11, 8e13) );

    fixplan_t fixplan;
    fixplan.resize(7);
    fixplan[0] = boost::assign::list_of("*/lattice_length_a")("*/nanoparticle_radius");
    fixplan[1] = boost::assign::list_of("*/meso_height")("*/meso_radius");
    fixplan[2] = boost::assign::list_of("*Beam/intensity");
    fixplan[3] = boost::assign::list_of("*/surface_filling_ratio");
    fixplan[4] = boost::assign::list_of("*/roughness");
    fixplan[5] = boost::assign::list_of("*/sigma_lattice_length_a")("*/sigma_nanoparticle_radius");
    fixplan[6] = boost::assign::list_of("*/sigma_meso_height")("*/sigma_meso_radius");

    // here we are fixing specific parameters before fit
    for( size_t i_plan=0; i_plan<fixplan.size(); ++i_plan) {
        std::ostringstream ostr;
        ostr << "strategy" <<i_plan;
        FitStrategyAdjustParameters *strategy = new FitStrategyAdjustParameters(ostr.str());
        strategy->fix_all();
        strategy->setPreserveOriginalValues(true); // initial values of parameters will be restored after each fit
        for(size_t i_par=0; i_par<fixplan[i_plan].size(); ++i_par) {
            strategy->release(fixplan[i_plan][i_par]);
        }
        m_fitSuite->addFitStrategy(strategy);
    }
    FitStrategyAdjustParameters *strategy_all = new FitStrategyAdjustParameters("strategy_all");
    strategy_all->release_all();
    m_fitSuite->addFitStrategy(strategy_all);

    // fitpreserve=1 - preserve original values
    // fitpreserve=0 - return always to previous fit values
    for(FitSuiteStrategies::iterator it = m_fitSuite->getFitStrategies()->begin(); it!= m_fitSuite->getFitStrategies()->end(); ++it) {
        FitStrategyAdjustParameters *strategy = dynamic_cast<FitStrategyAdjustParameters *>( (*it) );
        assert(strategy);
        strategy->setPreserveOriginalValues( (*mp_options)["fitpreserve"].as<int>() );
    }

    m_fitSuite->addSimulationAndRealData(*m_simulation, *m_real_data);

}


/* ************************************************************************* */
//
/* ************************************************************************* */
void TestMesoCrystal2::initializeSimulation(const OutputData<double> *output_data)
{
    delete m_simulation;

    m_simulation = new Simulation(mp_options);
    m_simulation->setSampleBuilder( m_sample_builder );
    m_simulation->setBeamParameters(1.77*Units::angstrom, 0.4*Units::degree, 0.0*Units::degree);
    m_simulation->setBeamIntensity(8e12);
    m_simulation->setDetectorResolutionFunction(new ResolutionFunction2DSimple(0.0002, 0.0002));

    if( !output_data ) {
        // initialize default detector
        m_simulation->setDetectorParameters(200, 0.3*Units::degree, 0.073, 200, -0.4*Units::degree, 0.066);
    } else {
        // if there is output_data as input parameter, build detector using output_data axises
        //const IAxis *axis0 = output_data->getAxis(0);
        //const IAxis *axis1 = output_data->getAxis(1);
        //std::cout << "Axis!!! " << axis0->getSize() << " " << axis0->getMin() << " " << axis0->getMax() << " " << axis1->getSize() << " " << axis1->getMin() << " " << axis1->getMax() << std::endl;
        //m_simulation->setDetectorParameters(axis0->getSize(), axis0->getMin(), axis0->getMax(), axis1->getSize(), axis1->getMin(), axis1->getMax());
        m_simulation->setDetectorParameters(*m_real_data);
    }
    m_simulation->printParameters();
}



/* ************************************************************************* */
// MesoCrystalBuilder member definitions
/* ************************************************************************* */
TestMesoCrystal2::SampleBuilder::SampleBuilder()
: m_meso_radius(1000.0*Units::nanometer)
, m_surface_filling_ratio(0.25)
, m_meso_height(500.0*Units::nanometer)
, m_sigma_meso_height(5.0*Units::nanometer)
, m_sigma_meso_radius(50.0*Units::nanometer)
, m_lattice_length_a(6.2*Units::nanometer)
, m_lattice_length_c(6.2*Units::nanometer)
, m_nanoparticle_radius(5.7*Units::nanometer)
, m_sigma_nanoparticle_radius(0.1*Units::nanometer)
, m_sigma_lattice_length_a(1.5*Units::nanometer)
, m_roughness(1.0*Units::nanometer)
{
    init_parameters();
}


ISample* TestMesoCrystal2::SampleBuilder::buildSample() const
{
    // create mesocrystal
    double surface_density = m_surface_filling_ratio/M_PI/m_meso_radius/m_meso_radius;
//    complex_t n_particle(1.0-1.55e-5, 1.37e-6); // data from Artur
    complex_t n_particle(1.0-2.84e-5, 4.7e-7); // data from http://henke.lbl.gov/optical_constants/getdb2.html
    complex_t avg_n_squared_meso = 0.7886*n_particle*n_particle + 0.2114;
    complex_t n_avg = std::sqrt(m_surface_filling_ratio*avg_n_squared_meso + 1.0 - m_surface_filling_ratio);
    complex_t n_particle_adapted = std::sqrt(n_avg*n_avg + n_particle*n_particle - 1.0);
    FormFactorCylinder ff_cyl(m_meso_radius, m_meso_height);
    FormFactorDecoratorDebyeWaller ff_meso(ff_cyl.clone(), m_sigma_meso_height*m_sigma_meso_height/2.0,
            m_sigma_meso_radius*m_sigma_meso_radius/2.0);

    // Create multilayer
    MultiLayer *p_multi_layer = new MultiLayer();
    complex_t n_air(1.0, 0.0);
    complex_t n_substrate(1.0-7.57e-6, 1.73e-7);

    HomogeneousMaterial air_material("Air", n_air);
    HomogeneousMaterial average_layer_material("Averagelayer", n_avg);
    HomogeneousMaterial substrate_material("Substrate", n_substrate);
    Layer air_layer;
    air_layer.setMaterial(air_material);
    Layer avg_layer;
    avg_layer.setMaterial(average_layer_material);
    avg_layer.setThickness(m_meso_height);
    Layer substrate_layer;
    substrate_layer.setMaterial(substrate_material);
    IInterferenceFunction *p_interference_funtion =
        new InterferenceFunctionNone();
    ParticleLayout particle_layout;
    size_t n_max_phi_rotation_steps = 1;
    size_t n_alpha_rotation_steps = 1;

//    double alpha_step = 5.0*Units::degree/n_alpha_rotation_steps;
//    double alpha_start = - (n_alpha_rotation_steps/2.0)*alpha_step;

    double phi_step = 2*M_PI/3.0/n_max_phi_rotation_steps;
    double phi_start = 0.0;
    for (size_t i=0; i<n_max_phi_rotation_steps; ++i) {
        for (size_t j=0; j<n_alpha_rotation_steps; ++j) {
            Geometry::Transform3D transform =
                    Geometry::Transform3D::createRotateZ(phi_start + i*phi_step);
//            Geometry::Transform3D transform2 =
//                Geometry::Transform3D::createRotateY(alpha_start + j*alpha_step);
            particle_layout.addParticle(
                createMesoCrystal(
                    m_lattice_length_a, m_lattice_length_c,
                    n_particle_adapted, &ff_meso),
                transform, m_meso_height);
        }
    }

    particle_layout.setTotalParticleSurfaceDensity(surface_density);
    particle_layout.addInterferenceFunction(p_interference_funtion);

    avg_layer.addLayout(particle_layout);

    LayerRoughness roughness(m_roughness, 0.3, 500.0*Units::nanometer);

    p_multi_layer->addLayer(air_layer);
    p_multi_layer->addLayer(avg_layer);
    p_multi_layer->addLayerWithTopRoughness(substrate_layer, roughness);

//    std::cout << "Average layer index: " << n_avg << std::endl;
//    std::cout << "Adapted particle index: " << n_particle_adapted << std::endl;
//    std::cout << "Substrate layer index: " << n_substrate << std::endl;

    return p_multi_layer;
}

void TestMesoCrystal2::SampleBuilder::init_parameters()
{
    clearParameterPool();
    registerParameter("meso_radius", &m_meso_radius);
    registerParameter("surface_filling_ratio", &m_surface_filling_ratio);
    registerParameter("meso_height", &m_meso_height);
    registerParameter("sigma_meso_height", &m_sigma_meso_height);
    registerParameter("sigma_meso_radius", &m_sigma_meso_radius);
    registerParameter("lattice_length_a", &m_lattice_length_a);
    registerParameter("lattice_length_c", &m_lattice_length_c);
    registerParameter("nanoparticle_radius", &m_nanoparticle_radius);
    registerParameter("sigma_nanoparticle_radius", &m_sigma_nanoparticle_radius);
    registerParameter("sigma_lattice_length_a", &m_sigma_lattice_length_a);
    registerParameter("roughness", &m_roughness);
}

//MesoCrystal* TestMesoCrystal2::SampleBuilder::createMesoCrystal(double stacking_radius, complex_t n_particle,
//        const IFormFactor* p_meso_form_factor) const
//{
//    const Lattice *p_lat = createLattice(stacking_radius);
//    kvector_t bas_a = p_lat->getBasisVectorA();
//    kvector_t bas_b = p_lat->getBasisVectorB();
//    kvector_t bas_c = p_lat->getBasisVectorC();
//    Particle particle(n_particle, new FormFactorSphereGaussianRadius(m_nanoparticle_radius, m_sigma_nanoparticle_radius));
//    kvector_t position_0 = kvector_t(0.0, 0.0, 0.0);
//    kvector_t position_1 = 1.0/3.0*(2.0*bas_a + bas_b + bas_c);
//    kvector_t position_2 = 1.0/3.0*(bas_a + 2.0*bas_b + 2.0*bas_c);
//    std::vector<kvector_t> pos_vector;
//    pos_vector.push_back(position_0);
//    pos_vector.push_back(position_1);
//    pos_vector.push_back(position_2);
//    LatticeBasis basis(particle, pos_vector);

//    Crystal npc(basis, *p_lat);
//    delete p_lat;
//    double dw_factor = m_sigma_lattice_length_a*m_sigma_lattice_length_a/6.0;
//    npc.setDWFactor(dw_factor);
//    return new MesoCrystal(npc.clone(), p_meso_form_factor->clone());
//}

//const Lattice *TestMesoCrystal2::SampleBuilder::createLattice(double stacking_radius) const
//{
//    Lattice *p_result = new Lattice(Lattice::createTrigonalLattice(stacking_radius*2.0, stacking_radius*2.0*2.3));
//    p_result->setSelectionRule(SimpleSelectionRule(-1, 1, 1, 3));
//    return p_result;
//}

MesoCrystal* TestMesoCrystal2::SampleBuilder::createMesoCrystal(double stacking_radius_a, double stacking_radius_c, complex_t n_particle,
        const IFormFactor* p_meso_form_factor) const
{
    const Lattice *p_lat = createLattice(stacking_radius_a, stacking_radius_c);
    kvector_t bas_a = p_lat->getBasisVectorA();
    kvector_t bas_b = p_lat->getBasisVectorB();
    kvector_t bas_c = p_lat->getBasisVectorC();

    HomogeneousMaterial particle_material("Particle", n_particle);

    Particle particle(particle_material, FormFactorSphereGaussianRadius(m_nanoparticle_radius, m_sigma_nanoparticle_radius));
    kvector_t position_0 = kvector_t(0.0, 0.0, 0.0);
    kvector_t position_1 = 1.0/3.0*(2.0*bas_a + bas_b + bas_c);
    kvector_t position_2 = 1.0/3.0*(bas_a + 2.0*bas_b + 2.0*bas_c);
    std::vector<kvector_t> pos_vector;
    pos_vector.push_back(position_0);
    pos_vector.push_back(position_1);
    pos_vector.push_back(position_2);
    LatticeBasis basis(particle, pos_vector);

    Crystal npc(basis, *p_lat);
    delete p_lat;
    double dw_factor = m_sigma_lattice_length_a*m_sigma_lattice_length_a/6.0;
    npc.setDWFactor(dw_factor);
    return new MesoCrystal(npc.clone(), p_meso_form_factor->clone());
}

const Lattice *TestMesoCrystal2::SampleBuilder::createLattice(double stacking_radius_a, double stacking_radius_c) const
{
    Lattice *p_result = new Lattice(Lattice::createTrigonalLattice(stacking_radius_a*2.0, stacking_radius_c*2.0*2.3));
    p_result->setSelectionRule(SimpleSelectionRule(-1, 1, 1, 3));
    return p_result;
}



