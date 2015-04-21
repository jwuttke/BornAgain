// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/src/IsGISAXSMorphologyFileStrategy.cpp
//! @brief     Implements class IsGISAXSMorphologyFileStrategy.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "IsGISAXSMorphologyFileStrategy.h"

#include <algorithm>

IsGISAXSMorphologyFileStrategy::IsGISAXSMorphologyFileStrategy
    (SimulationParameters sim_params)
    : IInterferenceFunctionStrategy(sim_params), m_win_x(0.), m_win_y(0.)
{
}

void IsGISAXSMorphologyFileStrategy::init(
        const SafePointerVector<FormFactorInfo>& form_factor_infos,
        const SafePointerVector<IInterferenceFunction>& ifs)
{
    IInterferenceFunctionStrategy::init(form_factor_infos, ifs);
    if (!checkVectorSizes()) {
        throw ClassInitializationException(
                "Wrong number of formfactors or interference functions "
                "for IsGISAXS morphology file strategy.");
    }
    initPositions();
}

void IsGISAXSMorphologyFileStrategy::initPositions()
{
    m_x_positions.clear();
    m_y_positions.clear();
    for (SafePointerVector<FormFactorInfo>::const_iterator it = m_ff_infos.begin();
            it != m_ff_infos.end(); ++it) {
        m_x_positions.push_back((*it)->m_pos_x);
        m_y_positions.push_back((*it)->m_pos_y);
    }
    // init window sizes for Hann function
    double x_min = *std::min_element(m_x_positions.begin(), m_x_positions.end());
    double x_max = *std::max_element(m_x_positions.begin(), m_x_positions.end());
    double y_min = *std::min_element(m_y_positions.begin(), m_y_positions.end());
    double y_max = *std::max_element(m_y_positions.begin(), m_y_positions.end());
    m_win_x = x_max - x_min;
    m_win_y = y_max - y_min;
    if (m_win_x <= 0. || m_win_y <= 0.) {
        throw Exceptions::ClassInitializationException(
            "IsGISAXSMorphologyFileStrategy::initPosition -> "
            "Hann-function window sizes should be strictly positive");
    }
}

double IsGISAXSMorphologyFileStrategy::evaluateForList(const cvector_t& k_i,
     const Bin1DCVector& k_f_bin, const std::vector<complex_t> &ff_list) const
{
    cvector_t q = k_i - k_f_bin.getMidPoint();
    complex_t mean_ff = complex_t(0., 0.);

    // calculate form factors
    for (size_t i=0; i<m_ff_infos.size(); ++i) {
        mean_ff += m_ff_infos[i]->m_abundance * ff_list[i];
    }

    // coherent part
    complex_t coherent_amplitude = complex_t(0., 0.);
    for (size_t i=0; i<m_ff_infos.size(); ++i) {
        double fraction = m_ff_infos[i]->m_abundance;
        double hann_value = hannFunction(m_x_positions[i], m_y_positions[i]);
        coherent_amplitude += fraction * ff_list[i] * hann_value;
    }
    double coherent_intensity = std::norm(coherent_amplitude);

    // diffuse part
    double diffuse_intensity = 0.;
    for (size_t i=0; i<m_ff_infos.size(); ++i) {
        diffuse_intensity += m_ff_infos[i]->m_abundance*std::norm(ff_list[i]);
        for (size_t j=i+1; j<m_ff_infos.size(); ++j) {
            diffuse_intensity += m_ff_infos[i]->m_abundance
                    * m_ff_infos[j]->m_abundance *
                    2.0*(ff_list[i]*std::conj(ff_list[j])).real();
        }
    }
//    // diffuse part from IsGISAXS --> seems to be wrong (contains only one probability in cross-products and lacks the factor 2)
//    double diffuse_intensity = 0.;
//    for (size_t i=0; i<m_form_factors.size(); ++i) {
//        for (size_t j=i; j<m_form_factors.size(); ++j) {
//            double x_diff = m_x_positions[i]-m_x_positions[j];
//            double y_diff = m_y_positions[i]-m_y_positions[j];
//            complex_t phase = q.x()*x_diff + q.y()*y_diff;
//            diffuse_intensity += m_fractions[i]*((ff_values[i]-mean_ff)*std::conj(ff_values[j]-mean_ff)*std::exp( complex_t(0., 1.0)*phase )).real();
//        }
//    }
    return coherent_intensity + diffuse_intensity;
}

bool IsGISAXSMorphologyFileStrategy::checkVectorSizes()
{
    size_t n_ffs = m_ff_infos.size();
    size_t n_ifs = m_ifs.size();
    return (n_ffs>0 && n_ifs==1);
}

double IsGISAXSMorphologyFileStrategy::hannFunction(double x, double y) const
{
    double result = (Units::PI*Units::PI/4.0)*std::cos(Units::PI*x/m_win_x)*std::cos(Units::PI*y/m_win_y);
    return result;
}
