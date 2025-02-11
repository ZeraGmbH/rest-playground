#include "veinentrysingleton.h"
#include <tcpnetworkfactory.h>
#include <QAbstractEventDispatcher>
#include <QCoreApplication>


TaskSimpleVeinGetterPtr VeinEntrySingleton::getFromVein(int entityId, QString componentName)
{
    TaskSimpleVeinGetterPtr task = TaskSimpleVeinGetter::create(entityId, componentName, m_cmdEventHandlerSystem);

    return task;
}

TaskSimpleVeinSetterPtr VeinEntrySingleton::setToVein(int entityId, QString componentName, QVariant value)
{
    TaskSimpleVeinSetterPtr task = TaskSimpleVeinSetter::create(entityId, componentName, value, m_cmdEventHandlerSystem);

    return task;
}

VeinEntrySingleton::VeinEntrySingleton() :
    m_tcpSystem(VeinTcp::TcpNetworkFactory::create()),
    m_cmdEventHandlerSystem(VfCmdEventHandlerSystem::create())
{
    m_eventHandler.addSubsystem(m_cmdEventHandlerSystem.get());
    m_netSystem.setOperationMode(VeinNet::NetworkSystem::VNOM_PASS_THROUGH);
    m_eventHandler.addSubsystem(&m_netSystem);
    m_eventHandler.addSubsystem(&m_tcpSystem);
    m_tcpSystem.connectToServer("127.0.0.1", 12000);
}

