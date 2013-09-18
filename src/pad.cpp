#include "pad.h"
#include<QtCore>
#include<iostream>
Pad::Pad()
{
    mainwindow.SetPad(this);
    mainwindow.show();
}

void Pad::dataReceived(QString data)
{
    windowBuffer = data;
//    qDebug()<<data;
}

Pad::~Pad()
{
    qDebug() << "pad with data - " << windowBuffer << "deleted";
}
