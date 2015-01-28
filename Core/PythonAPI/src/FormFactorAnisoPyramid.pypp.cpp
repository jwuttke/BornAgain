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
#include "FormFactorAnisoPyramid.pypp.h"

namespace bp = boost::python;

struct FormFactorAnisoPyramid_wrapper : FormFactorAnisoPyramid, bp::wrapper< FormFactorAnisoPyramid > {

    FormFactorAnisoPyramid_wrapper(double length, double width, double height, double alpha )
    : FormFactorAnisoPyramid( length, width, height, alpha )
      , bp::wrapper< FormFactorAnisoPyramid >(){
        // constructor
    m_pyobj = 0;
    }

    virtual ::FormFactorAnisoPyramid * clone(  ) const  {
        if( bp::override func_clone = this->get_override( "clone" ) )
            return func_clone(  );
        else{
            return this->FormFactorAnisoPyramid::clone(  );
        }
    }
    
    ::FormFactorAnisoPyramid * default_clone(  ) const  {
        return FormFactorAnisoPyramid::clone( );
    }

    virtual ::complex_t evaluate_for_q( ::cvector_t const & q ) const  {
        if( bp::override func_evaluate_for_q = this->get_override( "evaluate_for_q" ) )
            return func_evaluate_for_q( boost::ref(q) );
        else{
            return this->FormFactorAnisoPyramid::evaluate_for_q( boost::ref(q) );
        }
    }
    
    ::complex_t default_evaluate_for_q( ::cvector_t const & q ) const  {
        return FormFactorAnisoPyramid::evaluate_for_q( boost::ref(q) );
    }

    virtual double getAlpha(  ) const  {
        if( bp::override func_getAlpha = this->get_override( "getAlpha" ) )
            return func_getAlpha(  );
        else{
            return this->FormFactorAnisoPyramid::getAlpha(  );
        }
    }
    
    double default_getAlpha(  ) const  {
        return FormFactorAnisoPyramid::getAlpha( );
    }

    virtual double getHeight(  ) const  {
        if( bp::override func_getHeight = this->get_override( "getHeight" ) )
            return func_getHeight(  );
        else{
            return this->FormFactorAnisoPyramid::getHeight(  );
        }
    }
    
    double default_getHeight(  ) const  {
        return FormFactorAnisoPyramid::getHeight( );
    }

    virtual double getLength(  ) const  {
        if( bp::override func_getLength = this->get_override( "getLength" ) )
            return func_getLength(  );
        else{
            return this->FormFactorAnisoPyramid::getLength(  );
        }
    }
    
    double default_getLength(  ) const  {
        return FormFactorAnisoPyramid::getLength( );
    }

    virtual int getNumberOfStochasticParameters(  ) const  {
        if( bp::override func_getNumberOfStochasticParameters = this->get_override( "getNumberOfStochasticParameters" ) )
            return func_getNumberOfStochasticParameters(  );
        else{
            return this->FormFactorAnisoPyramid::getNumberOfStochasticParameters(  );
        }
    }
    
    int default_getNumberOfStochasticParameters(  ) const  {
        return FormFactorAnisoPyramid::getNumberOfStochasticParameters( );
    }

    virtual double getWidth(  ) const  {
        if( bp::override func_getWidth = this->get_override( "getWidth" ) )
            return func_getWidth(  );
        else{
            return this->FormFactorAnisoPyramid::getWidth(  );
        }
    }
    
    double default_getWidth(  ) const  {
        return FormFactorAnisoPyramid::getWidth( );
    }

    virtual void setAlpha( double alpha ) {
        if( bp::override func_setAlpha = this->get_override( "setAlpha" ) )
            func_setAlpha( alpha );
        else{
            this->FormFactorAnisoPyramid::setAlpha( alpha );
        }
    }
    
    void default_setAlpha( double alpha ) {
        FormFactorAnisoPyramid::setAlpha( alpha );
    }

    virtual void setHeight( double height ) {
        if( bp::override func_setHeight = this->get_override( "setHeight" ) )
            func_setHeight( height );
        else{
            this->FormFactorAnisoPyramid::setHeight( height );
        }
    }
    
