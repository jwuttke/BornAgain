// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/MaterialEditor/MaterialProperty.h
//! @brief     Defines class MaterialProperty
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef MATERIALPROPERTY_H
#define MATERIALPROPERTY_H

#include <QColor>
#include <QPixmap>
#include <QMetaType>
#include <QString>
#include <QVariant>

#include "WinDllMacros.h"

//! The MaterialProperty class defines unique identifier to help LayerItem, ParticleItem etc
//! to access materials from MaterialEditor;
class BA_CORE_API_ MaterialProperty
{
public:
    explicit MaterialProperty(const QString &identifier=QString())
        : m_identifier(identifier){}

    QString getIdentifier() const {
        return m_identifier;
    }

    QVariant getVariant() const
    {
        QVariant variant;
        variant.setValue(*this);
        return variant;
    }

    QString getName() const;
    QColor getColor() const;
    QPixmap getPixmap() const;

    bool isDefined() const;

private:
    QString m_identifier;
};

Q_DECLARE_METATYPE(MaterialProperty)

#endif // MATERIALPROPERTY_H
