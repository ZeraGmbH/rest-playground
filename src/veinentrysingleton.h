#ifndef VEINENTRYSINGLETON_H
#define VEINENTRYSINGLETON_H

#include <QObject>

class VeinEntrySingleton : public QObject
{
    Q_OBJECT

public:
    static VeinEntrySingleton& getInstance()
    {
        static VeinEntrySingleton instance;

        return instance;
    }

    QString getTest();
private:
    VeinEntrySingleton();


    QString m_Test;
public:
    VeinEntrySingleton(VeinEntrySingleton const&)   = delete;
    void operator=(VeinEntrySingleton const&)       = delete;

signals:

};

#endif // VEINENTRYSINGLETON_H
