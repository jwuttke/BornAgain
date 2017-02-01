// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Parametrization/ParameterPool.h
//! @brief     Defines class ParameterPool.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef PARAMETERPOOL_H
#define PARAMETERPOOL_H

#include "ICloneable.h"
#include <ostream>
#include <string>
#include <vector>

class RealLimits;
class RealParameter;

//! Container with parameters for IParameterized object.
//! @ingroup tools_internal

class BA_CORE_API_ ParameterPool : public ICloneable
{
public:
    ParameterPool();
    virtual ~ParameterPool();

    ParameterPool* clone() const;

    void copyToExternalPool(const std::string& prefix, ParameterPool* external_pool) const;

    void clear();

    //! Returns number of parameters in the pool.
    size_t size() const { return m_params.size(); }

    RealParameter& addParameter(RealParameter* par);

    RealParameter* getParameter(const std::string& name);

    const RealParameter* getParameter(const std::string& name) const;

    //! Returns full vector of parameters.
    const std::vector<RealParameter*> getParameters() const { return m_params; }

    std::vector<RealParameter*> getMatchedParameters(const std::string& wildcards) const;
    RealParameter* getUniqueMatch(const std::string& pattern) const;

    void setParameterValue(const std::string& name, double value);

    int setMatchedParametersValue(const std::string& wildcards, double value);
    void setUniqueMatchValue(const std::string& pattern, double value);

    std::vector<std::string> parameterNames() const;

    friend std::ostream& operator<<(std::ostream& ostr, const ParameterPool& obj) {
        obj.print(ostr); return ostr; }

    void removeParameter(const std::string& name);
private:
    virtual void print(std::ostream& ostr) const;
    void report_find_matched_parameters_error(const std::string& pattern) const;
    void report_set_value_error(const std::string& parname, double value) const;

    std::vector<RealParameter*> m_params;
};

#endif // PARAMETERPOOL_H
