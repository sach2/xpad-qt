#include "padserializer.h"
#include<QFile>
#include<QTextStream>
#include<map>
#include<iostream>
#include<functional>
#include<QFileInfo>
#include<QTime>
#include<QDir>
#include<QDebug>
using namespace std;

PadSerializer::PadSerializer(QString infoFile, QString contentFile)
{
    infoFilename = infoFile;
    if (contentFile == "")
    {
        // get content file name
        QFile file(infoFilename);
        if (file.open(QIODevice::ReadOnly))
        {
            QTextStream in(&file);
            while (! in.atEnd())
            {
                QString line = in.readLine();
                if (line.startsWith("contents="))
                {
                    contentFile = line.split("=")[1];
                }
            }
        }
    }
    contentFilename = contentFile;
    // create new info file for new pads, with default properties
    if (! QFile(infoFilename).exists())
    {
        SaveProperties(Properties());
    }
    // write blank file, if not present
    if (! QFile(contentFilename).exists())
    {
        SaveContents(QString(""));
    }
}

Properties PadSerializer::LoadProperties() const
{
    Properties properties;
    QColor& backColor(properties.backColor);
    QColor& textColor(properties.textColor);
    // register handlers for keys found in config file
    map<QString, function<void(QString)>> keyToHandlerMap;
    keyToHandlerMap["backcolor.red"] = [&](const QString& value)
            {backColor.setRed(value.toInt());};
    keyToHandlerMap["backcolor.green"] = [&](const QString& value)
            {backColor.setGreen(value.toInt());};
    keyToHandlerMap["backcolor.blue"] = [&](const QString& value)
            {backColor.setBlue(value.toInt());};
    keyToHandlerMap["textcolor.red"] = [&](const QString& value)
            {textColor.setRed(value.toInt());};
    keyToHandlerMap["textcolor.green"] = [&](const QString& value)
            {textColor.setGreen(value.toInt());};
    keyToHandlerMap["textcolor.blue"] = [&](const QString& value)
            {textColor.setBlue(value.toInt());};

    // read config file and call registered handlers
    QFile file(infoFilename);
    if (file.open(QIODevice::ReadOnly))
    {
        QTextStream in(&file);
        while (! in.atEnd())
        {
            QString line = in.readLine();
            if (line == "")
                continue;
            auto iter = keyToHandlerMap.find(line.split("=")[0]);
            if (iter != keyToHandlerMap.end())
            {
                auto handler = (*iter).second;
                handler(line.split("=")[1]);
            }
        }
    }
    return properties;
}

void PadSerializer::SaveProperties(const Properties &properties) const
{
    QFile file(infoFilename);
    if (file.open(QIODevice::WriteOnly))
    {
        QTextStream out(&file);
        out << "backcolor.red=" << properties.backColor.red() << endl;
        out << "backcolor.green=" << properties.backColor.green() << endl;
        out << "backcolor.blue=" << properties.backColor.blue() << endl;
        out << "textcolor.red=" << properties.textColor.red() << endl;
        out << "textcolor.green=" << properties.textColor.green() << endl;
        out << "textcolor.blue=" << properties.textColor.blue() << endl;
        out << "contents=" << contentFilename << endl;
    }
}

QString PadSerializer::LoadContents() const
{
    QString contents;
    QFile file(contentFilename);
    if (file.open(QIODevice::ReadOnly))
    {
        QTextStream in(&file);
        while (! in.atEnd())
        {
            contents += in.readLine();
            contents += "\n";
        }
    }
    return contents;
}


void PadSerializer::SaveContents(QString contents) const
{
    SaveProperties(Properties());
    QFile file(contentFilename);
    if (file.open(QIODevice::WriteOnly))
    {
        QTextStream out(&file);
        out << contents << endl;
    }
}

void PadSerializer::DeletePad()
{

    if (QFile(infoFilename).exists())
        QFile(infoFilename).remove();
    if (QFile(contentFilename).exists())
        QFile(contentFilename).remove();
}
