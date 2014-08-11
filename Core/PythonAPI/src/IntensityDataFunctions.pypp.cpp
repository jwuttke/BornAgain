// This file has been generated by Py++.

// BornAgain: simulate and fit scattering at grazing incidence
//! @brief Automatically generated boost::python code for PythonCoreAPI

#include "Macros.h"
GCC_DIAG_OFF(unused-parameter)
GCC_DIAG_OFF(missing-field-initializers)
#include "boost/python.hpp"
GCC_DIAG_ON(unused-parameter)
GCC_DIAG_ON(missing-field-initializers)
#include "PythonCoreList.h"
#include "IntensityDataFunctions.pypp.h"

namespace bp = boost::python;

void register_IntensityDataFunctions_class(){

    { //::IntensityDataFunctions
        typedef bp::class_< IntensityDataFunctions > IntensityDataFunctions_exposer_t;
        IntensityDataFunctions_exposer_t IntensityDataFunctions_exposer = IntensityDataFunctions_exposer_t( "IntensityDataFunctions" );
        bp::scope IntensityDataFunctions_scope( IntensityDataFunctions_exposer );
        { //::IntensityDataFunctions::GetRelativeDifference
        
            typedef double ( *GetRelativeDifference_function_type )( ::OutputData< double > const &,::OutputData< double > const & );
            
            IntensityDataFunctions_exposer.def( 
                "GetRelativeDifference"
                , GetRelativeDifference_function_type( &::IntensityDataFunctions::GetRelativeDifference )
                , ( bp::arg("result"), bp::arg("reference") ) );
        
        }
        { //::IntensityDataFunctions::createClippedDataSet
        
            typedef ::OutputData< double > * ( *createClippedDataSet_function_type )( ::OutputData< double > const &,double,double,double,double );
            
            IntensityDataFunctions_exposer.def( 
                "createClippedDataSet"
                , createClippedDataSet_function_type( &::IntensityDataFunctions::createClippedDataSet )
                , ( bp::arg("origin"), bp::arg("x1"), bp::arg("y1"), bp::arg("x2"), bp::arg("y2") )
                , bp::return_value_policy< bp::manage_new_object >() );
        
        }
        { //::IntensityDataFunctions::setEllipticMask
        
            typedef void ( *setEllipticMask_function_type )( ::OutputData< double > &,double,double,double,double );
            
            IntensityDataFunctions_exposer.def( 
                "setEllipticMask"
                , setEllipticMask_function_type( &::IntensityDataFunctions::setEllipticMask )
                , ( bp::arg("data"), bp::arg("xc"), bp::arg("yc"), bp::arg("rx"), bp::arg("ry") ) );
        
        }
        { //::IntensityDataFunctions::setRectangularMask
        
            typedef void ( *setRectangularMask_function_type )( ::OutputData< double > &,double,double,double,double );
            
            IntensityDataFunctions_exposer.def( 
                "setRectangularMask"
                , setRectangularMask_function_type( &::IntensityDataFunctions::setRectangularMask )
                , ( bp::arg("data"), bp::arg("x1"), bp::arg("y1"), bp::arg("x2"), bp::arg("y2") ) );
        
        }
        IntensityDataFunctions_exposer.staticmethod( "GetRelativeDifference" );
        IntensityDataFunctions_exposer.staticmethod( "createClippedDataSet" );
        IntensityDataFunctions_exposer.staticmethod( "setEllipticMask" );
        IntensityDataFunctions_exposer.staticmethod( "setRectangularMask" );
    }

}
