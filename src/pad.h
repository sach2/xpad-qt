#ifndef PAD_H
#define PAD_H

#include<QObject>
#include<padwindow.h>

class Pad : public QObject
{
    Q_OBJECT
    PadWindow mainwindow;
    QString windowBuffer;
public:
    Pad();
    ~Pad();
public slots:
    void dataReceived(QString data) ;

};

#endif // PAD_H
