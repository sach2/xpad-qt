
#include "padwindow.h"
#include "ui_padwindow.h"

#include<QDebug>
#include<QCloseEvent>
#include<QMenu>
#include<string>
#include<istream>
#include<pad.h>
#include<preferenceswindow.h>

PadWindow::PadWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PadWindow)
{
    ui->setupUi(this);
    SyncWithProperties();
    initContextMenu();
}

void PadWindow::initContextMenu()
{
    auto newPadAction = new QAction("&New pad", ui->textEdit);
    newPadAction->setShortcutContext(Qt::ApplicationShortcut);
    newPadAction->setShortcut(QKeySequence::New);
    //newPadAction->setShortcut(QKeySequence(Qt::Key_PageDown));
    connect(newPadAction, &QAction::triggered, [&](){
        emit pad->newPadRequested();
    });
    //ui->textEdit->addAction(newPadAction);

    auto propertiesAction = new QAction("&Properties", ui->textEdit);
    propertiesAction->setShortcut(QKeySequence("Ctrl+,"));
    connect(propertiesAction, &QAction::triggered, [&](){
        propertiesWindowRequested();;
    });
    //ui->textEdit->addAction(propertiesAction);

    auto closeAction = new QAction("&Close", ui->textEdit);
    closeAction->setShortcut(QKeySequence::Close);
    connect(closeAction, &QAction::triggered, [&](){
        hide();
    });
    //ui->textEdit->addAction(closeAction);

    auto deletePadAction = new QAction("&Delete pad", ui->textEdit);
    deletePadAction->setShortcut(QKeySequence("Shift+Del"));
    connect(deletePadAction, &QAction::triggered,[&](){
        emit pad->deletePadRequested(pad);
    });
    //ui->textEdit->addAction(deletePadAction);

    padMenu.setTitle("&Pad");
    padMenu.addAction(newPadAction);
    padMenu.addAction(propertiesAction);
    padMenu.addAction(closeAction);
    padMenu.addAction(deletePadAction);

    auto readonlyAction = new QAction("&Readonly", ui->textEdit);
    readonlyAction->setCheckable(true);
    readonlyAction->setChecked(properties.readonly);
    connect(readonlyAction, &QAction::triggered, [&](){
        properties.readonly = !properties.readonly;
        ui->textEdit->setReadOnly(properties.readonly);
    });
    //ui->textEdit->addAction(readonlyAction);

    auto preferencesAction = new QAction("P&references", ui->textEdit);
    preferencesAction->setShortcut(QKeySequence("Ctrl+p"));
    connect(preferencesAction, &QAction::triggered, [&](){
        preferencesWindowRequested();
    });
    //ui->textEdit->addAction(preferencesAction);

    editMenu.setTitle("&Edit");
    editMenu.addAction(readonlyAction);
    editMenu.addAction(preferencesAction);

    ui->textEdit->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->textEdit, &QWidget::customContextMenuRequested,
            this, &PadWindow::showContextMenu);
}

void PadWindow::showContextMenu(const QPoint &pos)
{
    QPoint globalPos = ui->textEdit->mapToGlobal(pos);
    QMenu contextMenu;
    contextMenu.addMenu(&padMenu);
    contextMenu.addMenu(&editMenu);
    contextMenu.exec(globalPos);
}

PadWindow::~PadWindow()
{
    delete ui;
}

void PadWindow::propertiesWindowRequested()
{
    if (!propertiesWindow)
    {
        // create instance and connect slots
        propertiesWindow.reset(new PropertiesWindow(properties));
        connect(propertiesWindow.get(), &QDialog::accepted,
                [&]()
                {
                    properties = propertiesWindow->GetProperties();
                    SyncWithProperties();
                    propertiesWindow.reset(nullptr);
                }
        );
        connect(propertiesWindow.get(), &QDialog::rejected,
                [&]()
                {
                    propertiesWindow.reset(nullptr);
                }
        );
    }
    // is hide necessary?
    propertiesWindow->hide();
    propertiesWindow->show();
}

void PadWindow::preferencesWindowRequested()
{
    if (!preferencesWindow)
    {
        // create instance and connect slots
        preferencesWindow.reset(new PreferencesWindow(properties));
        connect(preferencesWindow.get(), &QDialog::accepted,
                [&]()
                {
                    properties = preferencesWindow->GetProperties();
                    SyncWithProperties();
                    preferencesWindow.reset(nullptr);
                }
        );
        connect(preferencesWindow.get(), &QDialog::rejected,
                [&]()
                {
                    preferencesWindow.reset(nullptr);
                }
        );
    }
    // is hide necessary?
    preferencesWindow->hide();
    preferencesWindow->show();
}

void PadWindow::SyncWithProperties()
{
    QString textColorString = QString("color: rgb(%1, %2, %3);")
            .arg(properties.textColor.red())
            .arg(properties.textColor.green())
            .arg(properties.textColor.blue());
    QString backColorString = QString("background-color: rgb(%1, %2, %3);")
            .arg(properties.backColor.red())
            .arg(properties.backColor.green())
            .arg(properties.backColor.blue());
    QString styleSheetString = "QTextEdit {" + textColorString + backColorString + "}";
    ui->textEdit->setStyleSheet(styleSheetString);
    ui->textEdit->setText(ui->textEdit->toPlainText());
    ui->textEdit->setReadOnly(properties.readonly);
}

void PadWindow::SetPad(Pad * p)
{
    pad = p;
}
void PadWindow::SetText(QString text)
{
    ui->textEdit->setText(text);
}

QString PadWindow::GetText()
{
    return ui->textEdit->toPlainText();
}

void PadWindow::closeEvent(QCloseEvent *e)
{
    pad->dataReceived(ui->textEdit->toPlainText());
    e->ignore();
    hide();
}
