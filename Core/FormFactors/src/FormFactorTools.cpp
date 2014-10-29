// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/src/FormFactorTools.cpp
//! @brief     Implements global functions that facilitate IFormFactor handling.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorTools.h"
#include "FormFactorDWBAConstZ.h"
#include "FormFactorDWBAPolConstZ.h"

IFormFactor* FormFactorTools::createDWBAScalarFormFactor(
        IFormFactor* p_form_factor, double depth)
{
    FormFactorDWBAConstZ *p_result =
        new FormFactorDWBAConstZ(p_form_factor, depth);
    return p_result;
}

IFormFactor* FormFactorTools::createDWBAMatrixFormFactor(
        IFormFactor* p_form_factor, double depth)
{
    FormFactorDWBAPol *p_result(0);
    if (depth) {
        p_result = new FormFactorDWBAPolConstZ(p_form_factor, depth);
    }
    else {
        p_result = new FormFactorDWBAPol(p_form_factor);
    }
    return p_result;
}
