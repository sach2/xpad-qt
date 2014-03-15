#ifndef CONTEXTMENUCREATOR_H
#define CONTEXTMENUCREATOR_H

#include <map>
#include <QAction>
#include <QPoint>
#include <set>
#include <vector>
#include <tuple>
#include <functional>
#include <QMenu>

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
    QPoint pos;
    std::set<int> registeredItems;
    std::vector<int> padMenuItems;
    QMenu mainMenu;
public:
    ContextMenuCreator();
    void SetInfo(const QPoint& point){pos = point;}
    void Register(MenuItems menuItem, std::function<void()> action);
    void Unregister(MenuItems menuItem);
    void Display();
    QAction* GetAction(MenuItems menuItem);
};

#endif // CONTEXTMENUCREATOR_H
