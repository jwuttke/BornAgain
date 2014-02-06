// This file has been generated by Py++.

// BornAgain: simulate and fit scattering at grazing incidence 
//! @brief automatically generated boost::python code for PythonCoreAPI  

#include "Macros.h"
GCC_DIAG_OFF(unused-parameter);
GCC_DIAG_OFF(missing-field-initializers);
#include "boost/python.hpp"
GCC_DIAG_ON(unused-parameter);
GCC_DIAG_ON(missing-field-initializers);
#include "PythonCoreList.h"
#include "IAxis.pypp.h"

namespace bp = boost::python;

struct IAxis_wrapper : IAxis, bp::wrapper< IAxis > {

    IAxis_wrapper(::std::string name )
    : IAxis( name )
      , bp::wrapper< IAxis >(){
        // constructor
    
    }

    virtual ::IAxis * clone(  ) const {
        bp::override func_clone = this->get_override( "clone" );
        return func_clone(  );
    }

    virtual ::IAxis * createDoubleBinSize(  ) const {
        bp::override func_createDoubleBinSize = this->get_override( "createDoubleBinSize" );
        return func_createDoubleBinSize(  );
    }

    virtual ::std::size_t findClosestIndex( double value ) const {
        bp::override func_findClosestIndex = this->get_override( "findClosestIndex" );
        return func_findClosestIndex( value );
    }

    virtual ::Bin1D getBin( ::std::size_t index ) const {
        bp::override func_getBin = this->get_override( "getBin" );
        return func_getBin( index );
    }

    virtual double getMax(  ) const {
        bp::override func_getMax = this->get_override( "getMax" );
        return func_getMax(  );
    }

    virtual double getMin(  ) const {
        bp::override func_getMin = this->get_override( "getMin" );
        return func_getMin(  );
    }

    virtual ::std::size_t getSize(  ) const {
        bp::override func_getSize = this->get_override( "getSize" );
        return func_getSize(  );
    }

    virtual double operator[]( ::std::size_t index ) const {
        bp::override func___getitem__ = this->get_override( "__getitem__" );
        return func___getitem__( index );
    }

};

void register_IAxis_class(){

    { //::IAxis
        typedef bp::class_< IAxis_wrapper, boost::noncopyable > IAxis_exposer_t;
        IAxis_exposer_t IAxis_exposer = IAxis_exposer_t( "IAxis", bp::init< std::string >(( bp::arg("name") )) );
        bp::scope IAxis_scope( IAxis_exposer );
        { //::IAxis::clone
        
            typedef ::IAxis * ( ::IAxis::*clone_function_type )(  ) const;
            
            IAxis_exposer.def( 
                "clone"
                , bp::pure_virtual( clone_function_type(&::IAxis::clone) )
                , bp::return_value_policy< bp::manage_new_object >() );
        
        }
        { //::IAxis::createDoubleBinSize
        
            typedef ::IAxis * ( ::IAxis::*createDoubleBinSize_function_type )(  ) const;
            
            IAxis_exposer.def( 
                "createDoubleBinSize"
                , bp::pure_virtual( createDoubleBinSize_function_type(&::IAxis::createDoubleBinSize) )
                , bp::return_value_policy< bp::manage_new_object >() );
        
        }
        { //::IAxis::findClosestIndex
        
            typedef ::std::size_t ( ::IAxis::*findClosestIndex_function_type )( double ) const;
            
            IAxis_exposer.def( 
                "findClosestIndex"
                , bp::pure_virtual( findClosestIndex_function_type(&::IAxis::findClosestIndex) )
                , ( bp::arg("value") ) );
        
        }
        { //::IAxis::getBin
        
            typedef ::Bin1D ( ::IAxis::*getBin_function_type )( ::std::size_t ) const;
            
            IAxis_exposer.def( 
                "getBin"
                , bp::pure_virtual( getBin_function_type(&::IAxis::getBin) )
                , ( bp::arg("index") ) );
        
        }
        { //::IAxis::getMax
        
            typedef double ( ::IAxis::*getMax_function_type )(  ) const;
            
            IAxis_exposer.def( 
                "getMax"
                , bp::pure_virtual( getMax_function_type(&::IAxis::getMax) ) );
        
        }
        { //::IAxis::getMin
        
            typedef double ( ::IAxis::*getMin_function_type )(  ) const;
            
            IAxis_exposer.def( 
                "getMin"
                , bp::pure_virtual( getMin_function_type(&::IAxis::getMin) ) );
        
        }
        { //::IAxis::getName
        
            typedef ::std::string ( ::IAxis::*getName_function_type )(  ) const;
            
            IAxis_exposer.def( 
                "getName"
                , getName_function_type( &::IAxis::getName ) );
        
        }
        { //::IAxis::getSize
        
            typedef ::std::size_t ( ::IAxis::*getSize_function_type )(  ) const;
            
            IAxis_exposer.def( 
                "getSize"
                , bp::pure_virtual( getSize_function_type(&::IAxis::getSize) ) );
        
        }
        { //::IAxis::operator[]
        
            typedef double ( ::IAxis::*__getitem___function_type )( ::std::size_t ) const;
            
            IAxis_exposer.def( 
                "__getitem__"
                , bp::pure_virtual( __getitem___function_type(&::IAxis::operator[]) )
                , ( bp::arg("index") ) );
        
        }
        { //::IAxis::setName
        
            typedef void ( ::IAxis::*setName_function_type )( ::std::string ) ;
            
            IAxis_exposer.def( 
                "setName"
                , setName_function_type( &::IAxis::setName )
                , ( bp::arg("name") ) );
        
        }
    }

}
