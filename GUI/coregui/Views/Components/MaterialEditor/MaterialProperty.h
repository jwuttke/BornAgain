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
