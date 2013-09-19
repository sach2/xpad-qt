
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
}

PadWindow::~PadWindow()
{
    delete ui;
}
void PadWindow::SetPad(Pad * p)
{
    pad = p;
}
void PadWindow::SetText(QString text)
{
    ui->textEdit->setText(text);
}

void PadWindow::closeEvent(QCloseEvent *e)
{
    pad->dataReceived(ui->textEdit->toPlainText());
    e->ignore();
    hide();
}
