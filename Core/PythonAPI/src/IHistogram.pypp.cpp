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
#include "IHistogram.pypp.h"

namespace bp = boost::python;

struct IHistogram_wrapper : IHistogram, bp::wrapper< IHistogram > {

    IHistogram_wrapper( )
    : IHistogram( )
      , bp::wrapper< IHistogram >(){
        // null constructor
    
    }

    IHistogram_wrapper(::IAxis const & axis_x )
    : IHistogram( boost::ref(axis_x) )
      , bp::wrapper< IHistogram >(){
        // constructor
    
    }

    IHistogram_wrapper(::IAxis const & axis_x, ::IAxis const & axis_y )
    : IHistogram( boost::ref(axis_x), boost::ref(axis_y) )
      , bp::wrapper< IHistogram >(){
        // constructor
    
    }

    IHistogram_wrapper(::OutputData< double > const & source )
    : IHistogram( boost::ref(source) )
      , bp::wrapper< IHistogram >(){
        // constructor
    
    }

    virtual ::std::size_t getRank(  ) const  {
        if( bp::override func_getRank = this->get_override( "getRank" ) )
            return func_getRank(  );
        else{
            return this->IHistogram::getRank(  );
        }
    }
    
    ::std::size_t default_getRank(  ) const  {
        return IHistogram::getRank( );
    }

    virtual ::std::size_t getTotalNumberOfBins(  ) const  {
        if( bp::override func_getTotalNumberOfBins = this->get_override( "getTotalNumberOfBins" ) )
            return func_getTotalNumberOfBins(  );
        else{
            return this->IHistogram::getTotalNumberOfBins(  );
        }
    }
    
    ::std::size_t default_getTotalNumberOfBins(  ) const  {
        return IHistogram::getTotalNumberOfBins( );
    }

    virtual ::IAxis const * getXaxis(  ) const  {
        if( bp::override func_getXaxis = this->get_override( "getXaxis" ) )
            return func_getXaxis(  );
        else{
            return this->IHistogram::getXaxis(  );
        }
    }
    
    ::IAxis const * default_getXaxis(  ) const  {
        return IHistogram::getXaxis( );
    }

    virtual double getXaxisValue( ::std::size_t globalbin ) {
        if( bp::override func_getXaxisValue = this->get_override( "getXaxisValue" ) )
            return func_getXaxisValue( globalbin );
        else{
            return this->IHistogram::getXaxisValue( globalbin );
        }
    }
    
    double default_getXaxisValue( ::std::size_t globalbin ) {
        return IHistogram::getXaxisValue( globalbin );
    }

    virtual double getXmax(  ) const  {
        if( bp::override func_getXmax = this->get_override( "getXmax" ) )
            return func_getXmax(  );
        else{
            return this->IHistogram::getXmax(  );
        }
    }
    
    double default_getXmax(  ) const  {
        return IHistogram::getXmax( );
    }

    virtual double getXmin(  ) const  {
        if( bp::override func_getXmin = this->get_override( "getXmin" ) )
            return func_getXmin(  );
        else{
            return this->IHistogram::getXmin(  );
        }
    }
    
    double default_getXmin(  ) const  {
        return IHistogram::getXmin( );
    }

    virtual ::IAxis const * getYaxis(  ) const  {
        if( bp::override func_getYaxis = this->get_override( "getYaxis" ) )
            return func_getYaxis(  );
        else{
            return this->IHistogram::getYaxis(  );
        }
    }
    
    ::IAxis const * default_getYaxis(  ) const  {
        return IHistogram::getYaxis( );
    }

    virtual double getYaxisValue( ::std::size_t globalbin ) {
        if( bp::override func_getYaxisValue = this->get_override( "getYaxisValue" ) )
            return func_getYaxisValue( globalbin );
        else{
            return this->IHistogram::getYaxisValue( globalbin );
        }
    }
    
    double default_getYaxisValue( ::std::size_t globalbin ) {
        return IHistogram::getYaxisValue( globalbin );
    }

