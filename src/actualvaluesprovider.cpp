#include "actualvaluesprovider.h"
#include "commondefines.h"

ActualValuesProvider::ActualValuesProvider()
{

}

OpenAPI::OAIVeinGetActualValues ActualValuesProvider::getActualValues(VeinStorage::AbstractDatabase *storage)
{
    OpenAPI::OAIVeinGetActualValues res;
    bool dcSession = isDc(storage);
    if(dcSession)
    {
        res.setFftModule1(getFftValues(storage));
        res.setPower1Module4(getPowerModule(storage, veinRestEntityIds::POWER1MODULE4));
        res.setDftModule1(getDftValues(storage));
    }
    else
    {
        res.setDftModule1(getDftValues(storage));
        res.setPower1Module1(getPowerModule(storage, veinRestEntityIds::POWER1MODULE1));
        res.setPower1Module2(getPowerModule(storage, veinRestEntityIds::POWER1MODULE2));
        res.setPower1Module3(getPowerModule(storage, veinRestEntityIds::POWER1MODULE3));
        res.setRangeModule1(getRangeValues(storage));
        res.setRmsModule1(getRmsValues(storage));
        res.setLambdaModule1(getLambdaValues(storage));
    }

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

OpenAPI::OAIVeinGetActualValues_RangeModule1 ActualValuesProvider::getRangeValues(VeinStorage::AbstractDatabase *storage)
{
    OpenAPI::OAIVeinGetActualValues_RangeModule1 res;

    double frequency = safeConvert<double>(extractFromStorage(storage, veinRestEntityIds::RANGEMODULE1, "ACT_Frequency"));
    res.setFrequency(frequency);

    return res;
}

OpenAPI::OAIVeinGetActualValues_RMSModule1 ActualValuesProvider::getRmsValues(VeinStorage::AbstractDatabase *storage)
{
    OpenAPI::OAIVeinGetActualValues_RMSModule1 res;

    double rmsPn1 = safeConvert<double>(extractFromStorage(storage, veinRestEntityIds::RMSMODULE1, "ACT_RMSPN1"));
    res.setActRmspn1(rmsPn1);

    double rmsPn2 = safeConvert<double>(extractFromStorage(storage, veinRestEntityIds::RMSMODULE1, "ACT_RMSPN2"));
    res.setActRmspn2(rmsPn2);

    double rmsPn3 = safeConvert<double>(extractFromStorage(storage, veinRestEntityIds::RMSMODULE1, "ACT_RMSPN3"));
    res.setActRmspn3(rmsPn3);

    double rmsPn4 = safeConvert<double>(extractFromStorage(storage, veinRestEntityIds::RMSMODULE1, "ACT_RMSPN4"));
    res.setActRmspn4(rmsPn4);

    double rmsPn5 = safeConvert<double>(extractFromStorage(storage, veinRestEntityIds::RMSMODULE1, "ACT_RMSPN5"));
    res.setActRmspn5(rmsPn5);

    double rmsPn6 = safeConvert<double>(extractFromStorage(storage, veinRestEntityIds::RMSMODULE1, "ACT_RMSPN6"));
    res.setActRmspn6(rmsPn6);

    double rmsPn7 = safeConvert<double>(extractFromStorage(storage, veinRestEntityIds::RMSMODULE1, "ACT_RMSPN7"));
    res.setActRmspn7(rmsPn7);

    double rmsPn8 = safeConvert<double>(extractFromStorage(storage, veinRestEntityIds::RMSMODULE1, "ACT_RMSPN8"));
    res.setActRmspn8(rmsPn8);

    return res;
}

OpenAPI::OAIVeinGetActualValues_FFTModule1 ActualValuesProvider::getFftValues(VeinStorage::AbstractDatabase *storage)
{
    OpenAPI::OAIVeinGetActualValues_FFTModule1 res;

    double fftDc1 = safeConvert<double>(extractFromStorage(storage, veinRestEntityIds::FFTMODULE1, "ACT_DC1"));
    res.setActDc1(fftDc1);

    double fftDc2 = safeConvert<double>(extractFromStorage(storage, veinRestEntityIds::FFTMODULE1, "ACT_DC2"));
    res.setActDc2(fftDc2);

    double fftDc3 = safeConvert<double>(extractFromStorage(storage, veinRestEntityIds::FFTMODULE1, "ACT_DC3"));
    res.setActDc3(fftDc3);

    double fftDc4 = safeConvert<double>(extractFromStorage(storage, veinRestEntityIds::FFTMODULE1, "ACT_DC4"));
    res.setActDc4(fftDc4);

    double fftDc5 = safeConvert<double>(extractFromStorage(storage, veinRestEntityIds::FFTMODULE1, "ACT_DC5"));
    res.setActDc5(fftDc5);

    double fftDc6 = safeConvert<double>(extractFromStorage(storage, veinRestEntityIds::FFTMODULE1, "ACT_DC6"));
    res.setActDc6(fftDc6);

    double fftDc7 = safeConvert<double>(extractFromStorage(storage, veinRestEntityIds::FFTMODULE1, "ACT_DC7"));
    res.setActDc7(fftDc7);

    double fftDc8 = safeConvert<double>(extractFromStorage(storage, veinRestEntityIds::FFTMODULE1, "ACT_DC8"));
    res.setActDc8(fftDc8);

    return res;
}

OpenAPI::OAIVeinGetActualValues_LambdaModule1 ActualValuesProvider::getLambdaValues(VeinStorage::AbstractDatabase *storage)
{
    OpenAPI::OAIVeinGetActualValues_LambdaModule1 res;

    double lambda1 = safeConvert<double>(extractFromStorage(storage, veinRestEntityIds::LAMBDAMODULE1, "ACT_Lambda1"));
    res.setActLambda1(lambda1);

    double lambda2 = safeConvert<double>(extractFromStorage(storage, veinRestEntityIds::LAMBDAMODULE1, "ACT_Lambda2"));
    res.setActLambda2(lambda2);

    double lambda3 = safeConvert<double>(extractFromStorage(storage, veinRestEntityIds::LAMBDAMODULE1, "ACT_Lambda3"));
    res.setActLambda3(lambda3);

    double lambda4 = safeConvert<double>(extractFromStorage(storage, veinRestEntityIds::LAMBDAMODULE1, "ACT_Lambda4"));
    res.setActLambda4(lambda4);

    return res;
}

bool ActualValuesProvider::isDc(VeinStorage::AbstractDatabase *storage)
{
    QString session = safeConvert<QString>(extractFromStorage(storage, veinRestEntityIds::SYSTEM, "SESSION"));

    return session.contains("emob-session-dc");
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
