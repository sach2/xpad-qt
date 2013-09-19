#include "pad.h"
#include <QtCore>
#include <iostream>
#include <fstream>
#include <string>
#include <QFile>

Pad::Pad()
{
    padwindow.SetPad(this);
    padwindow.show();
}

// close clicked handler
void Pad::dataReceived(QString data)
{
    windowBuffer = data;
    saveToFile();
}

void Pad::show()
{
    padwindow.show();
}

void Pad::setFilename(QString file)
{
    filename = file;
}

void Pad::loadFromFile()
{
    QFile file(filename);
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);
    QString contents;
    while(!in.atEnd())
    {
        QString line = in.readLine();
        contents.append(line);
        contents.append('\n');
    }
    windowBuffer = contents;
    padwindow.SetText(windowBuffer);
}

void Pad::saveToFile()
{
    // wofstream doesn't work in qt
//    wstring f;
//    wofstream file;
//    file.open(f.c_str()); // error
//    file << windowBuffer;
//    file.close();

    QFile file(filename);
    if (file.open(QIODevice::WriteOnly))
    {
        QTextStream stream(&file);
        stream << windowBuffer << endl;
    }
}

Pad::~Pad()
{
}
