#include "veinentrysingleton.h"
#include <VfConvenientCode/vfatomiccliententitysubscriber.h>

#include <QAbstractEventDispatcher>
#include <QCoreApplication>

void VeinEntrySingleton::subscribeToEntity(unsigned int entityId)
{
    VfAtomicClientEntitySubscriberPtr entityToSubscribe = VfAtomicClientEntitySubscriber::create(entityId);
    m_cmdEventHandlerSystem.addItem(entityToSubscribe);
    entityToSubscribe->sendSubscription();
    m_cmdEventHandlerSystem.removeItem(entityToSubscribe);
}

QPair<VfCmdEventItemEntityPtr, VfAtomicClientComponentFetcherPtr> VeinEntrySingleton::triggerGetComponent(unsigned int entityId, QString componentName)
{
    VfCmdEventItemEntityPtr entityItem = VfCmdEventItemEntity::create(entityId);
    VfAtomicClientComponentFetcherPtr getter = VfAtomicClientComponentFetcher::create(componentName, entityItem);
    m_cmdEventHandlerSystem.addItem(entityItem);
    entityItem->addItem(getter);
    getter->startGetComponent();
    return qMakePair(entityItem, getter);
}

void VeinEntrySingleton::removeItem(VfCmdEventItemEntityPtr getter)
{
    m_cmdEventHandlerSystem.removeItem(getter);
}

VeinEntrySingleton::VeinEntrySingleton()
{
    m_eventHandler.addSubsystem(&m_cmdEventHandlerSystem);
    m_netSystem.setOperationMode(VeinNet::NetworkSystem::VNOM_PASS_THROUGH);
    m_eventHandler.addSubsystem(&m_netSystem);
    m_eventHandler.addSubsystem(&m_tcpSystem);
    m_tcpSystem.connectToServer("127.0.0.1", 12000);
}

