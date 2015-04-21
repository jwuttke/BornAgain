#ifdef _MSC_VER
#define _VARIADIC_MAX 10
#endif
#include "gtest/gtest.h"

#include "FitParameterTest.h"
#include "FitParameterLinkedTest.h"
#include "MinimizerOptionsTest.h"


struct ErrorStreamRedirect {
    ErrorStreamRedirect( std::streambuf * new_buffer )
        : old( std::cerr.rdbuf( new_buffer ) )
    { }

    ~ErrorStreamRedirect( ) {
        std::cerr.rdbuf( old );
    }

private:
    std::streambuf * old;
};

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    // redirect std::cerr stream
    std::stringstream oss;
    ErrorStreamRedirect redirecter( oss.rdbuf() );
    (void)redirecter;

    // run all google tests
    return RUN_ALL_TESTS();
}

