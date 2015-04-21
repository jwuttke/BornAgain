// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/inc/FormFactorBox.h
//! @brief     Defines class FormFactorBox.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORBOX_H
#define FORMFACTORBOX_H

#include "IFormFactorBorn.h"

//! @class FormFactorBox
//! @ingroup formfactors
//! @brief The formfactor for a rectangular box.

class BA_CORE_API_ FormFactorBox : public IFormFactorBorn
{
public:
    //! @brief Box constructor
    //! @param length of Box's base
    //! @param width of Box's base
    //! @param height of Box
    FormFactorBox( double length, double width, double height)
        : m_length(length), m_width(width), m_height(height) {

            setName("FormFactorBox");
            check_initialization();
            init_parameters();
        }

    virtual ~FormFactorBox() {}

    FormFactorBox *clone() const;

    virtual void accept(ISampleVisitor *visitor) const { visitor->visit(this); }

    int getNumberOfStochasticParameters() const { return 3; }

    //! Returns length of Box
    double getLength() const { return m_length; }

    //! Returns height of Box
    double getHeight() const { return m_height; }

    //! Returns radius of Box
    double getRadius() const { return m_length/2.0; }

    //! Returns width of Box
    double getWidth() const { return m_width; }

    virtual complex_t evaluate_for_q(const cvector_t& q) const;

protected:
    virtual bool check_initialization() const;
    virtual void init_parameters();

private:
    double m_length;
    double m_width;
    double m_height;
};

#endif // FORMFACTORBOX_H


