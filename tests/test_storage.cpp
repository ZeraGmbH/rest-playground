#include "test_storage.h"
#include "actualvaluesprovider.h"
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
    m_testRunner = setupModuleManager(ZeraModules::ModuleManager::getInstalledSessionPath() + "/mt310s2-emob-session-ac.json");

}

void test_storage::access_storage_of_vein_singleton()
{
    VeinEntrySingleton& veinSingleton = VeinEntrySingleton::getInstance();
    VeinStorage::AbstractDatabase* veinStorageDb = veinSingleton.getStorageDb();

    TestDspInterfacePtr dspInterface = m_testRunner->getDspInterfaceList()[6];
    TestDspValues dspValues(dspInterface->getValueList());

    dspValues.setAllValuesSymmetricAc(5, 5, 0, 50);
    dspValues.fireDftActualValues(dspInterface);
    TimeMachineObject::feedEventLoop();

    QList<QString> comp1050 = veinStorageDb->getComponentList(1050);
    QVERIFY(comp1050.length() == 28);
    QVERIFY(veinStorageDb->hasStoredValue(1050, "ACT_POL_DFTPN4") == true);

    QList<double> exampleValue = veinStorageDb->getStoredValue(1050, "ACT_POL_DFTPN4").value<QList<double>>();

    QVERIFY(exampleValue[0] == 7.071067810058594);
}

void test_storage::actual_value_get_valid()
{
    TestDspInterfacePtr dspInterface = m_testRunner->getDspInterfaceList()[6];
    TestDspValues dspValues(dspInterface->getValueList());

    dspValues.setAllValuesSymmetricAc(5, 5, 5, 50);
    dspValues.fireDftActualValues(dspInterface);
    TimeMachineObject::feedEventLoop();

    ActualValuesProvider provider;

    OpenAPI::OAIVeinGetActualValues actualValues = provider.getActualValues(VeinEntrySingleton::getInstance().getStorageDb());
    QCOMPARE(actualValues.getDftModule1().getRfield(), "123");
    QVERIFY(actualValues.getDftModule1().getActDftpn1Deg() == 0);
    QVERIFY(actualValues.getDftModule1().getActDftpn2Deg() == 119.99999957375515);
    QVERIFY(actualValues.getDftModule1().getActDftpn3Deg() == 240.00000042624484);
    QVERIFY(actualValues.getDftModule1().getActDftpn4Deg() == 5.000000125275222);
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
