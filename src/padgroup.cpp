#include "padgroup.h"
#include<pad.h>

PadGroup::PadGroup()
{
}

void PadGroup::CreateNewPad()
{
    auto pad = new Pad();
    pads.push_back(pad);
}

PadGroup::~PadGroup()
{
    for(auto pad : pads)
    {
        delete pad;
    }
}
