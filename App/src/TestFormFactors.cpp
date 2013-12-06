// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/src/TestFormFactors.cpp
//! @brief     Implements class TestFormFactors.
//
//! Homepage:  apps.jcns.fz-juelich.de/BornAgain
//! License:   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "TestFormFactors.h"
#include "IsGISAXSTools.h"
#include "OutputDataIOFactory.h"
#include "Units.h"
#include "Utils.h"
#include "Simulation.h"
#include "MultiLayer.h"
#include "ParticleDecoration.h"
#include "MaterialManager.h"
#include "FormFactors.h"
#include "InterferenceFunctionNone.h"

TestFormFactors::TestFormFactors()
: IApplicationTest("TestFormFactors")
, mp_form_factor(0)
{
    setOutputPath(Utils::FileSystem::GetPathToData(
            "../Tests/ReferenceData/IsGISAXS/FormFactors/" ));
}

void TestFormFactors::execute()
{
   //Cylinder
   FormFactorCylinder ff_cyl(5.0, 5.0);
   IFormFactor* p_form_factor0 =& ff_cyl;
   run_isgisaxs_simulation(p_form_factor0->clone());

   //Box
   FormFactorBox ff_box(10.0, 20.0, 5.0);
   IFormFactor* p_form_factor1 =& ff_box;
   run_isgisaxs_simulation(p_form_factor1->clone());

   //Cone
   FormFactorCone ff_cone(5.0, 5.0, Units::deg2rad(54.73 ));
   IFormFactor* p_form_factor2 =& ff_cone;
   run_isgisaxs_simulation(p_form_factor2->clone());

   //Cone6
   FormFactorCone6 ff_cone6(2./sqrt(3.)*5.0, 5.0, Units::deg2rad(54.73));
   IFormFactor* p_form_factor3 =& ff_cone6;
   run_isgisaxs_simulation(p_form_factor3->clone());

   //FullSphere
   FormFactorFullSphere ff_fsph(5.0);
   IFormFactor* p_form_factor4 =& ff_fsph;
   run_isgisaxs_simulation(p_form_factor4->clone());

   //Parallelepiped
   FormFactorParallelepiped ff_par(5.0, 5.0);
   IFormFactor* p_form_factor5 =& ff_par;
   run_isgisaxs_simulation(p_form_factor5->clone());

   //Prism3
   FormFactorPrism3 ff_pr3(5.0, 5.0);
   IFormFactor* p_form_factor6 =& ff_pr3;
   run_isgisaxs_simulation(p_form_factor6->clone());

   //Prism6
   FormFactorPrism6 ff_pr6(2./sqrt(3.)*5.0, 5.0);
   IFormFactor* p_form_factor7 =& ff_pr6;
   run_isgisaxs_simulation(p_form_factor7->clone());

   //Pyramid
   FormFactorPyramid ff_pyr(5.0, 5.0, Units::deg2rad(54.73 ));
   IFormFactor* p_form_factor8 =& ff_pyr;
   run_isgisaxs_simulation(p_form_factor8->clone());

   //Sphere
   FormFactorSphere ff_sph(5.0, 5.0);
   IFormFactor* p_form_factor9 =& ff_sph;
   run_isgisaxs_simulation(p_form_factor9->clone());

   // Tetrahedron
   FormFactorTetrahedron ff_tetr(5.0, 5.0, Units::deg2rad(54.73 ));
   IFormFactor* p_form_factor10 =& ff_tetr;
   run_isgisaxs_simulation(p_form_factor10->clone());
}


