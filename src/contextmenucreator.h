#ifndef CONTEXTMENUCREATOR_H
#define CONTEXTMENUCREATOR_H

#include <map>
#include <QAction>
#include <QPoint>
#include <set>
#include <vector>
#include <list>
#include <tuple>
#include <functional>
#include <QMenu>
#include "IMenuPlaceholderProvider.h"

class PadWindow;

enum MenuItems
{
    NewPad = 0,
    EditPad,
    ClosePad,
    DeletePad,
    PadProperties,
    Readonly,
    Preferences,
    ShowAll,
    HideAll
};

class ContextMenuCreator
{
    std::map<MenuItems, QAction*> menuItemToActionMap;
    std::map<MenuPlaceholders, std::list<IMenuPlaceholderProvider*>> placeholderToActionMap;
    QPoint pos;
    QMenu mainMenu;
public:
    ContextMenuCreator();
    void SetInfo(const QPoint& point){pos = point;}
    void Register(MenuItems menuItem, std::function<void()> action);
    void RegisterPlaceholder(MenuPlaceholders placeholder, IMenuPlaceholderProvider* action);
    void UnregisterPlaceholder(MenuPlaceholders, IMenuPlaceholderProvider* action);
    void Unregister(MenuItems menuItem);
    void Display();
    QAction* GetAction(MenuItems menuItem);
};

#endif // CONTEXTMENUCREATOR_H
