// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/src/ParameterPool.cpp
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
#include "Exceptions.h"
#include "Utils.h"
#include "MessageService.h"
#include <boost/algorithm/string/replace.hpp>
#include <iostream>
#include <sstream>

//! Returns a clone with _prefix_ added to every parameter key.

ParameterPool *ParameterPool::cloneWithPrefix(const std::string& prefix) const
{
    ParameterPool *new_pool = new ParameterPool();
    for(parametermap_t::const_iterator it=m_map.begin(); it!= m_map.end(); ++it)
    {
        new_pool->addParameter(prefix+it->first, it->second);
    }
    return new_pool;
}

//! Registers parameter with given name.

void ParameterPool::registerParameter(const std::string& name,
                                      double *parameter_address, const AttLimits &limits)
{
    parameter_t par(parameter_address, limits);
    if( !addParameter(name, par) ) throw RuntimeErrorException(
       "ParameterPool::registerParameter() -> Error! Can't register parameter");
}

//! Low-level routine.

bool ParameterPool::addParameter(const std::string& name, parameter_t par)
{
    parametermap_t::iterator it = m_map.find(name);
    if( it!=m_map.end() ) {
        print(std::cout);
        std::ostringstream os;
        os << "ParameterPool::registerParameter() -> Warning!"
              " Registering parameter with same name '" << name
           << "'. Previous link will be replaced ";
        throw RuntimeErrorException(os.str());
    }
    return m_map.insert(parametermap_t::value_type(name, par ) ).second;
}

//! Copy parameters of given pool to the external pool while adding prefix to
//! local parameter keys

void ParameterPool::copyToExternalPool(const std::string& prefix,
                                       ParameterPool *external_pool) const
{
    for(parametermap_t::const_iterator it=m_map.begin(); it!= m_map.end(); ++it)
    {
        external_pool->addParameter(prefix+it->first, it->second);
    }
}

//! Returns parameter with given name.

ParameterPool::parameter_t ParameterPool::getParameter(
        const std::string& name) const
{
    parametermap_t::const_iterator it = m_map.find(name);
    if( it!=m_map.end() ) {
        return (*it).second;
    } else {
        throw LogicErrorException("ParameterPool::getParameter() -> Warning."
                                  " No parameter with name '"+name+"'");
    }
}

//! Returns vector of parameters which fit pattern.

std::vector<ParameterPool::parameter_t> ParameterPool::getMatchedParameters(
        const std::string& wildcards) const
{
    std::vector<ParameterPool::parameter_t > selected_parameters;
    // loop over all parameters in the pool
    for(parametermap_t::const_iterator it=m_map.begin(); it!= m_map.end(); ++it) {
        // (*it).first - parameter key, (*it).second - parameter itself
        // parameters whose key match pattern is added to the FitMultiParameter
        // container
        if( Utils::String::MatchPattern( (*it).first, wildcards ) ) {
            selected_parameters.push_back((*it).second);
        }
    }
    if( selected_parameters.empty() ) {
        report_find_matched_parameters_error(wildcards);
    }
    return selected_parameters;
}

//! Sets parameter value.

bool ParameterPool::setParameterValue(const std::string& name, double value)
{
    parameter_t x = getParameter(name);
    if( x.isNull() ) {
        throw LogicErrorException("ParameterPool::setParameterValue() ->"
                                  " Error! Unitialized parameter '"+name+"'.");
    }

    if(!x.setValue(value)) report_set_value_error(name, value);

    return true;
}

//! Sets parameter value.

int ParameterPool::setMatchedParametersValue(const std::string& wildcards,
                                             double value)
{
    int npars(0);
    for(parametermap_t::iterator it=m_map.begin(); it!= m_map.end(); ++it) {
        if( Utils::String::MatchPattern( (*it).first, wildcards ) ) {
            bool success = (*it).second.setValue(value);
            if(!success) {
                report_set_value_error((*it).first, value);
            } else {
                npars++;
            }
        }
    }
    if(npars == 0) {
        report_find_matched_parameters_error(wildcards);
    }
    return npars;
}

std::vector<std::string> ParameterPool::getParameterNames() const
{
    std::vector<std::string> result;
    for (parametermap_t::const_iterator it=m_map.begin(); it!= m_map.end(); ++it) {
        result.push_back(it->first);
    }
    return result;
}

//! Prints content on the screen.

void ParameterPool::print(std::ostream& ostr) const
{
    const size_t number_of_pars_in_line(12);
    if( m_map.size() ) {
        // printing in one line
        if(m_map.size() < number_of_pars_in_line) {
            ostr << "POOL_" << m_map.size();
            ostr << "(";
            for(parametermap_t::const_iterator it=m_map.begin();
                it!= m_map.end(); ++it) {
                ostr << "'" << (*it).first << "'" << ":"
                     << it->second.getValue() << " " ;
            }
            ostr << ")";
        // printing in several lines
        } else {
            for(parametermap_t::const_iterator it=m_map.begin();
                it!= m_map.end(); ++it) {
                ostr << "'" << (*it).first << "'" << ":"
                     << it->second.getValue() << std::endl;
            }
        }
    } else {
        ostr << "POOL_0";
    }
}


std::string ParameterPool::get_error_message(const std::string &criteria) const
{
    std::ostringstream ostr;
    ostr << "No parameters satisfying  criteria '" << criteria
       << "' have been found. Existing keys are:" << std::endl;
    for(parametermap_t::const_iterator it=m_map.begin(); it!= m_map.end(); ++it)
        ostr << "'" << (*it).first << "'" << std::endl;
    return ostr.str();
}

void ParameterPool::report_find_matched_parameters_error(const std::string &pattern) const
{
    std::ostringstream ostr;
    ostr << "ParameterPool::find_matched_parameters_error() -> Error! ";
    ostr << "No parameters matching  pattern '" << pattern
       << "' have been found. Existing keys are:" << std::endl;
    for(parametermap_t::const_iterator it=m_map.begin(); it!= m_map.end(); ++it)
        ostr << "'" << (*it).first << "'" << std::endl;
    throw LogicErrorException(ostr.str());
}

void ParameterPool::report_set_value_error(const std::string &parname, double value) const
{
    std::ostringstream ostr;
    parametermap_t::const_iterator it=m_map.find(parname);
    assert(it!=m_map.end());
    ostr << "ParameterPool::set_value_error() -> Attempt to set value ";
    ostr << value;
    ostr << " for parameter '" << parname << "' failed. Out of bounds?";
    ostr << " Parameter limits " << (*it).second.getAttLimits() << ".\n";
    throw LogicErrorException(ostr.str());
}
