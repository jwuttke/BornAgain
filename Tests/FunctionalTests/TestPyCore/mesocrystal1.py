# functional test: mesocrystal simulation
#

import sys
import os
import numpy
import time
import ctypes
import math
from utils import get_reference_data


sys.path.append(os.path.abspath(
                os.path.join(os.path.split(__file__)[0],
                '..', '..', '..', 'lib')))

from libBornAgainCore import *


# ----------------------------------------------------------------------------
# Sample builder to build mixture of cylinders and prisms on top of substrate
# 5 parameters
2# ----------------------------------------------------------------------------
class MySampleBuilder(ISampleBuilder):
    def __init__(self):
        ISampleBuilder.__init__(self)
        self.sample = None
        # parameters describing the sample
        self.lattice_length_a = ctypes.c_double(6.2091e+00*nanometer)
        self.lattice_length_c = ctypes.c_double(6.5677e+00*nanometer)
        self.nanoparticle_radius = ctypes.c_double(4.6976e+00*nanometer)
        self.sigma_nanoparticle_radius = ctypes.c_double(3.6720e-01*nanometer)
        self.meso_height = ctypes.c_double(1.1221e+02*nanometer)
        self.meso_radius = ctypes.c_double(9.4567e+02*nanometer)
        self.sigma_meso_height = ctypes.c_double(1.3310e+00*nanometer)
        self.sigma_meso_radius = ctypes.c_double(1.3863e+00*nanometer)
        self.sigma_lattice_length_a = ctypes.c_double(1.1601e+00*nanometer)
        self.surface_filling_ratio = ctypes.c_double(1.7286e-01)
        self.roughness = ctypes.c_double(2.8746e+01*nanometer)
        # register parameters
        self.registerParameter("lattice_length_a", ctypes.addressof(self.lattice_length_a) )
        self.registerParameter("lattice_length_c", ctypes.addressof(self.lattice_length_c) )
        self.registerParameter("nanoparticle_radius", ctypes.addressof(self.nanoparticle_radius) )
        self.registerParameter("sigma_nanoparticle_radius", ctypes.addressof(self.sigma_nanoparticle_radius) )
        self.registerParameter("meso_height", ctypes.addressof(self.meso_height) )
        self.registerParameter("meso_radius",  ctypes.addressof(self.meso_radius) )
        self.registerParameter("sigma_meso_height", ctypes.addressof(self.sigma_meso_height) )
        self.registerParameter("sigma_meso_radius", ctypes.addressof(self.sigma_meso_radius) )
        self.registerParameter("sigma_lattice_length_a", ctypes.addressof(self.sigma_lattice_length_a) )
        self.registerParameter("surface_filling_ratio", ctypes.addressof(self.surface_filling_ratio) )
        self.registerParameter("roughness", ctypes.addressof(self.roughness) )

    # -------------------------------------------------------------------------
    # constructs the sample for current values of parameters
    # -------------------------------------------------------------------------
    def buildSample(self):
        surface_density = self.surface_filling_ratio.value/numpy.pi/self.meso_radius.value/self.meso_radius.value
        n_particle = complex(1.0-2.84e-5, 4.7e-7)
        avg_n_squared_meso = complex(0.7886*n_particle*n_particle + 0.2114)
        n_avg = complex(numpy.sqrt(self.surface_filling_ratio.value*avg_n_squared_meso + 1.0 - self.surface_filling_ratio.value))
        n_particle_adapted = complex(numpy.sqrt(n_avg*n_avg + n_particle*n_particle - 1.0))
        ff_cyl = FormFactorCylinder(self.meso_radius.value, self.meso_height.value)
        ff_meso = FormFactorDecoratorDebyeWaller(ff_cyl, self.sigma_meso_height.value*self.sigma_meso_height.value/2.0, self.sigma_meso_radius.value*self.sigma_meso_radius.value/2.0)

        # Create multilayer
        p_multi_layer = MultiLayer()
        n_air = complex(1.0, 0.0)
        n_substrate = complex(1.0-7.57e-6, 1.73e-7)

        p_air_material = HomogeneousMaterial("Air", n_air)
        p_average_layer_material = HomogeneousMaterial("Averagelayer", n_avg)
        p_substrate_material = HomogeneousMaterial("Substrate", n_substrate)
        air_layer = Layer(p_air_material)
        avg_layer = Layer(p_average_layer_material, self.meso_height.value)
        substrate_layer = Layer(p_substrate_material)
        p_interference_funtion = InterferenceFunctionNone()
        particle_layout = ParticleLayout()

        n_max_phi_rotation_steps = 2
        n_alpha_rotation_steps = 1
        alpha_step = 5.0*degree/n_alpha_rotation_steps
        alpha_start = - (n_alpha_rotation_steps/2.0)*alpha_step;

        phi_step = 2*numpy.pi/3.0/n_max_phi_rotation_steps
        phi_start = 0.0;
        for i in range(0, n_max_phi_rotation_steps):
            for j in range(0, n_alpha_rotation_steps):

                p_total_transform = Transform3D.createRotateZ(phi_start + i*phi_step)
                meso = self.createMesoCrystal(self.lattice_length_a.value, self.lattice_length_c.value, n_particle_adapted, ff_meso)
                particle_layout.addParticle(meso, p_total_transform, self.meso_height.value)

        particle_layout.setTotalParticleSurfaceDensity(surface_density)
        particle_layout.addInterferenceFunction(p_interference_funtion)
        
        avg_layer.addLayout(particle_layout)

        roughness = LayerRoughness(self.roughness.value, 0.3, 500.0*nanometer)

        p_multi_layer.addLayer(air_layer)
        p_multi_layer.addLayer(avg_layer)
        p_multi_layer.addLayerWithTopRoughness(substrate_layer, roughness)

        self.sample = p_multi_layer
        return self.sample
    
    # -------------------------------------------------------------------------
    # building meso crystal
    # -------------------------------------------------------------------------
    def createMesoCrystal(self,stacking_radius_a, stacking_radius_c, n_particle, p_meso_form_factor):
        
        mParticle = HomogeneousMaterial("Particle", n_particle )
        
        p_lat = self.createLattice(stacking_radius_a, stacking_radius_c)
        bas_a = p_lat.getBasisVectorA()
        bas_b = p_lat.getBasisVectorB()
        bas_c = p_lat.getBasisVectorC()
        ff_sphere = FormFactorSphereGaussianRadius(self.nanoparticle_radius.value, self.sigma_nanoparticle_radius.value)
        particle = Particle(mParticle, ff_sphere )
        position_0 = kvector_t(0.0, 0.0, 0.0)
        position_1 = kvector_t(0.0, 0.0, 0.0)
        position_2 = kvector_t(0.0, 0.0, 0.0)        
        position_1 = 1.0/3.0*(2.0*bas_a + bas_b + bas_c)
        position_2 = 1.0/3.0*(bas_a + 2.0*bas_b + 2.0*bas_c)
        positions = [ position_0, position_1, position_2 ]
        basis = LatticeBasis()
        basis.addParticle(particle, positions)

        npc = Crystal(basis, p_lat)
        dw_factor = self.sigma_lattice_length_a.value*self.sigma_lattice_length_a.value/6.0
        npc.setDWFactor(dw_factor)
        meso = MesoCrystal(npc, p_meso_form_factor)
        return meso
  
    # -------------------------------------------------------------------------
    # create lattice
    # -------------------------------------------------------------------------
    def createLattice(self, stacking_radius_a, stacking_radius_c):
        lattice = Lattice.createTrigonalLattice(stacking_radius_a*2.0, stacking_radius_c*2.0*2.3)
        p_result = Lattice(lattice)
        selection_rule = SimpleSelectionRule(-1, 1, 1, 3)
        p_result.setSelectionRule( selection_rule )
        return p_result


