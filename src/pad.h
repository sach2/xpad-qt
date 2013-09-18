#ifndef PAD_H
#define PAD_H

#include<QObject>
#include<padwindow.h>

class Pad : public QObject
{
    Q_OBJECT
    PadWindow padwindow;
    QString windowBuffer;
public:
    Pad();
    ~Pad();
public slots:
    void dataReceived(QString data);
    PadWindow& GetWindow();
    void show();

};

#endif // PAD_H
