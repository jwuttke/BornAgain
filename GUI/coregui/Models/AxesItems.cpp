// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/AxesItems.cpp
//! @brief     Implements various axis items
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Models/AxesItems.h"
#include "Core/Binning/FixedBinAxis.h"

const QString BasicAxisItem::P_IS_VISIBLE = "Visibility";
const QString BasicAxisItem::P_NBINS = "Nbins";
const QString BasicAxisItem::P_MIN = "Min [deg]";
const QString BasicAxisItem::P_MAX = "Max [deg]";
const QString BasicAxisItem::P_TITLE = "title";
const QString BasicAxisItem::P_TITLE_IS_VISIBLE = "Title Visibility";

static const int max_detector_pixels = 65536;

BasicAxisItem::BasicAxisItem(const QString& type) : SessionItem(type)
{
    register_basic_properties();
}

std::unique_ptr<IAxis> BasicAxisItem::createAxis(double scale) const
{
    return std::make_unique<FixedBinAxis>(
        getItemValue(P_TITLE).toString().toStdString(), getItemValue(P_NBINS).toInt(),
        getItemValue(P_MIN).toDouble() * scale, getItemValue(P_MAX).toDouble() * scale);
}

BasicAxisItem::~BasicAxisItem() = default;

void BasicAxisItem::register_basic_properties()
{
    addProperty(P_IS_VISIBLE, true)->setVisible(false);
    addProperty(P_NBINS, 100)->setLimits(RealLimits::limited(1, max_detector_pixels));
    addProperty(P_MIN, 0.0)->setDecimals(3);
    getItem(P_MIN)->setLimits(RealLimits::limitless());
    addProperty(P_MAX, -1.0)->setDecimals(3);
    getItem(P_MAX)->setLimits(RealLimits::limitless());
    addProperty(P_TITLE, QString());
    addProperty(P_TITLE_IS_VISIBLE, true)->setVisible(false);
}

// ---------------------------------------------------------------------------------------------- //

const QString AmplitudeAxisItem::P_IS_LOGSCALE = "log10";
const QString AmplitudeAxisItem::P_LOCK_MIN_MAX = "Lock (min, max)";

AmplitudeAxisItem::AmplitudeAxisItem() : BasicAxisItem(Constants::AmplitudeAxisType)
{
    addProperty(P_LOCK_MIN_MAX, false)->setVisible(false);
    addProperty(P_IS_LOGSCALE, true);
    getItem(BasicAxisItem::P_TITLE)->setVisible(false);
    getItem(BasicAxisItem::P_IS_VISIBLE)->setVisible(true);
    setMinMaxEditor(Constants::ScientificEditorType);

    mapper()->setOnPropertyChange([this](const QString& name) {
        if (name == P_IS_LOGSCALE) {
            if (getItemValue(P_IS_LOGSCALE).toBool())
                setMinMaxEditor(Constants::ScientificEditorType);
            else
                setMinMaxEditor(Constants::DefaultEditorType);
        }
    });
}

//! Sets editor for min, max values of axes

void AmplitudeAxisItem::setMinMaxEditor(const QString& editorType)
{
    getItem(BasicAxisItem::P_MIN)->setEditorType(editorType);
    getItem(BasicAxisItem::P_MAX)->setEditorType(editorType);
}
