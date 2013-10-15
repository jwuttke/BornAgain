// This file has been generated by Py++.

// BornAgain: simulate and fit scattering at grazing incidence 
//! @brief automatically generated boost::python code for PythonCoreAPI  

#include "Macros.h"
GCC_DIAG_OFF(unused-parameter);
GCC_DIAG_OFF(missing-field-initializers);
#include "boost/python.hpp"
GCC_DIAG_ON(unused-parameter);
GCC_DIAG_ON(missing-field-initializers);
#include "__call_policies.pypp.hpp"
#include "__convenience.pypp.hpp"
#include "PythonCoreList.h"
#include "ParticleInfo.pypp.h"

namespace bp = boost::python;

struct ParticleInfo_wrapper : ParticleInfo, bp::wrapper< ParticleInfo > {

    ParticleInfo_wrapper(::Particle const & p_particle, double depth=0, double abundance=0 )
    : ParticleInfo( boost::ref(p_particle), depth, abundance )
      , bp::wrapper< ParticleInfo >(){
        // constructor
    
    }

    virtual ::ParticleInfo * clone(  ) const  {
        if( bp::override func_clone = this->get_override( "clone" ) )
            return func_clone(  );
        else
            return this->ParticleInfo::clone(  );
    }
    
    
    ::ParticleInfo * default_clone(  ) const  {
        return ParticleInfo::clone( );
    }

    virtual ::ParticleInfo * cloneInvertB(  ) const  {
        if( bp::override func_cloneInvertB = this->get_override( "cloneInvertB" ) )
            return func_cloneInvertB(  );
        else
            return this->ParticleInfo::cloneInvertB(  );
    }
    
    
    ::ParticleInfo * default_cloneInvertB(  ) const  {
        return ParticleInfo::cloneInvertB( );
    }

    virtual bool areParametersChanged(  ) {
        if( bp::override func_areParametersChanged = this->get_override( "areParametersChanged" ) )
            return func_areParametersChanged(  );
        else
            return this->IParameterized::areParametersChanged(  );
    }
    
    
    bool default_areParametersChanged(  ) {
        return IParameterized::areParametersChanged( );
    }

    virtual void clearParameterPool(  ) {
        if( bp::override func_clearParameterPool = this->get_override( "clearParameterPool" ) )
            func_clearParameterPool(  );
        else
            this->IParameterized::clearParameterPool(  );
    }
    
    
    void default_clearParameterPool(  ) {
        IParameterized::clearParameterPool( );
    }

    virtual ::ParameterPool * createParameterTree(  ) const  {
        if( bp::override func_createParameterTree = this->get_override( "createParameterTree" ) )
            return func_createParameterTree(  );
        else
            return this->IParameterized::createParameterTree(  );
    }
    
    
    ::ParameterPool * default_createParameterTree(  ) const  {
        return IParameterized::createParameterTree( );
    }

    virtual void printParameters(  ) const  {
        if( bp::override func_printParameters = this->get_override( "printParameters" ) )
            func_printParameters(  );
        else
            this->IParameterized::printParameters(  );
    }
    
    
    void default_printParameters(  ) const  {
        IParameterized::printParameters( );
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
        if( dynamic_cast< ParticleInfo_wrapper * >( boost::addressof( inst ) ) ){
            inst.::IParameterized::registerParameter(name, reinterpret_cast< double * >( parpointer ));
        }
        else{
            inst.registerParameter(name, reinterpret_cast< double * >( parpointer ));
        }
    }

    virtual int setMatchedParametersValue( ::std::string const & wildcards, double value ) {
        if( bp::override func_setMatchedParametersValue = this->get_override( "setMatchedParametersValue" ) )
            return func_setMatchedParametersValue( wildcards, value );
        else
            return this->IParameterized::setMatchedParametersValue( wildcards, value );
    }
    
    
    int default_setMatchedParametersValue( ::std::string const & wildcards, double value ) {
        return IParameterized::setMatchedParametersValue( wildcards, value );
    }

