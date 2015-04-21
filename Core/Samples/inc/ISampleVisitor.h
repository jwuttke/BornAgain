// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/inc/ISampleVisitor.h
//! @brief     Defines interface class ISampleVisitor.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ISAMPLEVISITOR_H
#define ISAMPLEVISITOR_H

#include "Exceptions.h"

class ISample;
// - the order according to the hierarchy as reported by IDE
class ICompositeSample;
// -
class IClusteredParticles;
class Crystal;
// -
class ILayout;
class ParticleLayout;
// -
class Layer;
// -
class LayerInterface;
// -
class MultiLayer;
// -
class IParticle;
class Particle;
class ParticleDistribution;
class ParticleComposition;
class MesoCrystal;
class ParticleCoreShell;
// -
class ParticleInfo;
// -
class IFormFactor;
// -
class FormFactorDWBAPol;
// -
class FormFactorWeighted;
// -
class IFormFactorBorn;
// -
class FormFactorAnisoPyramid;
class FormFactorBox;
class FormFactorCone;
class FormFactorCone6;
class FormFactorCuboctahedron;
class FormFactorCrystal;
class FormFactorCylinder;
class FormFactorEllipsoidalCylinder;
class FormFactorFullSphere;
class FormFactorFullSpheroid;
class FormFactorGauss;
class FormFactorHemiEllipsoid;
class FormFactorInfLongBox;
class FormFactorInfLongRipple1;
class FormFactorInfLongRipple2;
class FormFactorLorentz;
class FormFactorPrism3;
class FormFactorPrism6;
class FormFactorPyramid;
class FormFactorRipple1;
class FormFactorRipple2;
class FormFactorSphereGaussianRadius;
class FormFactorSphereLogNormalRadius;
class FormFactorTetrahedron;
class FormFactorTrivial;
class FormFactorTruncatedCube;
class FormFactorTruncatedSphere;
class FormFactorTruncatedSpheroid;
class IFormFactorBornSeparable;
// -
class IFormFactorDecorator;
// -
class FormFactorDWBA;
class FormFactorDecoratorDebyeWaller;
class FormFactorDecoratorFactor;
class FormFactorDecoratorMaterial;
class FormFactorDecoratorMultiPositionFactor;
class FormFactorDecoratorPositionFactor;
class FormFactorDecoratorTransformation;
// -
class IInterferenceFunction;
class InterferenceFunction1DLattice;
class InterferenceFunctionRadialParaCrystal;
class InterferenceFunction2DLattice;
class InterferenceFunction2DParaCrystal;
class InterferenceFunctionNone;
// -
class IRoughness;
class LayerRoughness;
// -
class IRotation;
class RotationX;
class RotationY;
class RotationZ;
class RotationEuler;

//! @class ISampleVisitor
//! @ingroup samples_internal
//! @brief Visitor interface to visit ISample objects
//!
//! From visitor pattern to achieve double dispatch

class BA_CORE_API_ ISampleVisitor
{
public:
    ISampleVisitor() : m_level(0) {}
    virtual ~ISampleVisitor(){}

    // visiting methods (the order according to the hierarchy as reported by IDE)

    virtual void visit(const ISample *);

    virtual void visit(const ICompositeSample *);

    virtual void visit(const IClusteredParticles *);
    virtual void visit(const Crystal *);

    virtual void visit(const ILayout *);
    virtual void visit(const ParticleLayout *);

    virtual void visit(const Layer *);

    virtual void visit(const LayerInterface *);

    virtual void visit(const MultiLayer *);

    virtual void visit(const IParticle *);
    virtual void visit(const Particle *);
    virtual void visit(const ParticleDistribution *);
    virtual void visit(const ParticleComposition *);
    virtual void visit(const MesoCrystal *);
    virtual void visit(const ParticleCoreShell *);

    virtual void visit(const ParticleInfo *);

    virtual void visit(const IFormFactor *);

    virtual void visit(const FormFactorDWBAPol *);

    virtual void visit(const FormFactorWeighted *);

    virtual void visit(const IFormFactorBorn *);

    virtual void visit(const FormFactorAnisoPyramid *);
    virtual void visit(const FormFactorBox *);
    virtual void visit(const FormFactorCone *);
    virtual void visit(const FormFactorCone6 *);
    virtual void visit(const FormFactorCuboctahedron *);
    virtual void visit(const FormFactorCrystal *);
    virtual void visit(const FormFactorCylinder *);
    virtual void visit(const FormFactorEllipsoidalCylinder *);
    virtual void visit(const FormFactorFullSphere *);
    virtual void visit(const FormFactorFullSpheroid *);
    virtual void visit(const FormFactorGauss *);
    virtual void visit(const FormFactorHemiEllipsoid *);
    virtual void visit(const FormFactorInfLongBox *);
    virtual void visit(const FormFactorInfLongRipple1 *);
    virtual void visit(const FormFactorInfLongRipple2 *);
    virtual void visit(const FormFactorLorentz *);
    virtual void visit(const FormFactorPrism3 *);
    virtual void visit(const FormFactorPrism6 *);
    virtual void visit(const FormFactorPyramid *);
    virtual void visit(const FormFactorRipple1 *);
    virtual void visit(const FormFactorRipple2 *);
    virtual void visit(const FormFactorSphereGaussianRadius *);
    virtual void visit(const FormFactorSphereLogNormalRadius *);
    virtual void visit(const FormFactorTetrahedron *);
    virtual void visit(const FormFactorTrivial *);
    virtual void visit(const FormFactorTruncatedCube *);
    virtual void visit(const FormFactorTruncatedSphere *);
    virtual void visit(const FormFactorTruncatedSpheroid *);
    virtual void visit(const IFormFactorBornSeparable *);

    virtual void visit(const IFormFactorDecorator *);

    virtual void visit(const FormFactorDWBA *);
    virtual void visit(const FormFactorDecoratorDebyeWaller *);
    virtual void visit(const FormFactorDecoratorFactor *);
    virtual void visit(const FormFactorDecoratorMaterial *);
    virtual void visit(const FormFactorDecoratorMultiPositionFactor *);
    virtual void visit(const FormFactorDecoratorPositionFactor *);
    virtual void visit(const FormFactorDecoratorTransformation *);

    virtual void visit(const IInterferenceFunction *);
    virtual void visit(const InterferenceFunction1DLattice *);
    virtual void visit(const InterferenceFunctionRadialParaCrystal *);
    virtual void visit(const InterferenceFunction2DLattice *);
    virtual void visit(const InterferenceFunction2DParaCrystal *);
    virtual void visit(const InterferenceFunctionNone *);

    virtual void visit(const IRoughness *);
    virtual void visit(const LayerRoughness *);

    virtual void visit(const IRotation *);
    virtual void visit(const RotationX *);
    virtual void visit(const RotationY *);
    virtual void visit(const RotationZ *);
    virtual void visit(const RotationEuler *);

    // enter and leave methods
    bool visitEnter(const ICompositeSample *);
    bool visitLeave(const ICompositeSample *);

    //! return current level of the visitor in the composite hierarchy
    int getLevel() const { return m_level; }

    //! set current level of the visitor in the composite hierarchy
    void setLevel(int level) { m_level = level; }

private:
    int m_level;
};

BA_CORE_API_ void VisitSampleTree(const ISample &sample, ISampleVisitor &visitor);


#endif // ISAMPLEVISITOR_H
