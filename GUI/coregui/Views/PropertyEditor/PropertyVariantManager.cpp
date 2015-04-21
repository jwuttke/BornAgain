// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/PropertyEditor/PropertyVariantManager.cpp
//! @brief     Implements class PropertyVariantManager
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "PropertyVariantManager.h"
#include "DesignerHelper.h"
#include "ParameterizedItem.h"
#include <QDebug>

PropertyVariantManager::PropertyVariantManager(QObject *parent)
    : QtVariantPropertyManager(parent)
{

}


int PropertyVariantManager::materialTypeId()
{
    int result = qMetaTypeId<MaterialProperty>();
    return result;
}

int PropertyVariantManager::colorPropertyTypeId()
{
    int result = qMetaTypeId<ColorProperty>();
    return result;
}

int PropertyVariantManager::scientificDoubleTypeId()
{
    int result = qMetaTypeId<ScientificDoubleProperty>();
    return result;
}

int PropertyVariantManager::fancyGroupTypeId()
{
    int result = qMetaTypeId<FancyGroupProperty_t>();
    return result;
}

int PropertyVariantManager::comboPropertyTypeId()
{
    int result = qMetaTypeId<ComboProperty>();
    return result;
}

bool PropertyVariantManager::isPropertyTypeSupported(int propertyType) const
{
    if (propertyType == materialTypeId())
        return true;
    if (propertyType == colorPropertyTypeId())
        return true;
    if (propertyType == scientificDoubleTypeId())
        return true;
    if (propertyType == fancyGroupTypeId())
        return true;
    if (propertyType == comboPropertyTypeId())
        return true;
    return QtVariantPropertyManager::isPropertyTypeSupported(propertyType);
}


int PropertyVariantManager::valueType(int propertyType) const
{
    if (propertyType == materialTypeId())
        return materialTypeId();
    if (propertyType == colorPropertyTypeId())
        return colorPropertyTypeId();
    if (propertyType == scientificDoubleTypeId())
        return scientificDoubleTypeId();
    if (propertyType == fancyGroupTypeId())
        return fancyGroupTypeId();
    if (propertyType == comboPropertyTypeId())
        return comboPropertyTypeId();
    return QtVariantPropertyManager::valueType(propertyType);
}


QVariant PropertyVariantManager::value(const QtProperty *property) const
{
    if (m_theMaterialValues.contains(property)) {
        QVariant v;
        v.setValue(m_theMaterialValues[property]);
        return v;
    }
    if(m_theColorValues.contains(property)) {
        QVariant v;
        v.setValue(m_theColorValues[property]);
        return v;
    }
    if(m_theScientificDoubleValues.contains(property)) {
        QVariant v;
        v.setValue(m_theScientificDoubleValues[property]);
        return v;
    }
    if(m_theFancyGroupValues.contains(property)) {
        QVariant v;
        v.setValue(m_theFancyGroupValues[property]);
        return v;
    }
    if(m_theComboValues.contains(property)) {
        QVariant v;
        v.setValue(m_theComboValues[property]);
        return v;
    }

    return QtVariantPropertyManager::value(property);
}


QString PropertyVariantManager::valueText(const QtProperty *property) const
{
    if (m_theMaterialValues.contains(property)) {
        return m_theMaterialValues[property].getName();
    }
    if (m_theColorValues.contains(property)) {
        return m_theColorValues[property].getText();
    }
    if (m_theScientificDoubleValues.contains(property)) {
        return m_theScientificDoubleValues[property].getText();
    }
    if (m_theFancyGroupValues.contains(property)) {
        return m_theFancyGroupValues[property]->getValueLabel();
    }
    if (m_theComboValues.contains(property)) {
        return m_theComboValues[property].getValue();
    }
    return QtVariantPropertyManager::valueText(property);
}


QIcon PropertyVariantManager::valueIcon(const QtProperty *property) const
{
    if (m_theMaterialValues.contains(property)) {
        return QIcon(m_theMaterialValues[property].getPixmap());
    }
    if (m_theColorValues.contains(property)) {
        return QIcon(m_theColorValues[property].getPixmap());
    }
    return QtVariantPropertyManager::valueIcon(property);
}


void PropertyVariantManager::setValue(QtProperty *property, const QVariant &val)
{
    qDebug() << "PropertyVariantManager::setValue(QtProperty *property, const QVariant &val)";
    if (m_theMaterialValues.contains(property)) {
        if( val.userType() != materialTypeId() ) return;
        MaterialProperty mat = val.value<MaterialProperty>();
        m_theMaterialValues[property] = mat;
        QVariant v2;
        v2.setValue(mat);
        emit propertyChanged(property);
        emit valueChanged(property, v2);
        return;
    }
    if (m_theColorValues.contains(property)) {
        if( val.userType() != colorPropertyTypeId() ) return;
        ColorProperty mat = val.value<ColorProperty>();
        m_theColorValues[property] = mat;
        QVariant v2;
        v2.setValue(mat);
        emit propertyChanged(property);
        emit valueChanged(property, v2);
        return;
    }
    if (m_theScientificDoubleValues.contains(property)) {
        if( val.userType() != scientificDoubleTypeId() ) return;
        ScientificDoubleProperty double_prop = val.value<ScientificDoubleProperty>();
        m_theScientificDoubleValues[property] = double_prop;
        QVariant v2;
        v2.setValue(double_prop);
        emit propertyChanged(property);
        emit valueChanged(property, v2);
        return;
    }
    if (m_theFancyGroupValues.contains(property)) {
        if( val.userType() != fancyGroupTypeId() ) return;
        FancyGroupProperty_t group_prop = val.value<FancyGroupProperty_t>();
        m_theFancyGroupValues[property] = group_prop;
        QVariant v2;
        v2.setValue(group_prop);
        emit propertyChanged(property);
        emit valueChanged(property, v2);
        return;
    }
    if (m_theComboValues.contains(property)) {
        if( val.userType() != comboPropertyTypeId() ) return;
        ComboProperty comboprop = val.value<ComboProperty>();
        m_theComboValues[property] = comboprop;
        QVariant v2;
        v2.setValue(comboprop);
        emit propertyChanged(property);
        emit valueChanged(property, v2);
        return;
    }

    QtVariantPropertyManager::setValue(property, val);
}


void PropertyVariantManager::initializeProperty(QtProperty *property)
{
    qDebug() << "PropertyVariantManager::initializeProperty(QtProperty *property)";
    if (propertyType(property) == materialTypeId()) {
        MaterialProperty m;
        m_theMaterialValues[property] = m;
    }
    if (propertyType(property) == colorPropertyTypeId()) {
        ColorProperty m;
        m_theColorValues[property] = m;
    }
    if (propertyType(property) == scientificDoubleTypeId()) {
        ScientificDoubleProperty m;
        m_theScientificDoubleValues[property] = m;
    }
    if (propertyType(property) == fancyGroupTypeId()) {
        FancyGroupProperty_t m;
        m_theFancyGroupValues[property] = m;
    }
    if (propertyType(property) == comboPropertyTypeId()) {
        ComboProperty m;
        m_theComboValues[property] = m;
    }

    QtVariantPropertyManager::initializeProperty(property);
}


void PropertyVariantManager::uninitializeProperty(QtProperty *property)
{
    m_theMaterialValues.remove(property);
    m_theColorValues.remove(property);
    m_theScientificDoubleValues.remove(property);
    m_theFancyGroupValues.remove(property);
    m_theComboValues.remove(property);
    QtVariantPropertyManager::uninitializeProperty(property);
}

