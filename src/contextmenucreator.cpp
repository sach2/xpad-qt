#include "contextmenucreator.h"
#include <algorithm>
#include"pad.h"

ContextMenuCreator::ContextMenuCreator()
{
    sequenceOfItems.push_back(PadProperties);
}
void ContextMenuCreator::registerFor(MenuItems menuItem, std::function<void()> action)
{
    registeredItems.insert(menuItem);
    auto preferencesAction = new QAction(QIcon::fromTheme("document-properties"),
                                         "P&references", nullptr);
    preferencesAction->setShortcut(QKeySequence("Ctrl+p"));
    preferencesAction->connect(preferencesAction, &QAction::triggered, action);
    menuItemToActionMap.insert(std::make_pair(menuItem, preferencesAction));
}
void ContextMenuCreator::display()
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
