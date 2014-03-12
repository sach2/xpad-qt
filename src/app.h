#ifndef APP_H
#define APP_H

#include <QSystemTrayIcon>
#include<QMenu>

#include <memory>
#include <thread>
#include "padgroup.h"
#include <QApplication>

using namespace std;

// Application object, contains top level objects and functionality
class App : public QApplication
{
    Q_OBJECT
    unique_ptr<QSystemTrayIcon> trayIcon;
    unique_ptr<PadGroup> padGroup;
    QString iconPath;
    QString padDirectory;
    std::thread padSaverThread;
    QMenu contextMenu;
private:
    void SavePadsThread();
public:
    App(int argc, char* argv[]);
    void CreateTrayMenu();
    void HideTray();
    void LoadPads();
    void AddMenu(QMenu* menu);
    QMenu& GetContextMenu();
public slots:
    void newPadRequested();
};

#endif // APP_H
