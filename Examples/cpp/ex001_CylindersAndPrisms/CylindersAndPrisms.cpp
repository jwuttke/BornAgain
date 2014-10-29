#include "OutputData.h"
#include "Simulation.h"
#include "ISample.h"
#include "MultiLayer.h"
#include "ParticleLayout.h"
#include "Materials.h"
#include "FormFactorCylinder.h"
#include "FormFactorPrism3.h"
#include "Units.h"
#include "InterferenceFunctionNone.h"

#include "TCanvas.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TH3D.h"
#include "TStyle.h"
#include "TLine.h"
#include "TROOT.h"
#include "TApplication.h"

#include "CylindersAndPrisms.h"


void CylindersAndPrismsExample::setSample() 
{
    m_sample = new MultiLayer();

    HomogeneousMaterial air_material("Air", 0., 0.);
    HomogeneousMaterial substrate_material("Substrate", 6e-6, 2e-8);

    Layer air_layer(air_material);
    Layer substrate_layer(substrate_material);

    ParticleLayout particle_layout;
    HomogeneousMaterial particle_material("Particle", 6e-4, 2e-8);

    particle_layout.addParticle(
                new Particle(particle_material,
                             FormFactorCylinder(5*Units::nanometer,
                                                    5*Units::nanometer)),
                0.0, 0.5);
    particle_layout.addParticle(
                new Particle(particle_material,
                             FormFactorPrism3(10*Units::nanometer,
                                                  5*Units::nanometer)),
                0.0, 0.5);
    particle_layout.addInterferenceFunction(new InterferenceFunctionNone());

    air_layer.addLayout(particle_layout);

    m_sample->addLayer(air_layer);
    m_sample->addLayer(substrate_layer);

}

void CylindersAndPrismsExample::setSimulation()  
{
    m_simulation = new Simulation();

    m_simulation->setDetectorParameters(
                400,-1.0*Units::degree, 1.0*Units::degree, 400,
                0.0*Units::degree, 2.0*Units::degree, true);
    m_simulation->setBeamParameters(
                1.0*Units::angstrom, 0.2*Units::degree, 0.0*Units::degree);

    m_simulation->setSample(*m_sample);
}

CylindersAndPrismsExample::CylindersAndPrismsExample() : m_result(0)
{
    setSample();
    setSimulation();
}

void CylindersAndPrismsExample::runSimulation() 
{
    m_simulation->runSimulation();
    m_result = m_simulation->getIntensityData();
}

void CylindersAndPrismsExample::drawResult()
{
    const IAxis *axisPhi = m_result->getAxis(0);
    const IAxis *axisAlpha = m_result->getAxis(1);

    size_t nPhibins = axisPhi->getSize();
    size_t nAlphabins = axisAlpha->getSize();

    TH2D *hist = new TH2D("Cylinders and prisms", "Cylinders and prisms",
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

    TCanvas *c1 = new TCanvas("Cylinders and prisms", "Cylinders and prisms", 980, 800);
    c1->cd();
    c1->SetLogz();
    hist->SetMinimum(1.0);
    hist->DrawCopy("colz");
    c1->Update();

    delete axisPhi;
    delete axisAlpha;
    delete hist;
}


int main(int argc, char **argv)
{
    CylindersAndPrismsExample* example = new CylindersAndPrismsExample();
    example->runSimulation();

    TApplication *theApp = new TApplication("theApp", &argc, argv);
    example->drawResult();
    theApp->Run();

    delete example;
    return 0;
}
