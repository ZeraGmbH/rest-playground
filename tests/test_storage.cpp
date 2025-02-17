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
#include <mocktcpnetworkfactory.h>

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

void test_storage::access_storage_of_vein_singleton()
{
    std::unique_ptr<ModuleManagerTestRunner> testRunner = setupModuleManager(ZeraModules::ModuleManager::getInstalledSessionPath() + "/mt310s2-emob-session-ac.json");

    VeinEntrySingleton& veinSingleton = VeinEntrySingleton::getInstance();
    VeinStorage::AbstractDatabase* veinStorageDb = veinSingleton.getStorageDb();

    TestDspInterfacePtr dspInterface = testRunner->getDspInterfaceList()[6];
    TestDspValues dspValues(dspInterface->getValueList());

    dspValues.setAllValuesSymmetricAc(5, 5, 0, 50);
    dspValues.fireDftActualValues(dspInterface);
    TimeMachineObject::feedEventLoop();

    QList<QString> comp1050 = veinStorageDb->getComponentList(1050);
    QVERIFY(comp1050.length() == 28);
    QVERIFY(veinStorageDb->hasStoredValue(1050, "ACT_POL_DFTPN4") == true);

    QList<double> exampleValue = veinStorageDb->getStoredValue(1050, "ACT_POL_DFTPN4").value<QList<double>>();

    QVERIFY(exampleValue[0] == 7.071067810058594);

    QList<QString> comp1130 = veinStorageDb->getComponentList(1130);
    QVERIFY(comp1130.length() == 37);
    QVERIFY(veinStorageDb->hasStoredValue(1130, "ACT_Status") == true);

    QVariant status = veinStorageDb->getStoredValue(1130, "ACT_Status");

    QList<QString> comp1150 = veinStorageDb->getComponentList(1150);
    QVERIFY(comp1150.length() == 17);
    QVERIFY(veinStorageDb->hasStoredValue(1150, "PAR_SerialNr") == true);

    QVariant serial = veinStorageDb->getStoredValue(1150, "PAR_SerialNr");
}

std::unique_ptr<ModuleManagerTestRunner> test_storage::setupModuleManager(QString config)
{
    VeinTcp::AbstractTcpNetworkFactoryPtr mockedVeinNetworkFactory = VeinTcp::MockTcpNetworkFactory::create();

    std::unique_ptr<ModuleManagerTestRunner> testRunner = std::make_unique<ModuleManagerTestRunner>(config);
    VeinNet::NetworkSystem* netSystem = new VeinNet::NetworkSystem();
    netSystem->setOperationMode(VeinNet::NetworkSystem::VNOM_PASS_THROUGH);

    VeinNet::TcpSystem* tcpSystem = new VeinNet::TcpSystem(mockedVeinNetworkFactory);

    // Order is important.
    testRunner->getModManFacade()->addSubsystem(netSystem);
    testRunner->getModManFacade()->addSubsystem(tcpSystem);

    tcpSystem->startServer(12000);

    VeinEntrySingleton::getInstance(mockedVeinNetworkFactory);

    TimeMachineObject::feedEventLoop();

    return testRunner;
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
