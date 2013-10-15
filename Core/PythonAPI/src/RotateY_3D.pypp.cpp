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
#include "RotateY_3D.pypp.h"

namespace bp = boost::python;

struct RotateY_3D_wrapper : Geometry::RotateY_3D, bp::wrapper< Geometry::RotateY_3D > {

    RotateY_3D_wrapper(Geometry::RotateY_3D const & arg )
    : Geometry::RotateY_3D( arg )
      , bp::wrapper< Geometry::RotateY_3D >(){
        // copy constructor
        
    }

    RotateY_3D_wrapper(double a )
    : Geometry::RotateY_3D( a )
      , bp::wrapper< Geometry::RotateY_3D >(){
        // constructor
    
    }

    virtual void print( ::std::ostream & ostr ) const  {
        if( bp::override func_print = this->get_override( "print" ) )
            func_print( boost::ref(ostr) );
        else
            this->Geometry::RotateY_3D::print( boost::ref(ostr) );
    }
    
    
    void default_print( ::std::ostream & ostr ) const  {
        Geometry::RotateY_3D::print( boost::ref(ostr) );
    }

};

void register_RotateY_3D_class(){

    { //::Geometry::RotateY_3D
        typedef bp::class_< RotateY_3D_wrapper, bp::bases< Geometry::ITransform3D > > RotateY_3D_exposer_t;
        RotateY_3D_exposer_t RotateY_3D_exposer = RotateY_3D_exposer_t( "RotateY_3D", bp::init< double >(( bp::arg("a") )) );
        bp::scope RotateY_3D_scope( RotateY_3D_exposer );
        { //::Geometry::RotateY_3D::print
        
            typedef void ( ::Geometry::RotateY_3D::*print_function_type )( ::std::ostream & ) const;
            typedef void ( RotateY_3D_wrapper::*default_print_function_type )( ::std::ostream & ) const;
            
            RotateY_3D_exposer.def( 
                "print"
                , print_function_type(&::Geometry::RotateY_3D::print)
                , default_print_function_type(&RotateY_3D_wrapper::default_print)
                , ( bp::arg("ostr") ) );
        
        }
    }

}
