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
    QString windowBuffer, title;
    PadSerializer serializer;
public:
    Pad(PadSerializer padSerializer);
    ~Pad();
    void show();
    void loadFromFile();
    void saveToFile();
    void deletePad();
    QString getTitle();
signals:
    void newPadRequested();
    void deletePadRequested(Pad* pad);
public slots:
    void dataReceived(QString data);
};

#endif // PAD_H
