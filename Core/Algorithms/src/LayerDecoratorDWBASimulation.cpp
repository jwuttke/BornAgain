#include "LayerDecoratorDWBASimulation.h"
#include "LayerDecorator.h"
#include "DWBAFormFactorConstZ.h"

LayerDecoratorDWBASimulation::LayerDecoratorDWBASimulation(
        const LayerDecorator *p_layer_decorator)
{
    mp_layer_decorator = p_layer_decorator->clone();
}

LayerDecoratorDWBASimulation::~LayerDecoratorDWBASimulation()
{
    delete mp_layer_decorator;
}

void LayerDecoratorDWBASimulation::run()
{
    // Currently, this is the decoupling approximation
    m_dwba_intensity.resetIndex();
    m_dwba_intensity.setAllTo(0.0);
    m_dwba_amplitude.resetIndex();
    m_dwba_amplitude.setAllTo(complex_t(0.0, 0.0));
    double lambda = 2.0*M_PI/m_ki.mag();
    complex_t k_iz = -mp_kz_function->evaluate(-m_alpha_i);
    const NanoParticleDecoration *p_decoration = mp_layer_decorator->getDecoration();
    complex_t n_layer = mp_layer_decorator->getRefractiveIndex();
    size_t number_of_particles = p_decoration->getNumberOfParticles();
    for (size_t particle_index=0; particle_index<number_of_particles; ++particle_index) {
        NanoParticle *p_particle = p_decoration->getNanoParticle(particle_index);
        double depth = p_decoration->getDepthOfNanoParticle(particle_index);
        double m_abundance_fraction = p_decoration->getAbundanceFractionOfNanoParticle(particle_index);
        complex_t n_decoration = p_particle->getRefractiveIndex();
        complex_t scattering_length_density = (n_layer*n_layer - n_decoration*n_decoration)*M_PI/lambda/lambda;
        double normalizing_factor = m_abundance_fraction*std::norm(scattering_length_density);
        DWBAFormFactorConstZ dwba_z(p_particle->getFormFactor()->clone(), depth);
        dwba_z.setReflectionFunction(mp_R_function);
        dwba_z.setTransmissionFunction(mp_T_function);
        while (m_dwba_intensity.hasNext() && m_dwba_amplitude.hasNext())
        {
            double phi_f = m_dwba_intensity.getCurrentValueOfAxis<double>("phi_f");
            double alpha_f = m_dwba_intensity.getCurrentValueOfAxis<double>("alpha_f");
            kvector_t k_f;
            complex_t k_fz = mp_kz_function->evaluate(alpha_f);
            k_f.setLambdaAlphaPhi(lambda, alpha_f, phi_f);
            complex_t ff = scattering_length_density*dwba_z.evaluateForComplexkz(m_ki, k_f, k_iz, k_fz);
            m_dwba_intensity.next() += m_abundance_fraction*std::norm(ff);
            m_dwba_amplitude.next() += m_abundance_fraction*ff;
        }
        m_dwba_intensity.resetIndex();
        m_dwba_amplitude.resetIndex();
    }
    if (number_of_particles!=0) {
        const IInterferenceFunction *p_interference_function = p_decoration->getInterferenceFunction();
        while (m_dwba_intensity.hasNext())
        {
            double phi_f = m_dwba_intensity.getCurrentValueOfAxis<double>("phi_f");
            double alpha_f = m_dwba_intensity.getCurrentValueOfAxis<double>("alpha_f");
            kvector_t k_f;
            k_f.setLambdaAlphaPhi(lambda, alpha_f, phi_f);
            complex_t mean_amplitude = m_dwba_amplitude.next();
            double amplitude_term = std::norm(mean_amplitude)*(p_interference_function->evaluate(m_ki-k_f) - 1.0);
            m_dwba_intensity.next() += amplitude_term;
        }
    }
}
