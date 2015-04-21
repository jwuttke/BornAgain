// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/SampleDesigner/InterferenceFunctionViews.h
//! @brief     Defines classes InterferenceFunctionViews
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef INTERFERENCEFUNCTIONVIEWS_H
#define INTERFERENCEFUNCTIONVIEWS_H


#include "ConnectableView.h"

class BA_CORE_API_ InterferenceFunctionRadialParaCrystalView : public ConnectableView
{
    Q_OBJECT

public:
    enum { TYPE = DesignerHelper::INTERFERENCE_FUNCTION_RADIAL_PARA };

    InterferenceFunctionRadialParaCrystalView(QGraphicsItem *parent = 0);

    int type() const { return TYPE; }
};


class BA_CORE_API_ InterferenceFunction2DParaCrystalView : public ConnectableView
{
    Q_OBJECT

public:
    enum { TYPE = DesignerHelper::INTERFERENCE_FUNCTION_2D_PARA };

    InterferenceFunction2DParaCrystalView(QGraphicsItem *parent = 0);

    int type() const { return TYPE; }
};

class BA_CORE_API_ InterferenceFunction2DLatticeView : public ConnectableView
{
    Q_OBJECT

public:
    enum { TYPE = DesignerHelper::INTERFERENCE_FUNCTION_2D_LATTICE };

    InterferenceFunction2DLatticeView(QGraphicsItem *parent = 0);

    int type() const { return TYPE; }
};

#endif // INTERFERENCEFUNCTIONVIEWS_H
