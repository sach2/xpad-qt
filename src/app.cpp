#include "app.h"
#include <QAction>
#include <QMenu>
#include <QApplication>

#include <pad.h>

App::App():trayIcon(new QSystemTrayIcon), padGroup(new PadGroup())
{
    iconPath = "/home/sachin/.xpad-qt/xpad.png";
    padDirectory = "/home/sachin/.xpad-qt/pads";

    // init tray icon
    trayIcon->setIcon(QIcon(iconPath));
    trayIcon->setVisible(true);
    trayIcon->show();

    // init pad group
    padGroup->SetDirectory(padDirectory);
}

void App::CreateTrayMenu()
{
    auto trayIconMenu = new QMenu();

    // new pad action
    auto new_pad_action = new QAction("&New Pad", NULL);
    QObject::connect(new_pad_action, &QAction::triggered, this, &App::newPadRequested);
    trayIconMenu->addAction(new_pad_action);

    // add menu items for all pads
    int counter = 0;
    for(auto pad : padGroup->GetPads())
    {
        auto padaction = new QAction(QString("&%1").arg(counter++), NULL);
        trayIcon->connect(padaction, &QAction::triggered, pad, &Pad::show);
        trayIconMenu->addAction(padaction);
    }

    // quit menu
    auto quitAction = new QAction("&Quit", NULL);
    trayIcon->connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
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
}

void App::HideTray()
{
    trayIcon->hide();
}

