#include "Convert.h"

QByteArray Convert::from(const quint8& data)
{
    QByteArray l;
    l.append(data);
    return l;
}

QByteArray Convert::from(const quint16& data)
{
    QByteArray l;
    l.append(data);
    l.append(data >> 8);
    return l;
}

QByteArray Convert::from(const quint32& data)
{
    QByteArray l;
    l.append(data);
    l.append(data >> 8);
    l.append(data >> 16);
    l.append(data >> 24);
    return l;
}

QByteArray Convert::from(const qint8& data)
{
    return from(quint8(data));
}

QByteArray Convert::from(const qint16& data)
{
    return from(quint16(data));
}

QByteArray Convert::from(const qint32& data)
{
    return from(quint32(data));
}

QByteArray Convert::from(const QBitArray& data)
{
    QByteArray byteArray;
    if (data.size() % 8 != 0) {
        byteArray.resize(data.size() / 8 + 1);
    } else {
        byteArray.resize(data.size() / 8);
    }


    // Convert from QBitArray to QByteArray
    for (quint16 i = 0; i < data.count(); ++i) {
        byteArray[i / 8] = (byteArray.at(i / 8) | ((data[i] ? 1 : 0) << (i % 8)));
    }
    return byteArray;
}

quint8 Convert::toquint8(const QByteArray& data)
{
    quint8 rData = 0;
    QDataStream ds(data);
    ds.setByteOrder(QDataStream::LittleEndian);
    ds >> rData;
    return rData;
}

quint16 Convert::toquint16(const QByteArray& data)
{
    quint16 rData = 0;
    QDataStream ds(data);
    ds.setByteOrder(QDataStream::LittleEndian);
    ds >> rData;
    return rData;
}

quint32 Convert::toquint32(const QByteArray& data)
{
    quint32 rData = 0;
    QDataStream ds(data);
    ds.setByteOrder(QDataStream::LittleEndian);
    ds >> rData;
    return rData;
}

qint8 Convert::toqint8(const QByteArray& data)
{
    qint8 rData = 0;
    QDataStream ds(data);
    ds.setByteOrder(QDataStream::LittleEndian);
    ds >> rData;
    return rData;
}

qint16 Convert::toqint16(const QByteArray& data)
{
    qint16 rData = 0;
    QDataStream ds(data);
    ds.setByteOrder(QDataStream::LittleEndian);
    ds >> rData;
    return rData;
}

qint32 Convert::toqint32(const QByteArray& data)
{
    qint32 rData = 0;
    QDataStream ds(data);
    ds.setByteOrder(QDataStream::LittleEndian);
    ds >> rData;
    return rData;
}

QBitArray Convert::tobool(const QByteArray& data)
{
    QBitArray bitArray;
    bitArray.resize(data.length() * 8);
    for (quint16 i = 0; i < data.length(); i++) {
        for (quint16 j = 0; j < 8; ++j) {
            bitArray.setBit(i * 8 + j, data.at(i) & (1 << j));
        }
    }
    return bitArray;
}
