// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/ItemFactory.cpp
//! @brief     Implements class ItemFactory
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ItemFactory.h"
#include "MultiLayerItem.h"
#include "LayerItem.h"
#include "ParticleLayoutItem.h"
#include "ParticleItem.h"
#include "TransformationItem.h"
#include "RotationItems.h"
#include "ParticleCoreShellItem.h"
#include "ParticleCompositionItem.h"
#include "ParticleDistributionItem.h"
#include "DistributionItem.h"
#include "InterferenceFunctionItems.h"
#include "InstrumentItem.h"
#include "BeamItem.h"
#include "DetectorItems.h"
#include "VectorItem.h"
#include "GUIHelpers.h"
#include "FormFactorItems.h"
#include "LayerRoughnessItems.h"
#include "FTDistributionItems.h"
#include "LatticeTypeItems.h"
#include "MaterialItem.h"
#include "RefractiveIndexItem.h"
#include "MagneticFieldItem.h"
#include "FitParameterItem.h"
#include "JobItem.h"
#include "IntensityDataItem.h"
#include "AxesItems.h"
#include "ResolutionFunctionItems.h"
#include "BeamDistributionItem.h"
#include "BeamWavelengthItem.h"
#include "BeamAngleItems.h"
#include <QDebug>

namespace {
template<typename T> ParameterizedItem *createInstance() { return new T; }

ItemFactory::ItemMap_t initializeItemMap() {
    ItemFactory::ItemMap_t result;

    result[Constants::MultiLayerType] = &createInstance<MultiLayerItem>;
    result[Constants::LayerType] = &createInstance<LayerItem>;
    result[Constants::ParticleLayoutType] = &createInstance<ParticleLayoutItem>;
    result[Constants::ParticleType] = &createInstance<ParticleItem>;
    result[Constants::TransformationType] = &createInstance<TransformationItem>;
    result[Constants::ParticleCoreShellType] = &createInstance<ParticleCoreShellItem>;
    result[Constants::ParticleCompositionType] = &createInstance<ParticleCompositionItem>;
    result[Constants::ParticleDistributionType] = &createInstance<ParticleDistributionItem>;
    result[Constants::InterferenceFunctionRadialParaCrystalType] = &createInstance<InterferenceFunctionRadialParaCrystalItem>;
    result[Constants::InterferenceFunction2DParaCrystalType] = &createInstance<InterferenceFunction2DParaCrystalItem>;
    result[Constants::InterferenceFunction2DLatticeType] = &createInstance<InterferenceFunction2DLatticeItem>;
    result[Constants::InstrumentType] = &createInstance<InstrumentItem>;
    result[Constants::DetectorType] = &createInstance<DetectorItem>;
    result[Constants::BeamType] = &createInstance<BeamItem>;
    result[Constants::VectorType] = &createInstance<VectorItem>;

    result[Constants::AnisoPyramidType] = &createInstance<AnisoPyramidItem>;
    result[Constants::BoxType] = &createInstance<BoxItem>;
    result[Constants::ConeType] = &createInstance<ConeItem>;
    result[Constants::Cone6Type] = &createInstance<Cone6Item>;
    result[Constants::CuboctahedronType] = &createInstance<CuboctahedronItem>;
    result[Constants::CylinderType] = &createInstance<CylinderItem>;
    result[Constants::EllipsoidalCylinderType] = &createInstance<EllipsoidalCylinderItem>;
    result[Constants::FullSphereType] = &createInstance<FullSphereItem>;
    result[Constants::FullSpheroidType] = &createInstance<FullSpheroidItem>;
    result[Constants::HemiEllipsoidType] = &createInstance<HemiEllipsoidItem>;
    result[Constants::Prism3Type] = &createInstance<Prism3Item>;
    result[Constants::Prism6Type] = &createInstance<Prism6Item>;
    result[Constants::PyramidType] = &createInstance<PyramidItem>;
    result[Constants::Ripple1Type] = &createInstance<Ripple1Item>;
    result[Constants::Ripple2Type] = &createInstance<Ripple2Item>;
    result[Constants::TetrahedronType] = &createInstance<TetrahedronItem>;
    result[Constants::TruncatedCubeType] = &createInstance<TruncatedCubeItem>;
    result[Constants::TruncatedSphereType] = &createInstance<TruncatedSphereItem>;
    result[Constants::TruncatedSpheroidType] = &createInstance<TruncatedSpheroidItem>;

    result[Constants::XRotationType] = &createInstance<XRotationItem>;
    result[Constants::YRotationType] = &createInstance<YRotationItem>;
    result[Constants::ZRotationType] = &createInstance<ZRotationItem>;
    result[Constants::EulerRotationType] = &createInstance<EulerRotationItem>;

    result[Constants::LayerBasicRoughnessType] = &createInstance<LayerBasicRoughnessItem>;
    result[Constants::LayerZeroRoughnessType] = &createInstance<LayerZeroRoughnessItem>;

    result[Constants::DetectorType] = &createInstance<DetectorItem>;
    result[Constants::PhiAlphaDetectorType] = &createInstance<PhiAlphaDetectorItem>;

    result[Constants::DistributionNoneType] = &createInstance<DistributionNoneItem>;
    result[Constants::DistributionGateType] = &createInstance<DistributionGateItem>;
    result[Constants::DistributionLorentzType] = &createInstance<DistributionLorentzItem>;
    result[Constants::DistributionGaussianType] = &createInstance<DistributionGaussianItem>;
    result[Constants::DistributionLogNormalType] = &createInstance<DistributionLogNormalItem>;
    result[Constants::DistributionCosineType] = &createInstance<DistributionCosineItem>;

    result[Constants::FTDistribution1DCauchyType] = &createInstance<FTDistribution1DCauchyItem>;
    result[Constants::FTDistribution1DGaussType] = &createInstance<FTDistribution1DGaussItem>;
    result[Constants::FTDistribution1DGateType] = &createInstance<FTDistribution1DGateItem>;
    result[Constants::FTDistribution1DTriangleType] = &createInstance<FTDistribution1DTriangleItem>;
    result[Constants::FTDistribution1DCosineType] = &createInstance<FTDistribution1DCosineItem>;
    result[Constants::FTDistribution1DVoigtType] = &createInstance<FTDistribution1DVoigtItem>;

    result[Constants::FTDistribution2DCauchyType] = &createInstance<FTDistribution2DCauchyItem>;
    result[Constants::FTDistribution2DGaussType] = &createInstance<FTDistribution2DGaussItem>;
    result[Constants::FTDistribution2DGateType] = &createInstance<FTDistribution2DGateItem>;
    result[Constants::FTDistribution2DConeType] = &createInstance<FTDistribution2DConeItem>;
    result[Constants::FTDistribution2DVoigtType] = &createInstance<FTDistribution2DVoigtItem>;

    result[Constants::BasicLatticeType] = &createInstance<BasicLatticeTypeItem>;
    result[Constants::SquareLatticeType] = &createInstance<SquareLatticeTypeItem>;
    result[Constants::HexagonalLatticeType] = &createInstance<HexagonalLatticeTypeItem>;

    result[Constants::MaterialType] = &createInstance<MaterialItem>;

    result[Constants::RefractiveIndexType] = &createInstance<RefractiveIndexItem>;

    result[Constants::MagneticFieldType] = &createInstance<MagneticFieldItem>;

    result[Constants::FitParameterType] = &createInstance<FitParameterItem>;

    result[Constants::JobItemType] = &createInstance<JobItem>;

    result[Constants::IntensityDataType] = &createInstance<IntensityDataItem>;

    result[Constants::BasicAxisType] = &createInstance<BasicAxisItem>;
    result[Constants::AmplitudeAxisType] = &createInstance<AmplitudeAxisItem>;

//    result[Constants::BeamDistributionType] = &createInstance<BeamDistributionItem>;
    result[Constants::BeamWavelengthType] = &createInstance<BeamWavelengthItem>;
    result[Constants::BeamAzimuthalAngleType] = &createInstance<BeamAzimuthalAngleItem>;
    result[Constants::BeamInclinationAngleType] = &createInstance<BeamInclinationAngleItem>;

    result[Constants::ResolutionFunctionNoneType] = &createInstance<ResolutionFunctionNoneItem>;
    result[Constants::ResolutionFunction2DGaussianType] = &createInstance<ResolutionFunction2DGaussianItem>;

    return result;
}
}

