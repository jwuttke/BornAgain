// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/item_constants.h
//! @brief     Defines item constants
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ITEMCONSTANTS_H
#define ITEMCONSTANTS_H

#include <QString>

namespace Constants {

// --- Items -------------------------------------------------------------------

typedef QString ModelType;

const ModelType LayerType = "Layer";
const ModelType MultiLayerType = "MultiLayer";
const ModelType ParticleType = "Particle";
const ModelType ParticleLayoutType = "ParticleLayout";
const ModelType ParticleCoreShellType = "ParticleCoreShell";
const ModelType ParticleDistributionType = "ParticleDistribution";
const ModelType ParticleCompositionType = "ParticleComposition";
const ModelType TransformationType = "Transformation";
const ModelType InterferenceFunctionRadialParaCrystalType = "InterferenceFunctionRadialParaCrystal";
const ModelType InterferenceFunction2DParaCrystalType = "InterferenceFunction2DParaCrystal";
const ModelType InterferenceFunction2DLatticeType = "InterferenceFunction2DLattice";
const ModelType InstrumentType = "Instrument";
const ModelType DetectorType = "Detector";
const ModelType BeamType = "Beam";

const ModelType FormFactorType = "FormFactor";
const ModelType AnisoPyramidType = "AnisoPyramid";
const ModelType BoxType = "Box";
const ModelType ConeType = "Cone";
const ModelType Cone6Type = "Cone6";
const ModelType CuboctahedronType = "Cuboctahedron";
const ModelType CylinderType = "Cylinder";
const ModelType EllipsoidalCylinderType = "EllipsoidalCylinder";
const ModelType FullSphereType = "FullSphere";
const ModelType FullSpheroidType = "FullSpheroid";
const ModelType HemiEllipsoidType = "HemiEllipsoid";
const ModelType Prism3Type = "Prism3";
const ModelType Prism6Type = "Prism6";
const ModelType PyramidType = "Pyramid";
const ModelType Ripple1Type = "Ripple1";
const ModelType Ripple2Type = "Ripple2";
const ModelType TetrahedronType = "Tetrahedron";
const ModelType TruncatedCubeType = "TruncatedCube";
const ModelType TruncatedSphereType = "TruncatedSphere";
const ModelType TruncatedSpheroidType = "TruncatedSpheroid";

const ModelType XRotationType = "XRotation";
const ModelType YRotationType = "YRotation";
const ModelType ZRotationType = "ZRotation";
const ModelType EulerRotationType = "EulerRotation";

const ModelType VectorType = "Vector";

const ModelType LayerBasicRoughnessType = "LayerBasicRoughness";
const ModelType LayerZeroRoughnessType = "LayerZeroRoughness";

const ModelType PhiAlphaDetectorType = "PhiAlphaDetector";

const ModelType DistributionNoneType = "DistributionNone";
const ModelType DistributionGateType = "DistributionGate";
const ModelType DistributionLorentzType = "DistributionLorentz";
const ModelType DistributionGaussianType = "DistributionGaussian";
const ModelType DistributionLogNormalType = "DistributionLogNormal";
const ModelType DistributionCosineType = "DistributionCosine";

const ModelType FTDistribution1DCauchyType = "FTDistribution1DCauchy";
const ModelType FTDistribution1DGaussType = "FTDistribution1DGauss";
const ModelType FTDistribution1DGateType = "FTDistribution1DGate";
const ModelType FTDistribution1DTriangleType = "FTDistribution1DTriangle";
const ModelType FTDistribution1DCosineType = "FTDistribution1DCosine";
const ModelType FTDistribution1DVoigtType = "FTDistribution1DVoigt";

const ModelType FTDistribution2DCauchyType = "FTDistribution2DCauchy";
const ModelType FTDistribution2DGaussType = "FTDistribution2DGauss";
const ModelType FTDistribution2DGateType = "FTDistribution2DGate";
const ModelType FTDistribution2DConeType = "FTDistribution2DCone";
const ModelType FTDistribution2DVoigtType = "FTDistribution2DVoigt";

const ModelType BasicLatticeType = "BasicLatticeType";
const ModelType SquareLatticeType = "SquareLatticeType";
const ModelType HexagonalLatticeType = "HexagonalLatticeType";

const ModelType MaterialType = "Material";
const ModelType HomogeneousMaterialType = "Homogeneous Material";
const ModelType HomogeneousMagneticMaterialType = "Homogeneous Magnetic Material";

const ModelType RefractiveIndexType = "RefractiveIndex";

const ModelType MagneticFieldType = "MagneticField";

const ModelType FitParameterType = "FitParameter";

const ModelType JobItemType = "JobItem";
const ModelType IntensityDataType = "IntensityData";

const ModelType BasicAxisType = "BasicAxis";
const ModelType AmplitudeAxisType = "AmplitudeAxis";

const ModelType BeamDistributionType = "BeamDistribution";
const ModelType BeamWavelengthType = "BeamWavelength";
const ModelType BeamAzimuthalAngleType = "BeamAzimuthalAngle";
const ModelType BeamInclinationAngleType = "BeamInclinationAngle";

const ModelType ResolutionFunctionNoneType = "ResolutionFunctionNone";
const ModelType ResolutionFunction2DGaussianType = "ResolutionFunction2DGaussian";

// --- Groups ------------------------------------------------------------------

const ModelType FormFactorGroup = "Form Factor";
const ModelType RotationGroup = "Rotation";
const ModelType LayerRoughnessGroup = "Roughness";
const ModelType DetectorGroup = "Detector group";
const ModelType DistributionGroup = "Distribution group";
const ModelType DistributionExtendedGroup = "Distribution extended group";
const ModelType FTDistribution1DGroup = "PDF 1D";
const ModelType FTDistribution2DGroup = "PDF 2D";
const ModelType LatticeGroup = "Lattice group";
const ModelType MaterialGroup = "Material group";
const ModelType ResolutionFunctionGroup = "Resolution function group";

// --- Units&Constants----------------------------------------------------------
const ModelType UnitsDegrees = "Degrees";
const ModelType UnitsRadians = "Radians";

const ModelType STATUS_IDLE = "Idle";
const ModelType STATUS_RUNNING = "Running";
const ModelType STATUS_COMPLETED = "Completed";
const ModelType STATUS_CANCELED = "Canceled";
const ModelType STATUS_FAILED = "Failed";

const ModelType GRADIENT_GRAYSCALE = "Grayscale";
const ModelType GRADIENT_HOT = "Hot";
const ModelType GRADIENT_COLD = "Cold";
const ModelType GRADIENT_NIGHT = "Night";
const ModelType GRADIENT_CANDY = "Candy";
const ModelType GRADIENT_GEOGRAPHY = "Geography";
const ModelType GRADIENT_ION = "Ion";
const ModelType GRADIENT_THERMAL = "Thermal";
const ModelType GRADIENT_POLAR = "Polar";
const ModelType GRADIENT_SPECTRUM = "Spectrum";
const ModelType GRADIENT_JET = "Jet";
const ModelType GRADIENT_HUES = "Hues";

const ModelType AXIS_FIXED_BINNING = "Fixed";
const ModelType AXIS_CONSTK_BINNING = "Const KBin";

}


#endif
