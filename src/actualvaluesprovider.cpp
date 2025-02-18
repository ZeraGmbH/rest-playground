#include "actualvaluesprovider.h"
#include "commondefines.h"

Q_DECLARE_METATYPE(QList<double>)


ActualValuesProvider::ActualValuesProvider()
{
    qRegisterMetaType<QList<double>>("QList<double>");
}

OpenAPI::OAIVeinGetActualValues ActualValuesProvider::getActualValues(VeinStorage::AbstractDatabase *storage)
{
    bool dcSession = isDc(storage);
    relevantForWhichSession currentSession = dcSession ? relevantForWhichSession::DC : relevantForWhichSession::AC;
    OpenAPI::OAIVeinGetActualValues res;
    OpenAPI::OAIPowerModule power1module1;
    OpenAPI::OAIPowerModule power1module2;
    OpenAPI::OAIPowerModule power1module3;
    OpenAPI::OAIPowerModule power1module4;
    OpenAPI::OAIVeinGetActualValues_DftModule1 dftModule1;
    OpenAPI::OAIVeinGetActualValues_RangeModule1 rangeModule1;
    OpenAPI::OAIVeinGetActualValues_RMSModule1 rmsModule1;
    OpenAPI::OAIVeinGetActualValues_FFTModule1 fftModule1;
    OpenAPI::OAIVeinGetActualValues_LambdaModule1 lambdaModule1;

    QList<componentMappingMetadata<double>> doubleMappings = {
        {veinRestEntityIds::POWER1MODULE1, "ACT_PQS1", relevantForWhichSession::AC,[&power1module1](double input){power1module1.setActPqs1(input);}},
        {veinRestEntityIds::POWER1MODULE1, "ACT_PQS2", relevantForWhichSession::AC,[&power1module1](double input){power1module1.setActPqs2(input);}},
        {veinRestEntityIds::POWER1MODULE1, "ACT_PQS3", relevantForWhichSession::AC,[&power1module1](double input){power1module1.setActPqs3(input);}},
        {veinRestEntityIds::POWER1MODULE1, "ACT_PQS4", relevantForWhichSession::AC,[&power1module1](double input){power1module1.setActPqs4(input);}},
        {veinRestEntityIds::POWER1MODULE1, "PAR_FOUTConstant0", relevantForWhichSession::AC,[&power1module1](double input){power1module1.setParFoutConstant0(input);}},
        {veinRestEntityIds::POWER1MODULE2, "ACT_PQS1", relevantForWhichSession::AC,[&power1module2](double input){power1module2.setActPqs1(input);}},
        {veinRestEntityIds::POWER1MODULE2, "ACT_PQS2", relevantForWhichSession::AC,[&power1module2](double input){power1module2.setActPqs2(input);}},
        {veinRestEntityIds::POWER1MODULE2, "ACT_PQS3", relevantForWhichSession::AC,[&power1module2](double input){power1module2.setActPqs3(input);}},
        {veinRestEntityIds::POWER1MODULE2, "ACT_PQS4", relevantForWhichSession::AC,[&power1module2](double input){power1module2.setActPqs4(input);}},
        {veinRestEntityIds::POWER1MODULE2, "PAR_FOUTConstant0", relevantForWhichSession::AC,[&power1module2](double input){power1module2.setParFoutConstant0(input);}},
        {veinRestEntityIds::POWER1MODULE3, "ACT_PQS1", relevantForWhichSession::AC,[&power1module3](double input){power1module3.setActPqs1(input);}},
        {veinRestEntityIds::POWER1MODULE3, "ACT_PQS2", relevantForWhichSession::AC,[&power1module3](double input){power1module3.setActPqs2(input);}},
        {veinRestEntityIds::POWER1MODULE3, "ACT_PQS3", relevantForWhichSession::AC,[&power1module3](double input){power1module3.setActPqs3(input);}},
        {veinRestEntityIds::POWER1MODULE3, "ACT_PQS4", relevantForWhichSession::AC,[&power1module3](double input){power1module3.setActPqs4(input);}},
        {veinRestEntityIds::POWER1MODULE3, "PAR_FOUTConstant0", relevantForWhichSession::AC,[&power1module3](double input){power1module3.setParFoutConstant0(input);}},
        {veinRestEntityIds::POWER1MODULE4, "ACT_PQS1", relevantForWhichSession::AC,[&power1module4](double input){power1module4.setActPqs1(input);}},
        {veinRestEntityIds::POWER1MODULE4, "ACT_PQS2", relevantForWhichSession::AC,[&power1module4](double input){power1module4.setActPqs2(input);}},
        {veinRestEntityIds::POWER1MODULE4, "ACT_PQS3", relevantForWhichSession::AC,[&power1module4](double input){power1module4.setActPqs3(input);}},
        {veinRestEntityIds::POWER1MODULE4, "ACT_PQS4", relevantForWhichSession::AC,[&power1module4](double input){power1module4.setActPqs4(input);}},
        {veinRestEntityIds::POWER1MODULE4, "PAR_FOUTConstant0", relevantForWhichSession::AC,[&power1module4](double input){power1module4.setParFoutConstant0(input);}},
    };

    for(auto item : std::as_const(doubleMappings)) {
        if (item.sessionRelevancy == relevantForWhichSession::ACDC || item.sessionRelevancy == currentSession) {
            QVariant variantValue = extractFromStorage(storage, item.entityId, item.componentName);
            if(variantValue.canConvert<double>()) item.insertionFunction(variantValue.value<double>());
        }
    }

    //addPowerModuleToList(doubleMappings, veinRestEntityIds::POWER1MODULE1, power1module1);
    //addPowerModuleToList(doubleMappings, veinRestEntityIds::POWER1MODULE2, power1module2);
    //addPowerModuleToList(doubleMappings, veinRestEntityIds::POWER1MODULE3, power1module3);
    //addPowerModuleToList(doubleMappings, veinRestEntityIds::POWER1MODULE4, power1module4);

    /*doubleMappings.append({veinRestEntityIds::POWER1MODULE1, "ACT_PQS1", relevantForWhichSession::AC,[&power1module1](double input){power1module1.setActPqs1(input);}});
    doubleMappings.append({veinRestEntityIds::POWER1MODULE1, "ACT_PQS2", relevantForWhichSession::AC,[&power1module1](double input){power1module1.setActPqs2(input);}});
    doubleMappings.append({veinRestEntityIds::POWER1MODULE1, "ACT_PQS3", relevantForWhichSession::AC,[&power1module1](double input){power1module1.setActPqs3(input);}});
    doubleMappings.append({veinRestEntityIds::POWER1MODULE1, "ACT_PQS4", relevantForWhichSession::AC,[&power1module1](double input){power1module1.setActPqs4(input);}});
    doubleMappings.append({veinRestEntityIds::POWER1MODULE1, "PAR_FOUTConstant0", relevantForWhichSession::AC,[&power1module1](double input){power1module1.setParFoutConstant0(input);}});

    doubleMappings.append({veinRestEntityIds::POWER1MODULE2, "ACT_PQS1", relevantForWhichSession::AC,[&power1module2](double input){power1module2.setActPqs1(input);}});
    doubleMappings.append({veinRestEntityIds::POWER1MODULE2, "ACT_PQS2", relevantForWhichSession::AC,[&power1module2](double input){power1module2.setActPqs2(input);}});
    doubleMappings.append({veinRestEntityIds::POWER1MODULE2, "ACT_PQS3", relevantForWhichSession::AC,[&power1module2](double input){power1module2.setActPqs3(input);}});
    doubleMappings.append({veinRestEntityIds::POWER1MODULE2, "ACT_PQS4", relevantForWhichSession::AC,[&power1module2](double input){power1module2.setActPqs4(input);}});
    doubleMappings.append({veinRestEntityIds::POWER1MODULE2, "PAR_FOUTConstant0", relevantForWhichSession::AC,[&power1module2](double input){power1module2.setParFoutConstant0(input);}});

    doubleMappings.append({veinRestEntityIds::POWER1MODULE3, "ACT_PQS1", relevantForWhichSession::AC,[&power1module3](double input){power1module3.setActPqs1(input);}});
    doubleMappings.append({veinRestEntityIds::POWER1MODULE3, "ACT_PQS2", relevantForWhichSession::AC,[&power1module3](double input){power1module3.setActPqs2(input);}});
    doubleMappings.append({veinRestEntityIds::POWER1MODULE3, "ACT_PQS3", relevantForWhichSession::AC,[&power1module3](double input){power1module3.setActPqs3(input);}});
    doubleMappings.append({veinRestEntityIds::POWER1MODULE3, "ACT_PQS4", relevantForWhichSession::AC,[&power1module3](double input){power1module3.setActPqs4(input);}});
    doubleMappings.append({veinRestEntityIds::POWER1MODULE3, "PAR_FOUTConstant0", relevantForWhichSession::AC,[&power1module3](double input){power1module3.setParFoutConstant0(input);}});

    doubleMappings.append({veinRestEntityIds::POWER1MODULE4, "ACT_PQS1", relevantForWhichSession::DC,[&power1module4](double input){power1module4.setActPqs1(input);}});
    doubleMappings.append({veinRestEntityIds::POWER1MODULE4, "ACT_PQS2", relevantForWhichSession::DC,[&power1module4](double input){power1module4.setActPqs2(input);}});
    doubleMappings.append({veinRestEntityIds::POWER1MODULE4, "ACT_PQS3", relevantForWhichSession::DC,[&power1module4](double input){power1module4.setActPqs3(input);}});
    doubleMappings.append({veinRestEntityIds::POWER1MODULE4, "ACT_PQS4", relevantForWhichSession::DC,[&power1module4](double input){power1module4.setActPqs4(input);}});
    doubleMappings.append({veinRestEntityIds::POWER1MODULE4, "PAR_FOUTConstant0", relevantForWhichSession::DC,[&power1module4](double input){power1module4.setParFoutConstant0(input);}});*/




    /*if(dcSession)
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

    res.setIsDc(dcSession);*/

    //res.setDftModule1(dftModule1);
    res.setDftModule1(getDftValues(storage));
    res.setPower1Module1(power1module1);
    res.setPower1Module2(power1module2);
    res.setPower1Module3(power1module3);
    res.setPower1Module4(power1module4);
    res.setFftModule1(fftModule1);
    res.setRangeModule1(rangeModule1);
    res.setRmsModule1(rmsModule1);
    res.setLambdaModule1(lambdaModule1);
    return res;
}

