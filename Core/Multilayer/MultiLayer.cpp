// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/MultiLayer.cpp
//! @brief     Implements class MultiLayer.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "MultiLayer.h"
#include "BornAgainNamespace.h"
#include "Layer.h"
#include "LayerInterface.h"
#include "Materials.h"
#include "MessageService.h"
#include "MultiLayerDWBASimulation.h"

using namespace BornAgain;

MultiLayer::MultiLayer() : m_crossCorrLength(0)
{
    setName(MultiLayerType);
    init_parameters();
}

MultiLayer::~MultiLayer()
{
    clear();
}

void MultiLayer::accept(ISampleVisitor *visitor) const
{
    visitor->visit(this);
}

std::string MultiLayer::to_str(int indent) const
{
    return std::string(80, '-') + "\n" + ISample::to_str(indent);
}

void MultiLayer::init_parameters()
{
    clearParameterPool();
    registerParameter(CrossCorrelationLength, &m_crossCorrLength);
}

void MultiLayer::clear()
{
    for(size_t i=0; i<m_layers.size(); i++) delete m_layers[i];
    m_layers.clear();

    for(size_t i=0; i<m_interfaces.size(); i++) delete m_interfaces[i];
    m_interfaces.clear();

    m_layers_z.clear();

    clearParameterPool();
}

MultiLayer *MultiLayer::clone() const
{
    MultiLayer *newMultiLayer = new MultiLayer();

    newMultiLayer->m_layers_z = m_layers_z;

    std::vector<Layer *> layer_buffer;
    for(size_t i=0; i<m_layers.size(); i++) {
        layer_buffer.push_back(m_layers[i]->clone() );
    }

    for(size_t i=0; i<m_interfaces.size(); i++) {
        const Layer *topLayer = layer_buffer[i];
        const Layer *bottomLayer = layer_buffer[i+1];

        LayerInterface *newInterface(0);
        if(m_interfaces[i]->getRoughness()) {
            newInterface = LayerInterface::createRoughInterface(topLayer,
                    bottomLayer, *m_interfaces[i]->getRoughness() );
        } else {
            newInterface = LayerInterface::createSmoothInterface(topLayer,
                    bottomLayer );
        }
        newMultiLayer->addAndRegisterLayer( layer_buffer[i] );
        newMultiLayer->addAndRegisterInterface( newInterface );
    }
    if(layer_buffer.size()) newMultiLayer->addAndRegisterLayer( layer_buffer.back() );

    newMultiLayer->m_crossCorrLength = m_crossCorrLength;

    newMultiLayer->init_parameters();

    return newMultiLayer;
}

MultiLayer* MultiLayer::cloneInvertB() const
{
    MultiLayer *newMultiLayer = new MultiLayer();

    newMultiLayer->m_layers_z = m_layers_z;

    std::vector<Layer *> layer_buffer;
    for(size_t i=0; i<m_layers.size(); i++)
        layer_buffer.push_back(m_layers[i]->cloneInvertB());

    for(size_t i=0; i<m_interfaces.size(); i++) {
        const Layer *topLayer = layer_buffer[i];
        const Layer *bottomLayer = layer_buffer[i+1];

        LayerInterface *newInterface(0);
        if(m_interfaces[i]->getRoughness()) {
            newInterface = LayerInterface::createRoughInterface(
                topLayer, bottomLayer, *m_interfaces[i]->getRoughness());
        } else {
            newInterface = LayerInterface::createSmoothInterface(topLayer, bottomLayer );
        }
        newMultiLayer->addAndRegisterLayer( layer_buffer[i] );
        newMultiLayer->addAndRegisterInterface( newInterface );
    }
    if(layer_buffer.size())
        newMultiLayer->addAndRegisterLayer( layer_buffer.back() );

    newMultiLayer->m_crossCorrLength = m_crossCorrLength;

    newMultiLayer->init_parameters();

    return newMultiLayer;
}

//! Returns pointer to the top interface of the layer.
//! nInterfaces = nLayers-1, first layer in multilayer doesn't have interface.
const LayerInterface *MultiLayer::getLayerTopInterface(size_t i_layer) const
{
    return i_layer>0 ? m_interfaces[ check_interface_index(i_layer-1) ] : 0;
}

//! Returns pointer to the bottom interface of the layer.
const LayerInterface *MultiLayer::getLayerBottomInterface(size_t i_layer) const
{
    return i_layer<m_interfaces.size() ? m_interfaces[ check_interface_index(i_layer) ] : 0;
}

//! Adds layer with top roughness

void MultiLayer::addLayerWithTopRoughness(const Layer& layer, const LayerRoughness& roughness)
{
    Layer *p_new_layer = layer.clone();
    if (getNumberOfLayers())
    {
        const Layer *p_last_layer = m_layers.back();
        LayerInterface *interface(0);
        if(roughness.getSigma() != 0.0) {
            interface = LayerInterface::createRoughInterface(
                p_last_layer, p_new_layer, roughness);
        } else {
            interface = LayerInterface::createSmoothInterface(
                p_last_layer, p_new_layer);
        }
        addAndRegisterInterface(interface);
        addAndRegisterLayer(p_new_layer);
        m_layers_z.push_back(m_layers_z.back() - layer.getThickness() );
        return;
    } else {
        if(p_new_layer->getThickness() != 0.0) {
            msglog(MSG::ERROR) << "MultiLayer::addLayer() -> Attempt to add top layer with "
                << "thickness defined. The layer is semi-infinite. Thickness will be ignored.";
            p_new_layer->setThickness(0.0);
        }
    }
    addAndRegisterLayer(p_new_layer);
    m_layers_z.push_back(0.0);
}