QStringList ItemFactory::m_valid_top_item_names = QStringList()
        << Constants::MultiLayerType
        << Constants::LayerType
        << Constants::ParticleLayoutType
        << Constants::ParticleType
        << Constants::TransformationType
        << Constants::ParticleCoreShellType
        << Constants::ParticleDistributionType
        << Constants::InterferenceFunctionRadialParaCrystalType
        << Constants::InterferenceFunction2DParaCrystalType
        << Constants::InterferenceFunction2DLatticeType;


ItemFactory::ItemMap_t ItemFactory::m_item_map = initializeItemMap();


ParameterizedItem *ItemFactory::createItem(const QString &model_name,
                                           ParameterizedItem *parent)
{
    qDebug() << "ItemFactory::createItem" << model_name;

    if(!m_item_map.contains(model_name))
        throw GUIHelpers::Error("ItemFactory::createItem() -> Error: Model name does not exist: "+model_name);

    ParameterizedItem *result = m_item_map[model_name]();
    if(parent) {
        parent->insertChildItem(-1, result);
    }

    return result;
}


ParameterizedItem *ItemFactory::createEmptyItem()
{
    return new ParameterizedItem();
}


QList<QString> ItemFactory::getValidTopItemNames() {
    return m_valid_top_item_names;
}