template<typename T>
void ActualValuesProvider::addPowerModuleToList(QList<componentMappingMetadata<double> >& list, veinRestEntityIds entityId, T &responseObject)
{
    list.append({entityId, "ACT_PQS1", relevantForWhichSession::AC,[&responseObject](double input){responseObject.setActPqs1(input);}});
    list.append({entityId, "ACT_PQS2", relevantForWhichSession::AC,[&responseObject](double input){responseObject.setActPqs2(input);}});
    list.append({entityId, "ACT_PQS3", relevantForWhichSession::AC,[&responseObject](double input){responseObject.setActPqs3(input);}});
    list.append({entityId, "ACT_PQS4", relevantForWhichSession::AC,[&responseObject](double input){responseObject.setActPqs4(input);}});
    list.append({entityId, "PAR_FOUTConstant0", relevantForWhichSession::AC,[&responseObject](double input){responseObject.setParFoutConstant0(input);}});
}

OpenAPI::OAIVeinGetActualValues_DftModule1 ActualValuesProvider::getDftValues(VeinStorage::AbstractDatabase *storage)
{
    OpenAPI::OAIVeinGetActualValues_DftModule1 res;

    QVariant rfield = extractFromStorage(storage, veinRestEntityIds::DFTMODULE1, "ACT_RFIELD");
    if(rfield.canConvert<QString>()) res.setRfield(rfield.value<QString>());

    QVariant polDftpn1 = extractFromStorage(storage, veinRestEntityIds::DFTMODULE1, "ACT_POL_DFTPN1");
    auto test = polDftpn1.toJsonObject();
    if(polDftpn1.canConvert<QList<double>>()) res.setActDftpn1Deg(polDftpn1.value<QList<double>>().size() >= 2 ? polDftpn1.value<QList<double>>()[2] : 0);

    QVariant polDftpn2 = extractFromStorage(storage, veinRestEntityIds::DFTMODULE1, "ACT_POL_DFTPN2");
    if(polDftpn2.canConvert<QList<double>>()) res.setActDftpn2Deg(polDftpn2.value<QList<double>>().size() >= 2 ? polDftpn2.value<QList<double>>()[2] : 0);

    QVariant polDftpn3 = extractFromStorage(storage, veinRestEntityIds::DFTMODULE1, "ACT_POL_DFTPN3");
    if(polDftpn3.canConvert<QList<double>>()) res.setActDftpn3Deg(polDftpn3.value<QList<double>>().size() >= 2 ? polDftpn3.value<QList<double>>()[2] : 0);

    QVariant polDftpn4 = extractFromStorage(storage, veinRestEntityIds::DFTMODULE1, "ACT_POL_DFTPN4");
    if(polDftpn4.canConvert<QList<double>>()) res.setActDftpn4Deg(polDftpn4.value<QList<double>>().size() >= 2 ? polDftpn4.value<QList<double>>()[2] : 0);

    QVariant polDftpn5 = extractFromStorage(storage, veinRestEntityIds::DFTMODULE1, "ACT_POL_DFTPN5");
    if(polDftpn5.canConvert<QList<double>>()) res.setActDftpn5Deg(polDftpn5.value<QList<double>>().size() >= 2 ? polDftpn5.value<QList<double>>()[2] : 0);

    QVariant polDftpn6 = extractFromStorage(storage, veinRestEntityIds::DFTMODULE1, "ACT_POL_DFTPN6");
    if(polDftpn6.canConvert<QList<double>>()) res.setActDftpn6Deg(polDftpn6.value<QList<double>>().size() >= 2 ? polDftpn6.value<QList<double>>()[2] : 0);

    QVariant polDftpn7 = extractFromStorage(storage, veinRestEntityIds::DFTMODULE1, "ACT_POL_DFTPN7");
    if(polDftpn7.canConvert<QList<double>>()) res.setActDftpn7Deg(polDftpn7.value<QList<double>>().size() >= 2 ? polDftpn7.value<QList<double>>()[2] : 0);

    QVariant polDftpn8 = extractFromStorage(storage, veinRestEntityIds::DFTMODULE1, "ACT_POL_DFTPN8");
    if(polDftpn8.canConvert<QList<double>>()) res.setActDftpn8Deg(polDftpn8.value<QList<double>>().size() >= 2 ? polDftpn8.value<QList<double>>()[2] : 0);

    return res;
}

