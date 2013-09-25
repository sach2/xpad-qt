#ifndef PADGROUP_H
#define PADGROUP_H

#include<list>
#include<QObject>
#include <map>

class Pad;

using namespace std;

class PadGroup : public QObject
{
    Q_OBJECT
    list<Pad*> pads;
    map<Pad*, QString> padToFilenameMap;
    QString directory;
    Pad* newPadWithInfo(QString filename);
public:
    PadGroup();
    const list<Pad*>& GetPads();
    void SetDirectory(QString dir);
    void LoadPads();
    ~PadGroup();
public slots:
    void CreateNewPad();
};

#endif // PADGROUP_H
