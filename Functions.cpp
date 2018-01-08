#include "Functions.h"

bool Functions::Inquire_Limit(const quint16& salveAdd, QBitArray& limitData)
{

    QByteArray dataSend, dataReceive;
    if (!Send(salveAdd, Protocol::Command_Inquire_Limit, dataSend, dataReceive)) {
        return false;
    }
    limitData = Convert::tobool(dataReceive);
    return true;
}

bool Functions::Inquire_ExLimit(const quint16& salveAdd, QBitArray& limitData)
{

    QByteArray dataSend, dataReceive;
    if (!Send(salveAdd, Protocol::Command_Inquire_ExLimit, dataSend, dataReceive)) {
        return false;
    }
    limitData = Convert::tobool(dataReceive);
    return true;
}

bool Functions::Inquire_Valve(const quint16& salveAdd, QBitArray& valveData)
{

    QByteArray dataSend, dataReceive;
    if (!Send(salveAdd, Protocol::Command_Inquire_Valve, dataSend, dataReceive)) {
        return false;
    }
    valveData = Convert::tobool(dataReceive);
    return true;
}

bool Functions::Inquire_Encoder(const quint16& salveAdd, const quint8& ch,
    qint32& encoderData)
{

    QByteArray dataSend, dataReceive;
    dataSend.append(ch);
    if (!Send(salveAdd, Protocol::Command_Inquire_Encoder, dataSend, dataReceive)) {
        return false;
    }
    encoderData = Convert::toqint32(dataReceive);
    return true;
}

bool Functions::Inquire_ADC(const quint16& salveAdd, const quint8& ch,
    qint16& adcData)
{

    QByteArray dataSend, dataReceive;
    dataSend.append(ch);
    if (!Send(salveAdd, Protocol::Command_Inquire_ADC, dataSend, dataReceive)) {
        return false;
    }
    adcData = Convert::toqint16(dataReceive);
    return true;
}

bool Functions::Inquire_ExADC(const quint16& salveAdd, const quint8& ch,
    qint16& adcData)
{

    QByteArray dataSend, dataReceive;
    dataSend.append(ch);
    if (!Send(salveAdd, Protocol::Command_Inquire_ExADC, dataSend, dataReceive)) {
        return false;
    }
    adcData = Convert::toqint16(dataReceive);
    return true;
}

bool Functions::Inquire_Tigger(const quint16& salveAdd, quint8& tiggerData)
{

    QByteArray dataSend, dataReceive;
    if (!Send(salveAdd, Protocol::Command_Inquire_Tigger, dataSend, dataReceive)) {
        return false;
    }
    tiggerData = dataReceive.at(0);
    return true;
}

bool Functions::Inquire_Motor(const quint16& salveAdd, qint16& speed)
{

    QByteArray dataSend, dataReceive;
    if (!Send(salveAdd, Protocol::Command_Inquire_Motor, dataSend, dataReceive)) {
        return false;
    }
    speed = Convert::toqint16(dataReceive);
    return true;
}

bool Functions::Inquire_Special(const quint16& salveAdd)
{
    // NOTE 暂时不做实现

    QByteArray dataSend, dataReceive;
    if (!Send(salveAdd, Protocol::Command_Inquire_Special, dataSend, dataReceive)) {
        return false;
    }
    return true;
}

bool Functions::Inquire_DAC(const quint16& salveAdd, const quint8& ch,
    quint16& dacData)
{

    QByteArray dataSend, dataReceive;
    dataSend.append(ch);
    if (!Send(salveAdd, Protocol::Command_Inquire_DAC, dataSend, dataReceive)) {
        return false;
    }
    dacData = Convert::toquint16(dataReceive);
    return true;
}

bool Functions::Inquire_SpecialADCWithTime(const quint16& salveAdd)
{
    // NOTE 暂时不做实现

    QByteArray dataSend, dataReceive;
    if (!Send(salveAdd, Protocol::Command_Inquire_SpecialADCWithTime, dataSend, dataReceive)) {
        return false;
    }
    return true;
}

