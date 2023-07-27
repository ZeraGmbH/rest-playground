#ifndef SIGNALTEST_H
#define SIGNALTEST_H

#include <QObject>
#include "OAIVeinApiRequest.h"
class SignalTest : public QObject
{
    Q_OBJECT
public:
    explicit SignalTest(QObject *parent = nullptr);
    void add(OpenAPI::OAIVeinApiRequest* iPtr, OpenAPI::OAIVeinGetResponse iRes);

public slots:
    void fireAll();

private:
    QList<QPair<OpenAPI::OAIVeinApiRequest*, OpenAPI::OAIVeinGetResponse>> mList;

signals:

};

#endif // SIGNALTEST_H
