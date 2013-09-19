#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class Pad;
namespace Ui {
class PadWindow;
}

class PadWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit PadWindow(QWidget *parent = 0);
    ~PadWindow();
    void SetPad(Pad*);
    void SetText(QString text);
public:
    void closeEvent(QCloseEvent *);
private:
    Pad*pad;
    Ui::PadWindow *ui;
};

#endif // MAINWINDOW_H
