#include "VectorItem.h"

const QString VectorItem::P_X = "X";
const QString VectorItem::P_Y = "Y";
const QString VectorItem::P_Z = "Z";

VectorItem::VectorItem(ParameterizedItem *parent)
    : ParameterizedItem(Constants::VectorType, parent)
{
    setItemName(Constants::VectorType);
    registerProperty(P_X, 0.0);
    registerProperty(P_Y, 0.0);
    registerProperty(P_Z, 0.0);
}

QString VectorItem::getItemLabel() const
{
    return QString("(%1, %2, %3)").arg(getRegisteredProperty(P_X).toDouble())
                                  .arg(getRegisteredProperty(P_Y).toDouble())
                                  .arg(getRegisteredProperty(P_Z).toDouble());
}

