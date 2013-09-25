#ifndef PAD_H
#define PAD_H

#include<QObject>
#include<padwindow.h>
#include<padserializer.h>

using namespace std;

class Pad : public QObject
{
    Q_OBJECT
    PadWindow padwindow;
    QString windowBuffer;
    PadSerializer serializer;
public:
    Pad(PadSerializer padSerializer);
    ~Pad();
public slots:
    void dataReceived(QString data);
public:
    void show();
    void loadFromFile();
    void saveToFile();
};

#endif // PAD_H
