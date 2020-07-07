// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/GroupInfoCatalogue.h
//! @brief     Defines class GroupInfoCatalogue
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef GROUPINFOCATALOGUE_H
#define GROUPINFOCATALOGUE_H

#include "GUI/coregui/Models/GroupInfo.h"

//! Catalogue to hold info for GroupProperty creation.

class BA_CORE_API_ GroupInfoCatalogue
{
public:
    GroupInfoCatalogue();

    GroupInfo groupInfo(const QString& groupType) const;

    bool containsGroup(const QString& groupType) const;

private:
    void addInfo(const GroupInfo& info);
    QVector<GroupInfo> m_groups;
};

#endif // GROUPINFOCATALOGUE_H
