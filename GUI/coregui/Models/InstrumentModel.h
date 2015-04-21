// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/InstrumentModel.h
//! @brief     Defines class InstrumentModel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef INSTRUMENTMODEL_H
#define INSTRUMENTMODEL_H

#include "SessionModel.h"
#include <QStringList>

class InstrumentItem;

class BA_CORE_API_ InstrumentModel : public SessionModel
{
    Q_OBJECT

public:
    explicit InstrumentModel(QObject *parent = 0);
    ~InstrumentModel(){}

    virtual InstrumentModel *createCopy(ParameterizedItem *parent=0);

    QMap<QString, ParameterizedItem *> getInstrumentMap() const;

    InstrumentItem *getInstrumentItem(const QString &instrument_name = QString());

};




#endif
