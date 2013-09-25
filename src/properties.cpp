#include "properties.h"

Properties::Properties()
{
    textColor = QColor::fromRgb(0, 85, 0);
    backColor = QColor::fromRgb(240, 240, 119);
}

bool Properties::operator ==(const Properties& rhs)
{
    return (textColor == rhs.textColor
            && backColor == rhs.backColor);
}
