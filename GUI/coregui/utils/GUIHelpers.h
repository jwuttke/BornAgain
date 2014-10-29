// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      utils/GUIHelpers.h
//! @brief     Defines GUI helper functions.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef GUIHELPERS_H
#define GUIHELPERS_H

#include "WinDllMacros.h"
#include <QWidget>
#include <QString>
#include <exception>

class QVariant;

namespace GUIHelpers
{
class BA_CORE_API_ Error : public std::exception
{
public:
    explicit Error(const QString &message) throw()
        : message(message) {}
    ~Error() throw() {}

    const char *what() const throw() { return message.toStdString().c_str(); }

private:
//    const char *message;
    QString message;
};

BA_CORE_API_ void information(QWidget *parent, const QString &title,
        const QString &text, const QString &detailedText=QString());
BA_CORE_API_ void warning(QWidget *parent, const QString &title,
        const QString &text, const QString &detailedText=QString());
BA_CORE_API_ bool question(QWidget *parent, const QString &title,
        const QString &text, const QString &detailedText=QString(),
        const QString &yesText=QObject::tr("&Yes"),
        const QString &noText=QObject::tr("&No"));
BA_CORE_API_ bool okToDelete(QWidget *parent, const QString &title,
        const QString &text, const QString &detailedText=QString());

BA_CORE_API_ int getVariantType(const QVariant &variant);

}

#endif // GUIHELPERS_H

