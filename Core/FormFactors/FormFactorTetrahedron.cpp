// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/FormFactorTetrahedron.cpp
//! @brief     Implements class FormFactorTetrahedron.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015-16
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorTetrahedron.h"
#include "MathFunctions.h"
#include "BornAgainNamespace.h"
#include "IntegratorComplex.h"

const FormFactorPolyhedron::Topology FormFactorTetrahedron::topology = {
    { { 2, 1, 0 }, false },
    { { 0, 1, 4, 3 }, false },
    { { 1, 2, 5, 4 }, false },
    { { 2, 0, 3, 5 }, false },
    { { 3, 4, 5 }, false }
};


//! @brief Tetrahedron constructor
//! @param base_edge of a side of Tetrahedron's base
//! @param height of Tetrahedron
//! @param angle in radians between base and facet

FormFactorTetrahedron::FormFactorTetrahedron(double base_edge, double height, double alpha)
    : FormFactorPolyhedron()
    , m_base_edge(base_edge)
    , m_height(height)
    , m_alpha(alpha)
{
    setName(BornAgain::FFTetrahedronType);
    registerParameter(BornAgain::Height, &m_height, AttLimits::n_positive());
    registerParameter(BornAgain::BaseEdge, &m_base_edge, AttLimits::n_positive());
    registerParameter(BornAgain::Alpha, &m_alpha, AttLimits::n_positive());
    onChange();
}

void FormFactorTetrahedron::onChange()
{
    double cot_alpha = MathFunctions::cot(m_alpha);
    if( !std::isfinite(cot_alpha) || cot_alpha<0 )
        throw Exceptions::OutOfBoundsException("pyramid angle alpha out of bounds");
    if (cot_alpha * 2*std::sqrt(3.) * m_height > m_base_edge) {
        std::ostringstream ostr;
        ostr << "FormFactorTetrahedron() -> Error in class initialization with parameters ";
        ostr << " height:" << m_height;
        ostr << " base_edge:" << m_base_edge;
        ostr << " alpha[rad]:" << m_alpha << "\n\n";
        ostr << "Check for '2.*sqrt(3.) * height <= base_edge*tan(alpha)' failed.";
        throw Exceptions::ClassInitializationException(ostr.str());
    }

    double a = m_base_edge;
    double as = a/2;
    double ac = a/sqrt(3)/2;
    double ah = a/sqrt(3);
    double b = a - 2*sqrt(3)*m_height*cot_alpha;
    double bs = b/2;
    double bc = b/sqrt(3)/2;
    double bh = b/sqrt(3);

    setVertices( {
        // base:
        { -as, -ac, 0. },
        {  as, -ac, 0. },
        {  0.,  ah, 0. },
        // top:
        { -bs, -bc, m_height },
        {  bs, -bc, m_height },
        {  0.,  bh, m_height } } );
    m_z_origin = 0;
    m_sym_Ci = false;
    FormFactorPolyhedron::precompute();
}

FormFactorTetrahedron* FormFactorTetrahedron::clone() const
{
    return new FormFactorTetrahedron(m_base_edge, m_height, m_alpha);
}

void FormFactorTetrahedron::accept(ISampleVisitor *visitor) const
{
    visitor->visit(this);
}
