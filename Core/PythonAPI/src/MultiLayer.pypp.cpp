// This file has been generated by Py++.

// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Automatically generated boost::python code for BornAgain Python bindings
//! @brief     Automatically generated boost::python code for BornAgain Python bindings
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Juelich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "Macros.h"
GCC_DIAG_OFF(unused-parameter)
GCC_DIAG_OFF(missing-field-initializers)
#include "boost/python.hpp"
GCC_DIAG_ON(unused-parameter)
GCC_DIAG_ON(missing-field-initializers)
#include "__call_policies.pypp.hpp"
#include "__convenience.pypp.hpp"
#include "PythonCoreList.h"
#include "MultiLayer.pypp.h"

namespace bp = boost::python;

struct MultiLayer_wrapper : MultiLayer, bp::wrapper< MultiLayer > {

    MultiLayer_wrapper( )
    : MultiLayer( )
      , bp::wrapper< MultiLayer >(){
        // null constructor
    m_pyobj = 0;
    }

    virtual ::MultiLayer * clone(  ) const  {
        if( bp::override func_clone = this->get_override( "clone" ) )
            return func_clone(  );
        else{
            return this->MultiLayer::clone(  );
        }
    }
    
    ::MultiLayer * default_clone(  ) const  {
        return MultiLayer::clone( );
    }

    virtual ::MultiLayer * cloneInvertB(  ) const  {
        if( bp::override func_cloneInvertB = this->get_override( "cloneInvertB" ) )
            return func_cloneInvertB(  );
        else{
            return this->MultiLayer::cloneInvertB(  );
        }
    }
    
    ::MultiLayer * default_cloneInvertB(  ) const  {
        return MultiLayer::cloneInvertB( );
    }

    virtual bool areParametersChanged(  ) {
        if( bp::override func_areParametersChanged = this->get_override( "areParametersChanged" ) )
            return func_areParametersChanged(  );
        else{
            return this->IParameterized::areParametersChanged(  );
        }
    }
    
    bool default_areParametersChanged(  ) {
        return IParameterized::areParametersChanged( );
    }

    virtual void clearParameterPool(  ) {
        if( bp::override func_clearParameterPool = this->get_override( "clearParameterPool" ) )
            func_clearParameterPool(  );
        else{
            this->IParameterized::clearParameterPool(  );
        }
    }
    
    void default_clearParameterPool(  ) {
        IParameterized::clearParameterPool( );
    }

    virtual bool containsMagneticMaterial(  ) const  {
        if( bp::override func_containsMagneticMaterial = this->get_override( "containsMagneticMaterial" ) )
            return func_containsMagneticMaterial(  );
        else{
            return this->ISample::containsMagneticMaterial(  );
        }
    }
    
    bool default_containsMagneticMaterial(  ) const  {
        return ISample::containsMagneticMaterial( );
    }

    virtual ::ParameterPool * createParameterTree(  ) const  {
        if( bp::override func_createParameterTree = this->get_override( "createParameterTree" ) )
            return func_createParameterTree(  );
        else{
            return this->IParameterized::createParameterTree(  );
        }
    }
    
    ::ParameterPool * default_createParameterTree(  ) const  {
        return IParameterized::createParameterTree( );
    }

    virtual ::ICompositeSample * getCompositeSample(  ) {
        if( bp::override func_getCompositeSample = this->get_override( "getCompositeSample" ) )
            return func_getCompositeSample(  );
        else{
            return this->ICompositeSample::getCompositeSample(  );
        }
    }
    
    ::ICompositeSample * default_getCompositeSample(  ) {
        return ICompositeSample::getCompositeSample( );
    }

    virtual ::ICompositeSample const * getCompositeSample(  ) const  {
        if( bp::override func_getCompositeSample = this->get_override( "getCompositeSample" ) )
            return func_getCompositeSample(  );
        else{
            return this->ICompositeSample::getCompositeSample(  );
        }
    }
    
