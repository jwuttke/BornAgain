#include "BeamItem.h"
#include "ParaCrystalItems.h"
#include "ComboProperty.h"
#include "Units.h"

const QString BeamItem::P_INTENSITY = "Intensity [1/s]";
const QString BeamItem::P_WAVELENGTH = "Wavelength [nm]";
const QString BeamItem::P_INCLINATION_ANGLE = "Inclination Angle";
const QString BeamItem::P_AZIMUTHAL_ANGLE = "Azimuthal Angle";
const QString BeamItem::P_ANGLE_UNITS = "Angle units";

BeamItem::BeamItem(ParameterizedItem *parent)
    : ParameterizedItem(Constants::BeamType, parent)
{
    setItemName(Constants::BeamType);
    registerProperty(P_INTENSITY, 1e+08);
    registerProperty(P_WAVELENGTH, 0.1);
    registerProperty(P_INCLINATION_ANGLE, 0.2);
    registerProperty(P_AZIMUTHAL_ANGLE, 0.0);

    ComboProperty units;
    //units << "Degrees" << "Radians";
    units << "Degrees";
    registerProperty(P_ANGLE_UNITS, units.getVariant());

}

