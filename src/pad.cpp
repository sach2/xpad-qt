#include "pad.h"
#include <QtCore>
#include <iostream>
#include <fstream>
#include <string>
#include <QFile>

Pad::Pad(PadSerializer padSerializer)
    :serializer(padSerializer)
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

void Pad::deletePad()
{
    padwindow.hide();
    serializer.deletePad();
}

void Pad::loadFromFile()
{
    padwindow.properties = serializer.loadProperties();
    padwindow.SetText(serializer.loadContents());
    padwindow.SyncWithProperties();
}

void Pad::saveToFile()
{
    auto current_buffer = padwindow.GetText();
    bool sameBuffer = current_buffer == windowBuffer;
    bool sameProperties = serializer.loadProperties() == padwindow.properties;
    if (sameBuffer && sameProperties)
    {
        return;
    }
    windowBuffer = current_buffer;
    serializer.saveProperties(padwindow.properties);
    serializer.saveContents(windowBuffer);
}

Pad::~Pad()
{
}
