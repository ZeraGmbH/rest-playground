#include "test_storage.h"
#include "veinentrysingleton.h"
#include "handlers/OAIVeinApiHandler.h"
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

void test_storage::get_multiple_values()
{
    VeinStorage::AbstractDatabase* veinStorageDb = VeinEntrySingleton::getInstance().getStorageDb();
    m_testRunner->setVfComponent(1050, "PAR_Interval", QVariant(2));
    m_testRunner->setVfComponent(1060, "PAR_Interval", QVariant(3));
    TimeMachineObject::feedEventLoop();

    OpenAPI::OAIVeinApiHandler handler;

    QList<OpenAPI::OAIVeinGetRequest> requests;
    requests.append(OpenAPI::OAIVeinGetRequest("{\"EntityId\": 1050, \"ComponentName\": \"PAR_Interval\"}"));
    requests.append(OpenAPI::OAIVeinGetRequest("{\"EntityId\": 1060, \"ComponentName\": \"PAR_Interval\"}"));

    QList<OpenAPI::OAIVeinGetResponse> response = handler.generateBulkAnswer(requests);

    QVERIFY(response.size() == 2);
    QCOMPARE(response[0].getReturnInformation(), "2");
    QCOMPARE(response[1].getReturnInformation(), "3");
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
