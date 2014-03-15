#include "contextmenucreator.h"
#include <algorithm>
#include"pad.h"

ContextMenuCreator::ContextMenuCreator()
{
    padMenuItems.push_back(NewPad);
    padMenuItems.push_back(PadProperties);
    padMenuItems.push_back(ClosePad);
    padMenuItems.push_back(Preferences);
    padMenuItems.push_back(DeletePad);

    auto newPadAction = new QAction(QIcon::fromTheme("window-new"),
                                    "&New pad", nullptr);
    newPadAction->setShortcutContext(Qt::ApplicationShortcut);
    newPadAction->setShortcut(QKeySequence::New);
    menuItemToActionMap[NewPad] = newPadAction;

    auto propertiesAction = new QAction(QIcon::fromTheme("document-properties"),
                                        "&Properties", nullptr);
    propertiesAction->setShortcut(QKeySequence("Ctrl+,"));
    menuItemToActionMap[PadProperties] = propertiesAction;

    auto closeAction = new QAction(QIcon::fromTheme("window-close"),
                                   "&Close", nullptr);
    closeAction->setShortcut(QKeySequence::Close);
    menuItemToActionMap[ClosePad] = closeAction;

    auto preferencesAction = new QAction(QIcon::fromTheme("document-properties"),
                                         "P&references", nullptr);
    preferencesAction->setShortcut(QKeySequence("Ctrl+p"));
    menuItemToActionMap[Preferences] = preferencesAction;

    auto deletePadAction = new QAction(QIcon::fromTheme("edit-delete"),
                                       "&Delete pad", nullptr);
    deletePadAction->setShortcut(QKeySequence("Ctrl+Del"));
    menuItemToActionMap[DeletePad] = deletePadAction;

    auto showAllAction = new QAction(QIcon::fromTheme("document-properties"),
                                         "Show All", nullptr);
    menuItemToActionMap[ShowAll] = showAllAction;

    auto hideAllAction = new QAction(QIcon::fromTheme("document-properties"),
                                         "Hide All", nullptr);
    menuItemToActionMap[HideAll] = hideAllAction;
}
void ContextMenuCreator::Register(MenuItems menuItem, std::function<void()> action)
{
    if (registeredItems.find(menuItem) == registeredItems.end())
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
    mainMenu.clear();
    auto padMenu = new QMenu("&Pad");
    std::for_each(padMenuItems.begin(), padMenuItems.end(),
                  [this, &padMenu](int menuItem)
    {
        if (registeredItems.find(menuItem) != registeredItems.end())
        {
            auto a = (*menuItemToActionMap.find((MenuItems)menuItem));
            padMenu->addAction(a.second);
        }
    }
    );
    mainMenu.addMenu(padMenu);
    auto notesMenu = new QMenu("&Notes");
    notesMenu->addAction(GetAction(ShowAll));
    notesMenu->addAction(GetAction(HideAll));
    mainMenu.addMenu(notesMenu);
    mainMenu.exec(pos);
}
QAction* ContextMenuCreator::GetAction(MenuItems menuItem)
{
    return menuItemToActionMap[menuItem];
}