    virtual bool setParameterValue( ::std::string const & name, double value ) {
        if( bp::override func_setParameterValue = this->get_override( "setParameterValue" ) )
            return func_setParameterValue( name, value );
        else
            return this->IParameterized::setParameterValue( name, value );
    }
    
    
    bool default_setParameterValue( ::std::string const & name, double value ) {
        return IParameterized::setParameterValue( name, value );
    }

    virtual void setParametersAreChanged(  ) {
        if( bp::override func_setParametersAreChanged = this->get_override( "setParametersAreChanged" ) )
            func_setParametersAreChanged(  );
        else
            this->IParameterized::setParametersAreChanged(  );
    }
    
    
    void default_setParametersAreChanged(  ) {
        IParameterized::setParametersAreChanged( );
    }

};

void register_ParticleInfo_class(){

    { //::ParticleInfo
        typedef bp::class_< ParticleInfo_wrapper, bp::bases< ICompositeSample >, boost::noncopyable > ParticleInfo_exposer_t;
        ParticleInfo_exposer_t ParticleInfo_exposer = ParticleInfo_exposer_t( "ParticleInfo", bp::init< Particle const &, bp::optional< double, double > >(( bp::arg("p_particle"), bp::arg("depth")=0, bp::arg("abundance")=0 )) );
        bp::scope ParticleInfo_scope( ParticleInfo_exposer );
        { //::ParticleInfo::clone
        
            typedef ::ParticleInfo * ( ::ParticleInfo::*clone_function_type )(  ) const;
            typedef ::ParticleInfo * ( ParticleInfo_wrapper::*default_clone_function_type )(  ) const;
            
            ParticleInfo_exposer.def( 
                "clone"
                , clone_function_type(&::ParticleInfo::clone)
                , default_clone_function_type(&ParticleInfo_wrapper::default_clone)
                , bp::return_value_policy< bp::manage_new_object >() );
        
        }
        { //::ParticleInfo::cloneInvertB
        
            typedef ::ParticleInfo * ( ::ParticleInfo::*cloneInvertB_function_type )(  ) const;
            typedef ::ParticleInfo * ( ParticleInfo_wrapper::*default_cloneInvertB_function_type )(  ) const;
            
            ParticleInfo_exposer.def( 
                "cloneInvertB"
                , cloneInvertB_function_type(&::ParticleInfo::cloneInvertB)
                , default_cloneInvertB_function_type(&ParticleInfo_wrapper::default_cloneInvertB)
                , bp::return_value_policy< bp::reference_existing_object >() );
        
        }
        { //::ParticleInfo::getAbundance
        
            typedef double ( ::ParticleInfo::*getAbundance_function_type )(  ) const;
            
            ParticleInfo_exposer.def( 
                "getAbundance"
                , getAbundance_function_type( &::ParticleInfo::getAbundance ) );
        
        }
        { //::ParticleInfo::getDepth
        
            typedef double ( ::ParticleInfo::*getDepth_function_type )(  ) const;
            
            ParticleInfo_exposer.def( 
                "getDepth"
                , getDepth_function_type( &::ParticleInfo::getDepth ) );
        
        }
        { //::ParticleInfo::getParticle
        
            typedef ::Particle const * ( ::ParticleInfo::*getParticle_function_type )(  ) const;
            
            ParticleInfo_exposer.def( 
                "getParticle"
                , getParticle_function_type( &::ParticleInfo::getParticle )
                , bp::return_value_policy< bp::reference_existing_object >() );
        
        }
        { //::ParticleInfo::setAbundance
        
            typedef void ( ::ParticleInfo::*setAbundance_function_type )( double ) ;
            
            ParticleInfo_exposer.def( 
                "setAbundance"
                , setAbundance_function_type( &::ParticleInfo::setAbundance )
                , ( bp::arg("abundance") ) );
        
        }
        { //::ParticleInfo::setDepth
        
            typedef void ( ::ParticleInfo::*setDepth_function_type )( double ) ;
            
            ParticleInfo_exposer.def( 
                "setDepth"
                , setDepth_function_type( &::ParticleInfo::setDepth )
                , ( bp::arg("depth") ) );
        
        }
        { //::IParameterized::areParametersChanged
        
            typedef bool ( ::IParameterized::*areParametersChanged_function_type )(  ) ;
            typedef bool ( ParticleInfo_wrapper::*default_areParametersChanged_function_type )(  ) ;
            
            ParticleInfo_exposer.def( 
                "areParametersChanged"
                , areParametersChanged_function_type(&::IParameterized::areParametersChanged)
                , default_areParametersChanged_function_type(&ParticleInfo_wrapper::default_areParametersChanged) );
        
        }
        { //::IParameterized::clearParameterPool
        
            typedef void ( ::IParameterized::*clearParameterPool_function_type )(  ) ;
            typedef void ( ParticleInfo_wrapper::*default_clearParameterPool_function_type )(  ) ;
            
            ParticleInfo_exposer.def( 
                "clearParameterPool"
                , clearParameterPool_function_type(&::IParameterized::clearParameterPool)
                , default_clearParameterPool_function_type(&ParticleInfo_wrapper::default_clearParameterPool) );
        
        }
        { //::IParameterized::createParameterTree
        
            typedef ::ParameterPool * ( ::IParameterized::*createParameterTree_function_type )(  ) const;
            typedef ::ParameterPool * ( ParticleInfo_wrapper::*default_createParameterTree_function_type )(  ) const;
            
            ParticleInfo_exposer.def( 
                "createParameterTree"
                , createParameterTree_function_type(&::IParameterized::createParameterTree)
                , default_createParameterTree_function_type(&ParticleInfo_wrapper::default_createParameterTree)
                , bp::return_value_policy< bp::manage_new_object >() );
        
        }
        { //::IParameterized::printParameters
        
            typedef void ( ::IParameterized::*printParameters_function_type )(  ) const;
            typedef void ( ParticleInfo_wrapper::*default_printParameters_function_type )(  ) const;
            
            ParticleInfo_exposer.def( 
                "printParameters"
                , printParameters_function_type(&::IParameterized::printParameters)
                , default_printParameters_function_type(&ParticleInfo_wrapper::default_printParameters) );
        
        }
        { //::IParameterized::registerParameter
        
            typedef void ( *default_registerParameter_function_type )( ::IParameterized &,::std::string const &,long unsigned int );
            
            ParticleInfo_exposer.def( 
                "registerParameter"
                , default_registerParameter_function_type( &ParticleInfo_wrapper::default_registerParameter )
                , ( bp::arg("inst"), bp::arg("name"), bp::arg("parpointer") ) );
        
        }
        { //::IParameterized::setMatchedParametersValue
        
            typedef int ( ::IParameterized::*setMatchedParametersValue_function_type )( ::std::string const &,double ) ;
            typedef int ( ParticleInfo_wrapper::*default_setMatchedParametersValue_function_type )( ::std::string const &,double ) ;
            
            ParticleInfo_exposer.def( 
                "setMatchedParametersValue"
                , setMatchedParametersValue_function_type(&::IParameterized::setMatchedParametersValue)
                , default_setMatchedParametersValue_function_type(&ParticleInfo_wrapper::default_setMatchedParametersValue)
                , ( bp::arg("wildcards"), bp::arg("value") ) );
        
        }
        { //::IParameterized::setParameterValue
        
            typedef bool ( ::IParameterized::*setParameterValue_function_type )( ::std::string const &,double ) ;
            typedef bool ( ParticleInfo_wrapper::*default_setParameterValue_function_type )( ::std::string const &,double ) ;
            
            ParticleInfo_exposer.def( 
                "setParameterValue"
                , setParameterValue_function_type(&::IParameterized::setParameterValue)
                , default_setParameterValue_function_type(&ParticleInfo_wrapper::default_setParameterValue)
                , ( bp::arg("name"), bp::arg("value") ) );
        
        }
        { //::IParameterized::setParametersAreChanged
        
            typedef void ( ::IParameterized::*setParametersAreChanged_function_type )(  ) ;
            typedef void ( ParticleInfo_wrapper::*default_setParametersAreChanged_function_type )(  ) ;
            
            ParticleInfo_exposer.def( 
                "setParametersAreChanged"
                , setParametersAreChanged_function_type(&::IParameterized::setParametersAreChanged)
                , default_setParametersAreChanged_function_type(&ParticleInfo_wrapper::default_setParametersAreChanged) );
        
        }
    }

}