OpenAPI::OAIPowerModule ActualValuesProvider::getPowerModule(VeinStorage::AbstractDatabase *storage, veinRestEntityIds powerModuleNo)
{
    OpenAPI::OAIPowerModule res;



    /*QVariant pqs1 = extractFromStorage(storage, powerModuleNo, "ACT_PQS1");
    if(pqs1.canConvert<double>()) res.setActPqs1(pqs1.value<double>());*/

    QVariant pqs2 = extractFromStorage(storage, powerModuleNo, "ACT_PQS2");
    if(pqs2.canConvert<double>()) res.setActPqs2(pqs2.value<double>());

    QVariant pqs3 = extractFromStorage(storage, powerModuleNo, "ACT_PQS3");
    if(pqs3.canConvert<double>()) res.setActPqs3(pqs3.value<double>());

    QVariant pqs4 = extractFromStorage(storage, powerModuleNo, "ACT_PQS4");
    if(pqs4.canConvert<double>()) res.setActPqs4(pqs4.value<double>());

    QVariant foutConstant = extractFromStorage(storage, powerModuleNo, "PAR_FOUTConstant0");
    if(foutConstant.canConvert<double>()) res.setParFoutConstant0(foutConstant.value<double>());

    QVariant measuringMode = extractFromStorage(storage, powerModuleNo, "PAR_MeasuringMode");
    if(measuringMode.canConvert<QString>()) res.setParMeasuringMode(measuringMode.value<QString>());

    QVariant measModePhaseSelect = extractFromStorage(storage, powerModuleNo, "PAR_MeasModePhaseSelect");
    if(measModePhaseSelect.canConvert<QString>()) res.setParMeasModePhaseSelect(measModePhaseSelect.value<QString>());

    return res;
}

