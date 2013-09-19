#ifndef APP_H
#define APP_H

#include <QSystemTrayIcon>

#include <memory>

#include "padgroup.h"

// Application object, contains top level objects and functionality
class App : public QObject
{
    Q_OBJECT
    unique_ptr<QSystemTrayIcon> trayIcon;
    unique_ptr<PadGroup> padGroup;
    QString iconPath;
    QString padDirectory;
public:
    App();
    void CreateTrayMenu();
    void HideTray();
    void LoadPads();
public slots:
    void newPadRequested();
};

#endif // APP_H
