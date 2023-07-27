#include "veinentrysingleton.h"




QString VeinEntrySingleton::getTest()
{
    return m_Test;
}

VeinEntrySingleton::VeinEntrySingleton() : m_Test("asdf")
{

}
