#include "test_storage.h"
#include <modulemanager.h>
#include <modulemanagertestrunner.h>
#include <QTest>

QTEST_MAIN(test_storage)

void test_storage::foo()
{
    const QString configFile = ZeraModules::ModuleManager::getInstalledSessionPath() + "/mt310s2-emob-session-ac.json";
    ModuleManagerTestRunner testRunner(configFile);
    QVERIFY(false);
}
