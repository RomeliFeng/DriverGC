#include "Communication.h"
#include <iostream>

bool Communication::Open(const QString& port, const quint32& baud)
{
    _com.setPortName(port);
    if (_com.open(QIODevice::ReadWrite)) {
        _com.setBaudRate(baud);
        _com.clearError();
        _com.clear();
        //连接串口接受事件
        connect(&_com, &QSerialPort::readyRead,
            this, &Communication::ReceiveEvent);
        //连接串口错误事件
        connect(&_com, &QSerialPort::errorOccurred,
                this, &Communication::GetSerialError);
        DebugOut(QString("Open serial port:%1 successful").arg(_com.portName()));
        return true;
    }
    DebugOut(QString("Open serial port:%1 failed").arg(_com.portName()));
    DebugOut(QString("Message: %1").arg(_com.errorString()));

    return false;
}

bool Communication::Close()
{
    if (_com.isOpen()) {
        _com.close();
    }
    return true;
}

bool Communication::IsOpened()
{
    if (_com.isOpen())
    {
        return true;
    }
    return false;
}

Communication::~Communication()
{
    Close();
}

void Communication::GetSerialError(QSerialPort::SerialPortError error)
{
    if(error == QSerialPort::ResourceError)
    {
        emit ErrorOut("ResourceError", _com.errorString());
    }
}
