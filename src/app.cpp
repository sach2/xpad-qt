#include "app.h"
#include <QAction>
#include <QMenu>
#include <QApplication>

#include <pad.h>

App::App():trayIcon(new QSystemTrayIcon), padGroup(new PadGroup())
{
    // create tray icon
    trayIcon->setIcon(QIcon("/home/sachin/icon.png"));
    trayIcon->setVisible(true);
    trayIcon->show();

    // test - create pad to avoid going to tray every time just to create
    padGroup->CreateNewPad();
}

void App::CreateTrayMenu()
{
    auto trayIconMenu = new QMenu();

    // new pad action
    auto new_pad_action = new QAction("&New Pad", NULL);
    QObject::connect(new_pad_action, &QAction::triggered, this, &App::newPadRequested);
    trayIconMenu->addAction(new_pad_action);

    // add menu items for all pads
    for(auto pad : padGroup->GetPads())
    {
        auto padaction = new QAction("Pad", NULL);
        trayIcon->connect(padaction, &QAction::triggered, pad, &Pad::show);
        trayIconMenu->addAction(padaction);
    }

    // quit menu
    auto quitAction = new QAction("&Quit", NULL);
    trayIcon->connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
    //todo - not working, should work
    //trayIcon->connect(quitAction, SIGNAL(triggered()), qApp, &QApplication::quit);
    trayIconMenu->addAction(quitAction);

    trayIcon->setContextMenu(trayIconMenu);
}

void App::newPadRequested()
{
    padGroup->CreateNewPad();
    CreateTrayMenu();
}

void App::HideTray()
{
    trayIcon->hide();
}

