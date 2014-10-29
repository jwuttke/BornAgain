// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/src/TestRipple2.cpp
//! @brief     Implements class TestRipple2.
//
//! Homepage:  apps.jcns.fz-juelich.de/BornAgain
//! License:   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "TestRipple2.h"
#include "DrawHelper.h"
#include "Simulation.h"
#include "InterferenceFunction1DParaCrystal.h"
#include "InterferenceFunctionNone.h"
#include "IsGISAXSData.h"
#include "IsGISAXSTools.h"
#include "Layer.h"
#include "Materials.h"
#include "MathFunctions.h"
#include "MultiLayer.h"
#include "OutputData.h"
#include "OutputDataFunctions.h"
#include "IntensityDataIOFactory.h"
#include "Particle.h"
#include "ParticleBuilder.h"
#include "ParticleLayout.h"
#include "ResolutionFunction2DSimple.h"
#include "StochasticGaussian.h"
#include "StochasticSampledParameter.h"
#include "Units.h"
#include "Utils.h"

#define protected public // needed to acess the protected evaluate_for_q mathod
#include "FormFactorRipple2.h"
#undef protected
#include <iostream>
#include <fstream>
#include <sstream>
#include "TCanvas.h"
#include "TGraph.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TLine.h"
#include "TROOT.h"
#include "TLegend.h"
#include "TStyle.h"
#include "FileSystem.h"


TestRipple2::TestRipple2()
: IApplicationTest("TestRipple2")
, mp_simulation(0)
, mp_sample_builder(new TestSampleBuilder())
{
    setOutputPath(Utils::FileSystem::GetPathToData("../Tests/ReferenceData/BornAgain/" ));
}

void TestRipple2::execute()
{
    // initializing simulation and sample builder
    initializeSimulation();
	mp_simulation->runSimulation();
    //save_results();
	plot_results();

    // plot the pure formfactor
    //drawff();
}

/* ************************************************************************* */
// save results of simulation to file
/* ************************************************************************* */
void TestRipple2::save_results()
{
    // run simulation for default sample parameters
    //mp_simulation->runSimulation();
    std::string filename(getOutputPath()+"test_ripple2_asym.ima");
    IntensityDataIOFactory::writeIntensityData(*(mp_simulation->getIntensityData()),
                                         filename);
}

/* ************************************************************************* */
// plot the pure formfactor
// evaluate_for_q mathod must be turned to public to use this function
/* ************************************************************************* */
void TestRipple2::drawff()
{
    FormFactorRipple2 *ff = new FormFactorRipple2(100.0*Units::nanometer, 20.0*Units::nanometer, 4.0*Units::nanometer, 3.0*Units::nanometer);
    size_t qybins = 400;
    size_t qzbins = 400;
	
	double qymin = -2.0;
	double qymax = 2.0;
	double qzmin = -2.0;
	double qzmax = 2.0;
	double stepqy = (qymax - qymin)/qybins;
	double stepqz = (qzmax - qzmin)/qzbins;

    TH2D *hist = new TH2D("Ripple2", "Ripple2",
                          (int)qybins, -2.0, 2.0,
                          (int)qzbins, -2.0, 2.0);

    hist->GetXaxis()->SetTitle( "Qy" );
    hist->GetYaxis()->SetTitle( "Qz" );
	
	cvector_t qq;
    for (size_t iqz=0; iqz < qzbins; iqz++) {
		for (size_t iqy=0; iqy < qybins; iqy++) {
			double qy = qymin + iqy*stepqy + stepqy/2.;
			double qz = qzmin + iqz*stepqz + stepqz/2.;
			qq.setXYZ(0.0, qy, qz);
			double value = std::abs(ff->evaluate_for_q(qq));
			hist->Fill(qy, qz, value*value + 1);
			//std::cout << "qy=" << qy << " qz=" << qz << " I=" << value*value << std::endl;
		}
    }

    hist->SetContour(50);
    hist->SetStats(0);
    hist->GetYaxis()->SetTitleOffset(1.1);

    gStyle->SetPalette(1);
    gStyle->SetOptStat(111111);

    TCanvas *c1 = new TCanvas("Ripple2", "Ripple2", 980, 800);
    c1->cd();
    c1->SetLogz();
    hist->SetMinimum(1.0);
    hist->DrawCopy("colz");
    c1->Update();
}