bool Functions::Inquire_SpecialADCTrigger(const quint16& salveAdd)
{
    // NOTE 暂时不做实现

    QByteArray dataSend, dataReceive;
    if (!Send(salveAdd, Protocol::Command_Inquire_SpecialADCTrigger, dataSend, dataReceive)) {
        return false;
    }
    return true;
}

bool Functions::Inquire_SpecialStatus(const quint16& salveAdd)
{
    // NOTE 暂时不做实现

    QByteArray dataSend, dataReceive;
    if (!Send(salveAdd, Protocol::Command_Inquire_SpecialStatus, dataSend, dataReceive)) {
        return false;
    }
    return true;
}

bool Functions::Inquire_SpecialDoubleADCTrigger(const quint16& salveAdd)
{
    // NOTE 暂时不做实现

    QByteArray dataSend, dataReceive;
    if (!Send(salveAdd, Protocol::Command_Inquire_SpecialDoubleADCTrigger, dataSend, dataReceive)) {
        return false;
    }
    return true;
}

bool Functions::Inquire_Status(const quint16& salveAdd, const quint8& ch,
    bool& status)
{

    QByteArray dataSend, dataReceive;
    dataSend.append(ch);
    if (!Send(salveAdd, Protocol::Command_Inquire_Status, dataSend, dataReceive)) {
        return false;
    }
    status = dataReceive.at(0) != 0;
    return true;
}

bool Functions::Control_Valve(const quint16& salveAdd, const QBitArray& status)
{

    QByteArray dataSend, dataReceive;
    dataSend.append(Convert::from(status));
    if (!Send(salveAdd, Protocol::Command_Control_Valve, dataSend, dataReceive)) {
        return false;
    }
    return true;
}

bool Functions::Control_Motor(const quint16& salveAdd, const qint16& speed)
{

    QByteArray dataSend, dataReceive;
    dataSend.append(Convert::from(speed));
    if (!Send(salveAdd, Protocol::Command_Control_Motor, dataSend, dataReceive)) {
        return false;
    }
    return true;
}

bool Functions::Control_SM(const quint16& salveAdd, const quint8& ch,
    const StepMotor& dir)
{

    QByteArray dataSend, dataReceive;
    dataSend.append(ch);
    dataSend.append(quint8(dir));
    if (!Send(salveAdd, Protocol::Command_Control_SM, dataSend, dataReceive)) {
        return false;
    }
    return true;
}

bool Functions::Control_DAC(const quint16& salveAdd, const quint8& ch,
    const quint16& data)
{

    QByteArray dataSend, dataReceive;
    dataSend.append(ch);
    dataSend.append(Convert::from(data));
    if (!Send(salveAdd, Protocol::Command_Control_DAC, dataSend, dataReceive)) {
        return false;
    }
    return true;
}

bool Functions::Control_ValveOpen(const quint16& salveAdd,
    const QBitArray& valveData)
{

    QByteArray dataSend, dataReceive;
    dataSend.append(Convert::from(valveData));
    if (!Send(salveAdd, Protocol::Command_Control_ValveOpen, dataSend, dataReceive)) {
        return false;
    }
    return true;
}

bool Functions::Control_ValveClose(const quint16& salveAdd,
    const QBitArray& valveData)
{

    QByteArray dataSend, dataReceive;
    dataSend.append(Convert::from(valveData));
    if (!Send(salveAdd, Protocol::Command_Control_ValveClose, dataSend, dataReceive)) {
        return false;
    }
    return true;
}

bool Functions::AutoControl_SM_By_Step(const quint16& salveAdd,
    const quint8& ch,
    const qint32& step)
{

    QByteArray dataSend, dataReceive;
    dataSend.append(Convert::from(ch));
    dataSend.append(Convert::from(step));
    if (Send(salveAdd, Protocol::Command_AutoControl_SM_By_Step, dataSend, dataReceive)) {
        return true;
    }
    return false;
}

