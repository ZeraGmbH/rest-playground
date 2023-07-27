#include "signaltest.h"

SignalTest::SignalTest(QObject *parent)
    : QObject{parent}
{

}

void SignalTest::add(OpenAPI::OAIVeinApiRequest *iPtr, OpenAPI::OAIVeinGetResponse iRes)
{
    mList.append(qMakePair(iPtr, iRes));
}

void SignalTest::fireAll()
{
    QPair<OpenAPI::OAIVeinApiRequest*, OpenAPI::OAIVeinGetResponse> item;
    foreach (item, mList)
    {
        item.first->apiV1VeinGetInfoPostResponse(item.second);
    }
}
