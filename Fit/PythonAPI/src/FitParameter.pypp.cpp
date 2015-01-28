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
#include "PythonFitList.h"
#include "FitParameter.pypp.h"

namespace bp = boost::python;

struct FitParameter_wrapper : FitParameter, bp::wrapper< FitParameter > {

    FitParameter_wrapper(FitParameter const & arg )
    : FitParameter( arg )
      , bp::wrapper< FitParameter >(){
        // copy constructor
        
    }

    FitParameter_wrapper( )
    : FitParameter( )
      , bp::wrapper< FitParameter >(){
        // null constructor
    
    }

    FitParameter_wrapper(::std::string const & name, double value, double step=0.0, ::AttLimits const & limits=AttLimits::limitless( ), double error=0.0 )
    : FitParameter( name, value, step, boost::ref(limits), error )
      , bp::wrapper< FitParameter >(){
        // constructor
    
    }

    virtual double getError(  ) const  {
        if( bp::override func_getError = this->get_override( "getError" ) )
            return func_getError(  );
        else{
            return this->FitParameter::getError(  );
        }
    }
    
    double default_getError(  ) const  {
        return FitParameter::getError( );
    }

    virtual double getStep(  ) const  {
        if( bp::override func_getStep = this->get_override( "getStep" ) )
            return func_getStep(  );
        else{
            return this->FitParameter::getStep(  );
        }
    }
    
    double default_getStep(  ) const  {
        return FitParameter::getStep( );
    }

    virtual double getValue(  ) const  {
        if( bp::override func_getValue = this->get_override( "getValue" ) )
            return func_getValue(  );
        else{
            return this->FitParameter::getValue(  );
        }
    }
    
    double default_getValue(  ) const  {
        return FitParameter::getValue( );
    }

    virtual void setError( double value ) {
        if( bp::override func_setError = this->get_override( "setError" ) )
            func_setError( value );
        else{
            this->FitParameter::setError( value );
        }
    }
    
    void default_setError( double value ) {
        FitParameter::setError( value );
    }

    virtual void setStep( double value ) {
        if( bp::override func_setStep = this->get_override( "setStep" ) )
            func_setStep( value );
        else{
            this->FitParameter::setStep( value );
        }
    }
    
    void default_setStep( double value ) {
        FitParameter::setStep( value );
    }

    virtual void setValue( double value ) {
        if( bp::override func_setValue = this->get_override( "setValue" ) )
            func_setValue( value );
        else{
            this->FitParameter::setValue( value );
        }
    }
    
    void default_setValue( double value ) {
        FitParameter::setValue( value );
    }

    virtual double getLowerLimit(  ) const  {
        if( bp::override func_getLowerLimit = this->get_override( "getLowerLimit" ) )
            return func_getLowerLimit(  );
        else{
            return this->AttLimits::getLowerLimit(  );
        }
    }
    
    double default_getLowerLimit(  ) const  {
        return AttLimits::getLowerLimit( );
    }

    virtual double getUpperLimit(  ) const  {
        if( bp::override func_getUpperLimit = this->get_override( "getUpperLimit" ) )
            return func_getUpperLimit(  );
        else{
            return this->AttLimits::getUpperLimit(  );
        }
    }
    
    double default_getUpperLimit(  ) const  {
        return AttLimits::getUpperLimit( );
    }

    virtual bool hasLowerAndUpperLimits(  ) const  {
        if( bp::override func_hasLowerAndUpperLimits = this->get_override( "hasLowerAndUpperLimits" ) )
            return func_hasLowerAndUpperLimits(  );
        else{
            return this->AttLimits::hasLowerAndUpperLimits(  );
        }
    }
    
    bool default_hasLowerAndUpperLimits(  ) const  {
        return AttLimits::hasLowerAndUpperLimits( );
    }

    virtual bool hasLowerLimit(  ) const  {
        if( bp::override func_hasLowerLimit = this->get_override( "hasLowerLimit" ) )
            return func_hasLowerLimit(  );
        else{
            return this->AttLimits::hasLowerLimit(  );
        }
    }
    
    bool default_hasLowerLimit(  ) const  {
        return AttLimits::hasLowerLimit( );
    }

    virtual bool hasUpperLimit(  ) const  {
        if( bp::override func_hasUpperLimit = this->get_override( "hasUpperLimit" ) )
            return func_hasUpperLimit(  );
        else{
            return this->AttLimits::hasUpperLimit(  );
        }
    }
    
