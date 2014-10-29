// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/src/Utils.cpp
//! @brief     Implements various stuff in namespace Utils.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "Utils.h"
#include "Exceptions.h"
#include <iostream>
#include <iomanip>
#include <boost/regex.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <boost/algorithm/string.hpp>
#include <string>

#include "Macros.h"
GCC_DIAG_OFF(strict-aliasing);
#include <boost/thread.hpp>
GCC_DIAG_ON(strict-aliasing);


#ifdef DEBUG_FPE
#include <fenv.h>
#ifdef Q_OS_MAC
#include "fp_exception_glibc_extension.h"
#endif
#endif



//! Parse double values from string to vector of double

vdouble1d_t Utils::String::parse_doubles(const std::string& str)
{
    vdouble1d_t buff_1d;
    std::istringstream iss(str);
    std::string svalue;
    while(iss >> svalue) {
        buff_1d.push_back(std::strtod(svalue.c_str(), NULL));
    }
// approach below doesnt work under mac 10.6 for doubles like 4.3882628771e-313
//    std::copy(std::istream_iterator<double>(iss),
//              std::istream_iterator<double>(), back_inserter(buff_1d));
    if( buff_1d.empty() ) {
        std::cout << "OutputDataReadFileASCII::parse_doubles() -> "
            "Warning! No parsed values in 1d vector of doubles." << std::endl;
        std::cout << "Line '" << str << "'" << std::endl;
    }
    return buff_1d;
}

//! Round double numbers in string to given precision.

//! If precision is 6, then 7.2908527770e+03 -> 7.290853e+03.
//! This method is used to compare IsGisaxs and our ASCII files
//! at equal precision.
//!
std::string Utils::String::round_doubles(const std::string& str, int precision)
{
    std::string newline;
    std::istringstream is0(str.c_str());
    double number;
    while( is0 >> number ) {
        std::ostringstream os;
        os << std::scientific << std::setprecision(precision) << number;
        newline += os.str() + std::string("    ");
    }
    return newline;
}

//! Returns true if text matches pattern with wildcards '*' and '?'.

bool Utils::String::MatchPattern(
    const std::string& text, std::string wildcardPattern)
{
    bool caseSensitive(true);

    // escape all regex special characters, except '?' and '*'
    boost::replace_all(wildcardPattern, "\\", "\\\\");
    boost::replace_all(wildcardPattern, "^", "\\^");
    boost::replace_all(wildcardPattern, ".", "\\.");
    boost::replace_all(wildcardPattern, "$", "\\$");
    boost::replace_all(wildcardPattern, "|", "\\|");
    boost::replace_all(wildcardPattern, "(", "\\(");
    boost::replace_all(wildcardPattern, ")", "\\)");
    boost::replace_all(wildcardPattern, "[", "\\[");
    boost::replace_all(wildcardPattern, "]", "\\]");
    boost::replace_all(wildcardPattern, "+", "\\+");
    boost::replace_all(wildcardPattern, "/", "\\/");

    // Convert chars '*?' to their regex equivalents
    boost::replace_all(wildcardPattern, "?", ".");
    boost::replace_all(wildcardPattern, "*", ".*");

    // constructing regexp pattern
    wildcardPattern = "^" + wildcardPattern + "$";
    boost::regex pattern(wildcardPattern, caseSensitive ? boost::regex::normal : boost::regex::icase);

    // applaying match
    return boost::regex_match(text, pattern);
}

//! Split string into vector of string using delimeter.

std::vector<std::string> Utils::String::Split(
    const std::string& text, const std::string& delimeter)
{
    std::vector<std::string> tokens;
    boost::split(tokens, text, boost::is_any_of(delimeter));
    return tokens;
}


void Utils::String::replaceItemsFromString(std::string &text, const std::vector<std::string> &items, const std::string &replacement)
{
    for(size_t i=0; i<items.size(); ++i) {
        boost::replace_all(text, items[i], replacement);
    }
}


int Utils::System::getThreadHardwareConcurrency()
{
    return (int)boost::thread::hardware_concurrency();
}


//! enables exception throw in the case of NaN, Inf
void Utils::EnableFloatingPointExceptions()
{
#ifdef DEBUG_FPE
#ifndef _WIN32
    std::cout << "Utils::EnableFloatingPointExceptions()  -> Enabling floating point exception debugging"
              << std::endl;
    feenableexcept(FE_DIVBYZERO | FE_INVALID | FE_OVERFLOW);
//    feenableexcept(-1);
#endif // _WIN32
#else
    std::cout << "Utils::EnableFloatingPointExceptions()  -> Can't enable floating point exceptions. Available in debug mode only."
              << std::endl;
#endif
}


