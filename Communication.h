#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include "drivergc_global.h"
#include <QByteArray>
#include <QDateTime>
#include <QDebug>
#include <QIODevice>
#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QString>
#include <QThread>

class DRIVERGCSHARED_EXPORT Communication : public QObject {
    Q_OBJECT
public:
    bool Open(const QString& port, const quint32& baud = 500000);
    bool Close();
signals:
    void DebugOut(QString msg, QDateTime curTime = QDateTime::currentDateTime());

protected:
    QSerialPort _com;

    ~Communication();
    virtual void ReceiveEvent() = 0;
};

#endif // COMMUNICATION_H
