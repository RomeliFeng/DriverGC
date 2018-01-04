#include "DriverGC.h"
using namespace std;

DriverGC* DriverGC::Instance()
{
    static QMutex mutex;
    static QScopedPointer<DriverGC> instance;
    if (Q_UNLIKELY(!instance)) {
        mutex.lock();
        if (!instance) {
            instance.reset(new DriverGC);
        }
        mutex.unlock();
    }
    return instance.data();
}

DriverGC::DriverGC()
{
}
