#include "test_storage.h"
#include "veinentrysingleton.h"
#include <modulemanager.h>
#include <modulemanagertestrunner.h>
#include <timemachinefortest.h>
#include <QTest>
#include <demovaluesdspdft.h>
#include <testdspvalues.h>
#include <timerfactoryqtfortest.h>
#include <QSignalSpy>

QTEST_MAIN(test_storage)

enum dspInterfaces{
    RangeObsermatic,
    AdjustManagement,
    RangeModuleMeasProgram
};

void test_storage::initTestCase()
{
    TimerFactoryQtForTest::enableTest();
}

void test_storage::foo()
{
    const QString configFile = ZeraModules::ModuleManager::getInstalledSessionPath() + "/mt310s2-emob-session-ac.json";
    ModuleManagerTestRunner testRunner(configFile);

    VeinNet::NetworkSystem* netSystem = new VeinNet::NetworkSystem();
    netSystem->setOperationMode(VeinNet::NetworkSystem::VNOM_PASS_THROUGH);
    VeinNet::TcpSystem* tcpSystem = new VeinNet::TcpSystem(testRunner.getTcpNetworkFactory());
    //do not reorder
    testRunner.getModManFacade()->addSubsystem(netSystem);
    testRunner.getModManFacade()->addSubsystem(tcpSystem);
    tcpSystem->startServer(12000);
    TimeMachineObject::feedEventLoop();

    VeinEntrySingleton& singleton = VeinEntrySingleton::getInstance(testRunner.getTcpNetworkFactory());
    TimeMachineObject::feedEventLoop();

    //QSignalSpy spy(&singleton, &VeinEntrySingleton::sigSubscriberTasksFinish);
    //waitForSignal(spy, 1);

    TestDspInterfacePtr dspInterface = testRunner.getDspInterfaceList()[6];
    TestDspValues dspValues(dspInterface->getValueList());

    dspValues.setAllValuesSymmetricAc(5, 5, 0, 50);
    dspValues.fireDftActualValues(dspInterface);
    TimeMachineObject::feedEventLoop();

    QStringList test = singleton.getStorageDb()->getComponentList(1050);
    bool hasComponent = singleton.getStorageDb()->hasStoredValue(1050, "ACT_POL_DFTPN4");
    QVariant exampleValue = singleton.getStorageDb()->getStoredValue(1050, "ACT_POL_DFTPN4");

    QVERIFY(false);
}

void test_storage::waitForSignal(QSignalSpy &signalSpy, int expectedNumberOfSignals)
{
    for(int i=0; i<100; i++) {
        if(signalSpy.count() < expectedNumberOfSignals)
            QTest::qWait(10);
        else
            break;
    }
}