OpenAPI::OAIVeinGetActualValues_RangeModule1 ActualValuesProvider::getRangeValues(VeinStorage::AbstractDatabase *storage)
{
    OpenAPI::OAIVeinGetActualValues_RangeModule1 res;

    QVariant frequency = extractFromStorage(storage, veinRestEntityIds::RANGEMODULE1, "ACT_Frequency");
    if(frequency.canConvert<double>()) res.setFrequency(frequency.value<double>());

    return res;
}

OpenAPI::OAIVeinGetActualValues_RMSModule1 ActualValuesProvider::getRmsValues(VeinStorage::AbstractDatabase *storage)
{
    OpenAPI::OAIVeinGetActualValues_RMSModule1 res;

    QVariant rmsPn1 = extractFromStorage(storage, veinRestEntityIds::RMSMODULE1, "ACT_RMSPN1");
    if(rmsPn1.canConvert<double>()) res.setActRmspn1(rmsPn1.value<double>());

    QVariant rmsPn2 = extractFromStorage(storage, veinRestEntityIds::RMSMODULE1, "ACT_RMSPN2");
    if(rmsPn2.canConvert<double>()) res.setActRmspn2(rmsPn2.value<double>());

    QVariant rmsPn3 = extractFromStorage(storage, veinRestEntityIds::RMSMODULE1, "ACT_RMSPN3");
    if(rmsPn3.canConvert<double>()) res.setActRmspn3(rmsPn3.value<double>());

    QVariant rmsPn4 = extractFromStorage(storage, veinRestEntityIds::RMSMODULE1, "ACT_RMSPN4");
    if(rmsPn4.canConvert<double>()) res.setActRmspn4(rmsPn4.value<double>());

    QVariant rmsPn5 = extractFromStorage(storage, veinRestEntityIds::RMSMODULE1, "ACT_RMSPN5");
    if(rmsPn5.canConvert<double>()) res.setActRmspn5(rmsPn5.value<double>());

    QVariant rmsPn6 = extractFromStorage(storage, veinRestEntityIds::RMSMODULE1, "ACT_RMSPN6");
    if(rmsPn6.canConvert<double>()) res.setActRmspn6(rmsPn6.value<double>());

    QVariant rmsPn7 = extractFromStorage(storage, veinRestEntityIds::RMSMODULE1, "ACT_RMSPN7");
    if(rmsPn7.canConvert<double>()) res.setActRmspn7(rmsPn7.value<double>());

    QVariant rmsPn8 = extractFromStorage(storage, veinRestEntityIds::RMSMODULE1, "ACT_RMSPN8");
    if(rmsPn8.canConvert<double>()) res.setActRmspn8(rmsPn8.value<double>());

    return res;
}

