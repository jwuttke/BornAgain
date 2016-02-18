// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/NJobModel.cpp
//! @brief     Implements class NJobModel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FitModel.h"
#include "SampleModel.h"
#include "InstrumentModel.h"
#include "FitParameterItems.h"
#include "ParameterizedItem.h"
#include "SessionModel.h"
#include "ComboProperty.h"
#include <QStringList>


FitModel::FitModel(SampleModel *samples, InstrumentModel *instruments, QObject *parent)
    : SessionModel(SessionXML::FitModelTag, parent)
    , m_sampleModel(samples)
    , m_instrumentModel(instruments)
{

}

FitParameterContainer *FitModel::getFitParameterContainer() {
    return dynamic_cast<FitParameterContainer *>
            (itemForIndex(QModelIndex())->getChildOfType(Constants::FitParameterContainerType));
}

FitSelectionItem *FitModel::getFitSelection() {
    return dynamic_cast<FitSelectionItem *>
            (itemForIndex(QModelIndex())->getChildOfType(Constants::FitSelectionType));
}

InputDataItem *FitModel::getInputData() {
    return dynamic_cast<InputDataItem *>
            (itemForIndex(QModelIndex())->getChildOfType(Constants::InputDataType));
}

QString FitModel::getSelectedSampleName () {
    return getFitSelection()->getRegisteredProperty(FitSelectionItem::P_SAMPLE).toString();
}

QString FitModel::getSelectedInstrumentName(){
    return getFitSelection()->getRegisteredProperty(FitSelectionItem::P_INSTRUMENT).toString();
}

QStringList FitModel::getSampleNames() {
    return retrieveDisplayNames(m_sampleModel, Constants::MultiLayerType);
}

QStringList FitModel::getInstrumentNames() {
    return retrieveDisplayNames(m_instrumentModel, Constants::InstrumentType);
}

QStringList FitModel::retrieveDisplayNames(SessionModel *model, const QString &type) {
    QStringList list;
    for (int i_row = 0; i_row < model->rowCount(QModelIndex()); ++i_row) {
        QModelIndex itemIndex = model->index(i_row, 0, QModelIndex());
        if (ParameterizedItem *item = model->itemForIndex(itemIndex)) {
            if (item->modelType()  == type) {
                list << item->displayName();
            }
        }
    }
    return list;
}

QString FitModel::getSampleItemNameForDisplayName(const QString &displayName) {
    if (auto *item = m_sampleModel->itemForIndex(QModelIndex())->getChildByDisplayName(displayName)) {
        return item->name();
    }
    return "";
}

QString FitModel::getInstrumentItemNameForDisplayName(const QString &displayName) {
    if (auto *item = m_instrumentModel->itemForIndex(QModelIndex())->getChildByDisplayName(displayName)) {
        return item->name();
    }
    return "";
}

ParameterizedItem *FitModel::getSelectedMultiLayerItem() {
    ParameterizedItem *samplesRoot = m_sampleModel->itemForIndex(QModelIndex());
    return samplesRoot->getChildByDisplayName(getSelectedSampleName());
}

ParameterizedItem *FitModel::getSelectedInstrumentItem() {
    ParameterizedItem *instrumentRoot = m_instrumentModel->itemForIndex(QModelIndex());
    return instrumentRoot->getChildByDisplayName(getSelectedInstrumentName());
}

void FitModel::setSelectedSample(const QString &displayName) {
    ParameterizedItem *selection = getFitSelection();
    selection->setRegisteredProperty(FitSelectionItem::P_SAMPLE, displayName);
}

void FitModel::setSelectedInstrument(const QString &displayName) {
    ParameterizedItem *selection = getFitSelection();
    selection->setRegisteredProperty(FitSelectionItem::P_INSTRUMENT, displayName);
}

MinimizerSettingsItem *FitModel::getMinimizerSettings() {
    return dynamic_cast<MinimizerSettingsItem *>
            (itemForIndex(QModelIndex())->getChildOfType(Constants::MinimizerSettingsType));
}

QString FitModel::getMinimizerAlgorithm() {
    if (auto *item = getMinimizerSettings()) {
        return item->getRegisteredProperty(MinimizerSettingsItem::P_ALGO).value<ComboProperty>()
                .getValue();
    }
    return QString();
}

QString FitModel::getInputDataPath() {
    if (auto *item = getInputData()) {
        return item->getRegisteredProperty(InputDataItem::P_PATH).toString();
    }
    return "";
}

void FitModel::setInputDataPath(const QString &path) {
    if (auto *item = getInputData()) {
        item->setRegisteredProperty(InputDataItem::P_PATH, path);
    }
}

void FitModel::dataChangedProxy(const QModelIndex & topLeft, const QModelIndex & bottomRight,
                           const QVector<int> & roles)
{
    emit dataChanged(topLeft, bottomRight, roles);
}
