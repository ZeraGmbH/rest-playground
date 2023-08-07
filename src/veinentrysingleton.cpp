#include "veinentrysingleton.h"
#include <QAbstractEventDispatcher>
#include <QCoreApplication>


TaskSimpleVeinGetterPtr VeinEntrySingleton::getFromVein(int entityId, QString componentName)
{
    TaskSimpleVeinGetterPtr task = TaskSimpleVeinGetter::create(entityId, componentName, m_cmdEventHandlerSystem);

    return task;
}

VeinEntrySingleton::VeinEntrySingleton() : m_cmdEventHandlerSystem(VfCmdEventHandlerSystem::create())
{
    m_eventHandler.addSubsystem(m_cmdEventHandlerSystem.get());
    m_netSystem.setOperationMode(VeinNet::NetworkSystem::VNOM_PASS_THROUGH);
    m_eventHandler.addSubsystem(&m_netSystem);
    m_eventHandler.addSubsystem(&m_tcpSystem);
    m_tcpSystem.connectToServer("127.0.0.1", 12000);
}

