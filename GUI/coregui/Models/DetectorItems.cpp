// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/DetectorItem.cpp
//! @brief     Implements class DetectorItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "DetectorItems.h"
#include "ComboProperty.h"
#include "AngleProperty.h"
#include "AxesItems.h"
#include <QDebug>

const QString DetectorItem::P_DETECTOR = "Detector";

DetectorItem::DetectorItem(ParameterizedItem *parent)
    : ParameterizedItem(Constants::DetectorType, parent)
{
    setItemName(Constants::DetectorType);
    registerGroupProperty(P_DETECTOR, Constants::DetectorGroup);
}

// -------------------------------------------------------------------------- //

const QString PhiAlphaDetectorItem::P_BINNING = "Binning";
const QString PhiAlphaDetectorItem::P_PHI_AXIS = "Phi axis";
const QString PhiAlphaDetectorItem::P_ALPHA_AXIS = "Alpha axis";
const QString PhiAlphaDetectorItem::P_RESOLUTION_FUNCTION = "Type";

PhiAlphaDetectorItem::PhiAlphaDetectorItem(ParameterizedItem *parent)
    : ParameterizedItem(Constants::PhiAlphaDetectorType, parent)
{
    setItemName(Constants::PhiAlphaDetectorType);
    ComboProperty binning;
    binning << Constants::AXIS_CONSTK_BINNING << Constants::AXIS_FIXED_BINNING;
    registerProperty(P_BINNING, binning.getVariant());

    registerGroupProperty(P_PHI_AXIS, Constants::BasicAxisType);
    getSubItems()[P_PHI_AXIS]->setPropertyAppearance(BasicAxisItem::P_TITLE, PropertyAttribute::HIDDEN);
    getSubItems()[P_PHI_AXIS]->setRegisteredProperty(BasicAxisItem::P_MIN, -1.0);
    getSubItems()[P_PHI_AXIS]->setRegisteredProperty(BasicAxisItem::P_MAX, 1.0);

    registerGroupProperty(P_ALPHA_AXIS, Constants::BasicAxisType);
    getSubItems()[P_ALPHA_AXIS]->setPropertyAppearance(BasicAxisItem::P_TITLE, PropertyAttribute::HIDDEN);
    getSubItems()[P_ALPHA_AXIS]->setRegisteredProperty(BasicAxisItem::P_MIN, 0.0);
    getSubItems()[P_ALPHA_AXIS]->setRegisteredProperty(BasicAxisItem::P_MAX, 2.0);

    registerGroupProperty(P_RESOLUTION_FUNCTION, Constants::ResolutionFunctionGroup);
    setGroupProperty(P_RESOLUTION_FUNCTION, Constants::ResolutionFunctionNoneType);
}



