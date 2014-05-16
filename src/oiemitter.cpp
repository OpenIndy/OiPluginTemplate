#include "oiemitter.h"

OiEmitter::OiEmitter(QObject *parent) :
    QObject(parent)
{
}


void OiEmitter::emitSendString(QString s){

    emit sendString(s);

}

void OiEmitter::emitSendConnectionStat(bool b)
{
    emit sendConnectionStat(b);
}

void OiEmitter::emitSendIsReadyForMeasurement(bool b)
{
    emit sendIsReadyForMeasurement(b);
}

void OiEmitter::emitSendSensorError(QString s)
{
    emit sendSensorError(s);
}

void OiEmitter::emitSendMeasureTrigger()
{
    emit sendMeasureTrigger();
}


