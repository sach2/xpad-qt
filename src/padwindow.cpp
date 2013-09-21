
#include "padwindow.h"
#include "ui_padwindow.h"

#include<QDebug>
#include<QCloseEvent>

#include<string>

#include<pad.h>

PadWindow::PadWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PadWindow)
{
    ui->setupUi(this);
    SyncWithProperties();
    connect(ui->propertiesButton, &QPushButton::pressed,
            this, &PadWindow::onPropertiesButtonPressed);
}

PadWindow::~PadWindow()
{
    delete ui;
}

void PadWindow::onPropertiesButtonPressed()
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