    bool default_hasUpperLimit(  ) const  {
        return AttLimits::hasUpperLimit( );
    }

    virtual bool isFixed(  ) const  {
        if( bp::override func_isFixed = this->get_override( "isFixed" ) )
            return func_isFixed(  );
        else{
            return this->AttLimits::isFixed(  );
        }
    }
    
    bool default_isFixed(  ) const  {
        return AttLimits::isFixed( );
    }

    virtual void removeLimits(  ) {
        if( bp::override func_removeLimits = this->get_override( "removeLimits" ) )
            func_removeLimits(  );
        else{
            this->AttLimits::removeLimits(  );
        }
    }
    
    void default_removeLimits(  ) {
        AttLimits::removeLimits( );
    }

    virtual void removeLowerLimit(  ) {
        if( bp::override func_removeLowerLimit = this->get_override( "removeLowerLimit" ) )
            func_removeLowerLimit(  );
        else{
            this->AttLimits::removeLowerLimit(  );
        }
    }
    
    void default_removeLowerLimit(  ) {
        AttLimits::removeLowerLimit( );
    }

    virtual void removeUpperLimit(  ) {
        if( bp::override func_removeUpperLimit = this->get_override( "removeUpperLimit" ) )
            func_removeUpperLimit(  );
        else{
            this->AttLimits::removeUpperLimit(  );
        }
    }
    
    void default_removeUpperLimit(  ) {
        AttLimits::removeUpperLimit( );
    }

    virtual void setFixed( bool is_fixed ) {
        if( bp::override func_setFixed = this->get_override( "setFixed" ) )
            func_setFixed( is_fixed );
        else{
            this->AttLimits::setFixed( is_fixed );
        }
    }
    
    void default_setFixed( bool is_fixed ) {
        AttLimits::setFixed( is_fixed );
    }

    virtual void setLimits( double xmin, double xmax ) {
        if( bp::override func_setLimits = this->get_override( "setLimits" ) )
            func_setLimits( xmin, xmax );
        else{
            this->AttLimits::setLimits( xmin, xmax );
        }
    }
    
    void default_setLimits( double xmin, double xmax ) {
        AttLimits::setLimits( xmin, xmax );
    }

    virtual void setLowerLimit( double value ) {
        if( bp::override func_setLowerLimit = this->get_override( "setLowerLimit" ) )
            func_setLowerLimit( value );
        else{
            this->AttLimits::setLowerLimit( value );
        }
    }
    
    void default_setLowerLimit( double value ) {
        AttLimits::setLowerLimit( value );
    }

    virtual void setUpperLimit( double value ) {
        if( bp::override func_setUpperLimit = this->get_override( "setUpperLimit" ) )
            func_setUpperLimit( value );
        else{
            this->AttLimits::setUpperLimit( value );
        }
    }
    
    void default_setUpperLimit( double value ) {
        AttLimits::setUpperLimit( value );
    }

};

