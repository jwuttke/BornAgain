#include "MaterialItem.h"
#include "ColorProperty.h"
#include "MaterialUtils.h"
#include "RefractiveIndexItem.h"
#include "ScientificDoubleProperty.h"
#include "ComboProperty.h"
#include "GUIHelpers.h"
#include <QUuid>
#include <QDebug>


const QString MaterialItem::P_MATERIAL_TYPE = "Material Type";
const QString MaterialItem::P_COLOR = "Color";
const QString MaterialItem::P_REFRACTIVE_INDEX = "Refractive index";
const QString MaterialItem::P_MAGNETIC_FIELD = "Magnetic field";
const QString MaterialItem::P_IDENTIFIER = "Identifier";


MaterialItem::MaterialItem(ParameterizedItem *parent)
    : ParameterizedItem(Constants::MaterialType, parent)
{
    setItemName(Constants::MaterialType);
    setPropertyAppearance(ParameterizedItem::P_NAME, PropertyAttribute::VisibleProperty);

    ComboProperty types;
    types << Constants::HomogeneousMaterialType << Constants::HomogeneousMagneticMaterialType;
    registerProperty(P_MATERIAL_TYPE, types.getVariant(), PropertyAttribute(PropertyAttribute::HiddenProperty));

    ColorProperty color;
    registerProperty(P_COLOR, color.getVariant());

    registerGroupProperty(P_REFRACTIVE_INDEX, Constants::RefractiveIndexType);

    registerProperty(P_IDENTIFIER, QUuid::createUuid().toString(), PropertyAttribute(PropertyAttribute::HiddenProperty));

}

void MaterialItem::setMaterialType(int index)
{
    ComboProperty combo_property = getRegisteredProperty(P_MATERIAL_TYPE).value<ComboProperty>();
    QString previous_type = combo_property.getValue();
    QString new_type = combo_property.toString(index);

    if(previous_type != new_type) {
        if(new_type == Constants::HomogeneousMagneticMaterialType) {
            registerGroupProperty(P_MAGNETIC_FIELD, Constants::MagneticFieldType);
        } else {
            removeRegisteredProperty(P_MAGNETIC_FIELD);
        }

        qDebug() << "MaterialItem::setMaterialType()" << index << combo_property.toString(index);
        combo_property.setValue(new_type);
        setRegisteredProperty(MaterialItem::P_MATERIAL_TYPE, combo_property.getVariant());
    }
}

QString MaterialItem::getIdentifier() const
{
    return getRegisteredProperty(P_IDENTIFIER).toString();
}


QColor MaterialItem::getColor() const
{
    ColorProperty color_property = getRegisteredProperty(P_COLOR).value<ColorProperty>();
    return color_property.getColor();
}

bool MaterialItem::isHomogeneousMaterial() const
{
    ComboProperty combo_property = getRegisteredProperty(MaterialItem::P_MATERIAL_TYPE).value<ComboProperty>();
    return (combo_property.getValue() == Constants::HomogeneousMaterialType);
}

bool MaterialItem::isHomogeneousMagneticMaterial() const
{
    ComboProperty combo_property = getRegisteredProperty(MaterialItem::P_MATERIAL_TYPE).value<ComboProperty>();
    return (combo_property.getValue() == Constants::HomogeneousMagneticMaterialType);
}