/* ************************************************************************* */
// initialize simulation
/* ************************************************************************* */
void TestRipple2::initializeSimulation()
{
  //  mp_sample_builder = new SampleBuilder();
    
	delete mp_simulation;
    mp_simulation = new Simulation(mp_options);
    mp_simulation->setSampleBuilder(mp_sample_builder);
    mp_simulation->setDetectorParameters(400, -1.5*Units::degree, 1.5*Units::degree, 400, 0.0*Units::degree, 2.0*Units::degree, true);
    mp_simulation->setBeamParameters(1.6*Units::angstrom, 0.3*Units::degree, 0.0*Units::degree);
}

/* ************************************************************************* */
// sample builder
/* ************************************************************************* */
TestRipple2::TestSampleBuilder::TestSampleBuilder()
    : m_w(20.0*Units::nanometer)
    , m_h(4.0*Units::nanometer)
    , m_l(100.0*Units::nanometer)
    , m_d(-3.0*Units::nanometer)
    , m_interf_distance(20.0*Units::nanometer)
    , m_interf_width(4.0*Units::nanometer)
{
      init_parameters();
}

void TestRipple2::TestSampleBuilder::init_parameters()
{
    clearParameterPool();
    registerParameter("width", &m_w);
    registerParameter("height", &m_h);
    registerParameter("length", &m_l);
    registerParameter("asymetry", &m_d);
    registerParameter("interf_distance", &m_interf_distance);
    registerParameter("interf_width", &m_interf_width);
}

ISample *TestRipple2::TestSampleBuilder::buildSample() const
{
    MultiLayer *p_multi_layer = new MultiLayer();

    complex_t n_particle(1.0-6e-4, 2e-8);
    HomogeneousMaterial air_material("Air", 0.0, 0.0);
    HomogeneousMaterial substrate_material("Substrate", 6e-6, 2e-8);
    HomogeneousMaterial particle_material("Particle", n_particle);

    Layer air_layer(air_material);
    FormFactorRipple2 ff_ripple2(m_l, m_w, m_h, m_d);
    Particle ripple(particle_material, ff_ripple2 );


    ParticleLayout particle_layout;
	particle_layout.addParticle(ripple,0.0,1.0);
    InterferenceFunction1DParaCrystal *p_interference_function =
            new InterferenceFunction1DParaCrystal(m_interf_distance,
                    1e7*Units::nanometer); // peak_distance, corr_length
    FTDistribution1DGauss pdf(m_interf_width);
    p_interference_function->setProbabilityDistribution(pdf);
    particle_layout.addInterferenceFunction(p_interference_function);

    // making layer holding all whose nano particles
    air_layer.addLayout(particle_layout);

    p_multi_layer->addLayer(air_layer);

    Layer substrate_layer;
    substrate_layer.setMaterial(substrate_material);
    p_multi_layer->addLayer(substrate_layer);

    return p_multi_layer;
}

void TestRipple2::plot_results()
{
	OutputData<double> *m_result = mp_simulation->getIntensityData();
    const IAxis *axisPhi = m_result->getAxis(0);
    const IAxis *axisAlpha = m_result->getAxis(1);

    size_t nPhibins = axisPhi->getSize();
    size_t nAlphabins = axisAlpha->getSize();

    TH2D *hist = new TH2D("Ripple2", "Ripple2",
                          (int)nPhibins, axisPhi->getMin()/Units::degree, axisPhi->getMax()/Units::degree,
                          (int)nAlphabins, axisAlpha->getMin()/Units::degree, axisAlpha->getMax()/Units::degree);

    hist->GetXaxis()->SetTitle( axisPhi->getName().c_str() );
    hist->GetYaxis()->SetTitle( axisAlpha->getName().c_str() );

    OutputData<double>::const_iterator it = m_result->begin();
    while (it != m_result->end())
    {
        double x = m_result->getValueOfAxis( axisPhi->getName(), it.getIndex() );
        double y = m_result->getValueOfAxis( axisAlpha->getName(), it.getIndex() );
        double value = *it++;
        hist->Fill(x/Units::degree, y/Units::degree, value);
    }

    hist->SetContour(50);
    hist->SetStats(0);
    hist->GetYaxis()->SetTitleOffset(1.1);

    gStyle->SetPalette(1);
    gStyle->SetOptStat(0);

    TCanvas *c1 = new TCanvas("Ripple2", "Ripple2", 980, 800);
    c1->cd();
    c1->SetLogz();
    hist->SetMinimum(1.0);
    hist->DrawCopy("colz");
    c1->Update();

    delete axisPhi;
    delete axisAlpha;
    delete hist;
}


