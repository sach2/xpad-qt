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

void ContextMenuCreator::RegisterPlaceholder(MenuPlaceholders placeholder, IMenuPlaceholderProvider *action)
{
    if (placeholderToActionMap.find(placeholder) == placeholderToActionMap.end())
    {
        std::list<IMenuPlaceholderProvider*> actionlist;
        placeholderToActionMap.insert(make_pair(placeholder,actionlist));
    }
    std::list<IMenuPlaceholderProvider*>& list = placeholderToActionMap[placeholder];
    list.push_back(action);
}

void ContextMenuCreator::UnregisterPlaceholder(MenuPlaceholders placeholder, IMenuPlaceholderProvider *action)
{
    if (placeholderToActionMap.find(placeholder) != placeholderToActionMap.end())
    {
        placeholderToActionMap[placeholder].remove(action);
    }
}

void ContextMenuCreator::Create(MenuContext context)
{
    mainMenu.clear();
    switch(context)
    {
    case OnPad:
        DisplayOnPad();
        break;
    case OnTray:
        PrepareForTray();
        break;
    }
}
void ContextMenuCreator::DisplayOnPad()
{
    contextMenu.clear();
    auto padMenu = new QMenu("&Pad");
    padMenu->addAction(GetAction(NewPad));
    padMenu->addAction(GetAction(PadProperties));
    padMenu->addAction(GetAction(ClosePad));
    padMenu->addAction(GetAction(DeletePad));
    contextMenu.addMenu(padMenu);

    auto editMenu = new QMenu("&Edit");
    editMenu->addAction(GetAction(Readonly));
    editMenu->addAction(GetAction(Preferences));
    contextMenu.addMenu(editMenu);

    auto notesMenu = new QMenu("&Notes");
    notesMenu->addAction(GetAction(ShowAll));
    notesMenu->addAction(GetAction(HideAll));
    notesMenu->addSeparator();
    // add PadList placeholders from providers
    std::for_each(placeholderToActionMap.begin(), placeholderToActionMap.end(),
                  [&notesMenu](pair<MenuPlaceholders, std::list<IMenuPlaceholderProvider*>> entry)
    {
        if (entry.first == PadList)
        {
            std::for_each(entry.second.begin(), entry.second.end(),
                  [&notesMenu](IMenuPlaceholderProvider* provider)
            {
                provider->AddPlaceholderActions(PadList, *notesMenu);
            });
        }
    });
    contextMenu.addMenu(notesMenu);

    contextMenu.exec(pos);
}

void ContextMenuCreator::PrepareForTray()
{
    mainMenu.addAction(GetAction(NewPad));

    mainMenu.addAction(GetAction(Preferences));

    mainMenu.addAction(GetAction(ShowAll));
    mainMenu.addAction(GetAction(HideAll));
    mainMenu.addSeparator();
    // add PadList placeholders from providers
    std::for_each(placeholderToActionMap.begin(), placeholderToActionMap.end(),
                  [this](pair<MenuPlaceholders, std::list<IMenuPlaceholderProvider*>> entry)
    {
        if (entry.first == PadList)
        {
            std::for_each(entry.second.begin(), entry.second.end(),
                  [this](IMenuPlaceholderProvider* provider)
            {
                provider->AddPlaceholderActions(PadList, mainMenu);
            });
        }
    });
}

QAction* ContextMenuCreator::GetAction(MenuItems menuItem)
{
    return menuItemToActionMap[menuItem];
}

void ContextMenuCreator::SetNotesActions(const QList<QAction *> &actions)
{

}
