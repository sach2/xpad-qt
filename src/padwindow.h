#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <propertieswindow.h>
#include <properties.h>
#include <QList>
#include <memory>

class Pad;
namespace Ui {
class PadWindow;
}

using namespace std;

class PadWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit PadWindow(QWidget *parent = 0);
    ~PadWindow();
    void SetPad(Pad*);
    void SetText(QString text);
    QString GetText();
    Properties properties;
public slots:
    void closeEvent(QCloseEvent *);
    void propertiesWindowRequested();
    void showContextMenu(const QPoint& pos);
private:
    Pad*pad;
    QList<QAction*> actions;
    unique_ptr<PropertiesWindow> propertiesWindow;
    Ui::PadWindow *ui;


private:
    void initContextMenu();
public:
    void SyncWithProperties();

};

#endif // MAINWINDOW_H
