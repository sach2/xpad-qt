#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <propertieswindow.h>
#include <properties.h>

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
public slots:
    void closeEvent(QCloseEvent *);
    void onPropertiesButtonPressed();
private:
    Pad*pad;
    Properties properties;
    unique_ptr<PropertiesWindow> propertiesWindow;
    Ui::PadWindow *ui;

private:
    void SyncWithProperties();

};

#endif // MAINWINDOW_H
