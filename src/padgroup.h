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
    QString directory;
    Pad* newPadWithInfo(QString filename);
public:
    PadGroup();
    const list<Pad*>& GetPads();
    void SetDirectory(QString dir);
    void LoadPads();
    ~PadGroup();
signals:
    void numberOfPadsChanged();
public slots:
    void CreateNewPad();
    void deletePad(Pad* pad);
};

#endif // PADGROUP_H
