#ifndef PADSERIALIZER_H
#define PADSERIALIZER_H

#include<QString>
#include<properties.h>
class PadSerializer
{
    QString infoFilename, contentFilename;
public:
    PadSerializer(QString infoFile);
    Properties loadProperties() const;
    void saveProperties(const Properties& properties) const;
    QString loadContents() const;
    void saveContents(QString contents) const;
    void deletePad();
};

#endif // PADSERIALIZER_H
