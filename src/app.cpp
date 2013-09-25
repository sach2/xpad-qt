#include "app.h"
#include <QAction>
#include <QMenu>
#include <QApplication>
#include <algorithm>
#include <functional>

#include <pad.h>

App::App():
    trayIcon(new QSystemTrayIcon),
    padGroup(new PadGroup())
{
    iconPath = "/home/sachin/.xpad-qt/xpad.png";
    padDirectory = "/home/sachin/.xpad-qt/pads";

    // init tray icon
    trayIcon->setIcon(QIcon(iconPath));
    trayIcon->setVisible(true);
    trayIcon->show();

    // init pad group
    padGroup->SetDirectory(padDirectory);
    connect(padGroup.get(), &PadGroup::numberOfPadsChanged,
            this, &App::CreateTrayMenu);
}

void App::SavePadsThread()
{
    while (true)
    {
        for_each(padGroup->GetPads().begin(), padGroup->GetPads().end(),
                 bind(&Pad::saveToFile, placeholders::_1));
        this_thread::sleep_for(chrono::seconds(5));
    }
}

void App::CreateTrayMenu()
{
    auto trayIconMenu = new QMenu();

    // new pad action
    auto new_pad_action = new QAction("&New Pad", NULL);
    connect(new_pad_action, &QAction::triggered, this, &App::newPadRequested);
    trayIconMenu->addAction(new_pad_action);

    // add menu items for all pads
    int counter = 0;
    for(auto pad : padGroup->GetPads())
    {
        auto padaction = new QAction(QString("&%1").arg(counter++), NULL);
        //        trayIcon->connect(padaction, &QAction::triggered, pad, &Pad::show);
        connect(padaction, &QAction::triggered, pad, &Pad::show);
        trayIconMenu->addAction(padaction);
    }

    // quit menu
    auto quitAction = new QAction("&Quit", NULL);
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
    //todo - not working, should work according to new syntax
    //trayIcon->connect(quitAction, SIGNAL(triggered()), qApp, &QApplication::quit);
    trayIconMenu->addAction(quitAction);

    trayIcon->setContextMenu(trayIconMenu);
}

// new pad action slot
void App::newPadRequested()
{
    padGroup->CreateNewPad();
    // recreate tray menu - can we optimize?
    CreateTrayMenu();
}

// load saved pads
void App::LoadPads()
{
    padGroup->LoadPads();
    padSaverThread = std::thread(&App::SavePadsThread, this);
}

void App::HideTray()
{
    trayIcon->hide();
    padSaverThread.detach();
}

