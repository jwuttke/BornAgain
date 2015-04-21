// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      ParameterDistribution.h
//! @brief     Defines class ParameterDistribution.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef PARAMETERDISTRIBUTION_H_
#define PARAMETERDISTRIBUTION_H_

#include "ParameterSample.h"
#include "IParameterized.h"
#include "AttLimits.h"

#include <memory>
#include <string>
#include <vector>

class IDistribution1D;

class BA_CORE_API_ ParameterDistribution : public IParameterized
{
public:
    ParameterDistribution(const std::string &par_name,
                          const IDistribution1D &distribution,
                          size_t nbr_samples, double sigma_factor=0.0,
                          const AttLimits &limits = AttLimits());

    ParameterDistribution(const std::string &par_name,
                          const IDistribution1D &distribution,
                          size_t nbr_samples, double xmin, double xmax);

    ParameterDistribution(const ParameterDistribution &other);
    ~ParameterDistribution();

    //! Overload assignment operator
    ParameterDistribution& operator=(const ParameterDistribution &other);

    ParameterDistribution& linkParameter(std::string par_name);

    //! get the main parameter's name
    std::string getMainParameterName() const {
        return m_name;
    }

    //! get number of samples for this distribution
    size_t getNbrSamples() const {
        return m_nbr_samples;
    }

    //! get the sigma factor
    double getSigmaFactor() const {
        return m_sigma_factor;
    }

    const IDistribution1D *getDistribution() const {
        return mP_distribution.get();
    }

    //! generate list of sampled values with their weight
    std::vector<ParameterSample> generateSamples() const;

    //! get list of linked parameter names
    std::vector<std::string> getLinkedParameterNames() const {
        return m_linked_par_names;
    }

    AttLimits getLimits() const {return m_limits;}

    double getMinValue() const { return m_xmin; }
    double getMaxValue() const { return m_xmax; }

protected:
    //! Registers some class members for later access via parameter pool
    void init_parameters();
private:
    std::string m_name;
    std::auto_ptr<IDistribution1D> mP_distribution;
    size_t m_nbr_samples;
    double m_sigma_factor;
    std::vector<std::string> m_linked_par_names;
    AttLimits m_limits;
    double m_xmin;
    double m_xmax;
};


#endif /* PARAMETERDISTRIBUTION_H_ */
