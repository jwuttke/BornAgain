// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/IsGISAXS01Builder.h
//! @brief     Defines class IsGISAXS01Builder.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef MULTIPLELAYOUTBUILDER_H
#define MULTIPLELAYOUTBUILDER_H

#include "ISampleBuilder.h"

//! @class MultipleLayoutBuilder
//! @ingroup standard_samples
//! @brief Builds sample: mixture of cylinders and prisms without interference
//! using multiple particle layouts

class BA_CORE_API_ MultipleLayoutBuilder : public ISampleBuilder
{
public:
    MultipleLayoutBuilder();
    ISample *buildSample() const;

protected:
    void init_parameters();

private:
    double m_cylinder_height;
    double m_cylinder_radius;
    double m_prism_height;
    double m_prism_length;
    double m_cylinder_weight;
};

#endif // MULTIPLELAYOUTBUILDER_H
