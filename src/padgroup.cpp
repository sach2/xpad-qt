#include "padgroup.h"
#include<pad.h>
#include <QDir>
#include <QFile>
#include <QTextStream>

PadGroup::PadGroup()
{
    newPadIndex = 0;
}

void PadGroup::CreateNewPad()
{
    auto filename = QString("%1/%2").arg(directory).arg(newPadIndex);
    newPadWithInfo(filename);
    ++newPadIndex;
}

Pad* PadGroup::newPadWithInfo(QString filename)
{
    auto pad = new Pad();
    pad->setFilename(filename);
    padToFilenameMap[pad] = filename;
    pads.push_back(pad);
    return pad;
}

void PadGroup::SetDirectory(QString dir)
{
    directory = dir;
}

const list<Pad*>& PadGroup::GetPads()
{
    return pads;
}

void PadGroup::LoadPads()
{
    QDir dir(directory);
    dir.setFilter(QDir::Files);
    for (auto file : dir.entryInfoList())
    {
        auto absFilepath = file.absoluteFilePath();
        // update new pad index
        auto fileno = file.fileName().toInt();
        if (fileno > newPadIndex)
            newPadIndex = fileno;
        auto pad = newPadWithInfo(absFilepath);
        pad->loadFromFile();
    }
    ++newPadIndex;
}

PadGroup::~PadGroup()
{
    for_each(pads.begin(), pads.end(), [](Pad*p){delete p;});
}
