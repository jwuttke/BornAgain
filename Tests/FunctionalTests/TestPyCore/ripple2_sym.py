# Functional test: triangular ripple formfactor within the 1D-paracrystal model
import sys
import os
import numpy
from utils import get_reference_data


sys.path.append(os.path.abspath(
    os.path.join(os.path.split(__file__)[0],
                 '..', '..', '..', 'lib')))

from libBornAgainCore import *


# ----------------------------------
# describe sample and run simulation
# ----------------------------------
def RunSimulation():
    # defining materials
    mAmbience = HomogeneousMaterial("Air", 0.0, 0.0)
    mSubstrate = HomogeneousMaterial("Substrate", 6e-6, 2e-8)
    mParticle = HomogeneousMaterial("Particle", 6e-4, 2e-8)

    # collection of particles
    ripple2_ff = FormFactorRipple2(100 * nanometer, 20 * nanometer, 4 * nanometer, 0 * nanometer)
    ripple = Particle(mParticle, ripple2_ff)

    particle_layout = ParticleLayout()
    particle_layout.addParticle(ripple, 0.0, 1.0)

    interference = InterferenceFunctionRadialParaCrystal(20 * nanometer, 1e7 * nanometer)
    pdf = FTDistribution1DGauss(4 * nanometer)
    interference.setProbabilityDistribution(pdf)
    particle_layout.addInterferenceFunction(interference)

    # air layer with particles and substrate form multi layer
    air_layer = Layer(mAmbience)
    air_layer.addLayout(particle_layout)
    substrate_layer = Layer(mSubstrate, 0)
    multi_layer = MultiLayer()
    multi_layer.addLayer(air_layer)
    multi_layer.addLayer(substrate_layer)

    # build and run experiment
    simulation = Simulation()
    simulation.setDetectorParameters(100, -1.5 * degree, 1.5 * degree, 100, 0.0 * degree, 2.0 * degree)
    simulation.setBeamParameters(1.6 * angstrom, 0.3 * degree, 0.0 * degree)
    simulation.setSample(multi_layer)
    simulation.runSimulation()
    # # intensity data
    return simulation.getIntensityData()


# --------------------------------------------------------------
# run test and analyse test results
# --------------------------------------------------------------
def runTest():
    result = RunSimulation()

    reference = get_reference_data("ripple2_sym_reference.int.gz")

    diff = IntensityDataFunctions.getRelativeDifference(result, reference)

    status = "OK"
    if (diff > 1e-10 or numpy.isnan(diff)):
        status = "FAILED"
    return "Ripple2", "Triangular ripple within the 1D-paracrystal model", diff, status


# -------------------------------------------------------------
# main()
#-------------------------------------------------------------
if __name__ == '__main__':
    name, description, diff, status = runTest()
    print name, description, diff, status
    if("FAILED" in status):
        exit(1)
