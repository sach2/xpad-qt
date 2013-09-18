
#include <QApplication>
#include <QtCore>

#include <app.h>
using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    App app;
    app.CreateTrayMenu();

    //wait untill quit message is posted
    int ret_value = a.exec();
    app.HideTray();
    return ret_value;
}

