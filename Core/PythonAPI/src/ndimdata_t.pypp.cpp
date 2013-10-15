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
#include "ndimdata_t.pypp.h"

namespace bp = boost::python;

void register_ndimdata_t_class(){

    { //::OutputData< double >
        typedef bp::class_< OutputData< double >, boost::noncopyable > ndimdata_t_exposer_t;
        ndimdata_t_exposer_t ndimdata_t_exposer = ndimdata_t_exposer_t( "ndimdata_t", bp::init< >() );
        bp::scope ndimdata_t_scope( ndimdata_t_exposer );
        { //::OutputData< double >::addAxis
        
            typedef OutputData< double > exported_class_t;
            typedef void ( exported_class_t::*addAxis_function_type )( ::IAxis const & ) ;
            
            ndimdata_t_exposer.def( 
                "addAxis"
                , addAxis_function_type( &::OutputData< double >::addAxis )
                , ( bp::arg("new_axis") ) );
        
        }
        { //::OutputData< double >::addAxis
        
            typedef OutputData< double > exported_class_t;
            typedef void ( exported_class_t::*addAxis_function_type )( ::std::string const &,::std::size_t,double,double ) ;
            
            ndimdata_t_exposer.def( 
                "addAxis"
                , addAxis_function_type( &::OutputData< double >::addAxis )
                , ( bp::arg("name"), bp::arg("size"), bp::arg("start"), bp::arg("end") ) );
        
        }
        { //::OutputData< double >::clear
        
            typedef OutputData< double > exported_class_t;
            typedef void ( exported_class_t::*clear_function_type )(  ) ;
            
            ndimdata_t_exposer.def( 
                "clear"
                , clear_function_type( &::OutputData< double >::clear ) );
        
        }
        { //::OutputData< double >::clone
        
            typedef OutputData< double > exported_class_t;
            typedef ::OutputData< double > * ( exported_class_t::*clone_function_type )(  ) const;
            
            ndimdata_t_exposer.def( 
                "clone"
                , clone_function_type( &::OutputData< double >::clone )
                , bp::return_value_policy< bp::manage_new_object >() );
        
        }
        { //::OutputData< double >::copyFrom
        
            typedef OutputData< double > exported_class_t;
            typedef void ( exported_class_t::*copyFrom_function_type )( ::OutputData< double > const & ) ;
            
            ndimdata_t_exposer.def( 
                "copyFrom"
                , copyFrom_function_type( &::OutputData< double >::copyFrom )
                , ( bp::arg("other") ) );
        
        }
        { //::OutputData< double >::getAllSizes
        
            typedef OutputData< double > exported_class_t;
            typedef ::std::vector< unsigned long > ( exported_class_t::*getAllSizes_function_type )(  ) const;
            
            ndimdata_t_exposer.def( 
                "getAllSizes"
                , getAllSizes_function_type( &::OutputData< double >::getAllSizes ) );
        
        }
        { //::OutputData< double >::getAllocatedSize
        
            typedef OutputData< double > exported_class_t;
            typedef ::std::size_t ( exported_class_t::*getAllocatedSize_function_type )(  ) const;
            
            ndimdata_t_exposer.def( 
                "getAllocatedSize"
                , getAllocatedSize_function_type( &::OutputData< double >::getAllocatedSize ) );
        
        }
        { //::OutputData< double >::getAxis
        
            typedef OutputData< double > exported_class_t;
            typedef ::IAxis const * ( exported_class_t::*getAxis_function_type )( ::std::size_t ) const;
            
            ndimdata_t_exposer.def( 
                "getAxis"
                , getAxis_function_type( &::OutputData< double >::getAxis )
                , ( bp::arg("index") )
                , bp::return_value_policy< bp::reference_existing_object >() );
        
        }
        { //::OutputData< double >::getAxis
        
            typedef OutputData< double > exported_class_t;
            typedef ::IAxis const * ( exported_class_t::*getAxis_function_type )( ::std::string const & ) const;
            
            ndimdata_t_exposer.def( 
                "getAxis"
                , getAxis_function_type( &::OutputData< double >::getAxis )
                , ( bp::arg("label") )
                , bp::return_value_policy< bp::reference_existing_object >() );
        
        }
        { //::OutputData< double >::getAxisIndex
        
            typedef OutputData< double > exported_class_t;
            typedef ::std::size_t ( exported_class_t::*getAxisIndex_function_type )( ::std::string const & ) const;
            
            ndimdata_t_exposer.def( 
                "getAxisIndex"
                , getAxisIndex_function_type( &::OutputData< double >::getAxisIndex )
                , ( bp::arg("label") ) );
        
        }
        { //::OutputData< double >::getIndexOfAxis
        
            typedef OutputData< double > exported_class_t;
            typedef ::std::size_t ( exported_class_t::*getIndexOfAxis_function_type )( ::std::string const &,::std::size_t ) const;
            
            ndimdata_t_exposer.def( 
                "getIndexOfAxis"
                , getIndexOfAxis_function_type( &::OutputData< double >::getIndexOfAxis )
                , ( bp::arg("axis_name"), bp::arg("total_index") ) );
        
        }
        { //::OutputData< double >::getRank
        
            typedef OutputData< double > exported_class_t;
            typedef ::std::size_t ( exported_class_t::*getRank_function_type )(  ) const;
            
            ndimdata_t_exposer.def( 
                "getRank"
                , getRank_function_type( &::OutputData< double >::getRank ) );
        
        }
        { //::OutputData< double >::getRawDataVector
        
            typedef OutputData< double > exported_class_t;
            typedef ::std::vector< double > ( exported_class_t::*getRawDataVector_function_type )(  ) const;
            
            ndimdata_t_exposer.def( 
                "getRawDataVector"
                , getRawDataVector_function_type( &::OutputData< double >::getRawDataVector ) );
        
        }
        { //::OutputData< double >::getValueOfAxis
        
            typedef OutputData< double > exported_class_t;
            typedef double ( exported_class_t::*getValueOfAxis_function_type )( ::std::string const &,::std::size_t ) const;
            
            ndimdata_t_exposer.def( 
                "getValueOfAxis"
                , getValueOfAxis_function_type( &::OutputData< double >::getValueOfAxis )
                , ( bp::arg("axis_name"), bp::arg("index") ) );
        
        }
        { //::OutputData< double >::hasSameDimensions
        
            typedef OutputData< double > exported_class_t;
            typedef bool ( exported_class_t::*hasSameDimensions_function_type )( ::OutputData< double > const & ) const;
            
            ndimdata_t_exposer.def( 
                "hasSameDimensions"
                , hasSameDimensions_function_type( &::OutputData< double >::hasSameDimensions )
                , ( bp::arg("right") ) );
        
        }
        { //::OutputData< double >::hasSameShape
        
            typedef OutputData< double > exported_class_t;
            typedef bool ( exported_class_t::*hasSameShape_function_type )( ::OutputData< double > const & ) const;
            
            ndimdata_t_exposer.def( 
                "hasSameShape"
                , hasSameShape_function_type( &::OutputData< double >::hasSameShape )
                , ( bp::arg("right") ) );
        
        }
        ndimdata_t_exposer.def( bp::self *= bp::self );
        ndimdata_t_exposer.def( bp::self += bp::self );
        ndimdata_t_exposer.def( bp::self -= bp::self );
        ndimdata_t_exposer.def( bp::self /= bp::self );
        { //::OutputData< double >::operator[]
        
            typedef OutputData< double > exported_class_t;
            typedef double & ( exported_class_t::*__getitem___function_type )( ::std::size_t ) ;
            
            ndimdata_t_exposer.def( 
                "__getitem__"
                , __getitem___function_type( &::OutputData< double >::operator[] )
                , ( bp::arg("index") )
                , bp::return_value_policy< bp::copy_non_const_reference >() );
        
        }
        { //::OutputData< double >::operator[]
        
            typedef OutputData< double > exported_class_t;
            typedef double const & ( exported_class_t::*__getitem___function_type )( ::std::size_t ) const;
            
            ndimdata_t_exposer.def( 
                "__getitem__"
                , __getitem___function_type( &::OutputData< double >::operator[] )
                , ( bp::arg("index") )
                , bp::return_value_policy< bp::copy_const_reference >() );
        
        }
        { //::OutputData< double >::removeAllMasks
        
            typedef OutputData< double > exported_class_t;
            typedef void ( exported_class_t::*removeAllMasks_function_type )(  ) ;
            
            ndimdata_t_exposer.def( 
                "removeAllMasks"
                , removeAllMasks_function_type( &::OutputData< double >::removeAllMasks ) );
        
        }
        { //::OutputData< double >::scaleAll
        
            typedef OutputData< double > exported_class_t;
            typedef void ( exported_class_t::*scaleAll_function_type )( double const & ) ;
            
            ndimdata_t_exposer.def( 
                "scaleAll"
                , scaleAll_function_type( &::OutputData< double >::scaleAll )
                , ( bp::arg("factor") ) );
        
        }
        { //::OutputData< double >::setAllTo
        
            typedef OutputData< double > exported_class_t;
            typedef void ( exported_class_t::*setAllTo_function_type )( double const & ) ;
            
            ndimdata_t_exposer.def( 
                "setAllTo"
                , setAllTo_function_type( &::OutputData< double >::setAllTo )
                , ( bp::arg("value") ) );
        
        }
        { //::OutputData< double >::setRawDataVector
        
            typedef OutputData< double > exported_class_t;
            typedef void ( exported_class_t::*setRawDataVector_function_type )( ::std::vector< double > const & ) ;
            
            ndimdata_t_exposer.def( 
                "setRawDataVector"
                , setRawDataVector_function_type( &::OutputData< double >::setRawDataVector )
                , ( bp::arg("data_vector") ) );
        
        }
        { //::OutputData< double >::toCoordinate
        
            typedef OutputData< double > exported_class_t;
            typedef int ( exported_class_t::*toCoordinate_function_type )( ::std::size_t,::std::size_t ) const;
            
            ndimdata_t_exposer.def( 
                "toCoordinate"
                , toCoordinate_function_type( &::OutputData< double >::toCoordinate )
                , ( bp::arg("index"), bp::arg("i_selected_axis") ) );
        
        }
        { //::OutputData< double >::toCoordinates
        
            typedef OutputData< double > exported_class_t;
            typedef ::std::vector< int > ( exported_class_t::*toCoordinates_function_type )( ::std::size_t ) const;
            
            ndimdata_t_exposer.def( 
                "toCoordinates"
                , toCoordinates_function_type( &::OutputData< double >::toCoordinates )
                , ( bp::arg("index") ) );
        
        }
        { //::OutputData< double >::toIndex
        
            typedef OutputData< double > exported_class_t;
            typedef ::std::size_t ( exported_class_t::*toIndex_function_type )( ::std::vector< int > ) const;
            
            ndimdata_t_exposer.def( 
                "toIndex"
                , toIndex_function_type( &::OutputData< double >::toIndex )
                , ( bp::arg("coordinates") ) );
        
        }
        { //::OutputData< double >::totalSum
        
            typedef OutputData< double > exported_class_t;
            typedef double ( exported_class_t::*totalSum_function_type )(  ) const;
            
            ndimdata_t_exposer.def( 
                "totalSum"
                , totalSum_function_type( &::OutputData< double >::totalSum ) );
        
        }
        ndimdata_t_exposer.def("__setitem__", &pyplusplus_setitem<OutputData<double >,int,double> );
    }

}
