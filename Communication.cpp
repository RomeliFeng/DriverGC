#include "Communication.h"
#include <iostream>

bool Communication::Open(const QString& port, const quint32& baud)
{
    _com.setPortName(port);
    if (_com.open(QIODevice::ReadWrite)) {
        _com.setBaudRate(baud);
        _com.clearError();
        _com.clear();
        connect(&_com, &QSerialPort::readyRead,
            this, &Communication::ReceiveEvent);
        DebugOut(QString("Open serial port:%1 successful").arg(_com.portName()));
        return true;
    }
    DebugOut(QString("Open serial port:%1 failed").arg(_com.portName()));
    return false;
}

bool Communication::Close()
{
    if (_com.isOpen()) {
        _com.close();
    }
    return true;
}

Communication::~Communication()
{
    Close();
}
