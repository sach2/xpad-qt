#ifndef PADGROUP_H
#define PADGROUP_H

#include<list>
#include<QObject>

class Pad;

using namespace std;

class PadGroup : public QObject
{
    Q_OBJECT
    list<Pad*> pads;
public:
    PadGroup();
    const list<Pad*>& GetPads();
    ~PadGroup();
public slots:
    void CreateNewPad();
};

#endif // PADGROUP_H
