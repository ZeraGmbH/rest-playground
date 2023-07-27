#include "veinentrysingleton.h"
#include <VfSimplePeer/vfsimpleentitysubscriber.h>



QString VeinEntrySingleton::getTest()
{
    return m_Test;
}

void VeinEntrySingleton::subscribeToEntity(unsigned int entityId)
{
    VfSimpleEntitySubscriberPtr entityToSubscribe = VfSimpleEntitySubscriber::create(entityId);
    m_cmdEventHandlerSystem.addItem(entityToSubscribe);
    entityToSubscribe->sendSubscrption();
}

VfSimpleGetterPtr VeinEntrySingleton::triggerGetComponent(unsigned int entityId, QString componentName)
{
    VfSimpleGetterPtr getter = VfSimpleGetter::create(entityId, componentName);
    m_cmdEventHandlerSystem.addItem(getter);
    getter->startGetComponent();
    return getter;
}

VeinEntrySingleton::VeinEntrySingleton() : m_Test("asdf")
{
    m_eventHandler.addSubsystem(&m_cmdEventHandlerSystem);
    //m_tcpSystem.connectToServer("127.0.0.1", 12000);
}
