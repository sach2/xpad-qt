#ifndef PROPERTIES_H
#define PROPERTIES_H

#include <QColor>

class Properties
{
public:
    QColor textColor;
    QColor backColor;
public:
    Properties();
    bool operator==(const Properties& rhs);
};

#endif // PROPERTIES_H
