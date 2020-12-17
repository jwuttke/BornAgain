//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/viewmodel/mvvm/viewmodel/standardchildrenstrategies.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_MVVM_VIEWMODEL_MVVM_VIEWMODEL_STANDARDCHILDRENSTRATEGIES_H
#define BORNAGAIN_MVVM_VIEWMODEL_MVVM_VIEWMODEL_STANDARDCHILDRENSTRATEGIES_H

//! @file childrenstrategies.h
//! @brief Collection of strategies to find children, actual of fictional, of given SessionItem.
//! Used for ViewModel generation when underlying SessionModel changes its layout.

#include "mvvm/interfaces/childrenstrategyinterface.h"

namespace ModelView {

class SessionItem;

//! Strategy to find children of given item: gives all actual children back.

class MVVM_VIEWMODEL_EXPORT AllChildrenStrategy : public ChildrenStrategyInterface {
public:
    std::vector<SessionItem*> children(const SessionItem* item) const override;
};

//! Strategy to find children of given item: only top level items will be given, all
//! property items will be filtered out.

class MVVM_VIEWMODEL_EXPORT TopItemsStrategy : public ChildrenStrategyInterface {
public:
    std::vector<SessionItem*> children(const SessionItem* item) const override;
};

//! Strategy to find children of given item: only property item will be given, all top level items
//! will be filtered out, all inactive children of GroupItem will be filtered out. See example
//! in code.

class MVVM_VIEWMODEL_EXPORT PropertyItemsStrategy : public ChildrenStrategyInterface {
public:
    std::vector<SessionItem*> children(const SessionItem* item) const override;
};

//! Strategy to find children of given item: flat alignment.
//! Acts as PropertyItemStrategy, with the difference that active subproperties of
//! GroupItem are moved to the same parent, as GroupItem itself. See example in code.

class MVVM_VIEWMODEL_EXPORT PropertyItemsFlatStrategy : public ChildrenStrategyInterface {
public:
    std::vector<SessionItem*> children(const SessionItem* item) const override;
};

} // namespace ModelView

#endif // BORNAGAIN_MVVM_VIEWMODEL_MVVM_VIEWMODEL_STANDARDCHILDRENSTRATEGIES_H