//! Adds layer with default (zero) roughness

void MultiLayer::addLayer(const Layer& layer)
{
    LayerRoughness zero_roughness;
    addLayerWithTopRoughness(layer, zero_roughness);
}


//! Fourier transform of the correlation function of roughnesses between the interfaces
//! j,k - indexes of layers in multilayer whose bottom interfaces we are considering
double MultiLayer::getCrossCorrSpectralFun(const kvector_t kvec, size_t j, size_t k) const
{
    if(m_crossCorrLength == 0)
        return 0.0;
    double z_j = getLayerBottomZ(j);
    double z_k = getLayerBottomZ(k);
    const LayerRoughness *rough_j = getLayerBottomInterface(j)->getRoughness();
    const LayerRoughness *rough_k = getLayerBottomInterface(k)->getRoughness();
    if( !rough_j || !rough_k )
        return 0.0;
    double sigma_j = rough_j->getSigma();
    double sigma_k = rough_k->getSigma();
    if(sigma_j == 0 || sigma_k == 0)
        return 0.0;
    double corr = 0.5*( (sigma_k/sigma_j)*rough_j->getSpectralFun(kvec) +
                        (sigma_j/sigma_k)*rough_k->getSpectralFun(kvec) ) *
        std::exp( -1*std::abs(z_j-z_k)/m_crossCorrLength );
    return corr;
}

void MultiLayer::setLayerThickness(size_t i_layer, double thickness)
{
    if (thickness < 0.)
        throw Exceptions::DomainErrorException("Layer thickness cannot be negative");

    m_layers[ check_layer_index(i_layer) ]->setThickness(thickness);
    // recalculating z-coordinates of layers
    m_layers_z.clear();
    m_layers_z.push_back(0.0);
    for(size_t il=1; il<getNumberOfLayers(); il++){
        m_layers_z.push_back(
            m_layers_z.back() -
            m_layers[ check_layer_index(il) ]->getThickness() );
    }
}

DWBASimulation* MultiLayer::createDWBASimulation() const
{
    return new MultiLayerDWBASimulation(this);
}

int MultiLayer::getIndexOfLayer(const Layer *layer) const
{
    for (size_t i=0; i<getNumberOfLayers(); ++i) {
        if(layer == m_layers[i]) return i;
    }
    return -1;
}

void MultiLayer::print(std::ostream& ostr) const
{
    ostr << "MultiLayer:" << getName() << "<" << this << "> : {\n";
    for(size_t i=0; i<getNumberOfLayers(); i++) {
        ostr << " layer " << std::left << std::setw(2) << i << " { "
             << *getLayer(i) << " }\n";
        const LayerInterface *interface = getLayerBottomInterface(i);
        if(interface) {
            ostr << " int.face {" << *interface << " }\n";
        } else {
            ostr << " int.face: NONE" << "\n";
        }
    }
    ostr << "}";
}

void MultiLayer::addAndRegisterLayer(Layer *child)
{
    m_layers.push_back(child);
    setNLayersInLayers();
    registerChild(child);
}

void MultiLayer::addAndRegisterInterface(LayerInterface *child)
{
    m_interfaces.push_back(child);
    registerChild(child);
}

void MultiLayer::setNLayersInLayers() const
{
    size_t n_layers = getNumberOfLayers();
    for (size_t i=0; i<getNumberOfLayers(); ++i) {
        m_layers[i]->setNumberOfLayers(n_layers);
    }
}

size_t MultiLayer::check_layer_index(size_t i_layer) const
{
    if( i_layer >= m_layers.size() )
        throw Exceptions::OutOfBoundsException("Layer index is out of bounds");
    return i_layer;
}

size_t MultiLayer::check_interface_index(size_t i_interface) const
{
    if( i_interface >= m_interfaces.size() )
        throw Exceptions::OutOfBoundsException("Interface index is out of bounds");
    return i_interface;
}

bool MultiLayer::requiresMatrixRTCoefficients() const
{
    for (auto layer: m_layers) {
        if (!(layer->getMaterial()->isScalarMaterial()))
            return true;
    }
    return false;
}

size_t MultiLayer::zToLayerIndex(double z_value)
{
    if(z_value < m_layers_z.back()) return m_layers_z.size()-1;
    std::vector<double>::reverse_iterator top_limit =
        std::upper_bound(m_layers_z.rbegin(), m_layers_z.rend(), z_value);
    size_t nbin = m_layers_z.rend() - top_limit;
    return nbin;
}

double MultiLayer::getLayerBottomZ(size_t i_layer) const
{
    return m_layers_z[ check_layer_index(i_layer) ];
}

double MultiLayer::getLayerThickness(size_t i_layer) const
{
    return m_layers[ check_layer_index(i_layer) ]->getThickness();
}

void MultiLayer::setCrossCorrLength(double crossCorrLength)
{
    if(crossCorrLength<0.0)
        throw Exceptions::LogicErrorException("Attempt to set crossCorrLength to negative value");
    m_crossCorrLength = crossCorrLength;
}
