#include <QApplication>
#include <QtCore>

#include <app.h>
using namespace std;

int main(int argc, char *argv[])
{
    App app(argc, argv);
    app.LoadPads();
    app.CreateTrayMenu();

    //wait untill quit message is posted
    int ret_value = app.exec();
    app.HideTray();
    return ret_value;
}

