#ifndef PAD_H
#define PAD_H

#include<QObject>
#include<padwindow.h>

using namespace std;

class Pad : public QObject
{
    Q_OBJECT
    PadWindow padwindow;
    QString windowBuffer;
    QString filename;
public:
    Pad();
    ~Pad();
public slots:
    void dataReceived(QString data);
public:
    void show();
    void loadFromFile();
    void saveToFile();
    void setFilename(QString file);
};

#endif // PAD_H
