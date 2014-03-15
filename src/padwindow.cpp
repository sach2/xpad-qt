
#include "padwindow.h"
#include "ui_padwindow.h"
#include "app.h"

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
    ui->textEdit->installEventFilter(this);
}
bool PadWindow::eventFilter(QObject *object, QEvent *event)
{
    App* app = (App*)qApp;
    if (event->type() == QEvent::FocusIn)
    {
        if (object == ui->textEdit)
        {
            auto propertiesAction = std::bind(&PadWindow::propertiesWindowRequested, this);
            app->contextMenuCreator.Register(PadProperties, propertiesAction);
            auto preferencesAction = std::bind(&PadWindow::preferencesWindowRequested, this);
            app->contextMenuCreator.Register(Preferences, preferencesAction);
            auto closeAction = std::bind(&PadWindow::hide, this);
            app->contextMenuCreator.Register(ClosePad, closeAction);
            auto deleteAction = std::bind(&Pad::deletePadRequested, pad, pad);
            app->contextMenuCreator.Register(DeletePad, deleteAction);
        }
    }
    else if(event->type() == QEvent::FocusOut)
    {
        if (object == ui->textEdit)
        {
            app->contextMenuCreator.Unregister(PadProperties);
            app->contextMenuCreator.Unregister(Preferences);
            app->contextMenuCreator.Unregister(ClosePad);
            app->contextMenuCreator.Unregister(DeletePad);
        }
    }
    return false;
}

void PadWindow::initContextMenu()
{
    App* app = (App*)qApp;
    ui->textEdit->addAction(app->contextMenuCreator.GetAction(NewPad));

    ui->textEdit->addAction(app->contextMenuCreator.GetAction(PadProperties));

    ui->textEdit->addAction(app->contextMenuCreator.GetAction(ClosePad));

    ui->textEdit->addAction(app->contextMenuCreator.GetAction(DeletePad));

    padMenu = new QMenu("&Pad");
    //padMenu->addAction(newPadAction);
    //padMenu->addAction(propertiesAction);
   // padMenu->addAction(closeAction);
    //padMenu->addAction(deletePadAction);

    auto readonlyAction = new QAction("&Readonly", ui->textEdit);
    readonlyAction->setCheckable(true);
    readonlyAction->setChecked(properties.readonly);
    connect(readonlyAction, &QAction::triggered, [&](){
        properties.readonly = !properties.readonly;
        ui->textEdit->setReadOnly(properties.readonly);
    });
    ui->textEdit->addAction(readonlyAction);

    auto preferencesAction = new QAction(QIcon::fromTheme("document-properties"),
                                         "P&references", ui->textEdit);
    preferencesAction->setShortcut(QKeySequence("Ctrl+p"));
    connect(preferencesAction, &QAction::triggered, [&](){
        preferencesWindowRequested();
    });
    ui->textEdit->addAction(preferencesAction);

    editMenu = new QMenu("&Edit");
    editMenu->addAction(readonlyAction);
    editMenu->addAction(preferencesAction);

    ui->textEdit->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->textEdit, &QWidget::customContextMenuRequested,
            this, &PadWindow::showContextMenu);
}

void PadWindow::showContextMenu(const QPoint &pos)
{
    App* app = (App*)qApp;
    QPoint globalPos = ui->textEdit->mapToGlobal(pos);
    app->contextMenuCreator.SetInfo(globalPos);
    app->contextMenuCreator.Display();
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
