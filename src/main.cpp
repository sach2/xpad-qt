
#include "padwindow.h"

#include <QApplication>
#include <QtCore>
#include <QSystemTrayIcon>
#include <QMenu>

#include <memory>

#include <padgroup.h>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // create tray icon
    unique_ptr<QSystemTrayIcon> trayicon(new QSystemTrayIcon);
    trayicon->setIcon(QIcon("/home/sachin/.xpad-qt/xpad.png"));
    trayicon->setVisible(true);
    trayicon->show();

    // new pad action
    auto new_pad_action = new QAction("&New Pad", NULL);
    unique_ptr<PadGroup> padGroup(new PadGroup());
    QObject::connect(new_pad_action, SIGNAL(triggered()), (QObject*)padGroup.get(), SLOT(CreateNewPad()));

    // quit menu
    auto quitAction = new QAction("&Quit", NULL);
    trayicon->connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));

    // create menu
    auto trayIconMenu = new QMenu();
    trayIconMenu->addAction(new_pad_action);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);
    trayicon->setContextMenu(trayIconMenu);

    //wait untill quit message is posted
    int ret_value = a.exec();
    trayicon->hide();
    return ret_value;
}
