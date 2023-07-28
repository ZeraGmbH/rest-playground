#ifndef VEINENTRYSINGLETON_H
#define VEINENTRYSINGLETON_H

#include <QObject>
#include <VfEvent/ve_eventhandler.h>
#include <VfNet2/vn_networksystem.h>
#include <VfNet2/vn_tcpsystem.h>
#include <VfConvenientCode/vfcommandeventhandlersystem.h>
#include <VfSimplePeer/vfsimplegetter.h>

class VeinEntrySingleton : public QObject
{
    Q_OBJECT

public:
    static VeinEntrySingleton& getInstance()
    {
        static VeinEntrySingleton instance;

        return instance;
    }

    void subscribeToEntity(unsigned int entityId);
    VfSimpleGetterPtr triggerGetComponent(unsigned int entityId, QString componentName);

private:
    VeinEntrySingleton();

    VeinEvent::EventHandler m_eventHandler;
    VeinNet::NetworkSystem m_netSystem;
    VeinNet::TcpSystem m_tcpSystem;
    VfCommandEventHandlerSystem m_cmdEventHandlerSystem;

public:
    VeinEntrySingleton(VeinEntrySingleton const&)   = delete;
    void operator=(VeinEntrySingleton const&)       = delete;

signals:

};

#endif // VEINENTRYSINGLETON_H
