// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Parametrization/ParameterPool.cpp
//! @brief     Implements standard mix-in ParameterPool.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ParameterPool.h"
#include "AttLimits.h"
#include "RealParameter.h"
#include "Exceptions.h"
#include "StringUtils.h"
#include <algorithm>
#include <cassert>
#include <iostream>
#include <sstream>

//! Constructs an empty parameter pool.
ParameterPool::ParameterPool(const std::string& name, std::function<void()>onChange)
    : m_name(name)
    , m_onChange(onChange)
{
}

ParameterPool::~ParameterPool()
{
    clear();
}

//! Returns a literal clone.
ParameterPool* ParameterPool::clone() const
{
    ParameterPool* new_pool = new ParameterPool(m_name, m_onChange);
    new_pool->m_params = m_params;
    return new_pool;
}


//! Returns a clone with _prefix_ added to every parameter key.

ParameterPool* ParameterPool::cloneWithPrefix(const std::string& prefix) const
{
    ParameterPool* new_pool = new ParameterPool(m_name, m_onChange);
    for (const auto* par: m_params)
        new_pool->addParameter( new RealParameter( prefix + par->getName(), *par ) );
    return new_pool;
}

//! Deletes parameter map.
void ParameterPool::clear()
{
    for(auto* par: m_params)
        delete par;
    m_params.clear();
}

//! Registers parameter with given name.
void ParameterPool::registerParameter(const std::string& name, double* parpointer)
{
    registerParameter(name, parpointer, AttLimits::limitless());
}

//! Registers parameter with given name.

void ParameterPool::registerParameter(
    const std::string& name, double* parameter_address, const AttLimits& limits)
{
    addParameter(new RealParameter(name, this, parameter_address, limits) );
}

//! Low-level routine.

void ParameterPool::addParameter(RealParameter* newPar)
{
    for (const auto* par: m_params )
        if( par->getName()==newPar->getName() )
            throw Exceptions::RuntimeErrorException(
                "BUG in ParameterPool::addParameter(): "
                "Parameter '"+newPar->getName()+"' is already registered");
    m_params.push_back(newPar);
}

//! Copy parameters of given pool to the external pool while adding prefix to
//! local parameter keys

void ParameterPool::copyToExternalPool(
    const std::string& prefix, ParameterPool* external_pool) const
{
    for (auto* par: m_params)
        external_pool->addParameter(new RealParameter(prefix+par->getName(), *par));
}

//! Returns parameter with given name.

const RealParameter* ParameterPool::getParameter(const std::string& name) const
{
    for (const auto* par: m_params )
        if( par->getName()==name )
            return par;
    throw Exceptions::LogicErrorException(
        "ParameterPool::getParameter() -> Warning. No parameter with name '"+name+"'");
}

//! Returns parameter with given name.

RealParameter* ParameterPool::getParameter(const std::string& name)
{
    for (auto* par: m_params )
        if( par->getName()==name )
            return par;
    throw Exceptions::LogicErrorException(
        "ParameterPool::getParameter() -> Warning. No parameter with name '"+name+"'");
}

//! Returns vector of parameters which fit pattern.

std::vector<RealParameter*> ParameterPool::getMatchedParameters(
    const std::string& wildcards) const
{
    std::vector<RealParameter*> selected_parameters;
    // loop over all parameters in the pool
    for (auto* par: m_params)
        if( StringUtils::matchesPattern( par->getName(), wildcards ) )
            selected_parameters.push_back(par);
    if( selected_parameters.empty() )
        report_find_matched_parameters_error(wildcards);
    return selected_parameters;
}

//! Sets parameter value.

void ParameterPool::setParameterValue(const std::string& name, double value)
{
    RealParameter* x = getParameter(name);
    if( x->isNull() )
        throw Exceptions::LogicErrorException(
            "ParameterPool::setParameterValue() -> Error! Unitialized parameter '"+name+"'.");
    try {
        x->setValue(value);
    } catch(Exceptions::RuntimeErrorException) {
        report_set_value_error(name, value);
    }
}

//! Sets parameter value.

int ParameterPool::setMatchedParametersValue(const std::string& wildcards, double value)
{
    int npars(0);
    for (auto* par: m_params) {
        if( StringUtils::matchesPattern( par->getName(), wildcards ) ) {
            try {
                par->setValue(value);
                npars++;
            } catch(Exceptions::RuntimeErrorException) {
                report_set_value_error(par->getName(), value);
            }
        }
    }
    if(npars == 0)
        report_find_matched_parameters_error(wildcards);
    return npars;
}

std::vector<std::string> ParameterPool::getParameterNames() const
{
    std::vector<std::string> result;
    for (const auto* par: m_params)
        result.push_back(par->getName());
    return result;
}

void ParameterPool::print(std::ostream& ostr) const
{
    const size_t number_of_pars_in_line(12);
    if( m_params.size() ) {
        if(m_params.size() < number_of_pars_in_line) { // print in one line
            ostr << "POOL_" << m_params.size();
            ostr << "(";
            for (const auto* par: m_params)
                ostr << "'" << par->getName() << "'" << ":" << par->getValue() << " " ;
            ostr << ")";
        } else { // print in several lines
            for (const auto* par: m_params)
                ostr << "'" << par->getName() << "'" << ":" << par->getValue() << "\n";
        }
    } else {
        ostr << "POOL_0";
    }
}

std::string ParameterPool::get_error_message(const std::string& criteria) const
{
    std::ostringstream ostr;
    ostr << "No parameters satisfying  criteria '" << criteria
       << "' have been found. Existing keys are:\n";
    for (const auto* par: m_params)
        ostr << "'" << par->getName() << "'\n";
    return ostr.str();
}

void ParameterPool::report_find_matched_parameters_error(const std::string& pattern) const
{
    std::ostringstream ostr;
    ostr << "ParameterPool::find_matched_parameters_error() -> Error! ";
    ostr << "No parameters matching  pattern '" << pattern
       << "' have been found. Existing keys are:" << std::endl;
    for (const auto* par: m_params)
        ostr << "'" << par->getName() << "'\n";
    throw Exceptions::LogicErrorException(ostr.str());
}

void ParameterPool::report_set_value_error(const std::string& parname, double value) const
{
    std::ostringstream ostr;
    ostr << "ParameterPool::set_value_error() -> Attempt to set value " << value;
    ostr << " for parameter '" << parname << "' failed. Out of bounds?";
    try {
        ostr << " Parameter limits " << getParameter(parname)->getAttLimits() << ".\n";
    } catch (...) {
        throw Exceptions::LogicErrorException(
            "DOUBLE BUG in ParameterPool: cannot even report the error");
    }
    throw Exceptions::LogicErrorException(ostr.str());
}