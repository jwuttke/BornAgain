'''
Simulation demo: Size Space Coupling Approximation
'''

import numpy, pylab, matplotlib

from libBornAgainCore import *

# ----------------------------------
# describe sample and run simulation
# ----------------------------------
def RunSimulation():
    # defining materials
    mAir = HomogeneousMaterial("Air", 0.0, 0.0)
    mSubstrate = HomogeneousMaterial("Substrate", 6e-6, 2e-8)
    mParticle =HomogeneousMaterial("Particle", 6e-4, 2e-8)
    mLayer = HomogeneousMaterial("Layer", 2e-5, 2e-8)

    # collection of particles
    cylinder_ff1 = FormFactorCylinder(2 * nanometer, 5 * nanometer)
    cylinder_ff2 = FormFactorCylinder(3 * nanometer, 6 * nanometer)
    cylinder_ff3 = FormFactorCylinder(4 * nanometer, 7 * nanometer)
    cylinder1 = Particle(mParticle, cylinder_ff1)
    cylinder2 = Particle(mParticle, cylinder_ff2)
    cylinder3 = Particle(mParticle, cylinder_ff3)
    particle_layout = ParticleLayout()
    particle_layout.addParticle(cylinder1)
    particle_layout.addParticle(cylinder2)
    particle_layout.addParticle(cylinder3)
    interference = InterferenceFunction1DParaCrystal(5 * nanometer)
    pdf = FTDistribution1DGauss(1 * nanometer)
    interference.setProbabilityDistribution(pdf)
    # set coupling between size and space
    interference.setKappa(2)
    particle_layout.addInterferenceFunction(interference)
    # particle_layout.setApproximation(ILayout.SSCA)
    particle_layout.setApproximation(ILayout.DA)

    # air layer with particles and substrate form multi layer
    air_layer = Layer(mAir)
    air_layer.addLayout(particle_layout)
    substrate_layer = Layer(mSubstrate)
    multi_layer = MultiLayer()
    multi_layer.addLayer(air_layer)
    roughness = LayerRoughness(10 * nanometer, 3, 20 * nanometer)
    multi_layer.addLayerWithTopRoughness(substrate_layer, roughness)

    # build and run experiment
    simulation = Simulation()
    simulation.setDetectorParameters(100, -4.0 * degree, 4.0 * degree, 100, 0.0 * degree, 8.0 * degree)
    simulation.setBeamParameters(1.0 * angstrom, 0.2 * degree, 0.0 * degree)
    simulation.setSample(multi_layer)
    simulation.runSimulation()
    # intensity data
    return simulation.getIntensityData().getArray()


#-------------------------------------------------------------
# main()
#-------------------------------------------------------------
if __name__ == '__main__':
    result = RunSimulation() + 1 # for log scale
    im = pylab.imshow(numpy.rot90(result, 1),
                 norm=matplotlib.colors.LogNorm(),
                 extent=[-4.0, 4.0, 0, 8.0])
    pylab.colorbar(im)
    pylab.xlabel(r'$\phi_f$', fontsize=20)
    pylab.ylabel(r'$\alpha_f$', fontsize=20)
    pylab.show()
