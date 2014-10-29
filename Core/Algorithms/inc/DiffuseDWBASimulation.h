// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/inc/DiffuseDWBASimulation.h
//! @brief     Defines class DiffuseDWBASimulation.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef DIFFUSEDWBASIMULATION_H_
#define DIFFUSEDWBASIMULATION_H_

#include "LayerDWBASimulation.h"
#include "DiffuseParticleInfo.h"

//! @class DiffuseDWBASimulation
//! @ingroup algorithms_internal
//! @brief Calculation of diffuse scattering in DWBA

class BA_CORE_API_ DiffuseDWBASimulation: public LayerDWBASimulation
{
public:
    DiffuseDWBASimulation(const Layer *p_layer)
        : LayerDWBASimulation(p_layer)
        , m_surface_density(1.0) {}

    virtual ~DiffuseDWBASimulation() {}

    virtual void run();

    size_t getSize() const { return m_np_infos.size(); }

    void addParticleInfo(DiffuseParticleInfo *p_info)
    { m_np_infos.push_back(p_info); }

    void setMaterial(const IMaterial *p_material);

    void setSurfaceDensity(double surface_density)
    { m_surface_density = surface_density; }

    void rescaleAbundances(double factor)
    {
        for (size_t np_index=0; np_index<m_np_infos.size(); ++np_index)
            m_np_infos[np_index]->scaleAbundance(factor);
    }

protected:
    virtual void runProtected();

private:
    double m_surface_density;
    SafePointerVector<DiffuseParticleInfo> m_np_infos;
    struct DiffuseFormFactorTerm {
        DiffuseFormFactorTerm()
            : m_form_factors(), m_probabilities(), m_factor(0.) {}
        ~DiffuseFormFactorTerm()
        {
            for (size_t i=0; i<m_form_factors.size(); ++i)
                delete m_form_factors[i];
        }
        std::vector<IFormFactor*> m_form_factors;
        std::vector<double> m_probabilities;
        double m_factor;
    };
    void initDiffuseFormFactorTerms(
        SafePointerVector<DiffuseFormFactorTerm>& terms,
        size_t nbr_heights, size_t samples_per_particle,
        complex_t wavevector_scattering_factor);
};

#endif /* DIFFUSEDWBASIMULATION_H_ */