void TestFormFactors::run_isgisaxs_simulation(IFormFactor *p_form_factor)
{
    const IMaterial *p_air_material =
            MaterialManager::getHomogeneousMaterial("Air", 0.0, 0.0);
    const IMaterial *particle_material =
            MaterialManager::getHomogeneousMaterial("Particle", 6e-4, 2e-8);

    // R=H=5nm W=2R, no rotation of particles angle =54.73deg
    // For Cone6 and prism6 radius = 2./sqrt(3.)R_{IsGiSaXs}
    // Length unit : nanometers

    //building sample
    MultiLayer multi_layer;
    Layer air_layer;
    air_layer.setMaterial(p_air_material);

    mp_form_factor=p_form_factor;
    ParticleDecoration particle_decoration( new Particle(particle_material,
                                                         mp_form_factor));
    particle_decoration.addInterferenceFunction(new InterferenceFunctionNone());
    air_layer.setDecoration(particle_decoration);
    multi_layer.addLayer(air_layer);

    // building simulation
    Simulation simulation(mp_options);
    simulation.setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree,
                                     100, 0.0*Units::degree, 2.0*Units::degree,
                                     true);
    simulation.setBeamParameters(1.0*Units::angstrom, 0.2*Units::degree,
               0.0*Units::degree);

    simulation.setSample(multi_layer);
    simulation.runSimulation();
    std::cout << mp_form_factor->getName().substr(10) <<std::endl;
    OutputDataIOFactory::writeIntensityData(*simulation.getOutputData(),
                       "this_"+mp_form_factor->getName().substr(10)+"_BA.ima");
}

//void TestFormFactors::execute()
//{
 //   // building simulation
 //   Simulation simulation(mp_options);
 //   simulation.setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree,
 //                                    100, 0.0*Units::degree, 2.0*Units::degree,
 //                                    true);
 //   simulation.setBeamParameters(1.0*Units::angstrom, 0.2*Units::degree,
 //           0.0*Units::degree);

    //building sample
   // MultiLayer multi_layer;
   // const IMaterial *p_air_material = MaterialManager::getHomogeneousMaterial("Air", 0.0, 0.0);
   // const IMaterial *p_substrate_material =
   //         MaterialManager::getHomogeneousMaterial("Substrate", 6e-6, 2e-8);
   // Layer air_layer;
  //  air_layer.setMaterial(p_air_material);
  //  Layer substrate_layer;
  //  substrate_layer.setMaterial(p_substrate_material);
  //  const IMaterial *particle_material =
  //          MaterialManager::getHomogeneousMaterial("Particle", 6e-4, 2e-8);

    // R=H=5nm W=2R, no rotation of particles angle =54.73deg
    // For Cone6 and prism6 radius = 2./sqrt(3.)R_{IsGiSaXs}
    //double angle = Units::deg2rad(54.73 );
   // double radius = 5.0*Units::nanometer;
   // double half_side = radius;
   // double height = 5.0*Units::nanometer;
   // double length = 2.*radius;
   // double width = 2.*length;
   // double side_hex_base = 2./sqrt(3.)*radius;

    //FormFactorCylinder ff(height, radius);
    //FormFactorBox ff(length, width, height);
   // FormFactorCone ff(radius, height, angle);
    //FormFactorCone6 ff(side_hex_base, height, angle);
    //FormFactorFullSphere ff(radius);
    //FormFactorParallelepiped ff(height, radius);
    //FormFactorPrism3 ff(height, half_side);
    //FormFactorPrism6 ff(side_hex_base, height);
    //FormFactorPyramid ff(height, half_side, angle);
    //FormFactorSphere ff(radius, height);
    //FormFactorTetrahedron ff(5.*Units::nanometer,5.*Units::nanometer, angle);

   // ParticleDecoration particle_decoration( new Particle(particle_material,ff));
   // particle_decoration.addInterferenceFunction(new InterferenceFunctionNone());
  //  air_layer.setDecoration(particle_decoration);
  //  multi_layer.addLayer(air_layer);
  //  // building simulation
  //  simulation.setSample(multi_layer);
  //  simulation.runSimulation();

    //OutputDataIOFactory::writeIntensityData(*simulation.getOutputData(), "this_cylinder_BA.ima");
    //OutputDataIOFactory::writeIntensityData(*simulation.getOutputData(), "this_box_BA.ima");
  //  OutputDataIOFactory::writeIntensityData(*simulation.getOutputData(), "this_cone_BA.ima");
    //OutputDataIOFactory::writeIntensityData(*simulation.getOutputData(), "this_cone6_BA.ima");
    //OutputDataIOFactory::writeIntensityData(*simulation.getOutputData(), "this_full_sphere_BA.ima");
    //OutputDataIOFactory::writeIntensityData(*simulation.getOutputData(), "this_parallelepiped_BA.ima");
    //OutputDataIOFactory::writeIntensityData(*simulation.getOutputData(), "this_prism3_BA.ima");
    //OutputDataIOFactory::writeIntensityData(*simulation.getOutputData(), "this_prism6_BA.ima");
    //OutputDataIOFactory::writeIntensityData(*simulation.getOutputData(), "this_pyramid_BA.ima");
    //OutputDataIOFactory::writeIntensityData(*simulation.getOutputData(), "this_sphere_BA.ima");
    //OutputDataIOFactory::writeIntensityData(*simulation.getOutputData(), "this_tetrahedron_BA.ima");
