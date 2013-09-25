#include "padgroup.h"
#include<pad.h>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <padserializer.h>
#include <QTime>

PadGroup::PadGroup()
{
}

void PadGroup::CreateNewPad()
{
    QTime current_time = QTime::currentTime();
    qsrand((uint)current_time.msec());
    auto filename = QString("%1/info-%2").arg(directory).arg(qrand() % 1000);
    newPadWithInfo(filename);
}

Pad* PadGroup::newPadWithInfo(QString filename)
{
    auto pad = new Pad(PadSerializer(filename));
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
    QStringList filters;
    filters << "info-*";
    dir.setNameFilters(filters);
    dir.setFilter(QDir::Files);
    for (auto file : dir.entryInfoList())
    {
        auto absFilepath = file.absoluteFilePath();
        auto pad = newPadWithInfo(absFilepath);
        pad->loadFromFile();
    }
}

PadGroup::~PadGroup()
{
    for_each(pads.begin(), pads.end(), [](Pad*p){delete p;});
}
