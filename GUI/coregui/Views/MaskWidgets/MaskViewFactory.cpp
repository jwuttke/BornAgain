// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/MaskWidgets/MaskViewFactory.cpp
//! @brief     Implements class MaskViewFactory
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/MaskWidgets/MaskViewFactory.h"
#include "GUI/coregui/Views/MaskWidgets/EllipseView.h"
#include "GUI/coregui/utils/GUIHelpers.h"
#include "GUI/coregui/Views/MaskWidgets/IShape2DView.h"
#include "GUI/coregui/Views/MaskWidgets/IntensityDataView.h"
#include "GUI/coregui/Views/MaskWidgets/LineViews.h"
#include "GUI/coregui/Views/MaskWidgets/MaskAllView.h"
#include "GUI/coregui/Views/MaskWidgets/MaskContainerView.h"
#include "GUI/coregui/Views/MaskWidgets/PolygonPointView.h"
#include "GUI/coregui/Views/MaskWidgets/PolygonView.h"
#include "GUI/coregui/Views/MaskWidgets/RectangleView.h"
#include "GUI/coregui/Views/MaskWidgets/RegionOfInterestView.h"
#include "GUI/coregui/Models/SessionItem.h"
#include "GUI/coregui/Models/item_constants.h"

IShape2DView* MaskViewFactory::createMaskView(SessionItem* item, ISceneAdaptor* adaptor)
{
    IShape2DView* result(0);
    QString model_type = item->modelType();

    if (model_type == Constants::MaskContainerType) {
        result = new MaskContainerView();
    }

    else if (model_type == Constants::ProjectionContainerType) {
        result = new MaskContainerView();
    }

    else if (model_type == Constants::RectangleMaskType) {
        result = new RectangleView();
    }

    else if (model_type == Constants::PolygonMaskType) {
        result = new PolygonView();
    }

    else if (model_type == Constants::PolygonPointType) {
        result = new PolygonPointView();
    }

    else if (model_type == Constants::VerticalLineMaskType) {
        result = new VerticalLineView();
    }

    else if (model_type == Constants::HorizontalLineMaskType) {
        result = new HorizontalLineView();
    }

    else if (model_type == Constants::EllipseMaskType) {
        result = new EllipseView();
    }

    else if (model_type == Constants::MaskAllType) {
        result = new MaskAllView();
    }

    else if (model_type == Constants::RegionOfInterestType) {
        result = new RegionOfInterestView();
    }

    else {
        throw GUIHelpers::Error("MaskViewFactory::createSampleView() -> Error! "
                                "Can't create a view for "
                                + model_type);
    }

    result->setParameterizedItem(item);
    result->setSceneAdaptor(adaptor);

    return result;
}
