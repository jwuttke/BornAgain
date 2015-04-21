"""
Infinitely long boxes at 1D lattice, OffSpecular simulation
"""
import numpy
import matplotlib
import pylab
from bornagain import *

phi_f_min, phi_f_max = -1.0, 1.0
alpha_f_min, alpha_f_max = 0.0, 10.0

alpha_i_min, alpha_i_max = 0.0, 10.0  # incoming beam


def get_sample():
    """
    Build and return the sample infinitely long boxes at 1D lattice
    """
    # defining materials
    m_ambience = HomogeneousMaterial("Air", 0.0, 0.0)
    m_substrate = HomogeneousMaterial("Substrate", 6e-6, 2e-8)
    m_particle = HomogeneousMaterial("Particle", 6e-4, 2e-8)

    # collection of particles
    lattice_length = 100.0*nanometer
    lattice_rotation_angle = 0.0*degree
    interference = InterferenceFunction1DLattice(lattice_length, lattice_rotation_angle)
    pdf = FTDistribution1DCauchy(1e+6)
    interference.setProbabilityDistribution(pdf)

    infbox_ff = FormFactorInfLongBox(20*nanometer, 10.0*nanometer)
    infbox = Particle(m_particle, infbox_ff)
    transform = RotationZ(90.0*degree)
    particle_layout = ParticleLayout()
    particle_layout.addParticle(infbox, transform)
    particle_layout.addInterferenceFunction(interference)

    # assembling the sample
    air_layer = Layer(m_ambience)
    air_layer.addLayout(particle_layout)
    substrate_layer = Layer(m_substrate)

    multi_layer = MultiLayer()
    multi_layer.addLayer(air_layer)
    multi_layer.addLayer(substrate_layer)
    return multi_layer


def get_simulation():
    """
    Create and return off-specular simulation with beam and detector defined
    """
    simulation = OffSpecSimulation()
    simulation.setDetectorParameters(20, phi_f_min*degree, phi_f_max*degree, 200, alpha_f_min*degree, alpha_f_max*degree)
    # defining the beam  with incidence alpha_i varied between alpha_i_min and alpha_i_max
    alpha_i_axis = FixedBinAxis("alpha_i", 200, alpha_i_min*degree, alpha_i_max*degree)
    simulation.setBeamParameters(1.0*angstrom, alpha_i_axis, 0.0*degree)
    simulation.setBeamIntensity(1e9)
    return simulation


def run_simulation():
    """
    Run simulation and plot results
    """
    sample = get_sample()
    simulation = get_simulation()
    simulation.setSample(sample)
    simulation.runSimulation()
    result = simulation.getIntensityData().getArray() + 1  # for log scale

    # showing the result
    im = pylab.imshow(numpy.rot90(result, 1), norm=matplotlib.colors.LogNorm(),
                      extent=[alpha_i_min, alpha_i_max, alpha_f_min, alpha_f_max], aspect='auto')
    cb = pylab.colorbar(im)
    cb.set_label(r'Intensity (arb. u.)', fontsize=16)
    pylab.xlabel(r'$\alpha_i (^{\circ})$', fontsize=16)
    pylab.ylabel(r'$\alpha_f (^{\circ})$', fontsize=16)
    pylab.show()


if __name__ == '__main__':
    run_simulation()
