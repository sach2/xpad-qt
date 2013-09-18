#include "pad.h"
#include<QtCore>
#include<iostream>
Pad::Pad()
{
    padwindow.SetPad(this);
    padwindow.show();
}

void Pad::dataReceived(QString data)
{
    windowBuffer = data;
//    qDebug()<<data;
}

PadWindow& Pad::GetWindow()
{
    return padwindow;
}

void Pad::show()
{
    padwindow.show();
}

Pad::~Pad()
{
    qDebug() << "pad with data - " << windowBuffer << "deleted";
}
