#ifndef PADGROUP_H
#define PADGROUP_H

#include<list>
#include<QObject>

class Pad;

class PadGroup : public QObject
{
    Q_OBJECT
    std::list<Pad*> pads;
public:
    PadGroup();
    ~PadGroup();
public slots:
    void CreateNewPad();
};

#endif // PADGROUP_H
