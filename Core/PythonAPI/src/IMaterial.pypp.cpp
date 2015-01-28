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
#include "PythonCoreList.h"
#include "IMaterial.pypp.h"

namespace bp = boost::python;

struct IMaterial_wrapper : IMaterial, bp::wrapper< IMaterial > {

    IMaterial_wrapper(IMaterial const & arg )
    : IMaterial( arg )
      , bp::wrapper< IMaterial >(){
        // copy constructor
        m_pyobj = 0;
    }

    IMaterial_wrapper(::std::string const & name )
    : IMaterial( name )
      , bp::wrapper< IMaterial >(){
        // constructor
    m_pyobj = 0;
    }

    virtual ::IMaterial * clone(  ) const  {
        if( bp::override func_clone = this->get_override( "clone" ) )
            return func_clone(  );
        else{
            return this->IMaterial::clone(  );
        }
    }
    
    ::IMaterial * default_clone(  ) const  {
        return IMaterial::clone( );
    }

    virtual ::IMaterial const * createTransformedMaterial( ::Geometry::Transform3D const & transform ) const  {
        if( bp::override func_createTransformedMaterial = this->get_override( "createTransformedMaterial" ) )
            return func_createTransformedMaterial( boost::ref(transform) );
        else{
            return this->IMaterial::createTransformedMaterial( boost::ref(transform) );
        }
    }
    
    ::IMaterial const * default_createTransformedMaterial( ::Geometry::Transform3D const & transform ) const  {
        return IMaterial::createTransformedMaterial( boost::ref(transform) );
    }

    virtual ::complex_t getRefractiveIndex(  ) const  {
        if( bp::override func_getRefractiveIndex = this->get_override( "getRefractiveIndex" ) )
            return func_getRefractiveIndex(  );
        else{
            return this->IMaterial::getRefractiveIndex(  );
        }
    }
    
    ::complex_t default_getRefractiveIndex(  ) const  {
        return IMaterial::getRefractiveIndex( );
    }

    virtual bool isScalarMaterial(  ) const  {
        if( bp::override func_isScalarMaterial = this->get_override( "isScalarMaterial" ) )
            return func_isScalarMaterial(  );
        else{
            return this->IMaterial::isScalarMaterial(  );
        }
    }
    
    bool default_isScalarMaterial(  ) const  {
        return IMaterial::isScalarMaterial( );
    }

    PyObject* m_pyobj;

};

void register_IMaterial_class(){

    { //::IMaterial
        typedef bp::class_< IMaterial_wrapper, std::auto_ptr< IMaterial_wrapper > > IMaterial_exposer_t;
        IMaterial_exposer_t IMaterial_exposer = IMaterial_exposer_t( "IMaterial", bp::init< std::string const & >(( bp::arg("name") )) );
        bp::scope IMaterial_scope( IMaterial_exposer );
        { //::IMaterial::clone
        
            typedef ::IMaterial * ( ::IMaterial::*clone_function_type)(  ) const;
            typedef ::IMaterial * ( IMaterial_wrapper::*default_clone_function_type)(  ) const;
            
            IMaterial_exposer.def( 
                "clone"
                , clone_function_type(&::IMaterial::clone)
                , default_clone_function_type(&IMaterial_wrapper::default_clone)
                , bp::return_value_policy< bp::manage_new_object >() );
        
        }
        { //::IMaterial::createTransformedMaterial
        
            typedef ::IMaterial const * ( ::IMaterial::*createTransformedMaterial_function_type)( ::Geometry::Transform3D const & ) const;
            typedef ::IMaterial const * ( IMaterial_wrapper::*default_createTransformedMaterial_function_type)( ::Geometry::Transform3D const & ) const;
            
            IMaterial_exposer.def( 
                "createTransformedMaterial"
                , createTransformedMaterial_function_type(&::IMaterial::createTransformedMaterial)
                , default_createTransformedMaterial_function_type(&IMaterial_wrapper::default_createTransformedMaterial)
                , ( bp::arg("transform") )
                , bp::return_value_policy< bp::manage_new_object >() );
        
        }
        { //::IMaterial::getRefractiveIndex
        
            typedef ::complex_t ( ::IMaterial::*getRefractiveIndex_function_type)(  ) const;
            typedef ::complex_t ( IMaterial_wrapper::*default_getRefractiveIndex_function_type)(  ) const;
            
            IMaterial_exposer.def( 
                "getRefractiveIndex"
                , getRefractiveIndex_function_type(&::IMaterial::getRefractiveIndex)
                , default_getRefractiveIndex_function_type(&IMaterial_wrapper::default_getRefractiveIndex) );
        
        }
        { //::IMaterial::isScalarMaterial
        
            typedef bool ( ::IMaterial::*isScalarMaterial_function_type)(  ) const;
            typedef bool ( IMaterial_wrapper::*default_isScalarMaterial_function_type)(  ) const;
            
            IMaterial_exposer.def( 
                "isScalarMaterial"
                , isScalarMaterial_function_type(&::IMaterial::isScalarMaterial)
                , default_isScalarMaterial_function_type(&IMaterial_wrapper::default_isScalarMaterial) );
        
        }
    }

}
