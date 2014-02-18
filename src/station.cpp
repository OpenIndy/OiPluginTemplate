#include "station.h"
#include <QVariant>

Station::Station(QString name)
{
    this->name = name;

    this->id = Configuration::generateID();
    position = new Point();

    //ini member
    coordSys = new CoordinateSystem();
    coordSys->name = this->name;

    instrument = NULL;
    sensorPad = new SensorControl(this);
    //InstrumentConfig = new SensorConfiguration; //TODO null pointer??
    InstrumentConfig = NULL;

    //move controller to the station thread
    sensorPad->moveToThread(&stationThread);

    //connections between station and sensorcontrol
    connect(this->sensorPad,SIGNAL(commandFinished(bool)),this,SLOT(emitActionFinished(bool)));

    connect(this,SIGNAL(startMeasure(Geometry*,bool)),this->sensorPad,SLOT(measure(Geometry*,bool)));
    connect(this,SIGNAL(startStream()),this->sensorPad,SLOT(stream()));
    connect(this,SIGNAL(startMove(double,double,double,bool)),this->sensorPad,SLOT(move(double,double,double,bool)));
    connect(this,SIGNAL(startMove(double,double,double)),this->sensorPad,SLOT(move(double,double,double)));
    connect(this,SIGNAL(startInitialize()),this->sensorPad,SLOT(initialize()));
    connect(this,SIGNAL(startMotorState(bool)),this->sensorPad,SLOT(motorState(bool)));
    connect(this,SIGNAL(startHome()),this->sensorPad,SLOT(home()));
    connect(this,SIGNAL(startToggleSight()),this->sensorPad,SLOT(toggleSight()));
    connect(this,SIGNAL(startCompensation()),this->sensorPad,SLOT(compensation()));
    connect(this,SIGNAL(startSendCommand(QString)),this->sensorPad,SLOT(sendCommandString(QString)));
    connect(this,SIGNAL(startConnect(ConnectionConfig*)),this->sensorPad,SLOT(connectSensor(ConnectionConfig*)));
    connect(this,SIGNAL(startDisconnect()),this->sensorPad,SLOT(disconnectSensor()));

    //start the station thread
    stationThread.start();

    this->isUpdated = false;
    this->isDrawn = true;

}

Station::~Station(){

    stationThread.quit();
    stationThread.wait();
}

void Station::stopThread(){
    stationThread.quit();
    stationThread.wait();
}

void Station::startThread(){
    stationThread.start();
}

void Station::setInstrumentConfig(SensorConfiguration *sensorConfig){

    InstrumentConfig = sensorConfig;
    instrument->setSensorConfiguration(sensorConfig);

}

SensorConfiguration* Station::getInstrumentConfig(){
    return InstrumentConfig;
}

/*!
 * \brief Station::recalc
 * Execute alls functions in the specified order
 */
void Station::recalc(){

}

/*!
 * \brief Station::emitActionFinished
 * \param wasSuccesful
 * will be emitted when the sensor action is completed
 */
void Station::emitActionFinished(bool wasSuccesful){

    emit actionFinished(wasSuccesful);
}

/*!
 * \brief emitStartStream
 */
void Station::emitStartStream(){
    emit startStream();
}

/*!
 * \brief Station::stopStream
 */
void Station::stopStream(){
    QThread::msleep(1);
    this->instrument->dataStreamIsActive = false;
    emit actionFinished(true);
}

void Station::emitStartCommand(QString cmd){
    emit startSendCommand(cmd);
}

/*!
 * \brief Station::emitStartMeasure
 * \param mConfig
 * \param geom
 * starts the measurement defined by the given MeasurementConfig.
 * The determined observation will be saved in the station coordinatesystem and
 * in the given geometry
 */
void Station::emitStartMeasure(Geometry *geom, bool isActiveCoordSys){
    emit startMeasure(geom,isActiveCoordSys);
}

/*!
 * \brief Station::emitStartMove
 * \param azimuth
 * \param zenith
 * \param dist
 * \param isRelativ
 */
void Station::emitStartMove(double azimuth, double zenith, double dist, bool isRelativ){
    emit startMove(azimuth, zenith, dist, isRelativ);
}

/*!
 * \brief Station::emitStartMove
 * \param x
 * \param y
 * \param z
 */
void Station::emitStartMove(double x, double y, double z){
    emit startMove(x, y, z);
}

/*!
 * \brief Station::emitStartInitialize
 */
void Station::emitStartInitialize(){
    emit startInitialize();
}

/*!
 * \brief Station::emitStartMotorState
 */
void Station::emitStartMotorState(bool b){
    emit startMotorState(b);
}


void Station::emitStartCompensation(){
    emit startCompensation();
}

/*!
 * \brief Station::emitStartHome
 */
void Station::emitStartHome(){
    emit startHome();
}

/*!
 * \brief Station::emitStartToggleSight
 */
void Station::emitStartToggleSight(){
    emit startToggleSight();
}

/*!
 * \brief Station::emitStartConnect
 */
void Station::emitStartConnect(ConnectionConfig *cConfig){
    emit startConnect(cConfig);
}

/*!
 * \brief Station::emitStartDisconnect
 */
void Station::emitStartDisconnect(){
    emit startDisconnect();
}

QString Station::getDisplayX() const{
    return QString::number(this->position->xyz.getAt(0)*UnitConverter::getDistanceMultiplier(),'f',UnitConverter::distanceDigits);
}

QString Station::getDisplayY() const{
    return QString::number(this->position->xyz.getAt(1)*UnitConverter::getDistanceMultiplier(),'f',UnitConverter::distanceDigits);
}

QString Station::getDisplayZ() const{
    return QString::number(this->position->xyz.getAt(2)*UnitConverter::getDistanceMultiplier(),'f',UnitConverter::distanceDigits);
}

QString Station::getDisplayIsCommon() const{
    return QString(position->isCommon?"true":"false");
}

QString Station::getDisplayIsNominal() const{
    return QString(position->isNominal?"true":"false");
}

QString Station::getDisplayObs() const{
    return QString::number(this->position->myObservations.size());
}

QString Station::getDisplaySolved() const{
    return QString(this->isSolved?"true":"false");
}

QString Station::getDisplayMConfig() const{
    return this->position->mConfig.name;
}

QString Station::getDisplayStdDev() const{

    if(this->position->myStatistic.isValid){
        return QString::number(this->position->myStatistic.stdev * UnitConverter::getDistanceMultiplier(),'f',UnitConverter::distanceDigits);
    }else{
        return "-/-";
    }
}
