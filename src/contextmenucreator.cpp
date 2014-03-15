#include "contextmenucreator.h"
#include <algorithm>
#include"pad.h"

ContextMenuCreator::ContextMenuCreator()
{
    auto newPadAction = new QAction(QIcon::fromTheme("window-new"),
                                    "&New pad", nullptr);
    newPadAction->setShortcutContext(Qt::ApplicationShortcut);
    newPadAction->setShortcut(QKeySequence::New);
    sequenceOfItems.push_back(NewPad);
    menuItemToActionMap[NewPad] = newPadAction;

    auto propertiesAction = new QAction(QIcon::fromTheme("document-properties"),
                                        "&Properties", nullptr);
    propertiesAction->setShortcut(QKeySequence("Ctrl+,"));
    sequenceOfItems.push_back(PadProperties);
    menuItemToActionMap[PadProperties] = propertiesAction;

    auto closeAction = new QAction(QIcon::fromTheme("window-close"),
                                   "&Close", nullptr);
    closeAction->setShortcut(QKeySequence::Close);
    sequenceOfItems.push_back(ClosePad);
    menuItemToActionMap[ClosePad] = closeAction;

    auto preferencesAction = new QAction(QIcon::fromTheme("document-properties"),
                                         "P&references", nullptr);
    preferencesAction->setShortcut(QKeySequence("Ctrl+p"));
    sequenceOfItems.push_back(Preferences);
    menuItemToActionMap[Preferences] = preferencesAction;
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
