// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/Ripple2Builder.cpp
//! @brief     Implement class Ripple2Builder.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "Ripple2Builder.h"
#include "MultiLayer.h"
#include "ParticleLayout.h"
#include "Materials.h"
#include "FormFactorRipple2.h"
#include "Units.h"
#include "InterferenceFunction1DParaCrystal.h"

Ripple2Builder::Ripple2Builder()
    : m_w(20.0*Units::nanometer)
    , m_h(4.0*Units::nanometer)
    , m_l(100.0*Units::nanometer)
    , m_d(0.0*Units::nanometer)
    , m_interf_distance(20.0*Units::nanometer)
    , m_interf_width(4.0*Units::nanometer)
{
    init_parameters();
}


void Ripple2Builder::init_parameters()
{
    clearParameterPool();
    registerParameter("width", &m_w);
    registerParameter("height", &m_h);
    registerParameter("length", &m_l);
    registerParameter("asymetry", &m_d);
    registerParameter("interf_distance", &m_interf_distance);
    registerParameter("interf_width", &m_interf_width);
}


ISample *Ripple2Builder::buildSample() const
{
    MultiLayer *p_multi_layer = new MultiLayer();

    HomogeneousMaterial air_material("Air", 0.0, 0.0);
    HomogeneousMaterial substrate_material("Substrate", 6e-6, 2e-8);
    HomogeneousMaterial particle_material("Particle", 6e-4, 2e-8);

    Layer air_layer(air_material);
    FormFactorRipple2 ff_ripple2(m_l, m_w, m_h, m_d);
    Particle ripple(particle_material, ff_ripple2 );

    ParticleLayout particle_layout;
	particle_layout.addParticle(ripple,0.0,1.0);
    InterferenceFunction1DParaCrystal *p_interference_function =
            new InterferenceFunction1DParaCrystal(m_interf_distance,
                    1e7*Units::nanometer); // peak_distance, corr_length
    FTDistribution1DGauss pdf(m_interf_width);
    p_interference_function->setProbabilityDistribution(pdf);
    particle_layout.addInterferenceFunction(p_interference_function);

    air_layer.addLayout(particle_layout);

    p_multi_layer->addLayer(air_layer);

    Layer substrate_layer(substrate_material);
    p_multi_layer->addLayer(substrate_layer);

    return p_multi_layer;
}