# -----------------------------------------------------------------------------
# run mesocrystal simulation
# -----------------------------------------------------------------------------
def runTest():
    # setting simulation
    sample_builder = MySampleBuilder()
    simulation = createSimulation()
    simulation.setSampleBuilder( sample_builder )

    # loading reference data
    reference = get_reference_data("mesocrystal01_reference.int.gz")

    # setting detector axis as in reference data
    simulation.setDetectorParameters(reference)

    #running simulation
    simulation.runSimulation()
    simulation.normalize()
    result = simulation.getIntensityData()

    diff = IntensityDataFunctions.getRelativeDifference(result, reference)

    status = "OK"
    if(diff > 1e-10 or numpy.isnan(diff)):
        status = "FAILED"
    return "MesoCrystal1", "Mesocrystal simulation", diff, status


# create simulation
def createSimulation():
    simulation = Simulation()
    simulation.setBeamParameters(1.77*angstrom, 0.4*degree, 0.0*degree)
    simulation.setBeamIntensity(5.0090e+12)
    #simulation.setDetectorResolutionFunction(ResolutionFunction2DSimple(0.0002, 0.0002))
    return simulation


if __name__ == '__main__':
    name, description, diff, status = runTest()
    print name, description, diff, status
    if("FAILED" in status):
        exit(1)