bool Functions::AutoControl_SM_By_Limit(const quint16& salveAdd,
    const quint8& ch, const StepMotor& dir, const quint8& limitNo)
{

    QByteArray dataSend, dataReceive;
    dataSend.append(ch);
    dataSend.append(Convert::from(quint8(dir)));
    dataSend.append(Convert::from(limitNo));
    if (Send(salveAdd, Protocol::Command_AutoControl_SM_By_Limit, dataSend, dataReceive)) {
        return true;
    }
    return false;
}

bool Functions::AutoControl_SM_By_Step_With_ADC_And_Encoder(const quint16& salveAdd)
{
    // NOTE 暂时不做实现

    QByteArray dataSend, dataReceive;
    if (Send(salveAdd, Protocol::Command_AutoControl_SM_By_Step_With_ADC_And_Encoder,
            dataSend, dataReceive)) {
        return true;
    }
    return false;
}

bool Functions::AutoControl_SpecialADCWithTime(const quint16& salveAdd)
{
    // NOTE 暂时不做实现

    QByteArray dataSend, dataReceive;
    if (Send(salveAdd, Protocol::Command_AutoControl_SpecialADCWithTime,
            dataSend, dataReceive)) {
        return true;
    }
    return false;
}

bool Functions::AutoControl_SpecialADCWithTrigger(const quint16& salveAdd)
{
    // NOTE 暂时不做实现

    QByteArray dataSend, dataReceive;
    if (Send(salveAdd, Protocol::Command_AutoControl_SpecialADCWithTrigger,
            dataSend, dataReceive)) {
        return true;
    }
    return false;
}

bool Functions::AutoControl_SpecialMotorPosition(const quint16& salveAdd)
{
    // NOTE 暂时不做实现

    QByteArray dataSend, dataReceive;
    if (Send(salveAdd, Protocol::Command_AutoControl_SpecialMotorPosition,
            dataSend, dataReceive)) {
        return true;
    }
    return false;
}

bool Functions::AutoControl_SpecialADCDoubleWithTrigger(const quint16& salveAdd)
{
    // NOTE 暂时不做实现

    QByteArray dataSend, dataReceive;
    if (Send(salveAdd, Protocol::Command_AutoControl_SpecialADCDoubleWithTrigger,
            dataSend, dataReceive)) {
        return true;
    }
    return false;
}

bool Functions::Setting_SM_Speed(const quint16& salveAdd, const quint8& ch,
    const quint16& speed, const quint32& accel)
{

    QByteArray dataSend, dataReceive;
    dataSend.append(ch);
    dataSend.append(Convert::from(speed));
    dataSend.append(Convert::from(accel));
    if (Send(salveAdd, Protocol::Command_Setting_SM_Speed, dataSend, dataReceive)) {
        return true;
    }
    return false;
}

bool Functions::Setting_Valve_Default(const quint16& salveAdd,
    const QBitArray& valveData)
{

    QByteArray dataSend, dataReceive;
    dataSend.append(Convert::from(valveData));
    if (Send(salveAdd, Protocol::Command_Setting_Valve_Default, dataSend, dataReceive)) {
        return true;
    }
    return false;
}

bool Functions::Setting_Encoder_Zero(const quint16& salveAdd, const quint8& ch)
{

    QByteArray dataSend, dataReceive;
    dataSend.append(ch);
    if (Send(salveAdd, Protocol::Command_Setting_Encoder_Zero, dataSend, dataReceive)) {
        return true;
    }
    return false;
}

bool Functions::Setting_Protect_Limit(const quint16& salveAdd, const quint8& ch,
    const StepMotor& dir, const quint8& limitNo)
{

    QByteArray dataSend, dataReceive;
    dataSend.append(ch);
    dataSend.append(quint8(dir));
    dataSend.append(limitNo);
    if (Send(salveAdd, Protocol::Command_Setting_Protect_Limit, dataSend, dataReceive)) {
        return true;
    }
    return false;
}

