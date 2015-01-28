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
#include "FormFactorTetrahedron.pypp.h"

namespace bp = boost::python;

struct FormFactorTetrahedron_wrapper : FormFactorTetrahedron, bp::wrapper< FormFactorTetrahedron > {

    FormFactorTetrahedron_wrapper(double length, double height, double alpha )
    : FormFactorTetrahedron( length, height, alpha )
      , bp::wrapper< FormFactorTetrahedron >(){
        // constructor
    m_pyobj = 0;
    }

    virtual ::FormFactorTetrahedron * clone(  ) const  {
        if( bp::override func_clone = this->get_override( "clone" ) )
            return func_clone(  );
        else{
            return this->FormFactorTetrahedron::clone(  );
        }
    }
    
    ::FormFactorTetrahedron * default_clone(  ) const  {
        return FormFactorTetrahedron::clone( );
    }

    virtual ::complex_t evaluate_for_q( ::cvector_t const & q ) const  {
        if( bp::override func_evaluate_for_q = this->get_override( "evaluate_for_q" ) )
            return func_evaluate_for_q( boost::ref(q) );
        else{
            return this->FormFactorTetrahedron::evaluate_for_q( boost::ref(q) );
        }
    }
    
    ::complex_t default_evaluate_for_q( ::cvector_t const & q ) const  {
        return FormFactorTetrahedron::evaluate_for_q( boost::ref(q) );
    }

    virtual double getAlpha(  ) const  {
        if( bp::override func_getAlpha = this->get_override( "getAlpha" ) )
            return func_getAlpha(  );
        else{
            return this->FormFactorTetrahedron::getAlpha(  );
        }
    }
    
    double default_getAlpha(  ) const  {
        return FormFactorTetrahedron::getAlpha( );
    }

    virtual double getHeight(  ) const  {
        if( bp::override func_getHeight = this->get_override( "getHeight" ) )
            return func_getHeight(  );
        else{
            return this->FormFactorTetrahedron::getHeight(  );
        }
    }
    
    double default_getHeight(  ) const  {
        return FormFactorTetrahedron::getHeight( );
    }

    virtual double getLength(  ) const  {
        if( bp::override func_getLength = this->get_override( "getLength" ) )
            return func_getLength(  );
        else{
            return this->FormFactorTetrahedron::getLength(  );
        }
    }
    
    double default_getLength(  ) const  {
        return FormFactorTetrahedron::getLength( );
    }

    virtual int getNumberOfStochasticParameters(  ) const  {
        if( bp::override func_getNumberOfStochasticParameters = this->get_override( "getNumberOfStochasticParameters" ) )
            return func_getNumberOfStochasticParameters(  );
        else{
            return this->FormFactorTetrahedron::getNumberOfStochasticParameters(  );
        }
    }
    
    int default_getNumberOfStochasticParameters(  ) const  {
        return FormFactorTetrahedron::getNumberOfStochasticParameters( );
    }

    virtual void setAlpha( double alpha ) {
        if( bp::override func_setAlpha = this->get_override( "setAlpha" ) )
            func_setAlpha( alpha );
        else{
            this->FormFactorTetrahedron::setAlpha( alpha );
        }
    }
    
    void default_setAlpha( double alpha ) {
        FormFactorTetrahedron::setAlpha( alpha );
    }

    virtual void setHeight( double height ) {
        if( bp::override func_setHeight = this->get_override( "setHeight" ) )
            func_setHeight( height );
        else{
            this->FormFactorTetrahedron::setHeight( height );
        }
    }
    
    void default_setHeight( double height ) {
        FormFactorTetrahedron::setHeight( height );
    }

    virtual void setLength( double length ) {
        if( bp::override func_setLength = this->get_override( "setLength" ) )
            func_setLength( length );
        else{
            this->FormFactorTetrahedron::setLength( length );
        }
    }
    
