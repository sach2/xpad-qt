#include "app.h"
#include <QAction>
#include <QMenu>
#include <QApplication>
#include <algorithm>
#include <functional>
#include <QDir>

#include <pad.h>

App::App(int argc, char* argv[]):QApplication(argc, argv),
    trayIcon(new QSystemTrayIcon),
    padGroup(new PadGroup())
{
    QString xpadHomeDir = QDir::homePath() + "/.xpad-qt";
    if (! QDir(xpadHomeDir).exists())
    {
        QDir::home().mkdir(xpadHomeDir);
    }
    // todo: refer icon from installed location
    iconPath = xpadHomeDir + "/xpad.png";

    padDirectory = xpadHomeDir + "/pads";
    if (! QDir(padDirectory).exists())
    {
        QDir::home().mkdir(padDirectory);
    }

    // init tray icon
    trayIcon->setIcon(QIcon(iconPath));
    trayIcon->setVisible(true);
    trayIcon->show();

    // init pad group
    padGroup->SetDirectory(padDirectory);
    connect(padGroup.get(), &PadGroup::numberOfPadsChanged,
            this, &App::CreateTrayMenu);

    // add new pad action
    contextMenuCreator.Register(NewPad, std::bind(&App::newPadRequested, this));
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
    delete trayIcon->contextMenu();
    auto trayIconMenu = new QMenu();

    // new pad action
    auto new_pad_action = new QAction("&New Pad", NULL);
    connect(new_pad_action, &QAction::triggered, this, &App::newPadRequested);
    trayIconMenu->addAction(new_pad_action);

    // add menu items for all pads
    int counter = 0;
    for(auto pad : padGroup->GetPads())
    {
        auto padaction = new QAction(
                    QString("&%1. %2").arg(++counter).arg(pad->getTitle()),
                    NULL);
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
