#include "point.h"
#include "function.h"

Point::Point() :xyz(4)
{
    this->id = Configuration::generateID();
    this->myNominalCoordSys = NULL;
    this->isSolved = false;
    this->isUpdated = false;
    this->isDrawn = true;
}

/*!
 * \brief Point::Point
 * \param copy
 */
Point::Point(const Point &copy){
    this->id = copy.id;
    this->name = copy.name;
    this->xyz = copy.xyz;
    this->isSolved = copy.isSolved;
}

Point::~Point(){

}

/*!
 * \brief Point::recalc
 * Execute alls functions in the specified order
 */
void Point::recalc(){
    //clear results
    this->myStatistic.displayResiduals.clear();
    /*
     * isDefined -> becomes true as soon as the first function of a feature has been executed, which defines the feature
     * isSolved -> is true as long as there isn't any function which cannot be successfully executed
     */
    bool isDefined = false;
    foreach(Function *f, this->functionList){
        f->clearResults();
        if(!isDefined){
            this->isSolved = f->exec(*this);
            isDefined = true;
        }else if(this->isSolved){
            this->isSolved = f->exec(*this);
        }
    }
    //if no function is set this feature cannot be solved and its coordinates are reset
    if(this->functionList.size() == 0 && this->isNominal == false){
        this->isSolved = false;
        this->xyz = OiVec(4);
    }
    //if not solved reset statistic
    if(!this->isSolved){
        this->myStatistic = Statistic();
    }
}

QString Point::getDisplayX() const{
    return QString::number(this->xyz.getAt(0)*UnitConverter::getDistanceMultiplier(),'f',UnitConverter::distanceDigits);
}

QString Point::getDisplayY() const{
    return QString::number(this->xyz.getAt(1)*UnitConverter::getDistanceMultiplier(),'f',UnitConverter::distanceDigits);
}

QString Point::getDisplayZ() const{
    return QString::number(this->xyz.getAt(2)*UnitConverter::getDistanceMultiplier(),'f',UnitConverter::distanceDigits);
}

QString Point::getDisplayIsCommon() const{
    return QString(isCommon?"true":"false");
}

QString Point::getDisplayIsNominal() const{
    return QString(isNominal?"true":"false");
}

QString Point::getDisplayObs() const{
    return QString::number(this->myObservations.size());
}

QString Point::getDisplaySolved() const{
    return QString(this->isSolved?"true":"false");
}

QString Point::getDisplayMConfig() const{
    return this->mConfig.name;
}

QString Point::getDisplayStdDev() const{

    if(this->myStatistic.isValid){
        return QString::number(this->myStatistic.stdev*UnitConverter::getDistanceMultiplier(),'f',UnitConverter::distanceDigits);
    }else{
        return "-/-";
    }
}
