#include "padgroup.h"
#include<pad.h>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <padserializer.h>
#include <QTime>
#include<QDebug>
#include<app.h>

PadGroup::PadGroup()
{
    nextPadId = 0;
    padSaverThread = std::thread(&PadGroup::SavePadsThreadFunc, this);
}
void PadGroup::SavePadsThreadFunc()
{
    while (true)
    {
        using map_type = decltype(padIdToInfoMap);
            for_each(padIdToInfoMap.begin(), padIdToInfoMap.end(),
                     [this](const map_type::value_type& el){
                el.second->serializer->SaveContents(el.second->padWindow->GetText());
            });
            this_thread::sleep_for(chrono::seconds(5));
    }
}

void PadGroup::CreateNewPad()
{
    QTime current_time = QTime::currentTime();
    qsrand((uint)current_time.msec());
    int num = qrand();
    auto filename = QString("%1/info-%2").arg(directory).arg(num % 1000);
    auto contentFilename = QString("%1/contents-%2").arg(directory).arg(num % 1000);
    AddPad(filename, contentFilename);
    emit numberOfPadsChanged();
}

void PadGroup::AddPad(QString infoFilename, QString contentsFilename)
{
    auto padId = nextPadId++;
    unique_ptr<Pad> pad(new Pad());
    unique_ptr<PadInfo> padInfo(new PadInfo());
    unique_ptr<PadSerializer> serializer;
    if (contentsFilename == "")
        serializer.reset(new PadSerializer(infoFilename));
    else
        serializer.reset(new PadSerializer(infoFilename, contentsFilename));

    pad->windowBuffer = serializer->LoadContents();
    padInfo->pad = std::move(pad);
    padInfo->padWindow.reset(new PadWindow());
    padInfo->padWindow->padId = padId;
    padInfo->padWindow->SetText(serializer->LoadContents());
    padInfo->padWindow->show();
    padInfo->serializer = std::move(serializer);

    connect(padInfo->padWindow.get(), &PadWindow::deletePadRequested, [&](int id){
        padIdToInfoMap[id]->padWindow->hide();
        padIdToInfoMap[id]->serializer->DeletePad();
        padIdToInfoMap.erase(id);
    });

    padIdToInfoMap[padId] = std::move(padInfo);
}

void PadGroup::AddPlaceholderActions(MenuPlaceholders placeholder, QMenu& menu)
{
    if (placeholder == MenuPlaceholders::PadList)
    {
        using map_type = decltype(padIdToInfoMap);
        for_each(padIdToInfoMap.begin(), padIdToInfoMap.end(),
                 [this,&menu](const map_type::value_type& entry){
                    auto switchToPadAction = new QAction(entry.second->padWindow->GetText(),NULL);
                    connect(switchToPadAction, &QAction::triggered,
                            [this, &entry](){
                                entry.second->padWindow->activateWindow();
                    });
                    menu.addAction(switchToPadAction);
        });
    }
}


void PadGroup::SetDirectory(QString dir)
{
    directory = dir;
}

void PadGroup::LoadPads()
{
    ((App*)qApp)->contextMenuCreator.RegisterPlaceholder(PadList, this);
    QDir dir(directory);
    QStringList filters;
    filters << "info-*";
    dir.setNameFilters(filters);
    dir.setFilter(QDir::Files);
    for (auto file : dir.entryInfoList())
    {
        auto absFilepath = file.absoluteFilePath();
        AddPad(absFilepath);
    }
}

PadGroup::~PadGroup()
{
}
