// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/FitWidgets/FittingWorker.h
//! @brief     Implements class FittingWorker
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FITTINGWORKER_H
#define FITTINGWORKER_H

#include "WinDllMacros.h"
#include <QObject>
#include <boost/shared_ptr.hpp>

class FitSuite;

class BA_CORE_API_ FittingWorker : public QObject
{
    Q_OBJECT

public:

    FittingWorker(boost::shared_ptr<FitSuite> suite) {m_fitsuite = suite;}

public slots:

    void startFit();

    void interruptFitting();

signals:

    void started();

    void finished();

private:

    boost::shared_ptr<FitSuite> m_fitsuite;

};

#endif
