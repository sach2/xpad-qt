#ifndef PAD_H
#define PAD_H

#include<QObject>
#include<padwindow.h>
#include<padserializer.h>

using namespace std;

class Pad : public QObject
{
    Q_OBJECT
public:
    QString windowBuffer, title;
    Pad();
    ~Pad();
    QString getTitle();
signals:
    // todo - check if this can be removed
    void deletePadRequested(int padid);
};

#endif // PAD_H
