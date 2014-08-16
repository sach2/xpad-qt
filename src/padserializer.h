#ifndef PADSERIALIZER_H
#define PADSERIALIZER_H

#include<QString>
#include<properties.h>
class PadSerializer
{
    QString infoFilename, contentFilename;
public:
    PadSerializer(QString infoFile, QString contentsFile="");
    Properties LoadProperties() const;
    void SaveProperties(const Properties& properties) const;
    QString LoadContents() const;
    void SaveContents(QString contents) const;
    void DeletePad();
};

#endif // PADSERIALIZER_H
