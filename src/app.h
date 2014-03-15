#ifndef APP_H
#define APP_H

#include <QSystemTrayIcon>
#include<QMenu>

#include <memory>
#include <thread>
#include "padgroup.h"
#include <QApplication>
#include "contextmenucreator.h"

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
private:
    void SavePadsThread();
public:
    App(int argc, char* argv[]);
    void CreateTrayMenu();
    void HideTray();
    void LoadPads();
    ContextMenuCreator contextMenuCreator;
public slots:
    void newPadRequested();
};

#endif // APP_H
