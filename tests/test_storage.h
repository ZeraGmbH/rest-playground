#ifndef TEST_STORAGE_H
#define TEST_STORAGE_H

#include "qsignalspy.h"
#include <QObject>

class test_storage : public QObject
{
    Q_OBJECT
private slots:
    void initTestCase();
    void foo();

private:
    void waitForSignal(QSignalSpy &signalSpy, int expectedNumberOfSignals);

signals:
};

#endif // TEST_STORAGE_H
