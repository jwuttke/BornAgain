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
#include "SquaredFunctionSimError.pypp.h"

namespace bp = boost::python;

struct SquaredFunctionSimError_wrapper : SquaredFunctionSimError, bp::wrapper< SquaredFunctionSimError > {

    SquaredFunctionSimError_wrapper( )
    : SquaredFunctionSimError( )
      , bp::wrapper< SquaredFunctionSimError >(){
        // null constructor
    m_pyobj = 0;
    }

    virtual double calculateSquaredDifference( double real_value, double simulated_value ) const  {
        if( bp::override func_calculateSquaredDifference = this->get_override( "calculateSquaredDifference" ) )
            return func_calculateSquaredDifference( real_value, simulated_value );
        else{
            return this->SquaredFunctionSimError::calculateSquaredDifference( real_value, simulated_value );
        }
    }
    
    double default_calculateSquaredDifference( double real_value, double simulated_value ) const  {
        return SquaredFunctionSimError::calculateSquaredDifference( real_value, simulated_value );
    }

    virtual double calculateSquaredError( double real_value, double simulated_value ) const  {
        if( bp::override func_calculateSquaredError = this->get_override( "calculateSquaredError" ) )
            return func_calculateSquaredError( real_value, simulated_value );
        else{
            return this->SquaredFunctionSimError::calculateSquaredError( real_value, simulated_value );
        }
    }
    
    double default_calculateSquaredError( double real_value, double simulated_value ) const  {
        return SquaredFunctionSimError::calculateSquaredError( real_value, simulated_value );
    }

    virtual ::SquaredFunctionSimError * clone(  ) const  {
        if( bp::override func_clone = this->get_override( "clone" ) )
            return func_clone(  );
        else{
            return this->SquaredFunctionSimError::clone(  );
        }
    }
    
    ::SquaredFunctionSimError * default_clone(  ) const  {
        return SquaredFunctionSimError::clone( );
    }

    PyObject* m_pyobj;

};

void register_SquaredFunctionSimError_class(){

    { //::SquaredFunctionSimError
        typedef bp::class_< SquaredFunctionSimError_wrapper, bp::bases< ISquaredFunction >, std::auto_ptr< SquaredFunctionSimError_wrapper >, boost::noncopyable > SquaredFunctionSimError_exposer_t;
        SquaredFunctionSimError_exposer_t SquaredFunctionSimError_exposer = SquaredFunctionSimError_exposer_t( "SquaredFunctionSimError", bp::init< >() );
        bp::scope SquaredFunctionSimError_scope( SquaredFunctionSimError_exposer );
        { //::SquaredFunctionSimError::calculateSquaredDifference
        
            typedef double ( ::SquaredFunctionSimError::*calculateSquaredDifference_function_type)( double,double ) const;
            typedef double ( SquaredFunctionSimError_wrapper::*default_calculateSquaredDifference_function_type)( double,double ) const;
            
            SquaredFunctionSimError_exposer.def( 
                "calculateSquaredDifference"
                , calculateSquaredDifference_function_type(&::SquaredFunctionSimError::calculateSquaredDifference)
                , default_calculateSquaredDifference_function_type(&SquaredFunctionSimError_wrapper::default_calculateSquaredDifference)
                , ( bp::arg("real_value"), bp::arg("simulated_value") ) );
        
        }
        { //::SquaredFunctionSimError::calculateSquaredError
        
            typedef double ( ::SquaredFunctionSimError::*calculateSquaredError_function_type)( double,double ) const;
            typedef double ( SquaredFunctionSimError_wrapper::*default_calculateSquaredError_function_type)( double,double ) const;
            
            SquaredFunctionSimError_exposer.def( 
                "calculateSquaredError"
                , calculateSquaredError_function_type(&::SquaredFunctionSimError::calculateSquaredError)
                , default_calculateSquaredError_function_type(&SquaredFunctionSimError_wrapper::default_calculateSquaredError)
                , ( bp::arg("real_value"), bp::arg("simulated_value") ) );
        
        }
        { //::SquaredFunctionSimError::clone
        
            typedef ::SquaredFunctionSimError * ( ::SquaredFunctionSimError::*clone_function_type)(  ) const;
            typedef ::SquaredFunctionSimError * ( SquaredFunctionSimError_wrapper::*default_clone_function_type)(  ) const;
            
            SquaredFunctionSimError_exposer.def( 
                "clone"
                , clone_function_type(&::SquaredFunctionSimError::clone)
                , default_clone_function_type(&SquaredFunctionSimError_wrapper::default_clone)
                , bp::return_value_policy< bp::manage_new_object >() );
        
        }
    }

}
