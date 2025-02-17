#ifndef ACTUALVALUESPROVIDER_H
#define ACTUALVALUESPROVIDER_H

#include "OAIVeinGetActualValues.h"
#include "vs_abstractdatabase.h"
#include "commondefines.h"
#include <QObject>

class ActualValuesProvider : public QObject
{
    Q_OBJECT
public:
    ActualValuesProvider();
    OpenAPI::OAIVeinGetActualValues getActualValues(VeinStorage::AbstractDatabase* storage);

private:
    OpenAPI::OAIVeinGetActualValues_DftModule1 getDftValues(VeinStorage::AbstractDatabase* storage);
    OpenAPI::OAIPowerModule getPowerModule(VeinStorage::AbstractDatabase* storage, veinRestEntityIds powerModuleNo);
    QVariant extractFromStorage(VeinStorage::AbstractDatabase* storage, veinRestEntityIds entityId, QString componentName);

    template <typename T>
    T safeConvert(const QVariant &input);
};

#endif // ACTUALVALUESPROVIDER_H
