#ifndef VEINENTRYSINGLETON_H
#define VEINENTRYSINGLETON_H

#include <QObject>
#include <VfEvent/ve_eventhandler.h>
#include <VfNet2/vn_networksystem.h>
#include <VfNet2/vn_tcpsystem.h>
#include <VfConvenientCode/vf_cmd_event_handler_system.h>
#include <VfConvenientCode/tasksimpleveingetter.h>
#include <VfConvenientCode/tasksimpleveinsetter.h>

class VeinEntrySingleton : public QObject
{
    Q_OBJECT

public:
    static VeinEntrySingleton& getInstance()
    {
        static VeinEntrySingleton instance;

        return instance;
    }



private:
    VeinEntrySingleton();


public:
    VeinEntrySingleton(VeinEntrySingleton const&)   = delete;
    void operator=(VeinEntrySingleton const&)       = delete;

signals:

};

#endif // VEINENTRYSINGLETON_H