    void default_setHeight( double height ) {
        FormFactorAnisoPyramid::setHeight( height );
    }

    virtual void setLength( double length ) {
        if( bp::override func_setLength = this->get_override( "setLength" ) )
            func_setLength( length );
        else{
            this->FormFactorAnisoPyramid::setLength( length );
        }
    }
    
    void default_setLength( double length ) {
        FormFactorAnisoPyramid::setLength( length );
    }

    virtual void setWidth( double width ) {
        if( bp::override func_setWidth = this->get_override( "setWidth" ) )
            func_setWidth( width );
        else{
            this->FormFactorAnisoPyramid::setWidth( width );
        }
    }
    
    void default_setWidth( double width ) {
        FormFactorAnisoPyramid::setWidth( width );
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

    virtual ::ISample * cloneInvertB(  ) const  {
        if( bp::override func_cloneInvertB = this->get_override( "cloneInvertB" ) )
            return func_cloneInvertB(  );
        else{
            return this->ISample::cloneInvertB(  );
        }
    }
    
    ::ISample * default_cloneInvertB(  ) const  {
        return ISample::cloneInvertB( );
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

    virtual void createDistributedFormFactors( ::std::vector< IFormFactor* > & form_factors, ::std::vector< double > & probabilities, ::std::size_t nbr_samples ) const  {
        if( bp::override func_createDistributedFormFactors = this->get_override( "createDistributedFormFactors" ) )
            func_createDistributedFormFactors( boost::ref(form_factors), boost::ref(probabilities), nbr_samples );
        else{
            this->IFormFactor::createDistributedFormFactors( boost::ref(form_factors), boost::ref(probabilities), nbr_samples );
        }
    }
    
    void default_createDistributedFormFactors( ::std::vector< IFormFactor* > & form_factors, ::std::vector< double > & probabilities, ::std::size_t nbr_samples ) const  {
        IFormFactor::createDistributedFormFactors( boost::ref(form_factors), boost::ref(probabilities), nbr_samples );
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

    virtual ::complex_t evaluate( ::cvector_t const & k_i, ::Bin1DCVector const & k_f_bin, ::Bin1D const & alpha_f_bin ) const  {
        if( bp::override func_evaluate = this->get_override( "evaluate" ) )
            return func_evaluate( boost::ref(k_i), boost::ref(k_f_bin), boost::ref(alpha_f_bin) );
        else{
            return this->IFormFactorBorn::evaluate( boost::ref(k_i), boost::ref(k_f_bin), boost::ref(alpha_f_bin) );
        }
    }
    
    ::complex_t default_evaluate( ::cvector_t const & k_i, ::Bin1DCVector const & k_f_bin, ::Bin1D const & alpha_f_bin ) const  {
        return IFormFactorBorn::evaluate( boost::ref(k_i), boost::ref(k_f_bin), boost::ref(alpha_f_bin) );
    }

    virtual ::ICompositeSample * getCompositeSample(  ) {
        if( bp::override func_getCompositeSample = this->get_override( "getCompositeSample" ) )
            return func_getCompositeSample(  );
        else{
            return this->ISample::getCompositeSample(  );
        }
    }
    
    ::ICompositeSample * default_getCompositeSample(  ) {
        return ISample::getCompositeSample( );
    }

    virtual ::ICompositeSample const * getCompositeSample(  ) const  {
        if( bp::override func_getCompositeSample = this->get_override( "getCompositeSample" ) )
            return func_getCompositeSample(  );
        else{
            return this->ISample::getCompositeSample(  );
        }
    }
    
    ::ICompositeSample const * default_getCompositeSample(  ) const  {
        return ISample::getCompositeSample( );
    }

    virtual double getRadius(  ) const  {
        if( bp::override func_getRadius = this->get_override( "getRadius" ) )
            return func_getRadius(  );
        else{
            return this->IFormFactor::getRadius(  );
        }
    }
    
    double default_getRadius(  ) const  {
        return IFormFactor::getRadius( );
    }

    virtual double getVolume(  ) const  {
        if( bp::override func_getVolume = this->get_override( "getVolume" ) )
            return func_getVolume(  );
        else{
            return this->IFormFactorBorn::getVolume(  );
        }
    }
    
    double default_getVolume(  ) const  {
        return IFormFactorBorn::getVolume( );
    }

    virtual bool isDistributedFormFactor(  ) const  {
        if( bp::override func_isDistributedFormFactor = this->get_override( "isDistributedFormFactor" ) )
            return func_isDistributedFormFactor(  );
        else{
            return this->IFormFactor::isDistributedFormFactor(  );
        }
    }
    
    bool default_isDistributedFormFactor(  ) const  {
        return IFormFactor::isDistributedFormFactor( );
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
        if( dynamic_cast< FormFactorAnisoPyramid_wrapper * >( boost::addressof( inst ) ) ){
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

void register_FormFactorAnisoPyramid_class(){

    { //::FormFactorAnisoPyramid
        typedef bp::class_< FormFactorAnisoPyramid_wrapper, bp::bases< IFormFactorBorn >, std::auto_ptr< FormFactorAnisoPyramid_wrapper >, boost::noncopyable > FormFactorAnisoPyramid_exposer_t;
        FormFactorAnisoPyramid_exposer_t FormFactorAnisoPyramid_exposer = FormFactorAnisoPyramid_exposer_t( "FormFactorAnisoPyramid", bp::init< double, double, double, double >(( bp::arg("length"), bp::arg("width"), bp::arg("height"), bp::arg("alpha") )) );
        bp::scope FormFactorAnisoPyramid_scope( FormFactorAnisoPyramid_exposer );
        { //::FormFactorAnisoPyramid::clone
        
            typedef ::FormFactorAnisoPyramid * ( ::FormFactorAnisoPyramid::*clone_function_type)(  ) const;
            typedef ::FormFactorAnisoPyramid * ( FormFactorAnisoPyramid_wrapper::*default_clone_function_type)(  ) const;
            
            FormFactorAnisoPyramid_exposer.def( 
                "clone"
                , clone_function_type(&::FormFactorAnisoPyramid::clone)
                , default_clone_function_type(&FormFactorAnisoPyramid_wrapper::default_clone)
                , bp::return_value_policy< bp::manage_new_object >() );
        
        }
        { //::FormFactorAnisoPyramid::evaluate_for_q
        
            typedef ::complex_t ( ::FormFactorAnisoPyramid::*evaluate_for_q_function_type)( ::cvector_t const & ) const;
            typedef ::complex_t ( FormFactorAnisoPyramid_wrapper::*default_evaluate_for_q_function_type)( ::cvector_t const & ) const;
            
            FormFactorAnisoPyramid_exposer.def( 
                "evaluate_for_q"
                , evaluate_for_q_function_type(&::FormFactorAnisoPyramid::evaluate_for_q)
                , default_evaluate_for_q_function_type(&FormFactorAnisoPyramid_wrapper::default_evaluate_for_q)
                , ( bp::arg("q") ) );
        
        }
        { //::FormFactorAnisoPyramid::getAlpha
        
            typedef double ( ::FormFactorAnisoPyramid::*getAlpha_function_type)(  ) const;
            typedef double ( FormFactorAnisoPyramid_wrapper::*default_getAlpha_function_type)(  ) const;
            
            FormFactorAnisoPyramid_exposer.def( 
                "getAlpha"
                , getAlpha_function_type(&::FormFactorAnisoPyramid::getAlpha)
                , default_getAlpha_function_type(&FormFactorAnisoPyramid_wrapper::default_getAlpha) );
        
        }
        { //::FormFactorAnisoPyramid::getHeight
        
            typedef double ( ::FormFactorAnisoPyramid::*getHeight_function_type)(  ) const;
            typedef double ( FormFactorAnisoPyramid_wrapper::*default_getHeight_function_type)(  ) const;
            
            FormFactorAnisoPyramid_exposer.def( 
                "getHeight"
                , getHeight_function_type(&::FormFactorAnisoPyramid::getHeight)
                , default_getHeight_function_type(&FormFactorAnisoPyramid_wrapper::default_getHeight) );
        
        }
        { //::FormFactorAnisoPyramid::getLength
        
            typedef double ( ::FormFactorAnisoPyramid::*getLength_function_type)(  ) const;
            typedef double ( FormFactorAnisoPyramid_wrapper::*default_getLength_function_type)(  ) const;
            
            FormFactorAnisoPyramid_exposer.def( 
                "getLength"
                , getLength_function_type(&::FormFactorAnisoPyramid::getLength)
                , default_getLength_function_type(&FormFactorAnisoPyramid_wrapper::default_getLength) );
        
        }
        { //::FormFactorAnisoPyramid::getNumberOfStochasticParameters
        
            typedef int ( ::FormFactorAnisoPyramid::*getNumberOfStochasticParameters_function_type)(  ) const;
            typedef int ( FormFactorAnisoPyramid_wrapper::*default_getNumberOfStochasticParameters_function_type)(  ) const;
            
            FormFactorAnisoPyramid_exposer.def( 
                "getNumberOfStochasticParameters"
                , getNumberOfStochasticParameters_function_type(&::FormFactorAnisoPyramid::getNumberOfStochasticParameters)
                , default_getNumberOfStochasticParameters_function_type(&FormFactorAnisoPyramid_wrapper::default_getNumberOfStochasticParameters) );
        
        }
        { //::FormFactorAnisoPyramid::getWidth
        
            typedef double ( ::FormFactorAnisoPyramid::*getWidth_function_type)(  ) const;
            typedef double ( FormFactorAnisoPyramid_wrapper::*default_getWidth_function_type)(  ) const;
            
            FormFactorAnisoPyramid_exposer.def( 
                "getWidth"
                , getWidth_function_type(&::FormFactorAnisoPyramid::getWidth)
                , default_getWidth_function_type(&FormFactorAnisoPyramid_wrapper::default_getWidth) );
        
        }
        { //::FormFactorAnisoPyramid::setAlpha
        
            typedef void ( ::FormFactorAnisoPyramid::*setAlpha_function_type)( double ) ;
            typedef void ( FormFactorAnisoPyramid_wrapper::*default_setAlpha_function_type)( double ) ;
            
            FormFactorAnisoPyramid_exposer.def( 
                "setAlpha"
                , setAlpha_function_type(&::FormFactorAnisoPyramid::setAlpha)
                , default_setAlpha_function_type(&FormFactorAnisoPyramid_wrapper::default_setAlpha)
                , ( bp::arg("alpha") ) );
        
        }
        { //::FormFactorAnisoPyramid::setHeight
        
            typedef void ( ::FormFactorAnisoPyramid::*setHeight_function_type)( double ) ;
            typedef void ( FormFactorAnisoPyramid_wrapper::*default_setHeight_function_type)( double ) ;
            
            FormFactorAnisoPyramid_exposer.def( 
                "setHeight"
                , setHeight_function_type(&::FormFactorAnisoPyramid::setHeight)
                , default_setHeight_function_type(&FormFactorAnisoPyramid_wrapper::default_setHeight)
                , ( bp::arg("height") ) );
        
        }
        { //::FormFactorAnisoPyramid::setLength
        
            typedef void ( ::FormFactorAnisoPyramid::*setLength_function_type)( double ) ;
            typedef void ( FormFactorAnisoPyramid_wrapper::*default_setLength_function_type)( double ) ;
            
            FormFactorAnisoPyramid_exposer.def( 
                "setLength"
                , setLength_function_type(&::FormFactorAnisoPyramid::setLength)
                , default_setLength_function_type(&FormFactorAnisoPyramid_wrapper::default_setLength)
                , ( bp::arg("length") ) );
        
        }
        { //::FormFactorAnisoPyramid::setWidth
        
            typedef void ( ::FormFactorAnisoPyramid::*setWidth_function_type)( double ) ;
            typedef void ( FormFactorAnisoPyramid_wrapper::*default_setWidth_function_type)( double ) ;
            
            FormFactorAnisoPyramid_exposer.def( 
                "setWidth"
                , setWidth_function_type(&::FormFactorAnisoPyramid::setWidth)
                , default_setWidth_function_type(&FormFactorAnisoPyramid_wrapper::default_setWidth)
                , ( bp::arg("width") ) );
        
        }
        { //::IParameterized::areParametersChanged
        
            typedef bool ( ::IParameterized::*areParametersChanged_function_type)(  ) ;
            typedef bool ( FormFactorAnisoPyramid_wrapper::*default_areParametersChanged_function_type)(  ) ;
            
            FormFactorAnisoPyramid_exposer.def( 
                "areParametersChanged"
                , areParametersChanged_function_type(&::IParameterized::areParametersChanged)
                , default_areParametersChanged_function_type(&FormFactorAnisoPyramid_wrapper::default_areParametersChanged) );
        
        }
        { //::IParameterized::clearParameterPool
        
            typedef void ( ::IParameterized::*clearParameterPool_function_type)(  ) ;
            typedef void ( FormFactorAnisoPyramid_wrapper::*default_clearParameterPool_function_type)(  ) ;
            
            FormFactorAnisoPyramid_exposer.def( 
                "clearParameterPool"
                , clearParameterPool_function_type(&::IParameterized::clearParameterPool)
                , default_clearParameterPool_function_type(&FormFactorAnisoPyramid_wrapper::default_clearParameterPool) );
        
        }
        { //::ISample::cloneInvertB
        
            typedef ::ISample * ( ::ISample::*cloneInvertB_function_type)(  ) const;
            typedef ::ISample * ( FormFactorAnisoPyramid_wrapper::*default_cloneInvertB_function_type)(  ) const;
            
            FormFactorAnisoPyramid_exposer.def( 
                "cloneInvertB"
                , cloneInvertB_function_type(&::ISample::cloneInvertB)
                , default_cloneInvertB_function_type(&FormFactorAnisoPyramid_wrapper::default_cloneInvertB)
                , bp::return_value_policy< bp::reference_existing_object >() );
        
        }
        { //::ISample::containsMagneticMaterial
        
            typedef bool ( ::ISample::*containsMagneticMaterial_function_type)(  ) const;
            typedef bool ( FormFactorAnisoPyramid_wrapper::*default_containsMagneticMaterial_function_type)(  ) const;
            
            FormFactorAnisoPyramid_exposer.def( 
                "containsMagneticMaterial"
                , containsMagneticMaterial_function_type(&::ISample::containsMagneticMaterial)
                , default_containsMagneticMaterial_function_type(&FormFactorAnisoPyramid_wrapper::default_containsMagneticMaterial) );
        
        }
        { //::IFormFactor::createDistributedFormFactors
        
            typedef void ( ::IFormFactor::*createDistributedFormFactors_function_type)( ::std::vector< IFormFactor* > &,::std::vector< double > &,::std::size_t ) const;
            typedef void ( FormFactorAnisoPyramid_wrapper::*default_createDistributedFormFactors_function_type)( ::std::vector< IFormFactor* > &,::std::vector< double > &,::std::size_t ) const;
            
            FormFactorAnisoPyramid_exposer.def( 
                "createDistributedFormFactors"
                , createDistributedFormFactors_function_type(&::IFormFactor::createDistributedFormFactors)
                , default_createDistributedFormFactors_function_type(&FormFactorAnisoPyramid_wrapper::default_createDistributedFormFactors)
                , ( bp::arg("form_factors"), bp::arg("probabilities"), bp::arg("nbr_samples") )
                , bp::return_value_policy< bp::manage_new_object >() );
        
        }
        { //::IParameterized::createParameterTree
        
            typedef ::ParameterPool * ( ::IParameterized::*createParameterTree_function_type)(  ) const;
            typedef ::ParameterPool * ( FormFactorAnisoPyramid_wrapper::*default_createParameterTree_function_type)(  ) const;
            
            FormFactorAnisoPyramid_exposer.def( 
                "createParameterTree"
                , createParameterTree_function_type(&::IParameterized::createParameterTree)
                , default_createParameterTree_function_type(&FormFactorAnisoPyramid_wrapper::default_createParameterTree)
                , bp::return_value_policy< bp::manage_new_object >() );
        
        }
        { //::IFormFactorBorn::evaluate
        
            typedef ::complex_t ( ::IFormFactorBorn::*evaluate_function_type)( ::cvector_t const &,::Bin1DCVector const &,::Bin1D const & ) const;
            typedef ::complex_t ( FormFactorAnisoPyramid_wrapper::*default_evaluate_function_type)( ::cvector_t const &,::Bin1DCVector const &,::Bin1D const & ) const;
            
            FormFactorAnisoPyramid_exposer.def( 
                "evaluate"
                , evaluate_function_type(&::IFormFactorBorn::evaluate)
                , default_evaluate_function_type(&FormFactorAnisoPyramid_wrapper::default_evaluate)
                , ( bp::arg("k_i"), bp::arg("k_f_bin"), bp::arg("alpha_f_bin") ) );
        
        }
        { //::ISample::getCompositeSample
        
            typedef ::ICompositeSample * ( ::ISample::*getCompositeSample_function_type)(  ) ;
            typedef ::ICompositeSample * ( FormFactorAnisoPyramid_wrapper::*default_getCompositeSample_function_type)(  ) ;
            
            FormFactorAnisoPyramid_exposer.def( 
                "getCompositeSample"
                , getCompositeSample_function_type(&::ISample::getCompositeSample)
                , default_getCompositeSample_function_type(&FormFactorAnisoPyramid_wrapper::default_getCompositeSample)
                , bp::return_value_policy< bp::reference_existing_object >() );
        
        }
        { //::ISample::getCompositeSample
        
            typedef ::ICompositeSample const * ( ::ISample::*getCompositeSample_function_type)(  ) const;
            typedef ::ICompositeSample const * ( FormFactorAnisoPyramid_wrapper::*default_getCompositeSample_function_type)(  ) const;
            
            FormFactorAnisoPyramid_exposer.def( 
                "getCompositeSample"
                , getCompositeSample_function_type(&::ISample::getCompositeSample)
                , default_getCompositeSample_function_type(&FormFactorAnisoPyramid_wrapper::default_getCompositeSample)
                , bp::return_value_policy< bp::reference_existing_object >() );
        
        }
        { //::IFormFactor::getRadius
        
            typedef double ( ::IFormFactor::*getRadius_function_type)(  ) const;
            typedef double ( FormFactorAnisoPyramid_wrapper::*default_getRadius_function_type)(  ) const;
            
            FormFactorAnisoPyramid_exposer.def( 
                "getRadius"
                , getRadius_function_type(&::IFormFactor::getRadius)
                , default_getRadius_function_type(&FormFactorAnisoPyramid_wrapper::default_getRadius) );
        
        }
        { //::IFormFactorBorn::getVolume
        
            typedef double ( ::IFormFactorBorn::*getVolume_function_type)(  ) const;
            typedef double ( FormFactorAnisoPyramid_wrapper::*default_getVolume_function_type)(  ) const;
            
            FormFactorAnisoPyramid_exposer.def( 
                "getVolume"
                , getVolume_function_type(&::IFormFactorBorn::getVolume)
                , default_getVolume_function_type(&FormFactorAnisoPyramid_wrapper::default_getVolume) );
        
        }
        { //::IFormFactor::isDistributedFormFactor
        
            typedef bool ( ::IFormFactor::*isDistributedFormFactor_function_type)(  ) const;
            typedef bool ( FormFactorAnisoPyramid_wrapper::*default_isDistributedFormFactor_function_type)(  ) const;
            
            FormFactorAnisoPyramid_exposer.def( 
                "isDistributedFormFactor"
                , isDistributedFormFactor_function_type(&::IFormFactor::isDistributedFormFactor)
                , default_isDistributedFormFactor_function_type(&FormFactorAnisoPyramid_wrapper::default_isDistributedFormFactor) );
        
        }
        { //::ISample::preprocess
        
            typedef bool ( ::ISample::*preprocess_function_type)(  ) ;
            typedef bool ( FormFactorAnisoPyramid_wrapper::*default_preprocess_function_type)(  ) ;
            
            FormFactorAnisoPyramid_exposer.def( 
                "preprocess"
                , preprocess_function_type(&::ISample::preprocess)
                , default_preprocess_function_type(&FormFactorAnisoPyramid_wrapper::default_preprocess) );
        
        }
        { //::IParameterized::printParameters
        
            typedef void ( ::IParameterized::*printParameters_function_type)(  ) const;
            typedef void ( FormFactorAnisoPyramid_wrapper::*default_printParameters_function_type)(  ) const;
            
            FormFactorAnisoPyramid_exposer.def( 
                "printParameters"
                , printParameters_function_type(&::IParameterized::printParameters)
                , default_printParameters_function_type(&FormFactorAnisoPyramid_wrapper::default_printParameters) );
        
        }
        { //::ISample::printSampleTree
        
            typedef void ( ::ISample::*printSampleTree_function_type)(  ) ;
            typedef void ( FormFactorAnisoPyramid_wrapper::*default_printSampleTree_function_type)(  ) ;
            
            FormFactorAnisoPyramid_exposer.def( 
                "printSampleTree"
                , printSampleTree_function_type(&::ISample::printSampleTree)
                , default_printSampleTree_function_type(&FormFactorAnisoPyramid_wrapper::default_printSampleTree) );
        
        }
        { //::IParameterized::registerParameter
        
            typedef void ( *default_registerParameter_function_type )( ::IParameterized &,::std::string const &,long unsigned int );
            
            FormFactorAnisoPyramid_exposer.def( 
                "registerParameter"
                , default_registerParameter_function_type( &FormFactorAnisoPyramid_wrapper::default_registerParameter )
                , ( bp::arg("inst"), bp::arg("name"), bp::arg("parpointer") ) );
        
        }
        { //::IParameterized::setParameterValue
        
            typedef bool ( ::IParameterized::*setParameterValue_function_type)( ::std::string const &,double ) ;
            typedef bool ( FormFactorAnisoPyramid_wrapper::*default_setParameterValue_function_type)( ::std::string const &,double ) ;
            
            FormFactorAnisoPyramid_exposer.def( 
                "setParameterValue"
                , setParameterValue_function_type(&::IParameterized::setParameterValue)
                , default_setParameterValue_function_type(&FormFactorAnisoPyramid_wrapper::default_setParameterValue)
                , ( bp::arg("name"), bp::arg("value") ) );
        
        }
        { //::IParameterized::setParametersAreChanged
        
            typedef void ( ::IParameterized::*setParametersAreChanged_function_type)(  ) ;
            typedef void ( FormFactorAnisoPyramid_wrapper::*default_setParametersAreChanged_function_type)(  ) ;
            
            FormFactorAnisoPyramid_exposer.def( 
                "setParametersAreChanged"
                , setParametersAreChanged_function_type(&::IParameterized::setParametersAreChanged)
                , default_setParametersAreChanged_function_type(&FormFactorAnisoPyramid_wrapper::default_setParametersAreChanged) );
        
        }
        { //::ICloneable::transferToCPP
        
            typedef void ( ::ICloneable::*transferToCPP_function_type)(  ) ;
            typedef void ( FormFactorAnisoPyramid_wrapper::*default_transferToCPP_function_type)(  ) ;
            
            FormFactorAnisoPyramid_exposer.def( 
                "transferToCPP"
                , transferToCPP_function_type(&::ICloneable::transferToCPP)
                , default_transferToCPP_function_type(&FormFactorAnisoPyramid_wrapper::default_transferToCPP) );
        
        }
    }

}
