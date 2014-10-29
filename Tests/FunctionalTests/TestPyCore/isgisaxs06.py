# IsGISAXS06 example: 2D lattice with different disorder
import sys
import os
import numpy
from utils import get_difference
from utils import get_reference_data

sys.path.append(os.path.abspath(
                os.path.join(os.path.split(__file__)[0],
                '..', '..', '..', 'lib')))

from libBornAgainCore import *

M_PI = numpy.pi

# ----------------------------------
# describe sample and run simulation
# ----------------------------------
def RunSimulation_lattice():
# defining materials
    mAmbience = HomogeneousMaterial("Air", 0.0, 0.0 )
    mSubstrate = HomogeneousMaterial("Substrate", 6e-6, 2e-8 )
    mParticle = HomogeneousMaterial("Particle", 6e-4, 2e-8 )
    
    # collection of particles
    interference = InterferenceFunction2DLattice.createSquare(10.0*nanometer)
    pdf = FTDistribution2DCauchy(300.0*nanometer/2.0/M_PI, 100.0*nanometer/2.0/M_PI)
    interference.setProbabilityDistribution(pdf)

    cylinder_ff = FormFactorCylinder(5*nanometer, 5*nanometer)
    cylinder = Particle(mParticle, cylinder_ff.clone())
    position = kvector_t(0.0, 0.0, 0.0)
    particle_layout = ParticleLayout()
    particle_info =  PositionParticleInfo(cylinder, position, 1.0)
    particle_layout.addParticleInfo(particle_info)
    particle_layout.addInterferenceFunction(interference)

    air_layer = Layer(mAmbience)
    air_layer.addLayout(particle_layout)
    substrate_layer = Layer(mSubstrate, 0)
    multi_layer = MultiLayer()
    multi_layer.addLayer(air_layer)
    multi_layer.addLayer(substrate_layer)
    # build and run experiment
    simulation = Simulation()
    simulation.setDetectorParameters(100,0.0*degree, 2.0*degree, 100, 0.0*degree, 2.0*degree, True)
    simulation.setBeamParameters(1.0*angstrom, 0.2*degree, 0.0*degree)

    simulation.setSample(multi_layer)
    simulation.runSimulation()
    return simulation.getIntensityData()


# ----------------------------------
# describe sample and run simulation - cylinders lattice centered
# ----------------------------------
def RunSimulation_centered():
    # defining materials
    mAmbience = HomogeneousMaterial("Air", 0.0, 0.0 )
    mSubstrate = HomogeneousMaterial("Substrate", 6e-6, 2e-8 )
    mParticle = HomogeneousMaterial("Particle", 6e-4, 2e-8 )
    # collection of particles
    interference = InterferenceFunction2DLattice(10.0*nanometer, 10.0*nanometer, 0.0*degree)
    pdf = FTDistribution2DCauchy(300.0*nanometer/2.0/M_PI, 100.0*nanometer/2.0/M_PI)
    interference.setProbabilityDistribution(pdf)

    # particle 1
    particle_layout1 = ParticleLayout()
    cylinder_ff = FormFactorCylinder(5*nanometer, 5*nanometer)
    cylinder = Particle(mParticle, cylinder_ff)
    position = kvector_t(0.0, 0.0, 0.0)
    particle_info = PositionParticleInfo(cylinder, position, 1.0)
    particle_layout1.addParticleInfo(particle_info)
    particle_layout1.addInterferenceFunction(interference)
    # particle 2
    particle_layout2 = ParticleLayout()
    position_2 = kvector_t(5.0*nanometer, 5.0*nanometer, 0.0)
    particle_info.setPosition(position_2)
    particle_layout2.addParticleInfo(particle_info)
    particle_layout2.addInterferenceFunction(interference)

    air_layer = Layer(mAmbience)
    air_layer.addLayout(particle_layout1)
    air_layer.addLayout(particle_layout2)
    substrate_layer = Layer(mSubstrate, 0)
    multi_layer = MultiLayer()
    multi_layer.addLayer(air_layer)
    multi_layer.addLayer(substrate_layer)
    # build and run experiment
    simulation = Simulation()
    simulation.setDetectorParameters(100,0.0*degree, 2.0*degree, 100, 0.0*degree, 2.0*degree, True)
    simulation.setBeamParameters(1.0*angstrom, 0.2*degree, 0.0*degree)

    simulation.setSample(multi_layer)
    simulation.runSimulation()
    return simulation.getIntensityData()


