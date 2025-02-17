#include "actualvaluesprovider.h"
#include "commondefines.h"

ActualValuesProvider::ActualValuesProvider()
{

}

OpenAPI::OAIVeinGetActualValues ActualValuesProvider::getActualValues(VeinStorage::AbstractDatabase *storage)
{
    OpenAPI::OAIVeinGetActualValues res;
    res.setDftModule1(getDftValues(storage));
    res.setPower1Module1(getPowerModule(storage, veinRestEntityIds::POWER1MODULE1));
    return res;
}

OpenAPI::OAIVeinGetActualValues_DftModule1 ActualValuesProvider::getDftValues(VeinStorage::AbstractDatabase *storage)
{
    OpenAPI::OAIVeinGetActualValues_DftModule1 res;

    QString rfield = safeConvert<QString>(extractFromStorage(storage, veinRestEntityIds::DFTMODULE1, "ACT_RFIELD"));
    res.setRfield(rfield);

    QList<double> polDftpn1 = safeConvert<QList<double>>(extractFromStorage(storage, veinRestEntityIds::DFTMODULE1, "ACT_POL_DFTPN1"));
    res.setActDftpn1Deg(polDftpn1.size() >= 2 ? polDftpn1[2] : 0);

    QList<double> polDftpn2 = safeConvert<QList<double>>(extractFromStorage(storage, veinRestEntityIds::DFTMODULE1, "ACT_POL_DFTPN2"));
    res.setActDftpn2Deg(polDftpn2.size() >= 2 ? polDftpn2[2] : 0);

    QList<double> polDftpn3 = safeConvert<QList<double>>(extractFromStorage(storage, veinRestEntityIds::DFTMODULE1, "ACT_POL_DFTPN3"));
    res.setActDftpn3Deg(polDftpn3.size() >= 2 ? polDftpn3[2] : 0);

    QList<double> polDftpn4 = safeConvert<QList<double>>(extractFromStorage(storage, veinRestEntityIds::DFTMODULE1, "ACT_POL_DFTPN4"));
    res.setActDftpn4Deg(polDftpn4.size() >= 2 ? polDftpn4[2] : 0);

    QList<double> polDftpn5 = safeConvert<QList<double>>(extractFromStorage(storage, veinRestEntityIds::DFTMODULE1, "ACT_POL_DFTPN5"));
    res.setActDftpn5Deg(polDftpn5.size() >= 2 ? polDftpn5[2] : 0);

    QList<double> polDftpn6 = safeConvert<QList<double>>(extractFromStorage(storage, veinRestEntityIds::DFTMODULE1, "ACT_POL_DFTPN6"));
    res.setActDftpn6Deg(polDftpn6.size() >= 2 ? polDftpn6[2] : 0);

    QList<double> polDftpn7 = safeConvert<QList<double>>(extractFromStorage(storage, veinRestEntityIds::DFTMODULE1, "ACT_POL_DFTPN7"));
    res.setActDftpn7Deg(polDftpn7.size() >= 2 ? polDftpn7[2] : 0);

    QList<double> polDftpn8 = safeConvert<QList<double>>(extractFromStorage(storage, veinRestEntityIds::DFTMODULE1, "ACT_POL_DFTPN8"));
    res.setActDftpn8Deg(polDftpn8.size() >= 2 ? polDftpn8[2] : 0);

    return res;
}

OpenAPI::OAIPowerModule ActualValuesProvider::getPowerModule(VeinStorage::AbstractDatabase *storage, veinRestEntityIds powerModuleNo)
{
    OpenAPI::OAIPowerModule res;

    double pqs1 = safeConvert<double>(extractFromStorage(storage, powerModuleNo, "ACT_PQS1"));
    res.setActPqs1(pqs1);

    double pqs2 = safeConvert<double>(extractFromStorage(storage, powerModuleNo, "ACT_PQS2"));
    res.setActPqs2(pqs2);

    double pqs3 = safeConvert<double>(extractFromStorage(storage, powerModuleNo, "ACT_PQS3"));
    res.setActPqs3(pqs3);

    double pqs4 = safeConvert<double>(extractFromStorage(storage, powerModuleNo, "ACT_PQS4"));
    res.setActPqs4(pqs4);

    double foutConstant = safeConvert<double>(extractFromStorage(storage, powerModuleNo, "PAR_FOUTConstant0"));
    res.setParFoutConstant0(foutConstant);

    QString measuringMode = safeConvert<QString>(extractFromStorage(storage, powerModuleNo, "PAR_MeasuringMode"));
    res.setParMeasuringMode(measuringMode);

    QString measModePhaseSelect = safeConvert<QString>(extractFromStorage(storage, powerModuleNo, "PAR_MeasModePhaseSelect"));
    res.setParMeasuringMode(measModePhaseSelect);

    return res;
}

QVariant ActualValuesProvider::extractFromStorage(VeinStorage::AbstractDatabase *storage, veinRestEntityIds entityId, QString componentName)
{
    if(storage->hasStoredValue(entityId, componentName))
        return storage->getStoredValue(entityId, componentName);
    else
        qWarning("Did not find: %s; in entity %i", qPrintable(componentName), entityId);
    return QVariant();
}


template<typename T>
T ActualValuesProvider::safeConvert(const QVariant &input)
{
    if (input.canConvert<T>()) {
        return input.value<T>();
    }

    // Return default value
    return T{};
}
