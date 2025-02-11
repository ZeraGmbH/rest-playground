#ifndef VEINENTRYSINGLETON_H
#define VEINENTRYSINGLETON_H

#include <QObject>
#include <ve_eventhandler.h>
#include <vn_networksystem.h>
#include <vn_tcpsystem.h>
#include <vf_cmd_event_handler_system.h>
#include <tasksimpleveingetter.h>
#include <tasksimpleveinsetter.h>

class VeinEntrySingleton : public QObject
{
    Q_OBJECT

public:
    static VeinEntrySingleton& getInstance()
    {
        static VeinEntrySingleton instance;

        return instance;
    }

    TaskSimpleVeinGetterPtr getFromVein(int entityId, QString componentName);
    TaskSimpleVeinSetterPtr setToVein(int entityId, QString componentName, QVariant value);

private:
    VeinEntrySingleton();

    VeinEvent::EventHandler m_eventHandler;
    VeinNet::NetworkSystem m_netSystem;
    VeinNet::TcpSystem m_tcpSystem;
    VfCmdEventHandlerSystemPtr m_cmdEventHandlerSystem;

public:
    VeinEntrySingleton(VeinEntrySingleton const&)   = delete;
    void operator=(VeinEntrySingleton const&)       = delete;

signals:

};

#endif // VEINENTRYSINGLETON_H