bool Functions::Setting_PIDParam(const quint16& salveAdd)
{
    // NOTE 暂时不做实现

    QByteArray dataSend, dataReceive;
    if (!Send(salveAdd, Protocol::Command_Setting_PIDParam, dataSend, dataReceive)) {
        return false;
    }
    return true;
}

bool Functions::Setting_PIDInput(const quint16& salveAdd)
{
    // NOTE 暂时不做实现

    QByteArray dataSend, dataReceive;
    if (!Send(salveAdd, Protocol::Command_Setting_PIDInput, dataSend, dataReceive)) {
        return false;
    }
    return true;
}

bool Functions::Setting_PIDEnable(const quint16& salveAdd)
{
    // NOTE 暂时不做实现

    QByteArray dataSend, dataReceive;
    if (!Send(salveAdd, Protocol::Command_Setting_PIDEnable, dataSend, dataReceive)) {
        return false;
    }
    return true;
}

bool Functions::Setting_SM_RelDir(const quint16& salveAdd, const quint8& ch, const Functions::StepMotor dir)
{

    QByteArray dataSend, dataReceive;
    dataSend.append(ch);
    dataSend.append(dir);
    if (Send(salveAdd, Protocol::Command_Setting_SM_RelDir, dataSend, dataReceive)) {
        return true;
    }
    return false;
}

bool Functions::Setting_USART(const quint16& salveAdd, const quint8& baundNo)
{

    QByteArray dataSend, dataReceive;
    dataSend.append(baundNo);
    if (Send(salveAdd, Protocol::Command_Setting_USART, dataSend, dataReceive)) {
        return true;
    }
    return false;
}

bool Functions::Setting_Address(const quint16& salveAdd, const quint16& salveAddSet)
{

    QByteArray dataSend, dataReceive;
    dataSend.append(salveAddSet);
    if (Send(salveAdd, Protocol::Command_Setting_Address, dataSend, dataReceive)) {
        return true;
    }
    return false;
}

bool Functions::Special_Reset(const quint16& salveAdd)
{

    QByteArray dataSend, dataReceive;
    if (Send(salveAdd, Protocol::Command_Special_Reset, dataSend, dataReceive)) {
        return true;
    }
    return false;
}

bool Functions::Special_Stop(const quint16& salveAdd)
{
    // NOTE 暂时不做实现

    QByteArray dataSend, dataReceive;
    if (Send(salveAdd, Protocol::Command_Special_Stop, dataSend, dataReceive)) {
        return true;
    }
    return false;
}

bool Functions::Special_Continue(const quint16& salveAdd)
{
    // NOTE 暂时不做实现

    QByteArray dataSend, dataReceive;
    if (Send(salveAdd, Protocol::Command_Special_Continue, dataSend, dataReceive)) {
        return true;
    }
    return false;
}

bool Functions::Special_Cacel(const quint16& salveAdd)
{
    // NOTE 暂时不做实现

    QByteArray dataSend, dataReceive;
    if (Send(salveAdd, Protocol::Command_Special_Cacel, dataSend, dataReceive)) {
        return true;
    }
    return false;
}

Functions::Functions()
{
    //    _Ptc.GoToThread(&_PtcThread);
    //    connect(this, &Functions::Send, &_Ptc, &Protocol::Send); //, Qt::BlockingQueuedConnection);
    //    connect(this, &Functions::Open, &_Ptc, &Protocol::Open); //, Qt::BlockingQueuedConnection);
    //    connect(this, &Functions::Close, &_Ptc, &Protocol::Close); //, Qt::BlockingQueuedConnection);
    //    connect(&_Ptc, &Protocol::DebugOut, this, &Functions::DebugOut);
}
