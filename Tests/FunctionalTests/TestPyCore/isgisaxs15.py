# IsGISAXS015 example: Size spacing correlation approximation
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
    mParticle = HomogeneousMaterial("Particle", 6e-4, 2e-8)

    # collection of particles
    cylinder_ff = FormFactorCylinder(5 * nanometer, 5 * nanometer)
    interference = InterferenceFunction1DParaCrystal(15.0 * nanometer, 1e3 * nanometer)
    pdf = FTDistribution1DGauss(5 * nanometer)
    interference.setProbabilityDistribution(pdf)
    interference.setKappa(4.02698)
    particle_layout = ParticleLayout()
    particle_prototype = Particle(mParticle, cylinder_ff)
    stochastic_radius = StochasticSampledParameter(StochasticDoubleGaussian(5.0 * nanometer, 1.25 * nanometer), 30, 2)

    particle_builder = ParticleBuilder()
    particle_builder.setPrototype(particle_prototype, "/Particle/FormFactorCylinder/radius", stochastic_radius)
    particle_builder.plantParticles(particle_layout)
    # Set height of each particle to its radius (H/R fixed)
    p_parameters = particle_layout.createParameterTree()
    nbr_replacements = p_parameters.fixRatioBetweenParameters("height", "radius", 1.0)
    #print "Number of replacements: ", nbr_replacements
    particle_layout.addInterferenceFunction(interference)
    particle_layout.setApproximation(ILayout.SSCA)

    air_layer = Layer(mAmbience)
    air_layer.addLayout(particle_layout)
    multi_layer = MultiLayer()
    multi_layer.addLayer(air_layer)

    # build and run experiment
    simulation = Simulation()
    simulation.setDetectorParameters(150, 0.05 * degree, 1.5 * degree, 150, 0.05 * degree, 1.5 * degree, True)
    simulation.setBeamParameters(1.0 * angstrom, 0.2 * degree, 0.0 * degree)

    simulation.setSample(multi_layer)
    simulation.runSimulation()
    return simulation.getIntensityData()


# --------------------------------------------------------------
# run test and analyse test results
# --------------------------------------------------------------
def runTest():
    result = RunSimulation()
    reference = get_reference_data("isgisaxs15_reference.int.gz")

    diff = IntensityDataFunctions.getRelativeDifference(result, reference)

    status = "OK"
    if (diff > 2e-10 or numpy.isnan(diff)):
        status = "FAILED"
    return "IsGISAXS15", "Size spacing correlation approximation", diff, status


# -------------------------------------------------------------
# main()
#-------------------------------------------------------------
if __name__ == '__main__':
    name, description, diff, status = runTest()
    print name, description, diff, status
    if("FAILED" in status):
        exit(1)

