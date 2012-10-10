// This file has been generated by Py++.

#include "boost/python.hpp"
#include "BasicVector3D.h"
#include "Experiment.h"
#include "FormFactorCrystal.h"
#include "FormFactorCylinder.h"
#include "FormFactorFullSphere.h"
#include "FormFactorGauss.h"
#include "FormFactorLorentz.h"
#include "FormFactorPrism3.h"
#include "FormFactorPyramid.h"
#include "GISASExperiment.h"
#include "HomogeneousMaterial.h"
#include "IClusteredParticles.h"
#include "ICompositeSample.h"
#include "IFormFactor.h"
#include "IInterferenceFunction.h"
#include "InterferenceFunctionNone.h"
#include "InterferenceFunction1DParaCrystal.h"
#include "IMaterial.h"
#include "ISample.h"
#include "ISingleton.h"
#include "Lattice.h"
#include "LatticeBasis.h"
#include "Layer.h"
#include "LayerDecorator.h"
#include "LayerRoughness.h"
#include "MaterialManager.h"
#include "MesoCrystal.h"
#include "MultiLayer.h"
#include "Particle.h"
#include "Crystal.h"
#include "ParticleDecoration.h"
#include "OpticalFresnel.h"
#include "ParameterPool.h"
#include "ParticleInfo.h"
#include "DiffuseParticleInfo.h"
#include "PythonOutputData.h"
#include "PythonPlusplusHelper.h"
#include "Transform3D.h"
#include "Units.h"
#include "Types.h"
#include "PythonInterface_global_variables.h"

namespace bp = boost::python;

void register_global_variables(){

    bp::scope().attr("PI") = Units::PI;

    bp::scope().attr("PI2") = Units::PI2;

    bp::scope().attr("PID2") = Units::PID2;

    bp::scope().attr("PI_SQR") = Units::PI_SQR;

    bp::scope().attr("angstrom") = Units::angstrom;

    bp::scope().attr("deg") = Units::deg;

    bp::scope().attr("degree") = Units::degree;

    bp::scope().attr("meter") = Units::meter;

    bp::scope().attr("micrometer") = Units::micrometer;

    bp::scope().attr("millimeter") = Units::millimeter;

    bp::scope().attr("milliradian") = Units::milliradian;

    bp::scope().attr("mrad") = Units::mrad;

    bp::scope().attr("nanometer") = Units::nanometer;

    bp::scope().attr("nm") = Units::nm;

    bp::scope().attr("rad") = Units::rad;

    bp::scope().attr("radian") = Units::radian;

    bp::scope().attr("sr") = Units::sr;

    bp::scope().attr("steradian") = Units::steradian;

}