# ----------------------------------
# describe sample and run simulation - cylinders lattice rotated
# ----------------------------------
def RunSimulation_rotated():
# defining materials
    mAmbience = HomogeneousMaterial("Air", 0.0, 0.0 )
    mSubstrate = HomogeneousMaterial("Substrate", 6e-6, 2e-8 )
    mParticle = HomogeneousMaterial("Particle", 6e-4, 2e-8 )
    # collection of particles
    interference = InterferenceFunction2DLattice.createSquare(10.0*nanometer, 30.0*degree)
    pdf = FTDistribution2DCauchy(300.0*nanometer/2.0/M_PI, 100.0*nanometer/2.0/M_PI)
    pdf.setGamma(30.0*degree)
    interference.setProbabilityDistribution(pdf)
    
    cylinder_ff = FormFactorCylinder(5*nanometer, 5*nanometer)
    cylinder = Particle(mParticle, cylinder_ff)
    position = kvector_t(0.0, 0.0, 0.0)
    particle_layout = ParticleLayout()
    particle_info =  PositionParticleInfo(cylinder, position, 1.0)
    particle_layout.addParticleInfo(particle_info)
    particle_layout.addInterferenceFunction(interference)

    air_layer = Layer(mAmbience)
    air_layer.addLayout(particle_layout)
    substrate_layer = Layer(mSubstrate, 0)
    multi_layer = MultiLayer()
    multi_layer.addLayer(air_layer)
    multi_layer.addLayer(substrate_layer)
    # build and run experiment
    simulation = Simulation()
    simulation.setDetectorParameters(100,0.0*degree, 2.0*degree, 100, 0.0*degree, 2.0*degree, True)
    simulation.setBeamParameters(1.0*angstrom, 0.2*degree, 0.0*degree)

    simulation.setSample(multi_layer)
    simulation.runSimulation()
    return simulation.getIntensityData()


# ----------------------------------
# describe sample and run simulation - lattice variants
# ----------------------------------
def RunSimulation_variants():

    # building simulation
    simulation = Simulation()
    simulation.setDetectorParameters(100,0.0*degree, 2.0*degree, 100, 0.0*degree, 2.0*degree, True)
    simulation.setBeamParameters(1.0*angstrom, 0.2*degree, 0.0*degree)
    
    # running simulation and copying data
    OutputData_total = simulation.getIntensityData()
    nbins = 3
    xi_min = 0.0*degree
    xi_max = 240.0*degree
    xi= StochasticSampledParameter(StochasticDoubleGate(xi_min, xi_max), nbins, xi_min, xi_max)
    #for size_t i in range(xi.getNbins()) :
    for i in range(xi.getNbins()):
        xi_value = xi.getBinValue(i)
        probability = xi.getNormalizedProbability(i)
        p_sample =  buildSample(xi_value)
        simulation.setSample(p_sample)
        simulation.runSimulation()

        single_output = simulation.getIntensityData()
        single_output.scaleAll(probability)
        OutputData_total += single_output

    return OutputData_total


# IsGISAXS6 functional test sample builder for varying xi angle
def buildSample(xi_value):
    mAmbience = HomogeneousMaterial("Air", 0.0, 0.0 )
    mSubstrate = HomogeneousMaterial("Substrate", 6e-6, 2e-8 )
    mParticle = HomogeneousMaterial("Particle", 6e-4, 2e-8 )
    air_layer = Layer(mAmbience)
    substrate_layer = Layer(mSubstrate)
    
    p_interference_function = InterferenceFunction2DLattice.createSquare(10.0*nanometer, xi_value)
    pdf = FTDistribution2DCauchy (300.0*nanometer/2.0/M_PI, 100.0*nanometer/2.0/M_PI)
    p_interference_function.setProbabilityDistribution(pdf)

    particle_layout = ParticleLayout()
    # particle
    ff_cyl = FormFactorCylinder(5.0*nanometer, 5.0*nanometer)
    position = kvector_t(0.0, 0.0, 0.0)
    cylinder = Particle(mParticle, ff_cyl.clone())
    particle_info = PositionParticleInfo( cylinder, position, 1.0)
    particle_layout.addParticleInfo(particle_info)
    particle_layout.addInterferenceFunction(p_interference_function)
    
    air_layer.addLayout(particle_layout)

    multi_layer = MultiLayer()
    multi_layer.addLayer(air_layer)
    multi_layer.addLayer(substrate_layer)
    return multi_layer



# --------------------------------------------------------------
# run test and analyse test results
# --------------------------------------------------------------
def runTest():
    result_lattice = RunSimulation_lattice()
    reference_lattice = get_reference_data("isgisaxs06_reference_lattice.int.gz")
    diff = IntensityDataFunctions.getRelativeDifference(result_lattice, reference_lattice)

#    result_centered = RunSimulation_centered()
#    reference_centered = get_reference_data("isgisaxs06_reference_centered.int.gz")
#    diff += IntensityDataFunctions.getRelativeDifference(result_centered, reference_centered)

    result_rotated = RunSimulation_rotated()
    reference_rotated = get_reference_data("isgisaxs06_reference_rotated.int.gz")
    diff += IntensityDataFunctions.getRelativeDifference(result_rotated, reference_rotated)

    result_variants = RunSimulation_variants()
    reference_variants = get_reference_data("isgisaxs06_reference_variants.int.gz")
    diff += IntensityDataFunctions.getRelativeDifference(result_variants, reference_variants)

    diff /=3

    status = "OK"
    if(diff > 2e-10 or numpy.isnan(diff)):
        status = "FAILED"

    return "IsGISAXS06", "2D lattice with different disorder", diff, status


#-------------------------------------------------------------
# main()
#-------------------------------------------------------------
if __name__ == '__main__':
    name, description, diff, status = runTest()
    print name, description, diff, status
    if("FAILED" in status):
        exit(1)




 
 
