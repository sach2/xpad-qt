#ifndef CONTEXTMENUCREATOR_H
#define CONTEXTMENUCREATOR_H

#include <map>
#include <QAction>
#include <QPoint>
#include <set>
#include <vector>
#include <tuple>
#include <functional>

class PadWindow;

enum MenuItems
{
    NewPad = 0,
    EditPad,
    DeletePad,
    PadProperties
};

class ContextMenuCreator
{
    std::map<MenuItems, QAction*> menuItemToActionMap;
    QPoint pos;
    std::set<int> registeredItems;
    std::vector<int> sequenceOfItems;
public:
    ContextMenuCreator();
    void SetInfo(const QPoint& point){pos = point;}
    void registerFor(MenuItems menuItem, std::function<void()> action);
    void display();
};

#endif // CONTEXTMENUCREATOR_H
