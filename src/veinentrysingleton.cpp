#include "veinentrysingleton.h"
#include "task_client_entity_subscribe.h"

#include <QAbstractEventDispatcher>
#include <QCoreApplication>
#include <taskcontainerparallel.h>


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

VeinEntrySingleton::VeinEntrySingleton(VeinTcp::AbstractTcpNetworkFactoryPtr tcpNetworkFactory) :
    m_tcpSystem(tcpNetworkFactory),
    m_cmdEventHandlerSystem(VfCmdEventHandlerSystem::create()),
    m_subscriberTask(TaskContainerParallel::create())
{
    m_eventHandler.addSubsystem(&m_netSystem);
    m_eventHandler.addSubsystem(&m_tcpSystem);
    m_eventHandler.addSubsystem(m_cmdEventHandlerSystem.get());
    m_eventHandler.addSubsystem(&m_storage);
    m_netSystem.setOperationMode(VeinNet::NetworkSystem::VNOM_PASS_THROUGH);

    m_tcpSystem.connectToServer("127.0.0.1", 12000);

    connect(m_subscriberTask.get(), &TaskTemplate::sigFinish, this, &VeinEntrySingleton::sigSubscriberTasksFinish);

    connect(&m_tcpSystem, &VeinNet::TcpSystem::sigConnnectionEstablished, this, [&](){
        m_dummyComponentList = std::make_unique<QStringList>();

        m_subscriberTask->addSub(createSubscriptionTask(1050, "DFTModule"));
        m_subscriberTask->addSub(createSubscriptionTask(1130, "SEM1Module"));
        m_subscriberTask->start();
    });
}

TaskTemplatePtr VeinEntrySingleton::createSubscriptionTask(int entityId, const QString &entityName)
{
    const QString logText = QString("%1 (ID %2)").arg(entityName).arg(entityId);
    TaskTemplatePtr task = TaskClientEntitySubscribe::create(entityId, m_cmdEventHandlerSystem, m_dummyComponentList, 2000, [=](){
        qWarning("Subscription on %s timed out!", qPrintable(logText));});
    qInfo("Start subscriptions..");
    connect(task.get(), &TaskTemplate::sigFinish, [=](bool ok) {
        if(ok)
            qInfo("Subsciptions on %s succeded.", qPrintable(logText));
        else
            qInfo("Subsciptions on %s failed!", qPrintable(logText));
    });
    return task;
}

