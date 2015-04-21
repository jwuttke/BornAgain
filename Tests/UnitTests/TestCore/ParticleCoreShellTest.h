#ifndef PARTICLECORESHELLTEST_H
#define PARTICLECORESHELLTEST_H

#include "ParticleCoreShell.h"
#include "Units.h"
#include "HomogeneousMaterial.h"
#include "FormFactorFullSphere.h"
#include <iostream>

class ParticleCoreShellTest : public ::testing::Test
{
protected:
    ParticleCoreShellTest();
    virtual ~ParticleCoreShellTest();

    ParticleCoreShell *mp_coreshell;
};

ParticleCoreShellTest::ParticleCoreShellTest()
    : mp_coreshell(0)
{
    Particle core;
    Particle shell;
    kvector_t position;
    mp_coreshell = new ParticleCoreShell(shell, core, position);
}

ParticleCoreShellTest::~ParticleCoreShellTest()
{
    delete mp_coreshell;
}


TEST_F(ParticleCoreShellTest, InitialState)
{
    kvector_t zero_vector;
    EXPECT_EQ(NULL, mp_coreshell->getAmbientMaterial());
    EXPECT_EQ(NULL, mp_coreshell->createFormFactor(1.0));
    EXPECT_EQ(NULL, mp_coreshell->getRotation());
    EXPECT_EQ("ParticleCoreShell", mp_coreshell->getName());
    EXPECT_EQ("Particle", mp_coreshell->getCoreParticle()->getName());
    EXPECT_EQ("Particle", mp_coreshell->getShellParticle()->getName());
    EXPECT_EQ(zero_vector, mp_coreshell->getRelativeCorePosition());
}

TEST_F(ParticleCoreShellTest, Clone)
{
    kvector_t zero_vector;
    ParticleCoreShell *p_clone = mp_coreshell->clone();
    EXPECT_EQ(NULL, p_clone->getAmbientMaterial());
    EXPECT_EQ(NULL, p_clone->createFormFactor(1.0));
    EXPECT_EQ(NULL, p_clone->getRotation());
    EXPECT_EQ("ParticleCoreShell", p_clone->getName());
    EXPECT_EQ("Particle", p_clone->getCoreParticle()->getName());
    EXPECT_EQ("Particle", p_clone->getShellParticle()->getName());
    EXPECT_EQ(zero_vector, p_clone->getRelativeCorePosition());
    delete p_clone;
}

TEST_F(ParticleCoreShellTest, CloneInvertB)
{
    kvector_t zero_vector;
    ParticleCoreShell *p_clone = mp_coreshell->cloneInvertB();
    EXPECT_EQ(NULL, p_clone->getAmbientMaterial());
    EXPECT_EQ(NULL, p_clone->createFormFactor(1.0));
    EXPECT_EQ(NULL, p_clone->getRotation());
    EXPECT_EQ("ParticleCoreShell_inv", p_clone->getName());
    EXPECT_EQ("Particle_inv", p_clone->getCoreParticle()->getName());
    EXPECT_EQ("Particle_inv", p_clone->getShellParticle()->getName());
    EXPECT_EQ(zero_vector, p_clone->getRelativeCorePosition());
    delete p_clone;
}

TEST_F(ParticleCoreShellTest, Transform)
{
    kvector_t zero_vector;
    RotationZ transform(1.0);
    mp_coreshell->setTransformation(transform);
    EXPECT_EQ(NULL, mp_coreshell->getAmbientMaterial());
    EXPECT_EQ(NULL, mp_coreshell->createFormFactor(1.0));
    Geometry::Transform3D transform_2 = mp_coreshell->getRotation()->getTransform3D();
    EXPECT_EQ(Geometry::Transform3D::ZAXIS, transform_2.getRotationType());
    transform_2 = mp_coreshell->getCoreParticle()->getRotation()->getTransform3D();
    EXPECT_EQ(Geometry::Transform3D::ZAXIS, transform_2.getRotationType());
    transform_2 = mp_coreshell->getShellParticle()->getRotation()->getTransform3D();
    EXPECT_EQ(Geometry::Transform3D::ZAXIS, transform_2.getRotationType());
    EXPECT_EQ("ParticleCoreShell", mp_coreshell->getName());
    EXPECT_EQ("Particle", mp_coreshell->getCoreParticle()->getName());
    EXPECT_EQ("Particle", mp_coreshell->getShellParticle()->getName());
    EXPECT_EQ(zero_vector, mp_coreshell->getRelativeCorePosition());
}

TEST_F(ParticleCoreShellTest, AmbientMaterial)
{
    kvector_t zero_vector;
    HomogeneousMaterial mat("Air", 0.0, 0.0);
    EXPECT_EQ(NULL, mp_coreshell->getAmbientMaterial());
    mp_coreshell->setAmbientMaterial(mat);
    const IMaterial *p_material = mp_coreshell->getAmbientMaterial();
    EXPECT_EQ("Air", p_material->getName());
    EXPECT_EQ(complex_t(1.0, 0.0), p_material->getRefractiveIndex());
    p_material = mp_coreshell->getCoreParticle()->getAmbientMaterial();
    EXPECT_EQ("Air", p_material->getName());
    EXPECT_EQ(complex_t(1.0, 0.0), p_material->getRefractiveIndex());
    p_material = mp_coreshell->getShellParticle()->getAmbientMaterial();
    EXPECT_EQ("Air", p_material->getName());
    EXPECT_EQ(complex_t(1.0, 0.0), p_material->getRefractiveIndex());
    EXPECT_EQ(NULL, mp_coreshell->createFormFactor(1.0));
    EXPECT_EQ("ParticleCoreShell", mp_coreshell->getName());
    EXPECT_EQ("Particle", mp_coreshell->getCoreParticle()->getName());
    EXPECT_EQ("Particle", mp_coreshell->getShellParticle()->getName());
    EXPECT_EQ(zero_vector, mp_coreshell->getRelativeCorePosition());
}

#endif // PARTICLECORESHELLTEST_H
