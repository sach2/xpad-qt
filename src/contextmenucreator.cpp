#include "contextmenucreator.h"
#include <algorithm>
#include"pad.h"

ContextMenuCreator::ContextMenuCreator()
{
    auto closeAction = new QAction(QIcon::fromTheme("window-close"),
                                   "&Close", nullptr);
    closeAction->setShortcut(QKeySequence::Close);
    sequenceOfItems.push_back(ClosePad);
    menuItemToActionMap.insert(std::make_pair(ClosePad, closeAction));

    auto preferencesAction = new QAction(QIcon::fromTheme("document-properties"),
                                         "P&references", nullptr);
    preferencesAction->setShortcut(QKeySequence("Ctrl+p"));
    sequenceOfItems.push_back(Preferences);
    menuItemToActionMap.insert(std::make_pair(Preferences, preferencesAction));
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
    QObject::disconnect(menu_action, 0, 0, 0);
}
void ContextMenuCreator::Display()
{
    auto editMenu = new QMenu("&Edit");
    std::for_each(sequenceOfItems.begin(), sequenceOfItems.end(),
                  [this, &editMenu](int menuItem)
    {
        if (registeredItems.find(menuItem) != registeredItems.end())
        {
            auto a = (*menuItemToActionMap.find((MenuItems)menuItem));
            editMenu->addAction(a.second);

        }
    }
    );
    editMenu->exec(pos);
}
QAction* ContextMenuCreator::GetAction(MenuItems menuItem)
{
    return menuItemToActionMap[menuItem];
}
