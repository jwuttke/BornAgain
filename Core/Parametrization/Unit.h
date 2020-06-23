// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Parametrization/Unit.h
//! @brief     Defines class Unit.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef UNIT_H
#define UNIT_H

#include <string>

//! A physical unit.

// TODO: Reconsider whether unit names can be made const.

class Unit
{
public:
    explicit Unit(const std::string& name = "") : m_name{name} {}
    void setUnit(const std::string& name) { m_name = name; }
    const std::string& getName() const { return m_name; }

private:
    std::string m_name;
};

#endif // UNIT_H
