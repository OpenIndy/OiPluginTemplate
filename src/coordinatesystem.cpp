#include "coordinatesystem.h"

#include "observation.h"
#include "trafoparam.h"
#include "geometry.h"
#include "point.h"

CoordinateSystem::CoordinateSystem() : origin(4){
    this->id = Configuration::generateID();
    this->isUpdated = false;
    this->isDrawn = true;
}

CoordinateSystem::~CoordinateSystem(){

    //delete all observations made from this station coordinate system (only if this is a station system)
    foreach(Observation *myObs, this->observations){
        if(myObs != NULL){
            delete myObs;
        }
    }

    //delete transformation parameter sets from this coordinate system
    foreach(TrafoParam *myTrafo, this->trafoParams){
        if(myTrafo != NULL){
            delete myTrafo;
        }
    }

    //delete nominals of this coordinate system
    foreach(Geometry *myGeom, this->nominals){
        if(myGeom != NULL){
            delete myGeom;
        }
    }

}

void CoordinateSystem::recalc(){

}

QString CoordinateSystem::getDisplayX() const{
    return QString::number(this->origin.getAt(0)*UnitConverter::getDistanceMultiplier(),'f',UnitConverter::distanceDigits);
}

QString CoordinateSystem::getDisplayY() const{
    return QString::number(this->origin.getAt(1)*UnitConverter::getDistanceMultiplier(),'f',UnitConverter::distanceDigits);
}

QString CoordinateSystem::getDisplayZ() const{
    return QString::number(this->origin.getAt(2)*UnitConverter::getDistanceMultiplier(),'f',UnitConverter::distanceDigits);
}

QString CoordinateSystem::getDisplaySolved() const{
    return QString(this->isSolved?"true":"false");
}

bool CoordinateSystem::toOpenIndyXML(QXmlStreamWriter &stream){

    stream.writeStartElement("coordinatesystem");
    stream.writeAttribute("id", QString::number(this->id));
    stream.writeAttribute("name", this->name);
    stream.writeAttribute("solved", QString::number(this->isSolved));


        foreach (Observation *obs, this->observations) {
            obs->writeProxyObservations(stream);
        }

        foreach (Geometry *geom, this->nominals) {

                stream.writeStartElement("member");
                stream.writeAttribute("type", "nominalGeometry");
                stream.writeAttribute("ref", QString::number(geom->id));
                stream.writeEndElement();

        }

        for(int k =0;k<this->trafoParams.size();k++){
            stream.writeStartElement("member");
            stream.writeAttribute("type", "transformationParameter");
            stream.writeAttribute("ref", QString::number(this->trafoParams.at(k)->id));
            stream.writeEndElement();
        }

        this->writeFeatureAttributes(stream);

        stream.writeEndElement();


    return true;
}

ElementDependencies CoordinateSystem::fromOpenIndyXML(QXmlStreamReader &xml){

    ElementDependencies dependencies;

    QXmlStreamAttributes attributes = xml.attributes();

    if(attributes.hasAttribute("name")){
        this->name = attributes.value("name").toString();
    }
    if(attributes.hasAttribute("id")) {
        this->id = attributes.value("id").toInt();
        dependencies.elementID = this->id;
        dependencies.typeOfElement = Configuration::eCoordinateSystemElement;
    }

    /* Next element... */
    xml.readNext();
    /*
     * We're going to loop over the things because the order might change.
     * We'll continue the loop until we hit an EndElement named coordinatesystem.
     */
    while(!(xml.tokenType() == QXmlStreamReader::EndElement &&
            xml.name() == "coordinatesystem")) {
        if(xml.tokenType() == QXmlStreamReader::StartElement) {

            if(xml.name() == "member"){

                while(!(xml.tokenType() == QXmlStreamReader::EndElement &&
                        xml.name() == "member")) {
                    if(xml.tokenType() == QXmlStreamReader::StartElement) {

                        QXmlStreamAttributes memberAttributes = xml.attributes();

                        if(memberAttributes.hasAttribute("type")){

                            if (memberAttributes.value("type") == "observation"){

                                if(memberAttributes.hasAttribute("ref")){
                                    dependencies.addObservationID(memberAttributes.value("ref").toInt());
                                }

                            }else if (memberAttributes.value("type") == "nominalGeometry"){

                                if(memberAttributes.hasAttribute("ref")){
                                    dependencies.addFeatureID(memberAttributes.value("ref").toInt(),"nominalGeometry");
                                }
                            }else{
                                 this->readFeatureAttributes(xml, dependencies);
                            }


                        }
                    }
                    /* ...and next... */
                    xml.readNext();
                }
            }

            if(xml.name() == "function"){

                this->readFunction(xml, dependencies);

            }

        }
        /* ...and next... */
        xml.readNext();
    }

    return dependencies;
}

/*!
 * \brief CoordinateSystem::transformObservations
 * \param to
 * \return
 */
bool CoordinateSystem::transformObservations(CoordinateSystem *to){
    if(to != NULL){
        if(this == to){ //if coordinate systems are identical
            foreach(Observation *obs, this->observations){
                obs->myXyz = obs->myOriginalXyz;
                obs->isValid = true;
            }
            return true;
        }else{ //if there is something to transform
            TrafoParam *tp = this->findTrafoParam(to);
            if(tp != NULL){ //trafo params available
                OiMat t;
                if(tp->to == to){ //if trafo params are in correct order
                    t = tp->homogenMatrix;
                }else{ //homogen matrix needs to be inverted
                    t = tp->homogenMatrix.inv();
                }
                //transform coordinates and Qxx matrix of each observation
                foreach(Observation *obs, this->observations){
                    obs->myXyz = t * obs->myOriginalXyz;
                    obs->myStatistic.qxx = t * obs->myOriginalStatistic.qxx;
                    obs->isValid = true;
                }
                return true;
            }else{ //no trafo params available
                foreach(Observation *obs, this->observations){
                    obs->isValid = false;
                }
                return false;
            }
        }
    }
    return false;
}

/*!
 * \brief CoordinateSystem::setObservationState
 * Set observations isValid to valid
 * \param valid
 */
void CoordinateSystem::setObservationState(bool valid){
    foreach(Observation *obs, this->observations){
        if(valid == true){
            obs->myXyz = obs->myOriginalXyz;
        }
        obs->isValid = valid;
    }
}

/*!
 * \brief CoordinateSystem::findTrafoParam
 * \param searchTP
 * \return
 */
TrafoParam* CoordinateSystem::findTrafoParam(CoordinateSystem *searchToSystem){
    foreach(TrafoParam *tp, this->trafoParams){
        if(tp->to != NULL && tp->from != NULL){
            if(tp->to == searchToSystem || tp->from == searchToSystem){
                return tp;
            }
        }
    }
    return NULL;
}
