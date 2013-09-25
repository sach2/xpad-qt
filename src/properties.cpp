#include "properties.h"

Properties::Properties()
{
    textColor = QColor::fromRgb(10, 10, 10);
    backColor = QColor::fromRgb(230, 230, 230);
}

bool Properties::operator ==(const Properties& rhs)
{
    return (textColor == rhs.textColor
            && backColor == rhs.backColor);
}
