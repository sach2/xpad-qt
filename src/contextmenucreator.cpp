#include "contextmenucreator.h"
#include <algorithm>
#include"pad.h"

ContextMenuCreator::ContextMenuCreator()
{
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

    auto readonlyAction = new QAction("&Readonly", nullptr);
    readonlyAction->setCheckable(true);
    menuItemToActionMap[Readonly] = readonlyAction;
}
void ContextMenuCreator::Register(MenuItems menuItem, std::function<void()> action)
{
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
    padMenu->addAction(GetAction(NewPad));
    padMenu->addAction(GetAction(PadProperties));
    padMenu->addAction(GetAction(ClosePad));
    padMenu->addAction(GetAction(DeletePad));
    mainMenu.addMenu(padMenu);

    auto editMenu = new QMenu("&Edit");
    editMenu->addAction(GetAction(Readonly));
    editMenu->addAction(GetAction(Preferences));
    mainMenu.addMenu(editMenu);

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
