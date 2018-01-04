#include "WaitForSignalHelper.h"
#include <QTimer>

WaitForSignalHelper::WaitForSignalHelper(QObject* parent, const char* signal)
    : QObject(parent)
    , m_bTimeout(false)
{
    connect(parent, signal, &m_eventLoop, SLOT(quit()));
}

bool WaitForSignalHelper::wait(int timeoutMs)
{
    QTimer timeoutHelper;
    if (timeoutMs != 0) //manage timeout
    {
        timeoutHelper.setInterval(timeoutMs);
        timeoutHelper.start();
        connect(&timeoutHelper, SIGNAL(timeout()), this, SLOT(timeout()));
    }
    //else, wait for ever!
    m_bTimeout = false;
    m_eventLoop.exec();
    return !m_bTimeout;
}

void WaitForSignalHelper::timeout()
{
    m_bTimeout = true;
    m_eventLoop.quit();
}
