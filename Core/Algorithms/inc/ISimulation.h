// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/inc/ISimulation.h
//! @brief     Defines interface class ISimulation.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ISIMULATION_H
#define ISIMULATION_H

#include "ICloneable.h"

//! @class ISimulation
//! @ingroup algorithms_internal
//! @brief Interface class, encapsulating different simulations.

class BA_CORE_API_  ISimulation : public ICloneable
{
public:
    ISimulation() : m_status(Idle) {}
    enum SimulationStatus {Idle, Running, Completed, Failed};

    virtual ~ISimulation() {}
    ISimulation *clone() const
    {
        throw NotImplementedException("ISimulation::clone() -> "
                                      "Error: not implemented exception.");
    }
    virtual void run() {}

    bool isCompleted() const { return m_status == Completed;}

    std::string getRunMessage() const { return m_run_message; }

protected:
    virtual void runProtected() {}
    void setStatus(SimulationStatus status) { m_status = status; }
    void setRunMessage(const std::string &message) { m_run_message = message; }

    SimulationStatus m_status;
    std::string m_run_message;
};

#endif // ISIMULATION_H


