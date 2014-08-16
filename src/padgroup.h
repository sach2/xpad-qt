#ifndef PADGROUP_H
#define PADGROUP_H

#include<list>
#include<QObject>
#include <map>
#include <thread>
#include <padwindow.h>
#include <properties.h>
#include <padserializer.h>
class Pad;

using namespace std;
struct PadInfo
{
    unique_ptr<Pad> pad;
    unique_ptr<PadWindow> padWindow;
    Properties properties;
    unique_ptr<PadSerializer> serializer;
};

class PadGroup : public QObject, public IMenuPlaceholderProvider
{
    Q_OBJECT
    map<int, unique_ptr<PadInfo>> padIdToInfoMap;
    QString directory;
    void AddPad(QString infoFilename, QString contentsFilename="");
    void CreatePad(QString infoFilename, QString contentsFilename);
    void LoadPadFrom(QString filename);
    std::thread padSaverThread;
    int nextPadId;
    void AddPlaceholderActions(MenuPlaceholders placeholder, QMenu& menu);
public:
    PadGroup();
    void SetDirectory(QString dir);
    void LoadPads();
    ~PadGroup();
    void SavePadsThreadFunc();
    void CreateNewPad();
signals:
    void numberOfPadsChanged();
};

#endif // PADGROUP_H
