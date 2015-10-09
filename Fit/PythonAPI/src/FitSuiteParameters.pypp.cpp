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
#include "FitSuiteParameters.pypp.h"

namespace bp = boost::python;

void register_FitSuiteParameters_class(){

    { //::FitSuiteParameters
        typedef bp::class_< FitSuiteParameters > FitSuiteParameters_exposer_t;
        FitSuiteParameters_exposer_t FitSuiteParameters_exposer = FitSuiteParameters_exposer_t( "FitSuiteParameters", "Holds vector of parameters for FitSuit.", bp::init< >() );
        bp::scope FitSuiteParameters_scope( FitSuiteParameters_exposer );
        { //::FitSuiteParameters::addParameter
        
            typedef void ( ::FitSuiteParameters::*addParameter_function_type)( ::std::string const &,double,double,::AttLimits const &,double ) ;
            
            FitSuiteParameters_exposer.def( 
                "addParameter"
                , addParameter_function_type( &::FitSuiteParameters::addParameter )
                , ( bp::arg("name"), bp::arg("value"), bp::arg("step"), bp::arg("attlim"), bp::arg("error")=0.0 )
                , "Adds fit parameter." );
        
        }
        { //::FitSuiteParameters::clear
        
            typedef void ( ::FitSuiteParameters::*clear_function_type)(  ) ;
            
            FitSuiteParameters_exposer.def( 
                "clear"
                , clear_function_type( &::FitSuiteParameters::clear )
                , "clear all defined parameters." );
        
        }
        { //::FitSuiteParameters::fixAll
        
            typedef void ( ::FitSuiteParameters::*fixAll_function_type)(  ) ;
            
            FitSuiteParameters_exposer.def( 
                "fixAll"
                , fixAll_function_type( &::FitSuiteParameters::fixAll )
                , "Fix all parameters." );
        
        }
        { //::FitSuiteParameters::getErrors
        
            typedef ::std::vector< double > ( ::FitSuiteParameters::*getErrors_function_type)(  ) const;
            
            FitSuiteParameters_exposer.def( 
                "getErrors"
                , getErrors_function_type( &::FitSuiteParameters::getErrors )
                , "Returns errors of all defined parameters." );
        
        }
        { //::FitSuiteParameters::getNfreeParameters
        
            typedef ::std::size_t ( ::FitSuiteParameters::*getNfreeParameters_function_type)(  ) const;
            
            FitSuiteParameters_exposer.def( 
                "getNfreeParameters"
                , getNfreeParameters_function_type( &::FitSuiteParameters::getNfreeParameters )
                , "Returns number of free parameters." );
        
        }
        { //::FitSuiteParameters::getParameter
        
            typedef ::FitParameter const * ( ::FitSuiteParameters::*getParameter_function_type)( ::std::string const & ) const;
            
            FitSuiteParameters_exposer.def( 
                "getParameter"
                , getParameter_function_type( &::FitSuiteParameters::getParameter )
                , ( bp::arg("name") )
                , bp::return_value_policy< bp::reference_existing_object >()
                , "Returns fit parameter with given name." );
        
        }
        { //::FitSuiteParameters::getParameter
        
            typedef ::FitParameter * ( ::FitSuiteParameters::*getParameter_function_type)( ::std::string const & ) ;
            
            FitSuiteParameters_exposer.def( 
                "getParameter"
                , getParameter_function_type( &::FitSuiteParameters::getParameter )
                , ( bp::arg("name") )
                , bp::return_value_policy< bp::reference_existing_object >()
                , "Returns fit parameter with given name." );
        
        }
        { //::FitSuiteParameters::getValues
        
            typedef ::std::vector< double > ( ::FitSuiteParameters::*getValues_function_type)(  ) const;
            
            FitSuiteParameters_exposer.def( 
                "getValues"
                , getValues_function_type( &::FitSuiteParameters::getValues )
                , "Returns values of all defined parameters." );
        
        }
        { //::FitSuiteParameters::operator[]
        
            typedef ::FitParameter const * ( ::FitSuiteParameters::*__getitem___function_type)( ::std::size_t ) const;
            
            FitSuiteParameters_exposer.def( 
                "__getitem__"
                , __getitem___function_type( &::FitSuiteParameters::operator[] )
                , ( bp::arg("index") )
                , bp::return_internal_reference< >()
                , "access to parameters by index." );
        
        }
        { //::FitSuiteParameters::operator[]
        
            typedef ::FitParameter * ( ::FitSuiteParameters::*__getitem___function_type)( ::std::size_t ) ;
            
            FitSuiteParameters_exposer.def( 
                "__getitem__"
                , __getitem___function_type( &::FitSuiteParameters::operator[] )
                , ( bp::arg("index") )
                , bp::return_internal_reference< >()
                , "access to parameters by index." );
        
        }
        { //::FitSuiteParameters::operator[]
        
            typedef ::FitParameter const * ( ::FitSuiteParameters::*__getitem___function_type)( ::std::string ) const;
            
            FitSuiteParameters_exposer.def( 
                "__getitem__"
                , __getitem___function_type( &::FitSuiteParameters::operator[] )
                , ( bp::arg("name") )
                , bp::return_internal_reference< >()
                , "access to parameters by parameter name." );
        
        }
        { //::FitSuiteParameters::operator[]
        
            typedef ::FitParameter * ( ::FitSuiteParameters::*__getitem___function_type)( ::std::string ) ;
            
            FitSuiteParameters_exposer.def( 
                "__getitem__"
                , __getitem___function_type( &::FitSuiteParameters::operator[] )
                , ( bp::arg("name") )
                , bp::return_internal_reference< >()
                , "access to parameters by parameter name." );
        
        }
        { //::FitSuiteParameters::printParameters
        
            typedef void ( ::FitSuiteParameters::*printParameters_function_type)(  ) const;
            
            FitSuiteParameters_exposer.def( 
                "printParameters"
                , printParameters_function_type( &::FitSuiteParameters::printParameters )
                , "Print defined parameters." );
        
        }
        { //::FitSuiteParameters::releaseAll
        
            typedef void ( ::FitSuiteParameters::*releaseAll_function_type)(  ) ;
            
            FitSuiteParameters_exposer.def( 
                "releaseAll"
                , releaseAll_function_type( &::FitSuiteParameters::releaseAll )
                , "Release all parameters." );
        
        }
        { //::FitSuiteParameters::setErrors
        
            typedef void ( ::FitSuiteParameters::*setErrors_function_type)( ::std::vector< double > const & ) ;
            
            FitSuiteParameters_exposer.def( 
                "setErrors"
                , setErrors_function_type( &::FitSuiteParameters::setErrors )
                , ( bp::arg("pars_errors") )
                , "set errors to all parameters." );
        
        }
        { //::FitSuiteParameters::setParametersFixed
        
            typedef void ( ::FitSuiteParameters::*setParametersFixed_function_type)( ::std::vector< std::string > const &,bool ) ;
            
            FitSuiteParameters_exposer.def( 
                "setParametersFixed"
                , setParametersFixed_function_type( &::FitSuiteParameters::setParametersFixed )
                , ( bp::arg("pars"), bp::arg("is_fixed") )
                , "Set fixed flag for parameters from the list." );
        
        }
        { //::FitSuiteParameters::setValues
        
            typedef void ( ::FitSuiteParameters::*setValues_function_type)( ::std::vector< double > const & ) ;
            
            FitSuiteParameters_exposer.def( 
                "setValues"
                , setValues_function_type( &::FitSuiteParameters::setValues )
                , ( bp::arg("pars_values") )
                , "Sets values for all defined parameters." );
        
        }
        { //::FitSuiteParameters::size
        
            typedef ::std::size_t ( ::FitSuiteParameters::*size_function_type)(  ) const;
            
            FitSuiteParameters_exposer.def( 
                "size"
                , size_function_type( &::FitSuiteParameters::size )
                , "Returns number of parameters." );
        
        }
    }

}
