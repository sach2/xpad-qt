#ifndef MENUPLACEHOLDERPROVIDER_H
#define MENUPLACEHOLDERPROVIDER_H

enum MenuPlaceholders
{
    PadList = 0
};

class IMenuPlaceholderProvider
{
public:
    virtual void AddPlaceholderActions(MenuPlaceholders placeholder, QMenu& menu) = 0;
};

#endif // MENUPLACEHOLDERPROVIDER_H