    ::ICompositeSample const * default_getCompositeSample(  ) const  {
        return ICompositeSample::getCompositeSample( );
    }

    virtual bool preprocess(  ) {
        if( bp::override func_preprocess = this->get_override( "preprocess" ) )
            return func_preprocess(  );
        else{
            return this->ISample::preprocess(  );
        }
    }
    
    bool default_preprocess(  ) {
        return ISample::preprocess( );
    }

    virtual void printParameters(  ) const  {
        if( bp::override func_printParameters = this->get_override( "printParameters" ) )
            func_printParameters(  );
        else{
            this->IParameterized::printParameters(  );
        }
    }
    
    void default_printParameters(  ) const  {
        IParameterized::printParameters( );
    }

    virtual void printSampleTree(  ) {
        if( bp::override func_printSampleTree = this->get_override( "printSampleTree" ) )
            func_printSampleTree(  );
        else{
            this->ISample::printSampleTree(  );
        }
    }
    
    void default_printSampleTree(  ) {
        ISample::printSampleTree( );
    }

    virtual void registerParameter( ::std::string const & name, double * parpointer ) {
        namespace bpl = boost::python;
        if( bpl::override func_registerParameter = this->get_override( "registerParameter" ) ){
            bpl::object py_result = bpl::call<bpl::object>( func_registerParameter.ptr(), name, parpointer );
        }
        else{
            IParameterized::registerParameter( name, parpointer );
        }
    }
    
    static void default_registerParameter( ::IParameterized & inst, ::std::string const & name, long unsigned int parpointer ){
        if( dynamic_cast< MultiLayer_wrapper * >( boost::addressof( inst ) ) ){
            inst.::IParameterized::registerParameter(name, reinterpret_cast< double * >( parpointer ));
        }
        else{
            inst.registerParameter(name, reinterpret_cast< double * >( parpointer ));
        }
    }

    virtual bool setParameterValue( ::std::string const & name, double value ) {
        if( bp::override func_setParameterValue = this->get_override( "setParameterValue" ) )
            return func_setParameterValue( name, value );
        else{
            return this->IParameterized::setParameterValue( name, value );
        }
    }
    
    bool default_setParameterValue( ::std::string const & name, double value ) {
        return IParameterized::setParameterValue( name, value );
    }

    virtual void setParametersAreChanged(  ) {
        if( bp::override func_setParametersAreChanged = this->get_override( "setParametersAreChanged" ) )
            func_setParametersAreChanged(  );
        else{
            this->IParameterized::setParametersAreChanged(  );
        }
    }
    
    void default_setParametersAreChanged(  ) {
        IParameterized::setParametersAreChanged( );
    }

    virtual ::std::size_t size(  ) const  {
        if( bp::override func_size = this->get_override( "size" ) )
            return func_size(  );
        else{
            return this->ICompositeSample::size(  );
        }
    }
    
    ::std::size_t default_size(  ) const  {
        return ICompositeSample::size( );
    }

    virtual void transferToCPP(  ) {
        
        if( !this->m_pyobj) {
            this->m_pyobj = boost::python::detail::wrapper_base_::get_owner(*this);
            Py_INCREF(this->m_pyobj);
        }
        
        if( bp::override func_transferToCPP = this->get_override( "transferToCPP" ) )
            func_transferToCPP(  );
        else{
            this->ICloneable::transferToCPP(  );
        }
    }
    
    void default_transferToCPP(  ) {
        
        if( !this->m_pyobj) {
            this->m_pyobj = boost::python::detail::wrapper_base_::get_owner(*this);
            Py_INCREF(this->m_pyobj);
        }
        
        ICloneable::transferToCPP( );
    }

    PyObject* m_pyobj;

};

