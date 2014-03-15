#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <propertieswindow.h>
#include <preferenceswindow.h>
#include <properties.h>
#include <QList>
#include <memory>
#include <QMenu>
#include "IMenuPlaceholderProvider.h"

class Pad;
namespace Ui {
class PadWindow;
}

using namespace std;

class PadWindow : public QMainWindow, public IMenuPlaceholderProvider
{
    Q_OBJECT
    
public:
    Properties properties;
    explicit PadWindow(QWidget *parent = 0);
    ~PadWindow();
    void SetPad(Pad*);
    void SetText(QString text);
    QString GetText();
    void SyncWithProperties();
    void AddPlaceholderActions(MenuPlaceholders placeholder, QMenu& menu);
public slots:
    void closeEvent(QCloseEvent *);
    void propertiesWindowRequested();
    void preferencesWindowRequested();
    void showContextMenu(const QPoint& pos);
    bool eventFilter(QObject *object, QEvent *event);
private:
    Pad*pad;
    QList<QAction*> actions;
    unique_ptr<PropertiesWindow> propertiesWindow;
    unique_ptr<PreferencesWindow> preferencesWindow;
    Ui::PadWindow *ui;
    void initContextMenu();
};

#endif // MAINWINDOW_H
