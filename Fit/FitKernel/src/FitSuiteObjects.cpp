// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FitKernel/src/FitSuiteObjects.cpp
//! @brief     Implements class FitSuiteObjects.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FitSuiteObjects.h"
#include "FitObject.h"
#include "ChiSquaredModule.h"
#include <sstream>

FitSuiteObjects::FitSuiteObjects()
  : m_total_weight(0)
   ,m_nfree_parameters(0)
  , m_chi_squared_value(0)
  , m_chi2_module(new ChiSquaredModule())
{
    setName("FitSuiteObjects");
    init_parameters();
}

FitSuiteObjects::~FitSuiteObjects()
{

}

void FitSuiteObjects::add(const GISASSimulation& simulation, const OutputData<double >& real_data,
                          double weight)
{
    m_total_weight += weight;
    m_fit_objects.push_back(new FitObject(simulation, real_data, weight));
}

size_t FitSuiteObjects::getNumberOfFitObjects() const
{
    return m_fit_objects.size();
}

//! Returns total number of data points
size_t FitSuiteObjects::getSizeOfDataSet() const
{
    size_t result(0);
    for(FitObjects_t::const_iterator it =
            m_fit_objects.begin(); it!= m_fit_objects.end(); ++it) {
        result += (*it)->getSizeOfData();
    }
    return result;
}

void FitSuiteObjects::setChiSquaredModule(const IChiSquaredModule &chi2_module)
{
    m_chi2_module.reset(chi2_module.clone());
}

const OutputData<double> *FitSuiteObjects::getRealData(size_t i_item) const
{
    return m_fit_objects[check_index(i_item)]->getRealData();
}

const OutputData<double> *FitSuiteObjects::getSimulationData(size_t i_item) const
{
    return m_fit_objects[check_index(i_item)]->getSimulationData();
}

OutputData<double> *FitSuiteObjects::getChiSquaredMap(size_t i_item) const
{
    check_index(i_item);
    size_t istart(0);
    for(size_t i=0; i<i_item; ++i) {
        std::cout << "FitSuiteObjects::getChiSquaredMap() -> FIXME HERE" << std::endl;
        assert(0);
        istart += m_fit_objects[i]->getSizeOfData();
    }
    std::vector<FitElement>::const_iterator start = m_fit_elements.begin() + istart;
    std::vector<FitElement>::const_iterator end = start + m_fit_objects[i_item]->getSizeOfData();
    return m_fit_objects[check_index(i_item)]->getChiSquaredMap(start, end);
}

//! loop through all defined simulations and run them
void FitSuiteObjects::runSimulations()
{
    if(getSizeOfDataSet() == 0) {
        std::ostringstream message;
        message << "FitSuiteObjects::runSimulations() -> Error. Zero size of dataset.";
        throw LogicErrorException(message.str());
    }

    m_fit_elements.clear();
    m_fit_elements.reserve(getSizeOfDataSet());

    for(FitObjects_t::iterator it =
            m_fit_objects.begin(); it!= m_fit_objects.end(); ++it) {
        (*it)->prepareFitElements(m_fit_elements, (*it)->getWeight()/m_total_weight);
    }

    if(m_fit_elements.size() != getSizeOfDataSet()) {
        std::ostringstream message;
        message << "FitSuiteObjects::runSimulations() -> Error. Dataset size mismatch. "
                << " m_fit_elements.size():" << m_fit_elements.size()
                << " getSizeOfDataset():" << getSizeOfDataSet() << std::endl;
        throw LogicErrorException(message.str());
    }

    m_chi_squared_value = calculateChiSquaredValue();
}

double FitSuiteObjects::getChiSquaredValue() const
{
    return m_chi_squared_value;
}

double FitSuiteObjects::getResidualValue(size_t global_index)
{
    if(global_index >= m_fit_elements.size()) {
        throw LogicErrorException("FitSuiteObjects::getResidualValue() -> Error. "
                                  "Index exceeds size of dataset.");
    }
    return m_fit_elements[global_index].getResidual();
}

//! Adds parameters from local pool to external pool
std::string FitSuiteObjects::addParametersToExternalPool(
    std::string path, ParameterPool* external_pool, int copy_number) const
{
    (void)copy_number;
    // add own parameters
    // top object in our chain, and its without parameters, lets not include its name in path
    std::string new_path
        = IParameterized::addParametersToExternalPool(path, external_pool, copy_number);
    //std::string new_path = path;

    int ncopy(0);
    // if we have only one object, lets get rid from copy number
    if(m_fit_objects.size()==1) ncopy=-1;
    for(FitObjects_t::const_iterator it =
            m_fit_objects.begin(); it!= m_fit_objects.end(); ++it, ++ncopy) {
        (*it)->addParametersToExternalPool(new_path, external_pool, ncopy);
    }

    if(m_chi2_module) {
        const IIntensityNormalizer* data_normalizer =
            m_chi2_module->getIntensityNormalizer();
        if(data_normalizer)
            data_normalizer->addParametersToExternalPool(
                new_path, external_pool, -1);
    }

    return new_path;
}

void FitSuiteObjects::setNfreeParameters(int nfree_parameters)
{
    m_nfree_parameters = nfree_parameters;
}

void FitSuiteObjects::clear()
{
    m_fit_objects.clear();
    m_fit_elements.clear();
}

void FitSuiteObjects::init_parameters()
{

}

double FitSuiteObjects::calculateChiSquaredValue()
{
    m_chi2_module->processFitElements(m_fit_elements.begin(), m_fit_elements.end());

    double result(0);
    for (std::vector<FitElement>::iterator it = m_fit_elements.begin(); it != m_fit_elements.end();
         ++it) {
        result += it->getSquaredDifference();
    }

    int fnorm = m_fit_elements.size() - m_nfree_parameters;
    if (fnorm <= 0) {
        throw LogicErrorException("FitSuiteObjects::calculateChiSquaredValue() -> Error. "
                                  "Normalization is 0");
    }

    return result / fnorm;
}

size_t FitSuiteObjects::check_index(size_t index) const
{
    return index < m_fit_objects.size() ? index :
                throw OutOfBoundsException("FitSuiteKit::check() -> Index outside of range");
}



