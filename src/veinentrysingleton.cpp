#include "veinentrysingleton.h"
#include "task_client_entity_subscribe.h"
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

VeinStorage::AbstractDatabase *VeinEntrySingleton::getStorageDb()
{
    return m_storage.getDb();
}

VeinEntrySingleton::VeinEntrySingleton() :
    m_tcpSystem(VeinTcp::TcpNetworkFactory::create()),
    m_cmdEventHandlerSystem(VfCmdEventHandlerSystem::create())
{
    m_eventHandler.addSubsystem(&m_netSystem);
    m_eventHandler.addSubsystem(&m_tcpSystem);
    m_eventHandler.addSubsystem(m_cmdEventHandlerSystem.get());
    m_eventHandler.addSubsystem(&m_storage);
    m_netSystem.setOperationMode(VeinNet::NetworkSystem::VNOM_PASS_THROUGH);

    m_tcpSystem.connectToServer("127.0.0.1", 12000);

    connect(&m_tcpSystem, &VeinNet::TcpSystem::sigConnnectionEstablished, this, [&](){
        m_dummyComponentList = std::make_unique<QStringList>();

        m_subscriberTask = TaskClientEntitySubscribe::create(1050, m_cmdEventHandlerSystem, m_dummyComponentList, 2000, [](){qWarning("foo");});
        m_subscriberTask->start();
    });

}