    void default_setLength( double length ) {
        FormFactorTetrahedron::setLength( length );
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
        if( dynamic_cast< FormFactorTetrahedron_wrapper * >( boost::addressof( inst ) ) ){
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

void register_FormFactorTetrahedron_class(){

    { //::FormFactorTetrahedron
        typedef bp::class_< FormFactorTetrahedron_wrapper, bp::bases< IFormFactorBorn >, std::auto_ptr< FormFactorTetrahedron_wrapper >, boost::noncopyable > FormFactorTetrahedron_exposer_t;
        FormFactorTetrahedron_exposer_t FormFactorTetrahedron_exposer = FormFactorTetrahedron_exposer_t( "FormFactorTetrahedron", bp::init< double, double, double >(( bp::arg("length"), bp::arg("height"), bp::arg("alpha") )) );
        bp::scope FormFactorTetrahedron_scope( FormFactorTetrahedron_exposer );
        { //::FormFactorTetrahedron::clone
        
            typedef ::FormFactorTetrahedron * ( ::FormFactorTetrahedron::*clone_function_type)(  ) const;
            typedef ::FormFactorTetrahedron * ( FormFactorTetrahedron_wrapper::*default_clone_function_type)(  ) const;
            
            FormFactorTetrahedron_exposer.def( 
                "clone"
                , clone_function_type(&::FormFactorTetrahedron::clone)
                , default_clone_function_type(&FormFactorTetrahedron_wrapper::default_clone)
                , bp::return_value_policy< bp::manage_new_object >() );
        
        }
        { //::FormFactorTetrahedron::evaluate_for_q
        
            typedef ::complex_t ( ::FormFactorTetrahedron::*evaluate_for_q_function_type)( ::cvector_t const & ) const;
            typedef ::complex_t ( FormFactorTetrahedron_wrapper::*default_evaluate_for_q_function_type)( ::cvector_t const & ) const;
            
            FormFactorTetrahedron_exposer.def( 
                "evaluate_for_q"
                , evaluate_for_q_function_type(&::FormFactorTetrahedron::evaluate_for_q)
                , default_evaluate_for_q_function_type(&FormFactorTetrahedron_wrapper::default_evaluate_for_q)
                , ( bp::arg("q") ) );
        
        }
        { //::FormFactorTetrahedron::getAlpha
        
            typedef double ( ::FormFactorTetrahedron::*getAlpha_function_type)(  ) const;
            typedef double ( FormFactorTetrahedron_wrapper::*default_getAlpha_function_type)(  ) const;
            
            FormFactorTetrahedron_exposer.def( 
                "getAlpha"
                , getAlpha_function_type(&::FormFactorTetrahedron::getAlpha)
                , default_getAlpha_function_type(&FormFactorTetrahedron_wrapper::default_getAlpha) );
        
        }
        { //::FormFactorTetrahedron::getHeight
        
            typedef double ( ::FormFactorTetrahedron::*getHeight_function_type)(  ) const;
            typedef double ( FormFactorTetrahedron_wrapper::*default_getHeight_function_type)(  ) const;
            
            FormFactorTetrahedron_exposer.def( 
                "getHeight"
                , getHeight_function_type(&::FormFactorTetrahedron::getHeight)
                , default_getHeight_function_type(&FormFactorTetrahedron_wrapper::default_getHeight) );
        
        }
        { //::FormFactorTetrahedron::getLength
        
            typedef double ( ::FormFactorTetrahedron::*getLength_function_type)(  ) const;
            typedef double ( FormFactorTetrahedron_wrapper::*default_getLength_function_type)(  ) const;
            
            FormFactorTetrahedron_exposer.def( 
                "getLength"
                , getLength_function_type(&::FormFactorTetrahedron::getLength)
                , default_getLength_function_type(&FormFactorTetrahedron_wrapper::default_getLength) );
        
        }
        { //::FormFactorTetrahedron::getNumberOfStochasticParameters
        
            typedef int ( ::FormFactorTetrahedron::*getNumberOfStochasticParameters_function_type)(  ) const;
            typedef int ( FormFactorTetrahedron_wrapper::*default_getNumberOfStochasticParameters_function_type)(  ) const;
            
            FormFactorTetrahedron_exposer.def( 
                "getNumberOfStochasticParameters"
                , getNumberOfStochasticParameters_function_type(&::FormFactorTetrahedron::getNumberOfStochasticParameters)
                , default_getNumberOfStochasticParameters_function_type(&FormFactorTetrahedron_wrapper::default_getNumberOfStochasticParameters) );
        
        }
        { //::FormFactorTetrahedron::setAlpha
        
            typedef void ( ::FormFactorTetrahedron::*setAlpha_function_type)( double ) ;
            typedef void ( FormFactorTetrahedron_wrapper::*default_setAlpha_function_type)( double ) ;
            
            FormFactorTetrahedron_exposer.def( 
                "setAlpha"
                , setAlpha_function_type(&::FormFactorTetrahedron::setAlpha)
                , default_setAlpha_function_type(&FormFactorTetrahedron_wrapper::default_setAlpha)
                , ( bp::arg("alpha") ) );
        
        }
        { //::FormFactorTetrahedron::setHeight
        
            typedef void ( ::FormFactorTetrahedron::*setHeight_function_type)( double ) ;
            typedef void ( FormFactorTetrahedron_wrapper::*default_setHeight_function_type)( double ) ;
            
            FormFactorTetrahedron_exposer.def( 
                "setHeight"
                , setHeight_function_type(&::FormFactorTetrahedron::setHeight)
                , default_setHeight_function_type(&FormFactorTetrahedron_wrapper::default_setHeight)
                , ( bp::arg("height") ) );
        
        }
        { //::FormFactorTetrahedron::setLength
        
            typedef void ( ::FormFactorTetrahedron::*setLength_function_type)( double ) ;
            typedef void ( FormFactorTetrahedron_wrapper::*default_setLength_function_type)( double ) ;
            
            FormFactorTetrahedron_exposer.def( 
                "setLength"
                , setLength_function_type(&::FormFactorTetrahedron::setLength)
                , default_setLength_function_type(&FormFactorTetrahedron_wrapper::default_setLength)
                , ( bp::arg("length") ) );
        
        }
        { //::IParameterized::areParametersChanged
        
            typedef bool ( ::IParameterized::*areParametersChanged_function_type)(  ) ;
            typedef bool ( FormFactorTetrahedron_wrapper::*default_areParametersChanged_function_type)(  ) ;
            
            FormFactorTetrahedron_exposer.def( 
                "areParametersChanged"
                , areParametersChanged_function_type(&::IParameterized::areParametersChanged)
                , default_areParametersChanged_function_type(&FormFactorTetrahedron_wrapper::default_areParametersChanged) );
        
        }
        { //::IParameterized::clearParameterPool
        
            typedef void ( ::IParameterized::*clearParameterPool_function_type)(  ) ;
            typedef void ( FormFactorTetrahedron_wrapper::*default_clearParameterPool_function_type)(  ) ;
            
            FormFactorTetrahedron_exposer.def( 
                "clearParameterPool"
                , clearParameterPool_function_type(&::IParameterized::clearParameterPool)
                , default_clearParameterPool_function_type(&FormFactorTetrahedron_wrapper::default_clearParameterPool) );
        
        }
        { //::ISample::cloneInvertB
        
            typedef ::ISample * ( ::ISample::*cloneInvertB_function_type)(  ) const;
            typedef ::ISample * ( FormFactorTetrahedron_wrapper::*default_cloneInvertB_function_type)(  ) const;
            
            FormFactorTetrahedron_exposer.def( 
                "cloneInvertB"
                , cloneInvertB_function_type(&::ISample::cloneInvertB)
                , default_cloneInvertB_function_type(&FormFactorTetrahedron_wrapper::default_cloneInvertB)
                , bp::return_value_policy< bp::reference_existing_object >() );
        
        }
        { //::ISample::containsMagneticMaterial
        
            typedef bool ( ::ISample::*containsMagneticMaterial_function_type)(  ) const;
            typedef bool ( FormFactorTetrahedron_wrapper::*default_containsMagneticMaterial_function_type)(  ) const;
            
            FormFactorTetrahedron_exposer.def( 
                "containsMagneticMaterial"
                , containsMagneticMaterial_function_type(&::ISample::containsMagneticMaterial)
                , default_containsMagneticMaterial_function_type(&FormFactorTetrahedron_wrapper::default_containsMagneticMaterial) );
        
        }
        { //::IFormFactor::createDistributedFormFactors
        
            typedef void ( ::IFormFactor::*createDistributedFormFactors_function_type)( ::std::vector< IFormFactor* > &,::std::vector< double > &,::std::size_t ) const;
            typedef void ( FormFactorTetrahedron_wrapper::*default_createDistributedFormFactors_function_type)( ::std::vector< IFormFactor* > &,::std::vector< double > &,::std::size_t ) const;
            
            FormFactorTetrahedron_exposer.def( 
                "createDistributedFormFactors"
                , createDistributedFormFactors_function_type(&::IFormFactor::createDistributedFormFactors)
                , default_createDistributedFormFactors_function_type(&FormFactorTetrahedron_wrapper::default_createDistributedFormFactors)
                , ( bp::arg("form_factors"), bp::arg("probabilities"), bp::arg("nbr_samples") )
                , bp::return_value_policy< bp::manage_new_object >() );
        
        }
        { //::IParameterized::createParameterTree
        
            typedef ::ParameterPool * ( ::IParameterized::*createParameterTree_function_type)(  ) const;
            typedef ::ParameterPool * ( FormFactorTetrahedron_wrapper::*default_createParameterTree_function_type)(  ) const;
            
            FormFactorTetrahedron_exposer.def( 
                "createParameterTree"
                , createParameterTree_function_type(&::IParameterized::createParameterTree)
                , default_createParameterTree_function_type(&FormFactorTetrahedron_wrapper::default_createParameterTree)
                , bp::return_value_policy< bp::manage_new_object >() );
        
        }
        { //::IFormFactorBorn::evaluate
        
            typedef ::complex_t ( ::IFormFactorBorn::*evaluate_function_type)( ::cvector_t const &,::Bin1DCVector const &,::Bin1D const & ) const;
            typedef ::complex_t ( FormFactorTetrahedron_wrapper::*default_evaluate_function_type)( ::cvector_t const &,::Bin1DCVector const &,::Bin1D const & ) const;
            
            FormFactorTetrahedron_exposer.def( 
                "evaluate"
                , evaluate_function_type(&::IFormFactorBorn::evaluate)
                , default_evaluate_function_type(&FormFactorTetrahedron_wrapper::default_evaluate)
                , ( bp::arg("k_i"), bp::arg("k_f_bin"), bp::arg("alpha_f_bin") ) );
        
        }
        { //::ISample::getCompositeSample
        
            typedef ::ICompositeSample * ( ::ISample::*getCompositeSample_function_type)(  ) ;
            typedef ::ICompositeSample * ( FormFactorTetrahedron_wrapper::*default_getCompositeSample_function_type)(  ) ;
            
            FormFactorTetrahedron_exposer.def( 
                "getCompositeSample"
                , getCompositeSample_function_type(&::ISample::getCompositeSample)
                , default_getCompositeSample_function_type(&FormFactorTetrahedron_wrapper::default_getCompositeSample)
                , bp::return_value_policy< bp::reference_existing_object >() );
        
        }
        { //::ISample::getCompositeSample
        
            typedef ::ICompositeSample const * ( ::ISample::*getCompositeSample_function_type)(  ) const;
            typedef ::ICompositeSample const * ( FormFactorTetrahedron_wrapper::*default_getCompositeSample_function_type)(  ) const;
            
            FormFactorTetrahedron_exposer.def( 
                "getCompositeSample"
                , getCompositeSample_function_type(&::ISample::getCompositeSample)
                , default_getCompositeSample_function_type(&FormFactorTetrahedron_wrapper::default_getCompositeSample)
                , bp::return_value_policy< bp::reference_existing_object >() );
        
        }
        { //::IFormFactor::getRadius
        
            typedef double ( ::IFormFactor::*getRadius_function_type)(  ) const;
            typedef double ( FormFactorTetrahedron_wrapper::*default_getRadius_function_type)(  ) const;
            
            FormFactorTetrahedron_exposer.def( 
                "getRadius"
                , getRadius_function_type(&::IFormFactor::getRadius)
                , default_getRadius_function_type(&FormFactorTetrahedron_wrapper::default_getRadius) );
        
        }
        { //::IFormFactorBorn::getVolume
        
            typedef double ( ::IFormFactorBorn::*getVolume_function_type)(  ) const;
            typedef double ( FormFactorTetrahedron_wrapper::*default_getVolume_function_type)(  ) const;
            
            FormFactorTetrahedron_exposer.def( 
                "getVolume"
                , getVolume_function_type(&::IFormFactorBorn::getVolume)
                , default_getVolume_function_type(&FormFactorTetrahedron_wrapper::default_getVolume) );
        
        }
        { //::IFormFactor::isDistributedFormFactor
        
            typedef bool ( ::IFormFactor::*isDistributedFormFactor_function_type)(  ) const;
            typedef bool ( FormFactorTetrahedron_wrapper::*default_isDistributedFormFactor_function_type)(  ) const;
            
            FormFactorTetrahedron_exposer.def( 
                "isDistributedFormFactor"
                , isDistributedFormFactor_function_type(&::IFormFactor::isDistributedFormFactor)
                , default_isDistributedFormFactor_function_type(&FormFactorTetrahedron_wrapper::default_isDistributedFormFactor) );
        
        }
        { //::ISample::preprocess
        
            typedef bool ( ::ISample::*preprocess_function_type)(  ) ;
            typedef bool ( FormFactorTetrahedron_wrapper::*default_preprocess_function_type)(  ) ;
            
            FormFactorTetrahedron_exposer.def( 
                "preprocess"
                , preprocess_function_type(&::ISample::preprocess)
                , default_preprocess_function_type(&FormFactorTetrahedron_wrapper::default_preprocess) );
        
        }
        { //::IParameterized::printParameters
        
            typedef void ( ::IParameterized::*printParameters_function_type)(  ) const;
            typedef void ( FormFactorTetrahedron_wrapper::*default_printParameters_function_type)(  ) const;
            
            FormFactorTetrahedron_exposer.def( 
                "printParameters"
                , printParameters_function_type(&::IParameterized::printParameters)
                , default_printParameters_function_type(&FormFactorTetrahedron_wrapper::default_printParameters) );
        
        }
        { //::ISample::printSampleTree
        
            typedef void ( ::ISample::*printSampleTree_function_type)(  ) ;
            typedef void ( FormFactorTetrahedron_wrapper::*default_printSampleTree_function_type)(  ) ;
            
            FormFactorTetrahedron_exposer.def( 
                "printSampleTree"
                , printSampleTree_function_type(&::ISample::printSampleTree)
                , default_printSampleTree_function_type(&FormFactorTetrahedron_wrapper::default_printSampleTree) );
        
        }
        { //::IParameterized::registerParameter
        
            typedef void ( *default_registerParameter_function_type )( ::IParameterized &,::std::string const &,long unsigned int );
            
            FormFactorTetrahedron_exposer.def( 
                "registerParameter"
                , default_registerParameter_function_type( &FormFactorTetrahedron_wrapper::default_registerParameter )
                , ( bp::arg("inst"), bp::arg("name"), bp::arg("parpointer") ) );
        
        }
        { //::IParameterized::setParameterValue
        
            typedef bool ( ::IParameterized::*setParameterValue_function_type)( ::std::string const &,double ) ;
            typedef bool ( FormFactorTetrahedron_wrapper::*default_setParameterValue_function_type)( ::std::string const &,double ) ;
            
            FormFactorTetrahedron_exposer.def( 
                "setParameterValue"
                , setParameterValue_function_type(&::IParameterized::setParameterValue)
                , default_setParameterValue_function_type(&FormFactorTetrahedron_wrapper::default_setParameterValue)
                , ( bp::arg("name"), bp::arg("value") ) );
        
        }
        { //::IParameterized::setParametersAreChanged
        
            typedef void ( ::IParameterized::*setParametersAreChanged_function_type)(  ) ;
            typedef void ( FormFactorTetrahedron_wrapper::*default_setParametersAreChanged_function_type)(  ) ;
            
            FormFactorTetrahedron_exposer.def( 
                "setParametersAreChanged"
                , setParametersAreChanged_function_type(&::IParameterized::setParametersAreChanged)
                , default_setParametersAreChanged_function_type(&FormFactorTetrahedron_wrapper::default_setParametersAreChanged) );
        
        }
        { //::ICloneable::transferToCPP
        
            typedef void ( ::ICloneable::*transferToCPP_function_type)(  ) ;
            typedef void ( FormFactorTetrahedron_wrapper::*default_transferToCPP_function_type)(  ) ;
            
            FormFactorTetrahedron_exposer.def( 
                "transferToCPP"
                , transferToCPP_function_type(&::ICloneable::transferToCPP)
                , default_transferToCPP_function_type(&FormFactorTetrahedron_wrapper::default_transferToCPP) );
        
        }
    }

}