void register_FitParameter_class(){

    { //::FitParameter
        typedef bp::class_< FitParameter_wrapper, bp::bases< INamed, AttLimits > > FitParameter_exposer_t;
        FitParameter_exposer_t FitParameter_exposer = FitParameter_exposer_t( "FitParameter", bp::init< >() );
        bp::scope FitParameter_scope( FitParameter_exposer );
        FitParameter_exposer.def( bp::init< std::string const &, double, bp::optional< double, AttLimits const &, double > >(( bp::arg("name"), bp::arg("value"), bp::arg("step")=0.0, bp::arg("limits")=AttLimits::limitless( ), bp::arg("error")=0.0 )) );
        { //::FitParameter::getError
        
            typedef double ( ::FitParameter::*getError_function_type)(  ) const;
            typedef double ( FitParameter_wrapper::*default_getError_function_type)(  ) const;
            
            FitParameter_exposer.def( 
                "getError"
                , getError_function_type(&::FitParameter::getError)
                , default_getError_function_type(&FitParameter_wrapper::default_getError) );
        
        }
        { //::FitParameter::getStep
        
            typedef double ( ::FitParameter::*getStep_function_type)(  ) const;
            typedef double ( FitParameter_wrapper::*default_getStep_function_type)(  ) const;
            
            FitParameter_exposer.def( 
                "getStep"
                , getStep_function_type(&::FitParameter::getStep)
                , default_getStep_function_type(&FitParameter_wrapper::default_getStep) );
        
        }
        { //::FitParameter::getValue
        
            typedef double ( ::FitParameter::*getValue_function_type)(  ) const;
            typedef double ( FitParameter_wrapper::*default_getValue_function_type)(  ) const;
            
            FitParameter_exposer.def( 
                "getValue"
                , getValue_function_type(&::FitParameter::getValue)
                , default_getValue_function_type(&FitParameter_wrapper::default_getValue) );
        
        }
        { //::FitParameter::setError
        
            typedef void ( ::FitParameter::*setError_function_type)( double ) ;
            typedef void ( FitParameter_wrapper::*default_setError_function_type)( double ) ;
            
            FitParameter_exposer.def( 
                "setError"
                , setError_function_type(&::FitParameter::setError)
                , default_setError_function_type(&FitParameter_wrapper::default_setError)
                , ( bp::arg("value") ) );
        
        }
        { //::FitParameter::setStep
        
            typedef void ( ::FitParameter::*setStep_function_type)( double ) ;
            typedef void ( FitParameter_wrapper::*default_setStep_function_type)( double ) ;
            
            FitParameter_exposer.def( 
                "setStep"
                , setStep_function_type(&::FitParameter::setStep)
                , default_setStep_function_type(&FitParameter_wrapper::default_setStep)
                , ( bp::arg("value") ) );
        
        }
        { //::FitParameter::setValue
        
            typedef void ( ::FitParameter::*setValue_function_type)( double ) ;
            typedef void ( FitParameter_wrapper::*default_setValue_function_type)( double ) ;
            
            FitParameter_exposer.def( 
                "setValue"
                , setValue_function_type(&::FitParameter::setValue)
                , default_setValue_function_type(&FitParameter_wrapper::default_setValue)
                , ( bp::arg("value") ) );
        
        }
        { //::AttLimits::getLowerLimit
        
            typedef double ( ::AttLimits::*getLowerLimit_function_type)(  ) const;
            typedef double ( FitParameter_wrapper::*default_getLowerLimit_function_type)(  ) const;
            
            FitParameter_exposer.def( 
                "getLowerLimit"
                , getLowerLimit_function_type(&::AttLimits::getLowerLimit)
                , default_getLowerLimit_function_type(&FitParameter_wrapper::default_getLowerLimit) );
        
        }
        { //::AttLimits::getUpperLimit
        
            typedef double ( ::AttLimits::*getUpperLimit_function_type)(  ) const;
            typedef double ( FitParameter_wrapper::*default_getUpperLimit_function_type)(  ) const;
            
            FitParameter_exposer.def( 
                "getUpperLimit"
                , getUpperLimit_function_type(&::AttLimits::getUpperLimit)
                , default_getUpperLimit_function_type(&FitParameter_wrapper::default_getUpperLimit) );
        
        }
        { //::AttLimits::hasLowerAndUpperLimits
        
            typedef bool ( ::AttLimits::*hasLowerAndUpperLimits_function_type)(  ) const;
            typedef bool ( FitParameter_wrapper::*default_hasLowerAndUpperLimits_function_type)(  ) const;
            
            FitParameter_exposer.def( 
                "hasLowerAndUpperLimits"
                , hasLowerAndUpperLimits_function_type(&::AttLimits::hasLowerAndUpperLimits)
                , default_hasLowerAndUpperLimits_function_type(&FitParameter_wrapper::default_hasLowerAndUpperLimits) );
        
        }
        { //::AttLimits::hasLowerLimit
        
            typedef bool ( ::AttLimits::*hasLowerLimit_function_type)(  ) const;
            typedef bool ( FitParameter_wrapper::*default_hasLowerLimit_function_type)(  ) const;
            
            FitParameter_exposer.def( 
                "hasLowerLimit"
                , hasLowerLimit_function_type(&::AttLimits::hasLowerLimit)
                , default_hasLowerLimit_function_type(&FitParameter_wrapper::default_hasLowerLimit) );
        
        }
        { //::AttLimits::hasUpperLimit
        
            typedef bool ( ::AttLimits::*hasUpperLimit_function_type)(  ) const;
            typedef bool ( FitParameter_wrapper::*default_hasUpperLimit_function_type)(  ) const;
            
            FitParameter_exposer.def( 
                "hasUpperLimit"
                , hasUpperLimit_function_type(&::AttLimits::hasUpperLimit)
                , default_hasUpperLimit_function_type(&FitParameter_wrapper::default_hasUpperLimit) );
        
        }
        { //::AttLimits::isFixed
        
            typedef bool ( ::AttLimits::*isFixed_function_type)(  ) const;
            typedef bool ( FitParameter_wrapper::*default_isFixed_function_type)(  ) const;
            
            FitParameter_exposer.def( 
                "isFixed"
                , isFixed_function_type(&::AttLimits::isFixed)
                , default_isFixed_function_type(&FitParameter_wrapper::default_isFixed) );
        
        }
        { //::AttLimits::removeLimits
        
            typedef void ( ::AttLimits::*removeLimits_function_type)(  ) ;
            typedef void ( FitParameter_wrapper::*default_removeLimits_function_type)(  ) ;
            
            FitParameter_exposer.def( 
                "removeLimits"
                , removeLimits_function_type(&::AttLimits::removeLimits)
                , default_removeLimits_function_type(&FitParameter_wrapper::default_removeLimits) );
        
        }
        { //::AttLimits::removeLowerLimit
        
            typedef void ( ::AttLimits::*removeLowerLimit_function_type)(  ) ;
            typedef void ( FitParameter_wrapper::*default_removeLowerLimit_function_type)(  ) ;
            
            FitParameter_exposer.def( 
                "removeLowerLimit"
                , removeLowerLimit_function_type(&::AttLimits::removeLowerLimit)
                , default_removeLowerLimit_function_type(&FitParameter_wrapper::default_removeLowerLimit) );
        
        }
        { //::AttLimits::removeUpperLimit
        
            typedef void ( ::AttLimits::*removeUpperLimit_function_type)(  ) ;
            typedef void ( FitParameter_wrapper::*default_removeUpperLimit_function_type)(  ) ;
            
            FitParameter_exposer.def( 
                "removeUpperLimit"
                , removeUpperLimit_function_type(&::AttLimits::removeUpperLimit)
                , default_removeUpperLimit_function_type(&FitParameter_wrapper::default_removeUpperLimit) );
        
        }
        { //::AttLimits::setFixed
        
            typedef void ( ::AttLimits::*setFixed_function_type)( bool ) ;
            typedef void ( FitParameter_wrapper::*default_setFixed_function_type)( bool ) ;
            
            FitParameter_exposer.def( 
                "setFixed"
                , setFixed_function_type(&::AttLimits::setFixed)
                , default_setFixed_function_type(&FitParameter_wrapper::default_setFixed)
                , ( bp::arg("is_fixed") ) );
        
        }
        { //::AttLimits::setLimits
        
            typedef void ( ::AttLimits::*setLimits_function_type)( double,double ) ;
            typedef void ( FitParameter_wrapper::*default_setLimits_function_type)( double,double ) ;
            
            FitParameter_exposer.def( 
                "setLimits"
                , setLimits_function_type(&::AttLimits::setLimits)
                , default_setLimits_function_type(&FitParameter_wrapper::default_setLimits)
                , ( bp::arg("xmin"), bp::arg("xmax") ) );
        
        }
        { //::AttLimits::setLowerLimit
        
            typedef void ( ::AttLimits::*setLowerLimit_function_type)( double ) ;
            typedef void ( FitParameter_wrapper::*default_setLowerLimit_function_type)( double ) ;
            
            FitParameter_exposer.def( 
                "setLowerLimit"
                , setLowerLimit_function_type(&::AttLimits::setLowerLimit)
                , default_setLowerLimit_function_type(&FitParameter_wrapper::default_setLowerLimit)
                , ( bp::arg("value") ) );
        
        }
        { //::AttLimits::setUpperLimit
        
            typedef void ( ::AttLimits::*setUpperLimit_function_type)( double ) ;
            typedef void ( FitParameter_wrapper::*default_setUpperLimit_function_type)( double ) ;
            
            FitParameter_exposer.def( 
                "setUpperLimit"
                , setUpperLimit_function_type(&::AttLimits::setUpperLimit)
                , default_setUpperLimit_function_type(&FitParameter_wrapper::default_setUpperLimit)
                , ( bp::arg("value") ) );
        
        }
    }

}
