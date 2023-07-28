#include "veinentrysingleton.h"
#include <VfSimplePeer/vfsimpleentitysubscriber.h>

#include <QAbstractEventDispatcher>
#include <QCoreApplication>

void VeinEntrySingleton::subscribeToEntity(unsigned int entityId)
{
    VfSimpleEntitySubscriberPtr entityToSubscribe = VfSimpleEntitySubscriber::create(entityId);
    m_cmdEventHandlerSystem.addItem(entityToSubscribe);
    entityToSubscribe->sendSubscription();
    feedEventLoop();
}

VfSimpleGetterPtr VeinEntrySingleton::triggerGetComponent(unsigned int entityId, QString componentName)
{
    VfSimpleGetterPtr getter = VfSimpleGetter::create(entityId, componentName);
    m_cmdEventHandlerSystem.addItem(getter);
    getter->startGetComponent();
    feedEventLoop();
    return getter;
}

VeinEntrySingleton::VeinEntrySingleton()
{
    m_eventHandler.addSubsystem(&m_cmdEventHandlerSystem);
    //m_netSystem.setOperationMode(VeinNet::NetworkSystem::VNOM_PASS_THROUGH);
    m_eventHandler.addSubsystem(&m_netSystem);
    m_eventHandler.addSubsystem(&m_tcpSystem);
    m_tcpSystem.connectToServer("127.0.0.1", 12000);
    feedEventLoop();
}

void VeinEntrySingleton::feedEventLoop()
{
    while(QCoreApplication::eventDispatcher()->processEvents(QEventLoop::AllEvents));
}