void register_MultiLayer_class(){

    { //::MultiLayer
        typedef bp::class_< MultiLayer_wrapper, bp::bases< ICompositeSample >, std::auto_ptr< MultiLayer_wrapper >, boost::noncopyable > MultiLayer_exposer_t;
        MultiLayer_exposer_t MultiLayer_exposer = MultiLayer_exposer_t( "MultiLayer", bp::init< >() );
        bp::scope MultiLayer_scope( MultiLayer_exposer );
        { //::MultiLayer::addLayer
        
            typedef void ( ::MultiLayer::*addLayer_function_type)( ::Layer const & ) ;
            
            MultiLayer_exposer.def( 
                "addLayer"
                , addLayer_function_type( &::MultiLayer::addLayer )
                , ( bp::arg("p_child") ) );
        
        }
        { //::MultiLayer::addLayerWithTopRoughness
        
            typedef void ( ::MultiLayer::*addLayerWithTopRoughness_function_type)( ::Layer const &,::LayerRoughness const & ) ;
            
            MultiLayer_exposer.def( 
                "addLayerWithTopRoughness"
                , addLayerWithTopRoughness_function_type( &::MultiLayer::addLayerWithTopRoughness )
                , ( bp::arg("layer"), bp::arg("roughness") ) );
        
        }
        { //::MultiLayer::clear
        
            typedef void ( ::MultiLayer::*clear_function_type)(  ) ;
            
            MultiLayer_exposer.def( 
                "clear"
                , clear_function_type( &::MultiLayer::clear ) );
        
        }
        { //::MultiLayer::clone
        
            typedef ::MultiLayer * ( ::MultiLayer::*clone_function_type)(  ) const;
            typedef ::MultiLayer * ( MultiLayer_wrapper::*default_clone_function_type)(  ) const;
            
            MultiLayer_exposer.def( 
                "clone"
                , clone_function_type(&::MultiLayer::clone)
                , default_clone_function_type(&MultiLayer_wrapper::default_clone)
                , bp::return_value_policy< bp::manage_new_object >() );
        
        }
        { //::MultiLayer::cloneInvertB
        
            typedef ::MultiLayer * ( ::MultiLayer::*cloneInvertB_function_type)(  ) const;
            typedef ::MultiLayer * ( MultiLayer_wrapper::*default_cloneInvertB_function_type)(  ) const;
            
            MultiLayer_exposer.def( 
                "cloneInvertB"
                , cloneInvertB_function_type(&::MultiLayer::cloneInvertB)
                , default_cloneInvertB_function_type(&MultiLayer_wrapper::default_cloneInvertB)
                , bp::return_value_policy< bp::reference_existing_object >() );
        
        }
        { //::MultiLayer::getCrossCorrLength
        
            typedef double ( ::MultiLayer::*getCrossCorrLength_function_type)(  ) const;
            
            MultiLayer_exposer.def( 
                "getCrossCorrLength"
                , getCrossCorrLength_function_type( &::MultiLayer::getCrossCorrLength ) );
        
        }
        { //::MultiLayer::getCrossCorrSpectralFun
        
            typedef double ( ::MultiLayer::*getCrossCorrSpectralFun_function_type)( ::kvector_t const &,::std::size_t,::std::size_t ) const;
            
            MultiLayer_exposer.def( 
                "getCrossCorrSpectralFun"
                , getCrossCorrSpectralFun_function_type( &::MultiLayer::getCrossCorrSpectralFun )
                , ( bp::arg("kvec"), bp::arg("j"), bp::arg("k") ) );
        
        }
        { //::MultiLayer::getLayer
        
            typedef ::Layer const * ( ::MultiLayer::*getLayer_function_type)( ::std::size_t ) const;
            
            MultiLayer_exposer.def( 
                "getLayer"
                , getLayer_function_type( &::MultiLayer::getLayer )
                , ( bp::arg("i_layer") )
                , bp::return_value_policy< bp::reference_existing_object >() );
        
        }
        { //::MultiLayer::getLayerBottomInterface
        
            typedef ::LayerInterface const * ( ::MultiLayer::*getLayerBottomInterface_function_type)( ::std::size_t ) const;
            
            MultiLayer_exposer.def( 
                "getLayerBottomInterface"
                , getLayerBottomInterface_function_type( &::MultiLayer::getLayerBottomInterface )
                , ( bp::arg("i_layer") )
                , bp::return_value_policy< bp::reference_existing_object >() );
        
        }
        { //::MultiLayer::getLayerBottomZ
        
            typedef double ( ::MultiLayer::*getLayerBottomZ_function_type)( ::std::size_t ) const;
            
            MultiLayer_exposer.def( 
                "getLayerBottomZ"
                , getLayerBottomZ_function_type( &::MultiLayer::getLayerBottomZ )
                , ( bp::arg("i_layer") ) );
        
        }
        { //::MultiLayer::getLayerInterface
        
            typedef ::LayerInterface const * ( ::MultiLayer::*getLayerInterface_function_type)( ::std::size_t ) const;
            
            MultiLayer_exposer.def( 
                "getLayerInterface"
                , getLayerInterface_function_type( &::MultiLayer::getLayerInterface )
                , ( bp::arg("i_interface") )
                , bp::return_value_policy< bp::reference_existing_object >() );
        
        }
        { //::MultiLayer::getLayerThickness
        
            typedef double ( ::MultiLayer::*getLayerThickness_function_type)( ::std::size_t ) const;
            
            MultiLayer_exposer.def( 
                "getLayerThickness"
                , getLayerThickness_function_type( &::MultiLayer::getLayerThickness )
                , ( bp::arg("i_layer") ) );
        
        }
        { //::MultiLayer::getLayerTopInterface
        
            typedef ::LayerInterface const * ( ::MultiLayer::*getLayerTopInterface_function_type)( ::std::size_t ) const;
            
            MultiLayer_exposer.def( 
                "getLayerTopInterface"
                , getLayerTopInterface_function_type( &::MultiLayer::getLayerTopInterface )
                , ( bp::arg("i_layer") )
                , bp::return_value_policy< bp::reference_existing_object >() );
        
        }
        { //::MultiLayer::getNumberOfInterfaces
        
            typedef ::std::size_t ( ::MultiLayer::*getNumberOfInterfaces_function_type)(  ) const;
            
            MultiLayer_exposer.def( 
                "getNumberOfInterfaces"
                , getNumberOfInterfaces_function_type( &::MultiLayer::getNumberOfInterfaces ) );
        
        }
        { //::MultiLayer::getNumberOfLayers
        
            typedef ::std::size_t ( ::MultiLayer::*getNumberOfLayers_function_type)(  ) const;
            
            MultiLayer_exposer.def( 
                "getNumberOfLayers"
                , getNumberOfLayers_function_type( &::MultiLayer::getNumberOfLayers ) );
        
        }
        { //::MultiLayer::requiresMatrixRTCoefficients
        
            typedef bool ( ::MultiLayer::*requiresMatrixRTCoefficients_function_type)(  ) const;
            
            MultiLayer_exposer.def( 
                "requiresMatrixRTCoefficients"
                , requiresMatrixRTCoefficients_function_type( &::MultiLayer::requiresMatrixRTCoefficients ) );
        
        }
        { //::MultiLayer::setCrossCorrLength
        
            typedef void ( ::MultiLayer::*setCrossCorrLength_function_type)( double ) ;
            
            MultiLayer_exposer.def( 
                "setCrossCorrLength"
                , setCrossCorrLength_function_type( &::MultiLayer::setCrossCorrLength )
                , ( bp::arg("crossCorrLength") ) );
        
        }
        { //::MultiLayer::setLayerThickness
        
            typedef void ( ::MultiLayer::*setLayerThickness_function_type)( ::std::size_t,double ) ;
            
            MultiLayer_exposer.def( 
                "setLayerThickness"
                , setLayerThickness_function_type( &::MultiLayer::setLayerThickness )
                , ( bp::arg("i_layer"), bp::arg("thickness") ) );
        
        }
        { //::MultiLayer::zToLayerIndex
        
            typedef ::std::size_t ( ::MultiLayer::*zToLayerIndex_function_type)( double ) ;
            
            MultiLayer_exposer.def( 
                "zToLayerIndex"
                , zToLayerIndex_function_type( &::MultiLayer::zToLayerIndex )
                , ( bp::arg("z_value") ) );
        
        }
        { //::IParameterized::areParametersChanged
        
            typedef bool ( ::IParameterized::*areParametersChanged_function_type)(  ) ;
            typedef bool ( MultiLayer_wrapper::*default_areParametersChanged_function_type)(  ) ;
            
            MultiLayer_exposer.def( 
                "areParametersChanged"
                , areParametersChanged_function_type(&::IParameterized::areParametersChanged)
                , default_areParametersChanged_function_type(&MultiLayer_wrapper::default_areParametersChanged) );
        
        }
        { //::IParameterized::clearParameterPool
        
            typedef void ( ::IParameterized::*clearParameterPool_function_type)(  ) ;
            typedef void ( MultiLayer_wrapper::*default_clearParameterPool_function_type)(  ) ;
            
            MultiLayer_exposer.def( 
                "clearParameterPool"
                , clearParameterPool_function_type(&::IParameterized::clearParameterPool)
                , default_clearParameterPool_function_type(&MultiLayer_wrapper::default_clearParameterPool) );
        
        }
        { //::ISample::containsMagneticMaterial
        
            typedef bool ( ::ISample::*containsMagneticMaterial_function_type)(  ) const;
            typedef bool ( MultiLayer_wrapper::*default_containsMagneticMaterial_function_type)(  ) const;
            
            MultiLayer_exposer.def( 
                "containsMagneticMaterial"
                , containsMagneticMaterial_function_type(&::ISample::containsMagneticMaterial)
                , default_containsMagneticMaterial_function_type(&MultiLayer_wrapper::default_containsMagneticMaterial) );
        
        }
        { //::IParameterized::createParameterTree
        
            typedef ::ParameterPool * ( ::IParameterized::*createParameterTree_function_type)(  ) const;
            typedef ::ParameterPool * ( MultiLayer_wrapper::*default_createParameterTree_function_type)(  ) const;
            
            MultiLayer_exposer.def( 
                "createParameterTree"
                , createParameterTree_function_type(&::IParameterized::createParameterTree)
                , default_createParameterTree_function_type(&MultiLayer_wrapper::default_createParameterTree)
                , bp::return_value_policy< bp::manage_new_object >() );
        
        }
        { //::ICompositeSample::getCompositeSample
        
            typedef ::ICompositeSample * ( ::ICompositeSample::*getCompositeSample_function_type)(  ) ;
            typedef ::ICompositeSample * ( MultiLayer_wrapper::*default_getCompositeSample_function_type)(  ) ;
            
            MultiLayer_exposer.def( 
                "getCompositeSample"
                , getCompositeSample_function_type(&::ICompositeSample::getCompositeSample)
                , default_getCompositeSample_function_type(&MultiLayer_wrapper::default_getCompositeSample)
                , bp::return_value_policy< bp::reference_existing_object >() );
        
        }
        { //::ICompositeSample::getCompositeSample
        
            typedef ::ICompositeSample const * ( ::ICompositeSample::*getCompositeSample_function_type)(  ) const;
            typedef ::ICompositeSample const * ( MultiLayer_wrapper::*default_getCompositeSample_function_type)(  ) const;
            
            MultiLayer_exposer.def( 
                "getCompositeSample"
                , getCompositeSample_function_type(&::ICompositeSample::getCompositeSample)
                , default_getCompositeSample_function_type(&MultiLayer_wrapper::default_getCompositeSample)
                , bp::return_value_policy< bp::reference_existing_object >() );
        
        }
        { //::ISample::preprocess
        
            typedef bool ( ::ISample::*preprocess_function_type)(  ) ;
            typedef bool ( MultiLayer_wrapper::*default_preprocess_function_type)(  ) ;
            
            MultiLayer_exposer.def( 
                "preprocess"
                , preprocess_function_type(&::ISample::preprocess)
                , default_preprocess_function_type(&MultiLayer_wrapper::default_preprocess) );
        
        }
        { //::IParameterized::printParameters
        
            typedef void ( ::IParameterized::*printParameters_function_type)(  ) const;
            typedef void ( MultiLayer_wrapper::*default_printParameters_function_type)(  ) const;
            
            MultiLayer_exposer.def( 
                "printParameters"
                , printParameters_function_type(&::IParameterized::printParameters)
                , default_printParameters_function_type(&MultiLayer_wrapper::default_printParameters) );
        
        }
        { //::ISample::printSampleTree
        
            typedef void ( ::ISample::*printSampleTree_function_type)(  ) ;
            typedef void ( MultiLayer_wrapper::*default_printSampleTree_function_type)(  ) ;
            
            MultiLayer_exposer.def( 
                "printSampleTree"
                , printSampleTree_function_type(&::ISample::printSampleTree)
                , default_printSampleTree_function_type(&MultiLayer_wrapper::default_printSampleTree) );
        
        }
        { //::IParameterized::registerParameter
        
            typedef void ( *default_registerParameter_function_type )( ::IParameterized &,::std::string const &,long unsigned int );
            
            MultiLayer_exposer.def( 
                "registerParameter"
                , default_registerParameter_function_type( &MultiLayer_wrapper::default_registerParameter )
                , ( bp::arg("inst"), bp::arg("name"), bp::arg("parpointer") ) );
        
        }
        { //::IParameterized::setParameterValue
        
            typedef bool ( ::IParameterized::*setParameterValue_function_type)( ::std::string const &,double ) ;
            typedef bool ( MultiLayer_wrapper::*default_setParameterValue_function_type)( ::std::string const &,double ) ;
            
            MultiLayer_exposer.def( 
                "setParameterValue"
                , setParameterValue_function_type(&::IParameterized::setParameterValue)
                , default_setParameterValue_function_type(&MultiLayer_wrapper::default_setParameterValue)
                , ( bp::arg("name"), bp::arg("value") ) );
        
        }
        { //::IParameterized::setParametersAreChanged
        
            typedef void ( ::IParameterized::*setParametersAreChanged_function_type)(  ) ;
            typedef void ( MultiLayer_wrapper::*default_setParametersAreChanged_function_type)(  ) ;
            
            MultiLayer_exposer.def( 
                "setParametersAreChanged"
                , setParametersAreChanged_function_type(&::IParameterized::setParametersAreChanged)
                , default_setParametersAreChanged_function_type(&MultiLayer_wrapper::default_setParametersAreChanged) );
        
        }
        { //::ICompositeSample::size
        
            typedef ::std::size_t ( ::ICompositeSample::*size_function_type)(  ) const;
            typedef ::std::size_t ( MultiLayer_wrapper::*default_size_function_type)(  ) const;
            
            MultiLayer_exposer.def( 
                "size"
                , size_function_type(&::ICompositeSample::size)
                , default_size_function_type(&MultiLayer_wrapper::default_size) );
        
        }
        { //::ICloneable::transferToCPP
        
            typedef void ( ::ICloneable::*transferToCPP_function_type)(  ) ;
            typedef void ( MultiLayer_wrapper::*default_transferToCPP_function_type)(  ) ;
            
            MultiLayer_exposer.def( 
                "transferToCPP"
                , transferToCPP_function_type(&::ICloneable::transferToCPP)
                , default_transferToCPP_function_type(&MultiLayer_wrapper::default_transferToCPP) );
        
        }
    }

}
