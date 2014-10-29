// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/IsGISAXS07Builder.cpp
//! @brief     Implements class IsGISAXS07Builder.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "IsGISAXS07Builder.h"
#include "MultiLayer.h"
#include "ParticleLayout.h"
#include "Materials.h"
#include "FormFactorBox.h"
#include "Simulation.h"
#include "IntensityDataIOFactory.h"
#include "PositionParticleInfo.h"
#include "Utils.h"
#include "Units.h"
#include "MathFunctions.h"
#include <iostream>
#include <cmath>

IsGISAXS07Builder::IsGISAXS07Builder()
{
}


ISample *IsGISAXS07Builder::buildSample() const
{
    MultiLayer* multi_layer = new MultiLayer();

    HomogeneousMaterial air_material("Air", 0.0, 0.0);
    HomogeneousMaterial particle_material("Particle", 6e-4, 2e-8);

    Layer air_layer(air_material);

    ParticleLayout particle_layout;

    // add particle number 1:
    FormFactorBox ff1(2.0*Units::nanometer, 2.0*Units::nanometer,
            1.0*Units::nanometer);
    kvector_t pos1(0.0*Units::nanometer, 0.0*Units::nanometer, 0.0);
    PositionParticleInfo particle_info1(new Particle(particle_material, ff1),
            pos1, 0.5);
    particle_layout.addParticleInfo(particle_info1);
    // add particle number 2:
    FormFactorBox ff2(2.0*Units::nanometer, 4.0*Units::nanometer,
            1.0*Units::nanometer);
    kvector_t pos2(5.0*Units::nanometer, 5.0*Units::nanometer, 0.0);
    Geometry::Transform3D m2 =
            Geometry::Transform3D::createRotateZ(10*Units::degree);
    PositionParticleInfo particle_info2(
            new Particle(particle_material, ff2, m2), pos2, 0.5);
    particle_layout.addParticleInfo(particle_info2);
    // add particle number 3:
    FormFactorBox ff3(2.0*Units::nanometer, 6.0*Units::nanometer,
            1.0*Units::nanometer);
    kvector_t pos3(-5.0*Units::nanometer, -5.0*Units::nanometer, 0.0);
    Geometry::Transform3D m3 =
            Geometry::Transform3D::createRotateZ(20*Units::degree);
    PositionParticleInfo particle_info3(
            new Particle(particle_material, ff3, m3), pos3, 0.5);
    particle_layout.addParticleInfo(particle_info3);
    // add particle number 4:
    FormFactorBox ff4(2.0*Units::nanometer, 8.0*Units::nanometer,
            1.0*Units::nanometer);
    kvector_t pos4(5.0*Units::nanometer, -5.0*Units::nanometer, 0.0);
    Geometry::Transform3D m4 =
            Geometry::Transform3D::createRotateZ(30*Units::degree);
    PositionParticleInfo particle_info4(
            new Particle(particle_material, ff4, m4), pos4, 0.5);
    particle_layout.addParticleInfo(particle_info4);
    // add particle number 5:
    FormFactorBox ff5(2.0*Units::nanometer, 10.0*Units::nanometer,
            1.0*Units::nanometer);
    kvector_t pos5(-5.0*Units::nanometer, 5.0*Units::nanometer, 0.0);
    Geometry::Transform3D m5 =
            Geometry::Transform3D::createRotateZ(40*Units::degree);
    PositionParticleInfo particle_info5(
            new Particle(particle_material, ff5, m5), pos5, 0.5);
    particle_layout.addParticleInfo(particle_info5);
    // add particle number 6:
    FormFactorBox ff6(2.0*Units::nanometer, 2.0*Units::nanometer,
            1.0*Units::nanometer);
    kvector_t pos6(0.0*Units::nanometer, 0.0*Units::nanometer, 0.0);
    Geometry::Transform3D m6 =
            Geometry::Transform3D::createRotateZ(50*Units::degree);
    PositionParticleInfo particle_info6(
            new Particle(particle_material, ff6, m6), pos6, 0.5);
    particle_layout.addParticleInfo(particle_info6);
    // add particle number 7:
    FormFactorBox ff7(2.0*Units::nanometer, 4.0*Units::nanometer,
            1.0*Units::nanometer);
    kvector_t pos7(5.0*Units::nanometer, 5.0*Units::nanometer, 0.0);
    Geometry::Transform3D m7 =
            Geometry::Transform3D::createRotateZ(60*Units::degree);
    PositionParticleInfo particle_info7(
            new Particle(particle_material, ff7, m7), pos7, 0.5);
    particle_layout.addParticleInfo(particle_info7);
    // add particle number 8:
    FormFactorBox ff8(2.0*Units::nanometer, 6.0*Units::nanometer,
            1.0*Units::nanometer);
    kvector_t pos8(-5.0*Units::nanometer, -5.0*Units::nanometer, 0.0);
    Geometry::Transform3D m8 =
            Geometry::Transform3D::createRotateZ(70*Units::degree);
    PositionParticleInfo particle_info8(
            new Particle(particle_material, ff8, m8), pos8, 0.5);
    particle_layout.addParticleInfo(particle_info8);
    // add particle number 9:
    FormFactorBox ff9(2.0*Units::nanometer, 8.0*Units::nanometer,
            1.0*Units::nanometer);
    kvector_t pos9(5.0*Units::nanometer, -5.0*Units::nanometer, 0.0);
    Geometry::Transform3D m9 =
            Geometry::Transform3D::createRotateZ(80*Units::degree);
    PositionParticleInfo particle_info9(
            new Particle(particle_material, ff9, m9), pos9, 0.5);
    particle_layout.addParticleInfo(particle_info9);
    // add particle number 10:
    FormFactorBox ff10(2.0*Units::nanometer, 10.0*Units::nanometer,
            1.0*Units::nanometer);
    kvector_t pos10(-5.0*Units::nanometer, 5.0*Units::nanometer, 0.0);
    Geometry::Transform3D m10 =
            Geometry::Transform3D::createRotateZ(90*Units::degree);
    PositionParticleInfo particle_info10(
            new Particle(particle_material, ff10, m10), pos10, 0.5);
    particle_layout.addParticleInfo(particle_info10);
    particle_layout.setApproximation(ILayout::ISGISAXSMOR);

    air_layer.addLayout(particle_layout);
    multi_layer->addLayer(air_layer);

    return multi_layer;
}

