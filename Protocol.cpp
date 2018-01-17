#include "Protocol.h"
#include "Convert.h"
#include <QDateTime>
#include <QDebug>
#include <QMutex>

#define RCV_TIMEOUT 1000 //命令超时时间，单位ms
#define RESEND_TIMES 3 //命令失败重试次数

#define FRAME_HEAD_POS 0
#define FRAME_HEAD1 0x0d
#define FRAME_HEAD2 0X0a
#define FRAME_HEAD_LENGHT 2
#define FRAME_SALVEADD_POS (FRAME_HEAD_POS + FRAME_HEAD_LENGHT)
#define FRAME_SALVEADD_LENGHT 1
#define FRAME_CMD_POS (FRAME_SALVEADD_POS + FRAME_SALVEADD_LENGHT)
#define FRAME_CMD_LENGHT 1
#define FRAME_DATALEN_POS (FRAME_CMD_POS + FRAME_CMD_LENGHT)
#define FRAME_DATALEN_LENGHT 2
#define FRAME_LENGHT_BEFORE_DATA (FRAME_HEAD_LENGHT + FRAME_SALVEADD_LENGHT + FRAME_CMD_LENGHT + FRAME_DATALEN_LENGHT)
#define FRAME_DATA_POS (FRAME_DATALEN_POS + FRAME_DATALEN_LENGHT) //数据帧开始位置
#define FRAME_RCVCMD_LENGHT 1 //数据帧里第一个字节为返回的命令
#define FRAME_DATA_DATA_POS (FRAME_DATA_POS + FRAME_RCVCMD_LENGHT) //数据帧里实际数据的位置
#define FRAME_CHECK_LENGHT 1

Protocol::Protocol():helper(this, SIGNAL(ReceiveDone()))
{
    meCommand = QMetaEnum::fromType<Protocol::Command>();
}

bool Protocol::Analysis(quint16 salveAdd, Protocol::Command cmd, QByteArray& dataOut)
{
    bool status = false;
    dataOut.clear();
    foreach (QByteArray item, _RcvFrameList) {
        if (item.at(FRAME_SALVEADD_POS) != salveAdd) {
            DebugOut("Here is an illegitimate child");
        } else {
            if (quint8(item.at(FRAME_DATA_POS)) != quint8(cmd)) {
                DebugOut("Here is incongruous");
            } else {
                Command pc = (Command)item.at(FRAME_CMD_POS);
                switch (pc) {
                case Command_Post_Get:
                    DebugOut("Controller received the command");
                    DebugOut(QString("Frame:%1").arg(QString(item.toHex())));
                    break;
                case Command_Post_Complete:
                    DebugOut("Controller completed the task");
                    DebugOut(QString("Frame:%1").arg(QString(item.toHex())));
                    //截取有用的返回数据 数据段第一个时命令
                    dataOut.append(item.mid(FRAME_DATA_DATA_POS,
                        item.length() - FRAME_DATA_DATA_POS - 1));
                    status = true;
                    break;
                case Command_Post_Error:
                    //截取有用的返回数据 数据段第一个时命令
                    dataOut.append(item.mid(FRAME_DATA_DATA_POS,
                        item.length() - FRAME_DATA_DATA_POS - 1));
                    break;
                default:
                    DebugOut("What are you talking about");
                    break;
                }
            }
        }
    }
    return status;
}

bool Protocol::Send(const quint16& salveAdd, const Command& cmd,
    const QByteArray& dataSend, QByteArray& dataReceive)
{
    // 锁定，防止多线程重入
    //    QMutexLocker locker(&mutex);
    bool status = false;
    QByteArray frame;
    quint8 sum = 0;

    // head \r \n
    frame.append(FRAME_HEAD1);
    frame.append(FRAME_HEAD2);

    // salve address
    // NOTE 地址位暂定为一个字节
    frame.append(quint8(salveAdd));
    sum += salveAdd;

    // command
    frame.append(quint8(cmd));
    sum += cmd;

    // data len
    frame.append(Convert::from(quint16(dataSend.length())));
    sum += dataSend.length();

    // data
    frame.append(dataSend);

    // frame sum check
    for (quint16 i = 0; i < dataSend.length(); ++i) {
        sum += dataSend.at(i);
    }
    frame.append(sum);

    DebugOut("I'am in");
    mutex.lock();
    // 建立一个等待信号
    DebugOut(QString("Controller:%1").arg(salveAdd));
    for (quint8 i = 0; i < RESEND_TIMES; ++i) {
        _RcvBuf.clear();
        _RcvFrameList.clear();
        flag=false;
        _com.write(frame);
        DebugOut(QString("Send:%1").arg(meCommand.valueToKey(cmd)));
        DebugOut(QString("Frame:%1").arg(QString(frame.toHex())));

//        if (helper.wait(RCV_TIMEOUT)) {
//            break;
//        } else {
//            DebugOut("Waitting receive timeout");
//        }
    }
    status = Analysis(salveAdd, cmd, dataReceive);
    DebugOut("I'am out");
    mutex.unlock();
    return status;
}

void Protocol::GoToThread(QThread* thread)
{
    _com.moveToThread(thread);
    moveToThread(thread);
}

void Protocol::ReceiveEvent()
{
    _RcvBuf.append(_com.readAll());
    while (_RcvBuf.length() >= FRAME_LENGHT_BEFORE_DATA) {
        //如果拿到了大于数据长度位置的帧计算本帧长度
        qDebug()<<QDateTime::currentDateTime().toString("yy:hh:ss:zzz") <<"RAW:"<<QString(_RcvBuf.toHex());
        quint16 dataLenght = (Convert::toqint16(_RcvBuf.mid(FRAME_DATALEN_POS, 2)));
        quint16 frameLenght = FRAME_LENGHT_BEFORE_DATA + dataLenght + FRAME_CHECK_LENGHT;
        if (!((_RcvBuf.at(0) == FRAME_HEAD1) && (_RcvBuf.at(1) == FRAME_HEAD2))) {
            DebugOut("Frame head error");
        }
        if (_RcvBuf.length() >= frameLenght) {
            //当帧数据大于一帧长度时循环，防止一次收到大量数据
            quint8 sum = 0;
            for (quint16 i = FRAME_SALVEADD_POS; i < frameLenght - 1; ++i) {
                sum += _RcvBuf.at(i);
            }
            if (sum == quint8(_RcvBuf.at(frameLenght - 1))) {
                _RcvFrameList.append(_RcvBuf.mid(0, frameLenght));
                _RcvBuf.remove(0, frameLenght);
            } else {
                _RcvBuf.remove(0,_RcvBuf.length());
                emit ReceiveDone();
                DebugOut("Frame check sum error");
            }
            if (_RcvFrameList.count() == 2) {
                emit ReceiveDone();
            }
        } else {
            break;
        }
    }
}
