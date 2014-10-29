#ifndef OBJECTVARIANTMANAGER_H
#define OBJECTVARIANTMANAGER_H

//! collection of classes extending QtPropertyBrowser functionality

#include <QtVariantPropertyManager>
#include "ColorProperty.h"
#include "ScientificDoubleProperty.h"
#include "FancyGroupProperty.h"
#include "MaterialProperty.h"
#include "ComboProperty.h"

class QObject;

//! The ObjectVariantManager class provides and manages user defined
//! QVariant based properties.
class BA_CORE_API_ PropertyVariantManager : public QtVariantPropertyManager
{
    Q_OBJECT
public:
    PropertyVariantManager(QObject *parent = 0);

    virtual QVariant value(const QtProperty *property) const;
    virtual int valueType(int propertyType) const;
    virtual bool isPropertyTypeSupported(int propertyType) const;
    static int materialTypeId();
    static int groupTypeId();
    static int colorPropertyTypeId();
    static int scientificDoubleTypeId();
    static int fancyGroupTypeId();
    static int comboPropertyTypeId();

public slots:
    virtual void setValue(QtProperty *property, const QVariant &val);
protected:
    virtual QString valueText(const QtProperty *property) const;
    QIcon valueIcon(const QtProperty *property) const;

    virtual void initializeProperty(QtProperty *property);
    virtual void uninitializeProperty(QtProperty *property);
private:
    QMap<const QtProperty *, MaterialProperty> m_theMaterialValues;
    QMap<const QtProperty *, ColorProperty> m_theColorValues;
    QMap<const QtProperty *, ScientificDoubleProperty> m_theScientificDoubleValues;
    QMap<const QtProperty *, FancyGroupProperty_t> m_theFancyGroupValues;
    QMap<const QtProperty *, ComboProperty> m_theComboValues;
};

#endif // OBJECTVARIANTMANAGER_H