//}

void TestFormFactors::finalise()
{
    std::vector< CompareStruct > tocompare;
    tocompare.push_back( CompareStruct(getOutputPath()+"isgi_cylinder_BA.ima",
            "this_Cylinder_BA.ima",
            "Cylinder BA Formfactor"));

    tocompare.push_back( CompareStruct(getOutputPath()+"isgi_box_BA.ima",
            "this_Box_BA.ima", "Box BA Formfactor"));

    tocompare.push_back( CompareStruct(getOutputPath()+"isgi_cone_BA.ima",
            "this_Cone_BA.ima", "Cone BA Formfactor"));

    tocompare.push_back( CompareStruct( getOutputPath()+"isgi_cone6_BA.ima",
            "this_Cone6_BA.ima", "Cone6 BA Formfactor"));

    tocompare.push_back( CompareStruct(getOutputPath()+
                                       "isgi_full_sphere_BA.ima",
            "this_FullSphere_BA.ima","Full Sphere BA Formfactor"));

    tocompare.push_back( CompareStruct(getOutputPath()+
                                      "isgi_parallelepiped_BA.ima",
            "this_Parallelepiped_BA.ima","Parallelepiped BA Formfactor"));

    tocompare.push_back( CompareStruct(getOutputPath()+"isgi_prism3_BA.ima",
            "this_Prism3_BA.ima", "Prism3 BA Formfactor"));

    tocompare.push_back( CompareStruct(getOutputPath()+"isgi_prism6_BA.ima",
            "this_Prism6_BA.ima", "Prism6 BA Formfactor"));

    tocompare.push_back( CompareStruct(getOutputPath()+"isgi_pyramid_BA.ima",
            "this_Pyramid_BA.ima","Pyramid BA Formfactor"));

    tocompare.push_back( CompareStruct(getOutputPath()+"isgi_sphere_BA.ima",
            "this_Sphere_BA.ima","Sphere BA Formfactor"));

    tocompare.push_back( CompareStruct(getOutputPath()+
                                       "isgi_tetrahedron_BA.ima",
            "this_Tetrahedron_BA.ima","Tetrahedron BA Formfactor"));

    const double threshold(2e-10);

    for(size_t i=0; i<tocompare.size(); ++i) {
        OutputData<double> *isgi_data = OutputDataIOFactory::readIntensityData(
                tocompare[i].isginame);
        OutputData<double> *our_data = OutputDataIOFactory::readIntensityData(
                tocompare[i].thisname);

        IsGISAXSTools::drawOutputDataComparisonResults(*our_data, *isgi_data,
                tocompare[i].descr, tocompare[i].descr);

        *our_data -= *isgi_data;
        *our_data /= *isgi_data;

        double diff(0);
        for(OutputData<double>::const_iterator it =
            our_data->begin(); it!=our_data->end(); ++it) {
            diff+= std::fabs(*it);
        }
        diff /= our_data->getAllocatedSize();
        bool status_ok(true);
        if( diff > threshold || MathFunctions::isnan(diff) ) status_ok=false;
        std::cout << m_name  << tocompare[i].descr<<" " <<
            (status_ok ? "[OK]" : "[FAILED]") << std::endl;

        delete isgi_data;
        delete our_data;
    }

}





