#include "contextmenucreator.h"
#include <algorithm>
#include"pad.h"

ContextMenuCreator::ContextMenuCreator()
{
    sequenceOfItems.push_back(PadProperties);
    auto preferencesAction = new QAction(QIcon::fromTheme("document-properties"),
                                         "P&references", nullptr);
    preferencesAction->setShortcut(QKeySequence("Ctrl+p"));
    menuItemToActionMap.insert(std::make_pair(PadProperties, preferencesAction));
}
void ContextMenuCreator::Register(MenuItems menuItem, std::function<void()> action)
{
    registeredItems.insert(menuItem);
    auto menu_action = GetAction(menuItem);
    menu_action->connect(menu_action, &QAction::triggered, action);
}
void ContextMenuCreator::Unregister(MenuItems menuItem)
{
    auto menu_action = GetAction(menuItem);
    //QObject::disconnect(menu_action, &QAction::triggered, padWindow);
    QObject::disconnect(menu_action, 0, 0, 0);
}
void ContextMenuCreator::Display()
{
    QAction* t;
    std::for_each(sequenceOfItems.begin(), sequenceOfItems.end(),
                  [this, &t](int menuItem)
    {
        if (registeredItems.find(menuItem) != registeredItems.end())
        {
            auto a = (*menuItemToActionMap.find((MenuItems)menuItem));
            t = a.second;

        }
    }
    );
    auto editMenu = new QMenu("&Edit");
    editMenu->addAction(t);
    editMenu->exec(pos);
}
QAction* ContextMenuCreator::GetAction(MenuItems menuItem)
{
    return menuItemToActionMap[menuItem];
}