OpenAPI::OAIVeinGetActualValues_FFTModule1 ActualValuesProvider::getFftValues(VeinStorage::AbstractDatabase *storage)
{
    OpenAPI::OAIVeinGetActualValues_FFTModule1 res;

    QVariant fftDc1 = extractFromStorage(storage, veinRestEntityIds::FFTMODULE1, "ACT_DC1");
    if(fftDc1.canConvert<double>()) res.setActDc1(fftDc1.value<double>());

    QVariant fftDc2 = extractFromStorage(storage, veinRestEntityIds::FFTMODULE1, "ACT_DC2");
    if(fftDc2.canConvert<double>()) res.setActDc2(fftDc2.value<double>());

    QVariant fftDc3 = extractFromStorage(storage, veinRestEntityIds::FFTMODULE1, "ACT_DC3");
    if(fftDc3.canConvert<double>()) res.setActDc3(fftDc3.value<double>());

    QVariant fftDc4 = extractFromStorage(storage, veinRestEntityIds::FFTMODULE1, "ACT_DC4");
    if(fftDc4.canConvert<double>()) res.setActDc4(fftDc4.value<double>());

    QVariant fftDc5 = extractFromStorage(storage, veinRestEntityIds::FFTMODULE1, "ACT_DC5");
    if(fftDc5.canConvert<double>()) res.setActDc5(fftDc5.value<double>());

    QVariant fftDc6 = extractFromStorage(storage, veinRestEntityIds::FFTMODULE1, "ACT_DC6");
    if(fftDc6.canConvert<double>()) res.setActDc6(fftDc6.value<double>());

    QVariant fftDc7 = extractFromStorage(storage, veinRestEntityIds::FFTMODULE1, "ACT_DC7");
    if(fftDc7.canConvert<double>()) res.setActDc7(fftDc7.value<double>());

    QVariant fftDc8 = extractFromStorage(storage, veinRestEntityIds::FFTMODULE1, "ACT_DC8");
    if(fftDc8.canConvert<double>()) res.setActDc8(fftDc8.value<double>());

    return res;
}

OpenAPI::OAIVeinGetActualValues_LambdaModule1 ActualValuesProvider::getLambdaValues(VeinStorage::AbstractDatabase *storage)
{
    OpenAPI::OAIVeinGetActualValues_LambdaModule1 res;

    QVariant lambda1 = extractFromStorage(storage, veinRestEntityIds::LAMBDAMODULE1, "ACT_Lambda1");
    if(lambda1.canConvert<double>()) res.setActLambda1(lambda1.value<double>());

    QVariant lambda2 = extractFromStorage(storage, veinRestEntityIds::LAMBDAMODULE1, "ACT_Lambda2");
    if(lambda2.canConvert<double>()) res.setActLambda2(lambda2.value<double>());

    QVariant lambda3 = extractFromStorage(storage, veinRestEntityIds::LAMBDAMODULE1, "ACT_Lambda3");
    if(lambda3.canConvert<double>()) res.setActLambda3(lambda3.value<double>());

    QVariant lambda4 = extractFromStorage(storage, veinRestEntityIds::LAMBDAMODULE1, "ACT_Lambda4");
    if(lambda4.canConvert<double>()) res.setActLambda4(lambda4.value<double>());

    return res;
}

bool ActualValuesProvider::isDc(VeinStorage::AbstractDatabase *storage)
{
    QString session = safeConvert<QString>(extractFromStorage(storage, veinRestEntityIds::SYSTEM, "Session"));

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
