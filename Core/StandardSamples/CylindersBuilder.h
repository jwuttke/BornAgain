// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/CylindersBuilder.h
//! @brief     Defines classes of CylindersBuilder family.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef CYLINDERSBUILDER_H
#define CYLINDERSBUILDER_H


#include "ISampleBuilder.h"

//! @class CylindersInBABuilder
//! @ingroup standard_samples
//! @brief Builds sample: cylinder formfactor in DWBA (IsGISAXS example #3, part I)

class BA_CORE_API_ CylindersInDWBABuilder : public ISampleBuilder
{
public:
    CylindersInDWBABuilder();
    ISample *buildSample() const;

protected:
    void init_parameters();

private:
    double m_height;
    double m_radius;
};


//! @class CylindersInBABuilder
//! @ingroup standard_samples
//! @brief Builds sample: cylinder formfactor in BA (IsGISAXS example #3, part II)

class BA_CORE_API_ CylindersInBABuilder : public ISampleBuilder
{
public:
    CylindersInBABuilder();
    ISample *buildSample() const;

protected:
    void init_parameters();

private:
    double m_height;
    double m_radius;
};


//! @class CylindersWithSizeDistributionBuilder
//! @ingroup standard_samples
//! @brief Builds sample: cylinder formfactor in BA with size distribution
//! (IsGISAXS example #3, part II)

class CylindersWithSizeDistributionBuilder : public ISampleBuilder
{
public:
    CylindersWithSizeDistributionBuilder();
    ISample *buildSample() const;

protected:
    void init_parameters();

private:
    double m_height;
    double m_radius;
};



#endif // CYLINDERSBUILDER_H