    virtual double getYmax(  ) const  {
        if( bp::override func_getYmax = this->get_override( "getYmax" ) )
            return func_getYmax(  );
        else{
            return this->IHistogram::getYmax(  );
        }
    }
    
    double default_getYmax(  ) const  {
        return IHistogram::getYmax( );
    }

    virtual double getYmin(  ) const  {
        if( bp::override func_getYmin = this->get_override( "getYmin" ) )
            return func_getYmin(  );
        else{
            return this->IHistogram::getYmin(  );
        }
    }
    
    double default_getYmin(  ) const  {
        return IHistogram::getYmin( );
    }

    virtual void reset(  ) {
        if( bp::override func_reset = this->get_override( "reset" ) )
            func_reset(  );
        else{
            this->IHistogram::reset(  );
        }
    }
    
    void default_reset(  ) {
        IHistogram::reset( );
    }

};

void register_IHistogram_class(){

    { //::IHistogram
        typedef bp::class_< IHistogram_wrapper, boost::noncopyable > IHistogram_exposer_t;
        IHistogram_exposer_t IHistogram_exposer = IHistogram_exposer_t( "IHistogram", "Base class for 1D and 2D histograms holding values of double typ.", bp::init< >() );
        bp::scope IHistogram_scope( IHistogram_exposer );
        bp::enum_< IHistogram::ProjectionType>("ProjectionType")
            .value("INTEGRAL", IHistogram::INTEGRAL)
            .value("AVERAGE", IHistogram::AVERAGE)
            .export_values()
            ;
        IHistogram_exposer.def( bp::init< IAxis const & >(( bp::arg("axis_x") )) );
        IHistogram_exposer.def( bp::init< IAxis const &, IAxis const & >(( bp::arg("axis_x"), bp::arg("axis_y") )) );
        IHistogram_exposer.def( bp::init< OutputData< double > const & >(( bp::arg("source") )) );
        { //::IHistogram::getArray
        
            typedef ::PyObject * ( ::IHistogram::*getArray_function_type)(  ) const;
            
            IHistogram_exposer.def( 
                "getArray"
                , getArray_function_type( &::IHistogram::getArray ) );
        
        }
        { //::IHistogram::getBinContent
        
            typedef double ( ::IHistogram::*getBinContent_function_type)( int ) const;
            
            IHistogram_exposer.def( 
                "getBinContent"
                , getBinContent_function_type( &::IHistogram::getBinContent )
                , ( bp::arg("bin") )
                , "Returns content of the bin with given index. For 1D histograms bin index is related to x-axis. For 2D histograms bin index is global bin index. @param bin Bin index @return The content of the bin (which is normally the value accumulated by the bin) \n\n:Parameters:\n  - 'bin' - Bin index\n" );
        
        }
        { //::IHistogram::getBinContent
        
            typedef double ( ::IHistogram::*getBinContent_function_type)( int,int ) const;
            
            IHistogram_exposer.def( 
                "getBinContent"
                , getBinContent_function_type( &::IHistogram::getBinContent )
                , ( bp::arg("binx"), bp::arg("biny") )
                , "Returns content of the bin of 2D histogram with given axes indices. @param binx X-axis bin index @param biny Y-axis bin index @return The content of the bin (which is normally the value accumulated by the bin) \n\n:Parameters:\n  - 'binx' - X-axis bin index\n  - 'biny' - Y-axis bin index\n" );
        
        }
        { //::IHistogram::getBinError
        
            typedef double ( ::IHistogram::*getBinError_function_type)( int ) const;
            
            IHistogram_exposer.def( 
                "getBinError"
                , getBinError_function_type( &::IHistogram::getBinError )
                , ( bp::arg("bin") )
                , "Returns error of the bin with given index." );
        
        }
        { //::IHistogram::getBinError
        
            typedef double ( ::IHistogram::*getBinError_function_type)( int,int ) const;
            
            IHistogram_exposer.def( 
                "getBinError"
                , getBinError_function_type( &::IHistogram::getBinError )
                , ( bp::arg("binx"), bp::arg("biny") )
                , "Returns error of the bin of 2D histogram with given axes indices." );
        
        }
        { //::IHistogram::getBinNumberOfEntries
        
            typedef int ( ::IHistogram::*getBinNumberOfEntries_function_type)( int ) const;
            
            IHistogram_exposer.def( 
                "getBinNumberOfEntries"
                , getBinNumberOfEntries_function_type( &::IHistogram::getBinNumberOfEntries )
                , ( bp::arg("bin") )
                , "Returns number of entries in the bin with given index." );
        
        }
        { //::IHistogram::getBinNumberOfEntries
        
            typedef int ( ::IHistogram::*getBinNumberOfEntries_function_type)( int,int ) const;
            
            IHistogram_exposer.def( 
                "getBinNumberOfEntries"
                , getBinNumberOfEntries_function_type( &::IHistogram::getBinNumberOfEntries )
                , ( bp::arg("binx"), bp::arg("biny") )
                , "Returns number of entries in the bin of 2D histogram with given axes indices." );
        
        }
        { //::IHistogram::getGlobalBin
        
            typedef int ( ::IHistogram::*getGlobalBin_function_type)( int,int ) const;
            
            IHistogram_exposer.def( 
                "getGlobalBin"
                , getGlobalBin_function_type( &::IHistogram::getGlobalBin )
                , ( bp::arg("binx"), bp::arg("biny")=(int)(0) )
                , "Returns global bin index for given axes indices. For 1D histogram the global bin index coinside with axis index. @param binx X-axis bin index @param biny Y-axis bin index @return The global bin index \n\n:Parameters:\n  - 'binx' - X-axis bin index\n  - 'biny' - Y-axis bin index\n" );
        
        }
        { //::IHistogram::getRank
        
            typedef ::std::size_t ( ::IHistogram::*getRank_function_type)(  ) const;
            typedef ::std::size_t ( IHistogram_wrapper::*default_getRank_function_type)(  ) const;
            
            IHistogram_exposer.def( 
                "getRank"
                , getRank_function_type(&::IHistogram::getRank)
                , default_getRank_function_type(&IHistogram_wrapper::default_getRank) );
        
        }
        { //::IHistogram::getTotalNumberOfBins
        
            typedef ::std::size_t ( ::IHistogram::*getTotalNumberOfBins_function_type)(  ) const;
            typedef ::std::size_t ( IHistogram_wrapper::*default_getTotalNumberOfBins_function_type)(  ) const;
            
            IHistogram_exposer.def( 
                "getTotalNumberOfBins"
                , getTotalNumberOfBins_function_type(&::IHistogram::getTotalNumberOfBins)
                , default_getTotalNumberOfBins_function_type(&IHistogram_wrapper::default_getTotalNumberOfBins) );
        
        }
        { //::IHistogram::getXaxis
        
            typedef ::IAxis const * ( ::IHistogram::*getXaxis_function_type)(  ) const;
            typedef ::IAxis const * ( IHistogram_wrapper::*default_getXaxis_function_type)(  ) const;
            
            IHistogram_exposer.def( 
                "getXaxis"
                , getXaxis_function_type(&::IHistogram::getXaxis)
                , default_getXaxis_function_type(&IHistogram_wrapper::default_getXaxis)
                , bp::return_value_policy< bp::reference_existing_object >() );
        
        }
        { //::IHistogram::getXaxisIndex
        
            typedef int ( ::IHistogram::*getXaxisIndex_function_type)( ::std::size_t ) const;
            
            IHistogram_exposer.def( 
                "getXaxisIndex"
                , getXaxisIndex_function_type( &::IHistogram::getXaxisIndex )
                , ( bp::arg("globalbin") )
                , "Returns x-axis bin index for given globalbin. For 1D histograms returned value conicide with globalbin value " );
        
        }
        { //::IHistogram::getXaxisValue
        
            typedef double ( ::IHistogram::*getXaxisValue_function_type)( ::std::size_t ) ;
            typedef double ( IHistogram_wrapper::*default_getXaxisValue_function_type)( ::std::size_t ) ;
            
            IHistogram_exposer.def( 
                "getXaxisValue"
                , getXaxisValue_function_type(&::IHistogram::getXaxisValue)
                , default_getXaxisValue_function_type(&IHistogram_wrapper::default_getXaxisValue)
                , ( bp::arg("globalbin") ) );
        
        }
        { //::IHistogram::getXmax
        
            typedef double ( ::IHistogram::*getXmax_function_type)(  ) const;
            typedef double ( IHistogram_wrapper::*default_getXmax_function_type)(  ) const;
            
            IHistogram_exposer.def( 
                "getXmax"
                , getXmax_function_type(&::IHistogram::getXmax)
                , default_getXmax_function_type(&IHistogram_wrapper::default_getXmax) );
        
        }
        { //::IHistogram::getXmin
        
            typedef double ( ::IHistogram::*getXmin_function_type)(  ) const;
            typedef double ( IHistogram_wrapper::*default_getXmin_function_type)(  ) const;
            
            IHistogram_exposer.def( 
                "getXmin"
                , getXmin_function_type(&::IHistogram::getXmin)
                , default_getXmin_function_type(&IHistogram_wrapper::default_getXmin) );
        
        }
        { //::IHistogram::getYaxis
        
            typedef ::IAxis const * ( ::IHistogram::*getYaxis_function_type)(  ) const;
            typedef ::IAxis const * ( IHistogram_wrapper::*default_getYaxis_function_type)(  ) const;
            
            IHistogram_exposer.def( 
                "getYaxis"
                , getYaxis_function_type(&::IHistogram::getYaxis)
                , default_getYaxis_function_type(&IHistogram_wrapper::default_getYaxis)
                , bp::return_value_policy< bp::reference_existing_object >() );
        
        }
        { //::IHistogram::getYaxisIndex
        
            typedef int ( ::IHistogram::*getYaxisIndex_function_type)( ::std::size_t ) const;
            
            IHistogram_exposer.def( 
                "getYaxisIndex"
                , getYaxisIndex_function_type( &::IHistogram::getYaxisIndex )
                , ( bp::arg("globalbin") )
                , "Returns x-axis bin index for given globalbin. For 1D histograms returned value conicide with globalbin value " );
        
        }
        { //::IHistogram::getYaxisValue
        
            typedef double ( ::IHistogram::*getYaxisValue_function_type)( ::std::size_t ) ;
            typedef double ( IHistogram_wrapper::*default_getYaxisValue_function_type)( ::std::size_t ) ;
            
            IHistogram_exposer.def( 
                "getYaxisValue"
                , getYaxisValue_function_type(&::IHistogram::getYaxisValue)
                , default_getYaxisValue_function_type(&IHistogram_wrapper::default_getYaxisValue)
                , ( bp::arg("globalbin") ) );
        
        }
        { //::IHistogram::getYmax
        
            typedef double ( ::IHistogram::*getYmax_function_type)(  ) const;
            typedef double ( IHistogram_wrapper::*default_getYmax_function_type)(  ) const;
            
            IHistogram_exposer.def( 
                "getYmax"
                , getYmax_function_type(&::IHistogram::getYmax)
                , default_getYmax_function_type(&IHistogram_wrapper::default_getYmax) );
        
        }
        { //::IHistogram::getYmin
        
            typedef double ( ::IHistogram::*getYmin_function_type)(  ) const;
            typedef double ( IHistogram_wrapper::*default_getYmin_function_type)(  ) const;
            
            IHistogram_exposer.def( 
                "getYmin"
                , getYmin_function_type(&::IHistogram::getYmin)
                , default_getYmin_function_type(&IHistogram_wrapper::default_getYmin) );
        
        }
        { //::IHistogram::reset
        
            typedef void ( ::IHistogram::*reset_function_type)(  ) ;
            typedef void ( IHistogram_wrapper::*default_reset_function_type)(  ) ;
            
            IHistogram_exposer.def( 
                "reset"
                , reset_function_type(&::IHistogram::reset)
                , default_reset_function_type(&IHistogram_wrapper::default_reset) );
        
        }
    }

}
