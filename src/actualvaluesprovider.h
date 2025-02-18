#ifndef ACTUALVALUESPROVIDER_H
#define ACTUALVALUESPROVIDER_H

#include "OAIVeinGetActualValues.h"
#include "vs_abstractdatabase.h"
#include "commondefines.h"
#include <QObject>

class ActualValuesProvider : public QObject
{
    enum relevantForWhichSession {
        AC = 0,
        DC = 1,
        ACDC = 2,
    };

    template <typename T>
    struct componentMappingMetadata {
        veinRestEntityIds entityId;
        QString componentName;
        relevantForWhichSession sessionRelevancy;
        std::function<void(T)> insertionFunction;
    };

    Q_OBJECT
public:
    ActualValuesProvider();
    OpenAPI::OAIVeinGetActualValues getActualValues(VeinStorage::AbstractDatabase* storage);

private:
    template <typename T>
    void addPowerModuleToList(QList<componentMappingMetadata<double>> &list , veinRestEntityIds entityId, T &responseObject);
    OpenAPI::OAIVeinGetActualValues_DftModule1 getDftValues(VeinStorage::AbstractDatabase* storage);
    OpenAPI::OAIPowerModule getPowerModule(VeinStorage::AbstractDatabase *storage, veinRestEntityIds powerModuleNo);
    OpenAPI::OAIVeinGetActualValues_RangeModule1 getRangeValues(VeinStorage::AbstractDatabase* storage);
    OpenAPI::OAIVeinGetActualValues_RMSModule1 getRmsValues(VeinStorage::AbstractDatabase* storage);
    OpenAPI::OAIVeinGetActualValues_FFTModule1 getFftValues(VeinStorage::AbstractDatabase* storage);
    OpenAPI::OAIVeinGetActualValues_LambdaModule1 getLambdaValues(VeinStorage::AbstractDatabase* storage);

    bool isDc(VeinStorage::AbstractDatabase* storage);

    QVariant extractFromStorage(VeinStorage::AbstractDatabase* storage, veinRestEntityIds entityId, QString componentName);

    template <typename T>
    T safeConvert(const QVariant &input);
};

#endif // ACTUALVALUESPROVIDER_H
