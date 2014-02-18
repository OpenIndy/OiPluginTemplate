#include "function.h"

/*!
 * \brief Function::exec
 * \param c
 * \return
 */
bool Function::exec(Circle &c){
    Console::addLine("Function \"" + this->getMetaData()->name + "\" not implemented for type circle");
    return false;
}

/*!
 * \brief Function::exec
 * \param c
 * \return
 */
bool Function::exec(Cone &c){
    Console::addLine("Function \"" + this->getMetaData()->name + "\" not implemented for type cone");
    return false;
}

/*!
 * \brief Function::exec
 * \param c
 * \return
 */
bool Function::exec(Cylinder &c){
    Console::addLine("Function \"" + this->getMetaData()->name + "\" not implemented for type cylinder");
    return false;
}

/*!
 * \brief Function::exec
 * \param c
 * \return
 */
bool Function::exec(CoordinateSystem &c){
    Console::addLine("Function \"" + this->getMetaData()->name + "\" not implemented for type point");
    return false;
}

/*!
 * \brief Function::exec
 * \param e
 * \return
 */
bool Function::exec(Ellipsoid &e){
    Console::addLine("Function \"" + this->getMetaData()->name + "\" not implemented for type ellipsoid");
    return false;
}

/*!
 * \brief Function::exec
 * \param h
 * \return
 */
bool Function::exec(Hyperboloid &h){
    Console::addLine("Function \"" + this->getMetaData()->name + "\" not implemented for type hyperboloid");
    return false;
}

/*!
 * \brief Function::exec
 * \param l
 * \return
 */
bool Function::exec(Line &l){
    Console::addLine("Function \"" + this->getMetaData()->name + "\" not implemented for type line");
    return false;
}

/*!
 * \brief Function::exec
 * \param n
 * \return
 */
bool Function::exec(Nurbs &n){
    Console::addLine("Function \"" + this->getMetaData()->name + "\" not implemented for type nurbs");
    return false;
}

/*!
 * \brief Function::exec
 * \param p
 * \return
 */
bool Function::exec(Paraboloid &p){
    Console::addLine("Function \"" + this->getMetaData()->name + "\" not implemented for type paraboloid");
    return false;
}

/*!
 * \brief Function::exec
 * \param p
 * \return
 */
bool Function::exec(Plane &p){
    Console::addLine("Function \"" + this->getMetaData()->name + "\" not implemented for type plane");
    return false;
}

/*!
 * \brief Function::exec
 * \param p
 * \return
 */
bool Function::exec(Point &p){
    Console::addLine("Function \"" + this->getMetaData()->name + "\" not implemented for type point");
    return false;
}

/*!
 * \brief Function::exec
 * \param p
 * \return
 */
bool Function::exec(PointCloud &p){
    Console::addLine("Function \"" + this->getMetaData()->name + "\" not implemented for type pointcloud");
    return false;
}

/*!
 * \brief Function::exec
 * \param s
 * \return
 */
bool Function::exec(ScalarEntityAngle &s){
    Console::addLine("Function \"" + this->getMetaData()->name + "\" not implemented for type angle");
    return false;
}

/*!
 * \brief Function::exec
 * \param s
 * \return
 */
bool Function::exec(ScalarEntityDistance &s){
    Console::addLine("Function \"" + this->getMetaData()->name + "\" not implemented for type distance");
    return false;
}

/*!
 * \brief Function::exec
 * \param s
 * \return
 */
bool Function::exec(Sphere &s){
    Console::addLine("Function \"" + this->getMetaData()->name + "\" not implemented for type sphere");
    return false;
}

/*!
 * \brief Function::exec
 * \param s
 * \return
 */
bool Function::exec(Station &s){
    Console::addLine("Function \"" + this->getMetaData()->name + "\" not implemented for type point");
    return false;
}

/*!
 * \brief Function::exec
 * \param t
 * \return
 */
bool Function::exec(TrafoParam &t){
    Console::addLine("Function \"" + this->getMetaData()->name + "\" not implemented for type point");
    return false;
}

/*!
 * \brief getIntegerParameter
 * Can be used for custom parameter definition of type int
 * \return
 */
QMap<QString, int> Function::getIntegerParameter(){
    QMap<QString, int> result;
    return result;
}

/*!
 * \brief getDoubleParameter
 * Can be used for custom parameter definition of type double
 * \return
 */
QMap<QString,double> Function::getDoubleParameter(){
    QMap<QString, double> result;
    return result;
}

/*!
 * \brief getStringParameter
 * Can be used for custom parameter definition string
 * \return
 */
QMap<QString, QStringList> Function::getStringParameter(){
    QMap<QString, QStringList> result;
    return result;
}

/*!
 * \brief Function::getResultProtocol
 * The complete result protocol is shown for every function after execution
 * \return
 */
QStringList Function::getResultProtocol(){
    return QStringList();
}

/*!
 * \brief Function::setFunctionConfiguration
 * Set function configuration which contains values for custom parameters
 * \param config
 */
void Function::setFunctionConfiguration(FunctionConfiguration config){
    this->myConfiguration = config;
    this->myConfiguration.functionConfigSet = true;
}

/*!
 * \brief Function::getFunctionConfiguration
 * Get function configuration which contains values for custom parameters
 * \return
 */
FunctionConfiguration Function::getFunctionConfiguration(){
    if(!this->myConfiguration.functionConfigSet){ //if function config is queried the first time it is filled with default values
        this->myConfiguration.intParameter = this->getIntegerParameter();
        this->myConfiguration.doubleParameter = this->getDoubleParameter();
        QMap<QString, QStringList> stringParameter = this->getStringParameter();
        QMapIterator<QString, QStringList> stringIterator(stringParameter);
        while(stringIterator.hasNext()){
            stringIterator.next();
            QString key = static_cast<QString>(stringIterator.key());
            QStringList value = static_cast<QStringList>(stringIterator.value());
            if(value.size() > 0){
                //first value in list is default value
                this->myConfiguration.stringParameter.insert(key, value.at(0));
            }
        }
    }
    return this->myConfiguration;
}

/*!
 * \brief Function::isValid
 * Checks wether all elements needed for calculation are present
 * \return
 */
bool Function::isValid(){
    QList<InputParams> params = this->getNeededElements();
    for(int i = 0; i < params.size(); i++){
        if(this->featureOrder.contains(i)){ //if featureOrder contains needed element i
            QMap<int, QList<InputFeature> >::iterator idx = this->featureOrder.find(i);
            if(idx != this->featureOrder.end() && idx.value().size() > 0){ //if the list with elements is not empty
                QList<InputFeature> featurePosition = idx.value();
                for(int j = 0; j < featurePosition.size(); j++){
                    if(featurePosition.at(j).typeOfElement != params.at(i).typeOfElement){ //if the element type is correct
                        return false;
                    }
                }
            }else{
                return false;
            }
        }else{
            return false;
        }
    }
    return true;
}

/*!
 * \brief Function::getFeatureOrder
 * \return
 */
QMap<int, QList<InputFeature> > Function::getFeatureOrder(){
    return this->featureOrder;
}

/*!
 * \brief Function::getStatistic
 * \return
 */
Statistic& Function::getStatistic(){
    return this->myStatistic;
}

/*!
 * \brief Function::getId
 * \return
 */
int Function::getId(){
    return this->id;
}

/*!
 * \brief Function::addStation
 * \param s
 * \param position
 */
void Function::addStation(Station *s, int position){
    this->stations.append(s);
    InputFeature feature;
    feature.id = s->id;
    feature.typeOfElement = Configuration::eStationElement;
    feature.isUsed = true;
    if(this->featureOrder.contains(position)){
        QMap<int, QList<InputFeature> >::iterator i = this->featureOrder.find(position);
        if(i != this->featureOrder.end()){
            QList<InputFeature> featurePosition = i.value();
            featurePosition.append(feature);
            this->featureOrder.insert(position, featurePosition);
        }
    }else{
        QList<InputFeature> featurePosition;
        featurePosition.append(feature);
        this->featureOrder.insert(position, featurePosition);
    }
}

/*!
 * \brief Function::removeStation
 * Remove the station with the specified id from the list of stations (if present)
 * \param id
 */
void Function::removeStation(int id){
    foreach(Station *s, this->stations){
        if(s->id == id){
            this->stations.removeOne(s);
            for(int i = 0; i < this->getNeededElements().length(); i++){
                if(this->featureOrder.contains(i)){
                    QMap<int, QList<InputFeature> >::iterator idx = this->featureOrder.find(i);
                    if(idx != this->featureOrder.end()){
                        QList<InputFeature> featurePosition = idx.value();
                        for(int j = 0; j < featurePosition.size(); j++){
                            if(featurePosition.at(j).id == id){
                                featurePosition.removeAt(j);
                                break;
                            }
                        }
                        this->featureOrder.insert(i, featurePosition);
                        break;
                    }
                }
            }
            break;
        }
    }
}

/*!
 * \brief Function::getStation
 * Returns the station with the specified id (if present) or NULL
 * \param id
 * \return
 */
Station* Function::getStation(int id){
    foreach(Station *s, this->stations){
        if(s->id == id){
            return s;
        }
    }
    return NULL;
}

/*!
 * \brief Function::getStations
 * Returns the complete list of stations
 * \return
 */
QList<Station*> Function::getStations(){
    return this->stations;
}

/*!
 * \brief Function::addCoordSystem
 * \param c
 * \param position
 */
void Function::addCoordSystem(CoordinateSystem *c, int position){
    this->coordSystems.append(c);
    InputFeature feature;
    feature.id = c->id;
    feature.typeOfElement = Configuration::eCoordinateSystemElement;
    feature.isUsed = true;
    if(this->featureOrder.contains(position)){
        QMap<int, QList<InputFeature> >::iterator i = this->featureOrder.find(position);
        if(i != this->featureOrder.end()){
            QList<InputFeature> featurePosition = i.value();
            featurePosition.append(feature);
            this->featureOrder.insert(position, featurePosition);
        }
    }else{
        QList<InputFeature> featurePosition;
        featurePosition.append(feature);
        this->featureOrder.insert(position, featurePosition);
    }
}

/*!
 * \brief Function::removeCoordSystem
 * Remove the coordinate system with the specified id from the list of coordinate systems (if present)
 * \param id
 */
void Function::removeCoordSystem(int id){
    foreach(CoordinateSystem *c, this->coordSystems){
        if(c->id == id){
            this->coordSystems.removeOne(c);
            for(int i = 0; i < this->getNeededElements().length(); i++){
                if(this->featureOrder.contains(i)){
                    QMap<int, QList<InputFeature> >::iterator idx = this->featureOrder.find(i);
                    if(idx != this->featureOrder.end()){
                        QList<InputFeature> featurePosition = idx.value();
                        for(int j = 0; j < featurePosition.size(); j++){
                            if(featurePosition.at(j).id == id){
                                featurePosition.removeAt(j);
                                break;
                            }
                        }
                        this->featureOrder.insert(i, featurePosition);
                        break;
                    }
                }
            }
            break;
        }
    }
}

/*!
 * \brief Function::getCoordinateSystem
 * Returns the coordinate system with the specified id (if present) or NULL
 * \param id
 * \return
 */
CoordinateSystem* Function::getCoordinateSystem(int id){
    foreach(CoordinateSystem *cs, this->coordSystems){
        if(cs->id == id){
            return cs;
        }
    }
    return NULL;
}

/*!
 * \brief Function::getCoordinateSystems
 * Returns the complete list of coordinate systems
 * \return
 */
QList<CoordinateSystem*> Function::getCoordinateSystems(){
    return this->coordSystems;
}

/*!
 * \brief Function::addTrafoParam
 * \param t
 * \param position
 */
void Function::addTrafoParam(TrafoParam *t, int position){
    this->trafoParams.append(t);
    InputFeature feature;
    feature.id = t->id;
    feature.typeOfElement = Configuration::eTrafoParamElement;
    feature.isUsed = true;
    if(this->featureOrder.contains(position)){
        QMap<int, QList<InputFeature> >::iterator i = this->featureOrder.find(position);
        if(i != this->featureOrder.end()){
            QList<InputFeature> featurePosition = i.value();
            featurePosition.append(feature);
            this->featureOrder.insert(position, featurePosition);
        }
    }else{
        QList<InputFeature> featurePosition;
        featurePosition.append(feature);
        this->featureOrder.insert(position, featurePosition);
    }
}

/*!
 * \brief Function::removeTrafoParam
 * Remove the transformations parameter with the specified id from the list of transformation parameters (if present)
 * \param id
 */
void Function::removeTrafoParam(int id){
    foreach(TrafoParam *t, this->trafoParams){
        if(t->id == id){
            this->trafoParams.removeOne(t);
            for(int i = 0; i < this->getNeededElements().length(); i++){
                if(this->featureOrder.contains(i)){
                    QMap<int, QList<InputFeature> >::iterator idx = this->featureOrder.find(i);
                    if(idx != this->featureOrder.end()){
                        QList<InputFeature> featurePosition = idx.value();
                        for(int j = 0; j < featurePosition.size(); j++){
                            if(featurePosition.at(j).id == id){
                                featurePosition.removeAt(j);
                                break;
                            }
                        }
                        this->featureOrder.insert(i, featurePosition);
                        break;
                    }
                }
            }
            break;
        }
    }
}

/*!
 * \brief Function::getTrafoParam
 * Returns the transformation parameter with the specified id (if present) or NULL
 * \param id
 * \return
 */
TrafoParam* Function::getTrafoParam(int id){
    foreach(TrafoParam *t, this->trafoParams){
        if(t->id == id){
            return t;
        }
    }
    return NULL;
}

/*!
 * \brief Function::getTrafoParams
 * Returns the complete list of transformation parameters
 * \return
 */
QList<TrafoParam*> Function::getTrafoParams(){
    return this->trafoParams;
}

/*!
 * \brief Function::addPoint
 * \param p
 * \param position
 */
void Function::addPoint(Point *p, int position){
    this->points.append(p);
    InputFeature feature;
    feature.id = p->id;
    feature.typeOfElement = Configuration::ePointElement;
    feature.isUsed = true;
    if(this->featureOrder.contains(position)){
        QMap<int, QList<InputFeature> >::iterator i = this->featureOrder.find(position);
        if(i != this->featureOrder.end()){
            QList<InputFeature> featurePosition = i.value();
            featurePosition.append(feature);
            this->featureOrder.insert(position, featurePosition);
        }
    }else{
        QList<InputFeature> featurePosition;
        featurePosition.append(feature);
        this->featureOrder.insert(position, featurePosition);
    }
}

/*!
 * \brief Function::removePoint
 * Remove the point with the specified id from the list of points (if present)
 * \param id
 */
void Function::removePoint(int id){
    foreach(Point *p, this->points){
        if(p->id == id){
            this->points.removeOne(p);
            for(int i = 0; i < this->getNeededElements().length(); i++){
                if(this->featureOrder.contains(i)){
                    QMap<int, QList<InputFeature> >::iterator idx = this->featureOrder.find(i);
                    if(idx != this->featureOrder.end()){
                        QList<InputFeature> featurePosition = idx.value();
                        for(int j = 0; j < featurePosition.size(); j++){
                            if(featurePosition.at(j).id == id){
                                featurePosition.removeAt(j);
                                break;
                            }
                        }
                        this->featureOrder.insert(i, featurePosition);
                        break;
                    }
                }
            }
            break;
        }
    }
}

/*!
 * \brief Function::getPoint
 * Returns the point with the specified id (if present) or NULL
 * \param id
 * \return
 */
Point* Function::getPoint(int id){
    foreach(Point *p, this->points){
        if(p->id == id){
            return p;
        }
    }
    return NULL;
}

/*!
 * \brief Function::getPoints
 * Returns the complete list of points
 * \return
 */
QList<Point*> Function::getPoints(){
    return this->points;
}

/*!
 * \brief Function::addLine
 * \param l
 * \param position
 */
void Function::addLine(Line *l, int position){
    this->lines.append(l);
    InputFeature feature;
    feature.id = l->id;
    feature.typeOfElement = Configuration::eLineElement;
    feature.isUsed = true;
    if(this->featureOrder.contains(position)){
        QMap<int, QList<InputFeature> >::iterator i = this->featureOrder.find(position);
        if(i != featureOrder.end()){
            QList<InputFeature> featurePosition = i.value();
            featurePosition.append(feature);
            this->featureOrder.insert(position, featurePosition);
        }
    }else{
        QList<InputFeature> featurePosition;
        featurePosition.append(feature);
        this->featureOrder.insert(position, featurePosition);
    }
}

/*!
 * \brief Function::removeLine
 * Remove the line with the specified id from the list of lines (if present)
 * \param id
 */
void Function::removeLine(int id){
    foreach(Line *l, this->lines){
        if(l->id == id){
            this->lines.removeOne(l);
            for(int i = 0; i < this->getNeededElements().length(); i++){
                if(this->featureOrder.contains(i)){
                    QMap<int, QList<InputFeature> >::iterator idx = this->featureOrder.find(i);
                    if(idx != this->featureOrder.end()){
                        QList<InputFeature> featurePosition = idx.value();
                        for(int j = 0; j < featurePosition.size(); j++){
                            if(featurePosition.at(j).id == id){
                                featurePosition.removeAt(j);
                                break;
                            }
                        }
                        this->featureOrder.insert(i, featurePosition);
                        break;
                    }
                }
            }
            break;
        }
    }
}

/*!
 * \brief Function::getLine
 * Returns the line with the specified id (if present) or NULL
 * \param id
 * \return
 */
Line* Function::getLine(int id){
    foreach(Line *l, this->lines){
        if(l->id == id){
            return l;
        }
    }
    return NULL;
}

/*!
 * \brief Function::getLines
 * Returns the complete list of lines
 * \return
 */
QList<Line*> Function::getLines(){
    return this->lines;
}

/*!
 * \brief Function::addPlane
 * \param p
 * \param position
 */
void Function::addPlane(Plane *p, int position){
    this->planes.append(p);
    InputFeature feature;
    feature.id = p->id;
    feature.typeOfElement = Configuration::ePlaneElement;
    feature.isUsed = true;
    if(this->featureOrder.contains(position)){
        QMap<int, QList<InputFeature> >::iterator i = this->featureOrder.find(position);
        if(i != this->featureOrder.end()){
            QList<InputFeature> featurePosition = i.value();
            featurePosition.append(feature);
            this->featureOrder.insert(position, featurePosition);
        }
    }else{
        QList<InputFeature> featurePosition;
        featurePosition.append(feature);
        this->featureOrder.insert(position, featurePosition);
    }
}

/*!
 * \brief removePlane
 * Remove the plane with the specified id from the list of planes (if present)
 * \param id
 */
void Function::removePlane(int id){
    foreach(Plane *p, this->planes){
        if(p->id == id){
            this->planes.removeOne(p);
            for(int i = 0; i < this->getNeededElements().length(); i++){
                if(this->featureOrder.contains(i)){
                    QMap<int, QList<InputFeature> >::iterator idx = this->featureOrder.find(i);
                    if(idx != this->featureOrder.end()){
                        QList<InputFeature> featurePosition = idx.value();
                        for(int j = 0; j < featurePosition.size(); j++){
                            if(featurePosition.at(j).id == id){
                                featurePosition.removeAt(j);
                                break;
                            }
                        }
                        this->featureOrder.insert(i, featurePosition);
                        break;
                    }
                }
            }
            break;
        }
    }
}

/*!
 * \brief getPlane
 * Returns the plane with the specified id (if present) or NULL
 * \param id
 * \return
 */
Plane* Function::getPlane(int id){
    foreach(Plane *p, this->planes){
        if(p->id == id){
            return p;
        }
    }
    return NULL;
}

/*!
 * \brief getPlanes
 * Returns the complete list of planes
 * \return
 */
QList<Plane*> Function::getPlanes(){
    return this->planes;
}

/*!
 * \brief Function::addSphere
 * \param s
 * \param position
 */
void Function::addSphere(Sphere *s, int position){
    this->spheres.append(s);
    InputFeature feature;
    feature.id = s->id;
    feature.typeOfElement = Configuration::eSphereElement;
    feature.isUsed = true;
    if(this->featureOrder.contains(position)){
        QMap<int, QList<InputFeature> >::iterator i = this->featureOrder.find(position);
        if(i != this->featureOrder.end()){
            QList<InputFeature> featurePosition = i.value();
            featurePosition.append(feature);
            this->featureOrder.insert(position, featurePosition);
        }
    }else{
        QList<InputFeature> featurePosition;
        featurePosition.append(feature);
        this->featureOrder.insert(position, featurePosition);
    }
}

/*!
 * \brief removeSphere
 * Remove the sphere with the specified id from the list of spheres (if present)
 * \param id
 */
void Function::removeSphere(int id){
    foreach(Sphere *s, this->spheres){
        if(s->id == id){
            this->spheres.removeOne(s);
            for(int i = 0; i < this->getNeededElements().length(); i++){
                if(this->featureOrder.contains(i)){
                    QMap<int, QList<InputFeature> >::iterator idx = this->featureOrder.find(i);
                    if(idx != this->featureOrder.end()){
                        QList<InputFeature> featurePosition = idx.value();
                        for(int j = 0; j < featurePosition.size(); j++){
                            if(featurePosition.at(j).id == id){
                                featurePosition.removeAt(j);
                                break;
                            }
                        }
                        this->featureOrder.insert(i, featurePosition);
                        break;
                    }
                }
            }
            break;
        }
    }
}

/*!
 * \brief getSphere
 * Returns the sphere with the specified id (if present) or NULL
 * \param id
 * \return
 */
Sphere* Function::getSphere(int id){
    foreach(Sphere *s, this->spheres){
        if(s->id == id){
            return s;
        }
    }
    return NULL;
}

/*!
 * \brief getSpheres
 * Returns the complete list of spheres
 * \return
 */
QList<Sphere*> Function::getSpheres(){
    return this->spheres;
}

/*!
 * \brief Function::addCircle
 * \param c
 * \param position
 */
void Function::addCircle(Circle *c, int position){
    this->circles.append(c);
    InputFeature feature;
    feature.id = c->id;
    feature.typeOfElement = Configuration::eCircleElement;
    feature.isUsed = true;
    if(this->featureOrder.contains(position)){
        QMap<int, QList<InputFeature> >::iterator i = this->featureOrder.find(position);
        if(i != this->featureOrder.end()){
            QList<InputFeature> featurePosition = i.value();
            featurePosition.append(feature);
            this->featureOrder.insert(position, featurePosition);
        }
    }else{
        QList<InputFeature> featurePosition;
        featurePosition.append(feature);
        this->featureOrder.insert(position, featurePosition);
    }
}

/*!
 * \brief Function::removeCircle
 * Remove the circle with the specified id from the list of circles (if present)
 * \param id
 */
void Function::removeCircle(int id){
    foreach(Circle *c, this->circles){
        if(c->id == id){
            this->circles.removeOne(c);
            for(int i = 0; i < this->getNeededElements().length(); i++){
                if(this->featureOrder.contains(i)){
                    QMap<int, QList<InputFeature> >::iterator idx = this->featureOrder.find(i);
                    if(idx != this->featureOrder.end()){
                        QList<InputFeature> featurePosition = idx.value();
                        for(int j = 0; j < featurePosition.size(); j++){
                            if(featurePosition.at(j).id == id){
                                featurePosition.removeAt(j);
                                break;
                            }
                        }
                        this->featureOrder.insert(i, featurePosition);
                        break;
                    }
                }
            }
            break;
        }
    }
}

/*!
 * \brief Function::getCircle
 * Returns the circle with the specified id (if present) or NULL
 * \param id
 * \return
 */
Circle* Function::getCircle(int id){
    foreach(Circle *c, this->circles){
        if(c->id == id){
            return c;
        }
    }
    return NULL;
}

/*!
 * \brief Function::getCircles
 * Returns the complete list of circles
 * \return
 */
QList<Circle*> Function::getCircles(){
    return this->circles;
}

/*!
 * \brief Function::addCone
 * \param c
 * \param position
 */
void Function::addCone(Cone *c, int position){
    this->cones.append(c);
    InputFeature feature;
    feature.id = c->id;
    feature.typeOfElement = Configuration::eConeElement;
    feature.isUsed = true;
    if(this->featureOrder.contains(position)){
        QMap<int, QList<InputFeature> >::iterator i = this->featureOrder.find(position);
        if(i != this->featureOrder.end()){
            QList<InputFeature> featurePosition = i.value();
            featurePosition.append(feature);
            this->featureOrder.insert(position, featurePosition);
        }
    }else{
        QList<InputFeature> featurePosition;
        featurePosition.append(feature);
        this->featureOrder.insert(position, featurePosition);
    }
}

/*!
 * \brief removeCone
 * Remove the cone with the specified id from the list of cones (if present)
 * \param id
 */
void Function::removeCone(int id){
    foreach(Cone *c, this->cones){
        if(c->id == id){
            this->cones.removeOne(c);
            for(int i = 0; i < this->getNeededElements().length(); i++){
                if(this->featureOrder.contains(i)){
                    QMap<int, QList<InputFeature> >::iterator idx = this->featureOrder.find(i);
                    if(idx != this->featureOrder.end()){
                        QList<InputFeature> featurePosition = idx.value();
                        for(int j = 0; j < featurePosition.size(); j++){
                            if(featurePosition.at(j).id == id){
                                featurePosition.removeAt(j);
                                break;
                            }
                        }
                        this->featureOrder.insert(i, featurePosition);
                        break;
                    }
                }
            }
            break;
        }
    }
}

/*!
 * \brief getCone
 * Returns the cone with the specified id (if present) or NULL
 * \param id
 * \return
 */
Cone* Function::getCone(int id){
    foreach(Cone *c, this->cones){
        if(c->id == id){
            return c;
        }
    }
    return NULL;
}

/*!
 * \brief getCones
 * Returns the complete list of cones
 * \return
 */
QList<Cone*> Function::getCones(){
    return this->cones;
}

/*!
 * \brief Function::addCylinder
 * \param c
 * \param position
 */
void Function::addCylinder(Cylinder *c, int position){
    this->cylinders.append(c);
    InputFeature feature;
    feature.id = c->id;
    feature.typeOfElement = Configuration::eCylinderElement;
    feature.isUsed = true;
    if(this->featureOrder.contains(position)){
        QMap<int, QList<InputFeature> >::iterator i = this->featureOrder.find(position);
        if(i != this->featureOrder.end()){
            QList<InputFeature> featurePosition = i.value();
            featurePosition.append(feature);
            this->featureOrder.insert(position, featurePosition);
        }
    }else{
        QList<InputFeature> featurePosition;
        featurePosition.append(feature);
        this->featureOrder.insert(position, featurePosition);
    }
}

/*!
 * \brief removeCylinder
 * Remove the cylinder with the specified id from the list of cylinders (if present)
 * \param id
 */
void Function::removeCylinder(int id){
    foreach(Cylinder *c, this->cylinders){
        if(c->id == id){
            this->cylinders.removeOne(c);
            for(int i = 0; i < this->getNeededElements().length(); i++){
                if(this->featureOrder.contains(i)){
                    QMap<int, QList<InputFeature> >::iterator idx = this->featureOrder.find(i);
                    if(idx != this->featureOrder.end()){
                        QList<InputFeature> featurePosition = idx.value();
                        for(int j = 0; j < featurePosition.size(); j++){
                            if(featurePosition.at(j).id == id){
                                featurePosition.removeAt(j);
                                break;
                            }
                        }
                        this->featureOrder.insert(i, featurePosition);
                        break;
                    }
                }
            }
            break;
        }
    }
}

/*!
 * \brief getCylinder
 * Returns the cylinder with the specified id (if present) or NULL
 * \param id
 * \return
 */
Cylinder* Function::getCylinder(int id){
    foreach(Cylinder *c, this->cylinders){
        if(c->id == id){
            return c;
        }
    }
    return NULL;
}

/*!
 * \brief getCylinders
 * Returns the complete list of cylinders
 * \return
 */
QList<Cylinder*> Function::getCylinders(){
    return this->cylinders;
}

/*!
 * \brief Function::addEllipsoid
 * \param e
 * \param position
 */
void Function::addEllipsoid(Ellipsoid *e, int position){
    this->ellipsoids.append(e);
    InputFeature feature;
    feature.id = e->id;
    feature.typeOfElement = Configuration::eEllipsoidElement;
    feature.isUsed = true;
    if(this->featureOrder.contains(position)){
        QMap<int, QList<InputFeature> >::iterator i = this->featureOrder.find(position);
        if(i != this->featureOrder.end()){
            QList<InputFeature> featurePosition = i.value();
            featurePosition.append(feature);
            this->featureOrder.insert(position, featurePosition);
        }
    }else{
        QList<InputFeature> featurePosition;
        featurePosition.append(feature);
        this->featureOrder.insert(position, featurePosition);
    }
}

/*!
 * \brief removeEllipsoid
 * Remove the ellipsoid with the specified id from the list of ellipsoids (if present)
 * \param id
 */
void Function::removeEllipsoid(int id){
    foreach(Ellipsoid *e, this->ellipsoids){
        if(e->id == id){
            this->ellipsoids.removeOne(e);
            for(int i = 0; i < this->getNeededElements().length(); i++){
                if(this->featureOrder.contains(i)){
                    QMap<int, QList<InputFeature> >::iterator idx = this->featureOrder.find(i);
                    if(idx != this->featureOrder.end()){
                        QList<InputFeature> featurePosition = idx.value();
                        for(int j = 0; j < featurePosition.size(); j++){
                            if(featurePosition.at(j).id == id){
                                featurePosition.removeAt(j);
                                break;
                            }
                        }
                        this->featureOrder.insert(i, featurePosition);
                        break;
                    }
                }
            }
            break;
        }
    }
}

/*!
 * \brief getEllipsoid
 * Returns the ellipsoid with the specified id (if present) or NULL
 * \param id
 * \return
 */
Ellipsoid* Function::getEllipsoid(int id){
    foreach(Ellipsoid *e, this->ellipsoids){
        if(e->id == id){
            return e;
        }
    }
    return NULL;
}

/*!
 * \brief getEllipsoids
 * Returns the complete list of ellipsoids
 * \return
 */
QList<Ellipsoid*> Function::getEllipsoids(){
    return this->ellipsoids;
}

/*!
 * \brief Function::addParaboloid
 * \param p
 * \param position
 */
void Function::addParaboloid(Paraboloid *p, int position){
    this->paraboloids.append(p);
    InputFeature feature;
    feature.id = p->id;
    feature.typeOfElement = Configuration::eParaboloidElement;
    feature.isUsed = true;
    if(this->featureOrder.contains(position)){
        QMap<int, QList<InputFeature> >::iterator i = this->featureOrder.find(position);
        if(i != this->featureOrder.end()){
            QList<InputFeature> featurePosition = i.value();
            featurePosition.append(feature);
            this->featureOrder.insert(position, featurePosition);
        }
    }else{
        QList<InputFeature> featurePosition;
        featurePosition.append(feature);
        this->featureOrder.insert(position, featurePosition);
    }
}

/*!
 * \brief removeParaboloid
 * Remove the paraboloid with the specified id from the list of paraboloids (if present)
 * \param id
 */
void Function::removeParaboloid(int id){
    foreach(Paraboloid *p, this->paraboloids){
        if(p->id == id){
            this->paraboloids.removeOne(p);
            for(int i = 0; i < this->getNeededElements().length(); i++){
                if(this->featureOrder.contains(i)){
                    QMap<int, QList<InputFeature> >::iterator idx = this->featureOrder.find(i);
                    if(idx != this->featureOrder.end()){
                        QList<InputFeature> featurePosition = idx.value();
                        for(int j = 0; j < featurePosition.size(); j++){
                            if(featurePosition.at(j).id == id){
                                featurePosition.removeAt(j);
                                break;
                            }
                        }
                        this->featureOrder.insert(i, featurePosition);
                        break;
                    }
                }
            }
            break;
        }
    }
}

/*!
 * \brief getParaboloid
 * Returns the paraboloid with the specified id (if present) or NULL
 * \param id
 * \return
 */
Paraboloid* Function::getParaboloid(int id){
    foreach(Paraboloid *p, this->paraboloids){
        if(p->id == id){
            return p;
        }
    }
    return NULL;
}

/*!
 * \brief getParaboloids
 * Returns the complete list of paraboloids
 * \return
 */
QList<Paraboloid*> Function::getParaboloids(){
    return this->paraboloids;
}

/*!
 * \brief Function::addHyperboloid
 * \param h
 * \param position
 */
void Function::addHyperboloid(Hyperboloid *h, int position){
    this->hyperboloids.append(h);
    InputFeature feature;
    feature.id = h->id;
    feature.typeOfElement = Configuration::eHyperboloidElement;
    feature.isUsed = true;
    if(this->featureOrder.contains(position)){
        QMap<int, QList<InputFeature> >::iterator i = this->featureOrder.find(position);
        if(i != this->featureOrder.end()){
            QList<InputFeature> featurePosition = i.value();
            featurePosition.append(feature);
            this->featureOrder.insert(position, featurePosition);
        }
    }else{
        QList<InputFeature> featurePosition;
        featurePosition.append(feature);
        this->featureOrder.insert(position, featurePosition);
    }
}

/*!
 * \brief removeHyperboloid
 * Remove the hyperboloid with the specified id from the list of hyperboloids (if present)
 * \param id
 */
void Function::removeHyperboloid(int id){
    foreach(Hyperboloid *h, this->hyperboloids){
        if(h->id == id){
            this->hyperboloids.removeOne(h);
            for(int i = 0; i < this->getNeededElements().length(); i++){
                if(this->featureOrder.contains(i)){
                    QMap<int, QList<InputFeature> >::iterator idx = this->featureOrder.find(i);
                    if(idx != this->featureOrder.end()){
                        QList<InputFeature> featurePosition = idx.value();
                        for(int j = 0; j < featurePosition.size(); j++){
                            if(featurePosition.at(j).id == id){
                                featurePosition.removeAt(j);
                                break;
                            }
                        }
                        this->featureOrder.insert(i, featurePosition);
                        break;
                    }
                }
            }
            break;
        }
    }
}

/*!
 * \brief getHyperboloid
 * Returns the hyperboloid with the specified id (if present) or NULL
 * \param id
 * \return
 */
Hyperboloid* Function::getHyperboloid(int id){
    foreach(Hyperboloid *h, this->hyperboloids){
        if(h->id == id){
            return h;
        }
    }
    return NULL;
}

/*!
 * \brief getHyperboloids
 * Returns the complete list of hyperboloids
 * \return
 */
QList<Hyperboloid*> Function::getHyperboloids(){
    return this->hyperboloids;
}

/*!
 * \brief Function::addNurb
 * \param n
 * \param position
 */
void Function::addNurb(Nurbs *n, int position){
    this->nurbs.append(n);
    InputFeature feature;
    feature.id = n->id;
    feature.typeOfElement = Configuration::eNurbsElement;
    feature.isUsed = true;
    if(this->featureOrder.contains(position)){
        QMap<int, QList<InputFeature> >::iterator i = this->featureOrder.find(position);
        if(i != this->featureOrder.end()){
            QList<InputFeature> featurePosition = i.value();
            featurePosition.append(feature);
            this->featureOrder.insert(position, featurePosition);
        }
    }else{
        QList<InputFeature> featurePosition;
        featurePosition.append(feature);
        this->featureOrder.insert(position, featurePosition);
    }
}

/*!
 * \brief removeNurb
 * Remove the nurb with the specified id from the list of nurbs (if present)
 * \param id
 */
void Function::removeNurb(int id){
    foreach(Nurbs *n, this->nurbs){
        if(n->id == id){
            this->nurbs.removeOne(n);
            for(int i = 0; i < this->getNeededElements().length(); i++){
                if(this->featureOrder.contains(i)){
                    QMap<int, QList<InputFeature> >::iterator idx = this->featureOrder.find(i);
                    if(idx != this->featureOrder.end()){
                        QList<InputFeature> featurePosition = idx.value();
                        for(int j = 0; j < featurePosition.size(); j++){
                            if(featurePosition.at(j).id == id){
                                featurePosition.removeAt(j);
                                break;
                            }
                        }
                        this->featureOrder.insert(i, featurePosition);
                        break;
                    }
                }
            }
            break;
        }
    }
}

/*!
 * \brief getNurb
 * Returns the nurb with the specified id (if present) or NULL
 * \param id
 * \return
 */
Nurbs* Function::getNurb(int id){
    foreach(Nurbs *n, this->nurbs){
        if(n->id == id){
            return n;
        }
    }
    return NULL;
}

/*!
 * \brief getNurbs
 * Returns the complete list of nurbs
 * \return
 */
QList<Nurbs*> Function::getNurbs(){
    return this->nurbs;
}

/*!
 * \brief Function::addPointCloud
 * \param p
 * \param position
 */
void Function::addPointCloud(PointCloud *p, int position){
    this->pointClouds.append(p);
    InputFeature feature;
    feature.id = p->id;
    feature.typeOfElement = Configuration::ePointCloudElement;
    feature.isUsed = true;
    if(this->featureOrder.contains(position)){
        QMap<int, QList<InputFeature> >::iterator i = this->featureOrder.find(position);
        if(i != this->featureOrder.end()){
            QList<InputFeature> featurePosition = i.value();
            featurePosition.append(feature);
            this->featureOrder.insert(position, featurePosition);
        }
    }else{
        QList<InputFeature> featurePosition;
        featurePosition.append(feature);
        this->featureOrder.insert(position, featurePosition);
    }
}

/*!
 * \brief removePointCloud
 * Remove the point cloud with the specified id from the list of point clouds (if present)
 * \param id
 */
void Function::removePointCloud(int id){
    foreach(PointCloud *p, this->pointClouds){
        if(p->id == id){
            this->pointClouds.removeOne(p);
            for(int i = 0; i < this->getNeededElements().length(); i++){
                if(this->featureOrder.contains(i)){
                    QMap<int, QList<InputFeature> >::iterator idx = this->featureOrder.find(i);
                    if(idx != this->featureOrder.end()){
                        QList<InputFeature> featurePosition = idx.value();
                        for(int j = 0; j < featurePosition.size(); j++){
                            if(featurePosition.at(j).id == id){
                                featurePosition.removeAt(j);
                                break;
                            }
                        }
                        this->featureOrder.insert(i, featurePosition);
                        break;
                    }
                }
            }
            break;
        }
    }
}

/*!
 * \brief getPointCloud
 * Returns the point cloud with the specified id (if present) or NULL
 * \param id
 * \return
 */
PointCloud* Function::getPointCloud(int id){
    foreach(PointCloud *p, this->pointClouds){
        if(p->id == id){
            return p;
        }
    }
    return NULL;
}

/*!
 * \brief getPointClouds
 * Returns the complete list of point clouds
 * \return
 */
QList<PointCloud*> Function::getPointClouds(){
    return this->pointClouds;
}

/*!
 * \brief addScalarEntityDistance
 * \param sed
 * \param position
 */
void Function::addScalarEntityDistance(ScalarEntityDistance *sed, int position){
    this->scalarEntityDistances.append(sed);
    InputFeature feature;
    feature.id = sed->id;
    feature.typeOfElement = Configuration::eScalarEntityDistanceElement;
    feature.isUsed = true;
    if(this->featureOrder.contains(position)){
        QMap<int, QList<InputFeature> >::iterator i = this->featureOrder.find(position);
        if(i != this->featureOrder.end()){
            QList<InputFeature> featurePosition = i.value();
            featurePosition.append(feature);
            this->featureOrder.insert(position, featurePosition);
        }
    }else{
        QList<InputFeature> featurePosition;
        featurePosition.append(feature);
        this->featureOrder.insert(position, featurePosition);
    }
}

/*!
 * \brief removeScalarEntityDistance
 * Remove the distance with the specified id from the list of distances (if present)
 * \param id
 */
void Function::removeScalarEntityDistance(int id){
    foreach(ScalarEntityDistance *sed, this->scalarEntityDistances){
        if(sed->id == id){
            this->scalarEntityDistances.removeOne(sed);
            for(int i = 0; i < this->getNeededElements().length(); i++){
                if(this->featureOrder.contains(i)){
                    QMap<int, QList<InputFeature> >::iterator idx = this->featureOrder.find(i);
                    if(idx != this->featureOrder.end()){
                        QList<InputFeature> featurePosition = idx.value();
                        for(int j = 0; j < featurePosition.size(); j++){
                            if(featurePosition.at(j).id == id){
                                featurePosition.removeAt(j);
                                break;
                            }
                        }
                        this->featureOrder.insert(i, featurePosition);
                        break;
                    }
                }
            }
            break;
        }
    }
}

/*!
 * \brief getScalarEntityDistance
 * Returns the distance with the specified id (if present) or NULL
 * \param id
 * \return
 */
ScalarEntityDistance* Function::getScalarEntityDistance(int id){
    foreach(ScalarEntityDistance *sed, this->scalarEntityDistances){
        if(sed->id == id){
            return sed;
        }
    }
    return NULL;
}

/*!
 * \brief getScalarEntityDistances
 * Returns the complete list of distances
 * \return
 */
QList<ScalarEntityDistance*> Function::getScalarEntityDistances(){
    return this->scalarEntityDistances;
}

/*!
 * \brief Function::addScalarEntityAngle
 * \param sea
 * \param position
 */
void Function::addScalarEntityAngle(ScalarEntityAngle *sea, int position){
    this->scalarEntityAngles.append(sea);
    InputFeature feature;
    feature.id = sea->id;
    feature.typeOfElement = Configuration::eScalarEntityAngleElement;
    feature.isUsed = true;
    if(this->featureOrder.contains(position)){
        QMap<int, QList<InputFeature> >::iterator i = this->featureOrder.find(position);
        if(i != this->featureOrder.end()){
            QList<InputFeature> featurePosition = i.value();
            featurePosition.append(feature);
            this->featureOrder.insert(position, featurePosition);
        }
    }else{
        QList<InputFeature> featurePosition;
        featurePosition.append(feature);
        this->featureOrder.insert(position, featurePosition);
    }
}

/*!
 * \brief removeScalarEntityAngle
 * Remove the angle with the specified id from the list of angles (if present)
 * \param id
 */
void Function::removeScalarEntityAngle(int id){
    foreach(ScalarEntityAngle *sea, this->scalarEntityAngles){
        if(sea->id == id){
            this->scalarEntityAngles.removeOne(sea);
            for(int i = 0; i < this->getNeededElements().length(); i++){
                if(this->featureOrder.contains(i)){
                    QMap<int, QList<InputFeature> >::iterator idx = this->featureOrder.find(i);
                    if(idx != this->featureOrder.end()){
                        QList<InputFeature> featurePosition = idx.value();
                        for(int j = 0; j < featurePosition.size(); j++){
                            if(featurePosition.at(j).id == id){
                                featurePosition.removeAt(j);
                                break;
                            }
                        }
                        this->featureOrder.insert(i, featurePosition);
                        break;
                    }
                }
            }
            break;
        }
    }
}

/*!
 * \brief getScalarEntityAngle
 * Returns the angle with the specified id (if present) or NULL
 * \param id
 * \return
 */
ScalarEntityAngle* Function::getScalarEntityAngle(int id){
    foreach(ScalarEntityAngle *sea, this->scalarEntityAngles){
        if(sea->id == id){
            return sea;
        }
    }
    return NULL;
}

/*!
 * \brief getScalarEntityAngles
 * Returns the complete list of angles
 * \return
 */
QList<ScalarEntityAngle*> Function::getScalarEntityAngles(){
    return this->scalarEntityAngles;
}

/*!
 * \brief addObservation
 * \param o
 * \param position
 */
void Function::addObservation(Observation *o, int position){
    this->observations.append(o);
    InputFeature feature;
    feature.id = o->id;
    feature.typeOfElement = Configuration::eObservationElement;
    feature.isUsed = true;
    if(this->featureOrder.contains(position)){
        QMap<int, QList<InputFeature> >::iterator i = this->featureOrder.find(position);
        if(i != this->featureOrder.end()){
            QList<InputFeature> featurePosition = i.value();
            featurePosition.append(feature);
            this->featureOrder.insert(position, featurePosition);
        }
    }else{
        QList<InputFeature> featurePosition;
        featurePosition.append(feature);
        this->featureOrder.insert(position, featurePosition);
    }
}

/*!
 * \brief removeObservation
 * Remove the observation with the specified id from the list of observations (if present)
 * \param id
 */
void Function::removeObservation(int id){
    foreach(Observation *o, this->observations){
        if(o->id == id){
            this->observations.removeOne(o);
            for(int i = 0; i < this->getNeededElements().length(); i++){
                if(this->featureOrder.contains(i)){
                    QMap<int, QList<InputFeature> >::iterator idx = this->featureOrder.find(i);
                    if(idx != this->featureOrder.end()){
                        QList<InputFeature> featurePosition = idx.value();
                        for(int j = 0; j < featurePosition.size(); j++){
                            if(featurePosition.at(j).id == id){
                                featurePosition.removeAt(j);
                                break;
                            }
                        }
                        this->featureOrder.insert(i, featurePosition);
                        break;
                    }
                }
            }
            break;
        }
    }
}

/*!
 * \brief getObservation
 * Returns the observation with the specified id (if present) or NULL
 * \param id
 * \return
 */
Observation* Function::getObservation(int id){
    foreach(Observation *o, this->observations){
        if(o->id == id){
            return o;
        }
    }
    return NULL;
}

/*!
 * \brief getObservations
 * Returns the complete list of observations
 * \return
 */
QList<Observation*> Function::getObservations(){
    return this->observations;
}

/*!
 * \brief addReadingPolar
 * \param r
 * \param position
 */
void Function::addReadingPolar(Reading *r, int position){
    this->polarReadings.append(r);
    InputFeature feature;
    feature.id = r->id;
    feature.typeOfElement = Configuration::eReadingPolarElement;
    feature.isUsed = true;
    if(this->featureOrder.contains(position)){
        QMap<int, QList<InputFeature> >::iterator i = this->featureOrder.find(position);
        if(i != this->featureOrder.end()){
            QList<InputFeature> featurePosition = i.value();
            featurePosition.append(feature);
            this->featureOrder.insert(position, featurePosition);
        }
    }else{
        QList<InputFeature> featurePosition;
        featurePosition.append(feature);
        this->featureOrder.insert(position, featurePosition);
    }
}

/*!
 * \brief removeReadingPolar
 * Remove the polar reading with the specified id from the list of polar readings (if present)
 * \param id
 */
void Function::removeReadingPolar(int id){
    foreach(Reading *r, this->polarReadings){
        if(r->id == id){
            this->polarReadings.removeOne(r);
            for(int i = 0; i < this->getNeededElements().length(); i++){
                if(this->featureOrder.contains(i)){
                    QMap<int, QList<InputFeature> >::iterator idx = this->featureOrder.find(i);
                    if(idx != this->featureOrder.end()){
                        QList<InputFeature> featurePosition = idx.value();
                        for(int j = 0; j < featurePosition.size(); j++){
                            if(featurePosition.at(j).id == id){
                                featurePosition.removeAt(j);
                                break;
                            }
                        }
                        this->featureOrder.insert(i, featurePosition);
                        break;
                    }
                }
            }
            break;
        }
    }
}

/*!
 * \brief getReadingPolar
 * Returns the polar reading with the specified id (if present) or NULL
 * \param id
 * \return
 */
Reading* Function::getReadingPolar(int id){
    foreach(Reading *r, this->polarReadings){
        if(r->id == id){
            return r;
        }
    }
    return NULL;
}

/*!
 * \brief getPolarReadings
 * Returns the complete list of polar readings
 * \return
 */
QList<Reading*> Function::getPolarReadings(){
    return this->polarReadings;
}

/*!
 * \brief addReadingDistance
 * \param r
 * \param position
 */
void Function::addReadingDistance(Reading *r, int position){
    this->distanceReadings.append(r);
    InputFeature feature;
    feature.id = r->id;
    feature.typeOfElement = Configuration::eReadingDistanceElement;
    feature.isUsed = true;
    if(this->featureOrder.contains(position)){
        QMap<int, QList<InputFeature> >::iterator i = this->featureOrder.find(position);
        if(i != this->featureOrder.end()){
            QList<InputFeature> featurePosition = i.value();
            featurePosition.append(feature);
            this->featureOrder.insert(position, featurePosition);
        }
    }else{
        QList<InputFeature> featurePosition;
        featurePosition.append(feature);
        this->featureOrder.insert(position, featurePosition);
    }
}

/*!
 * \brief removeReadingDistance
 * Remove the distance reading with the specified id from the list of distance readings (if present)
 * \param id
 */
void Function::removeReadingDistance(int id){
    foreach(Reading *r, this->distanceReadings){
        if(r->id == id){
            this->distanceReadings.removeOne(r);
            for(int i = 0; i < this->getNeededElements().length(); i++){
                if(this->featureOrder.contains(i)){
                    QMap<int, QList<InputFeature> >::iterator idx = this->featureOrder.find(i);
                    if(idx != this->featureOrder.end()){
                        QList<InputFeature> featurePosition = idx.value();
                        for(int j = 0; j < featurePosition.size(); j++){
                            if(featurePosition.at(j).id == id){
                                featurePosition.removeAt(j);
                                break;
                            }
                        }
                        this->featureOrder.insert(i, featurePosition);
                        break;
                    }
                }
            }
            break;
        }
    }
}

/*!
 * \brief getReadingDistance
 * Returns the distance reading with the specified id (if present) or NULL
 * \param id
 * \return
 */
Reading* Function::getReadingDistance(int id){
    foreach(Reading *r, this->distanceReadings){
        if(r->id == id){
            return r;
        }
    }
    return NULL;
}

/*!
 * \brief getDistanceReadings
 * Returns the complete list of distances readings
 * \return
 */
QList<Reading*> Function::getDistanceReadings(){
    return this->distanceReadings;
}

/*!
 * \brief addReadingDirection
 * \param r
 * \param position
 */
void Function::addReadingDirection(Reading *r, int position){
    this->directionReadings.append(r);
    InputFeature feature;
    feature.id = r->id;
    feature.typeOfElement = Configuration::eReadingDirectionElement;
    feature.isUsed = true;
    if(this->featureOrder.contains(position)){
        QMap<int, QList<InputFeature> >::iterator i = this->featureOrder.find(position);
        if(i != this->featureOrder.end()){
            QList<InputFeature> featurePosition = i.value();
            featurePosition.append(feature);
            this->featureOrder.insert(position, featurePosition);
        }
    }else{
        QList<InputFeature> featurePosition;
        featurePosition.append(feature);
        this->featureOrder.insert(position, featurePosition);
    }
}

/*!
 * \brief removeReadingDirection
 * Remove the direction reading with the specified id from the list of direction readings (if present)
 * \param id
 */
void Function::removeReadingDirection(int id){
    foreach(Reading *r, this->directionReadings){
        if(r->id == id){
            this->directionReadings.removeOne(r);
            for(int i = 0; i < this->getNeededElements().length(); i++){
                if(this->featureOrder.contains(i)){
                    QMap<int, QList<InputFeature> >::iterator idx = this->featureOrder.find(i);
                    if(idx != this->featureOrder.end()){
                        QList<InputFeature> featurePosition = idx.value();
                        for(int j = 0; j < featurePosition.size(); j++){
                            if(featurePosition.at(j).id == id){
                                featurePosition.removeAt(j);
                                break;
                            }
                        }
                        this->featureOrder.insert(i, featurePosition);
                        break;
                    }
                }
            }
            break;
        }
    }
}

/*!
 * \brief getReadingDirection
 * Returns the direction reading with the specified id (if present) or NULL
 * \param id
 * \return
 */
Reading* Function::getReadingDirection(int id){
    foreach(Reading *r, this->directionReadings){
        if(r->id == id){
            return r;
        }
    }
    return NULL;
}

/*!
 * \brief getDirectionReadings
 * Returns the complete list of direction readings
 * \return
 */
QList<Reading*> Function::getDirectionReadings(){
    return this->directionReadings;
}

/*!
 * \brief addReadingCartesian
 * \param r
 * \param position
 */
void Function::addReadingCartesian(Reading *r, int position){
    this->cartesianReadings.append(r);
    InputFeature feature;
    feature.id = r->id;
    feature.typeOfElement = Configuration::eReadingCartesianElement;
    feature.isUsed = true;
    if(this->featureOrder.contains(position)){
        QMap<int, QList<InputFeature> >::iterator i = this->featureOrder.find(position);
        if(i != this->featureOrder.end()){
            QList<InputFeature> featurePosition = i.value();
            featurePosition.append(feature);
            this->featureOrder.insert(position, featurePosition);
        }
    }else{
        QList<InputFeature> featurePosition;
        featurePosition.append(feature);
        this->featureOrder.insert(position, featurePosition);
    }
}

/*!
 * \brief removeReadingCartesian
 * Remove the cartesian reading with the specified id from the list of cartesian readings (if present)
 * \param id
 */
void Function::removeReadingCartesian(int id){
    foreach(Reading *r, this->cartesianReadings){
        if(r->id == id){
            this->cartesianReadings.removeOne(r);
            for(int i = 0; i < this->getNeededElements().length(); i++){
                if(this->featureOrder.contains(i)){
                    QMap<int, QList<InputFeature> >::iterator idx = this->featureOrder.find(i);
                    if(idx != this->featureOrder.end()){
                        QList<InputFeature> featurePosition = idx.value();
                        for(int j = 0; j < featurePosition.size(); j++){
                            if(featurePosition.at(j).id == id){
                                featurePosition.removeAt(j);
                                break;
                            }
                        }
                        this->featureOrder.insert(i, featurePosition);
                        break;
                    }
                }
            }
            break;
        }
    }
}

/*!
 * \brief getReadingCartesian
 * Returns the cartesian reading with the specified id (if present) or NULL
 * \param id
 * \return
 */
Reading* Function::getReadingCartesian(int id){
    foreach(Reading *r, this->cartesianReadings){
        if(r->id == id){
            return r;
        }
    }
    return NULL;
}

/*!
 * \brief getCartesianReadings
 * Returns the complete list of cartesian readings
 * \return
 */
QList<Reading*> Function::getCartesianReadings(){
    return this->cartesianReadings;
}

/*!
 * \brief clear
 * Reset function
 */
void Function::clear(){
    //clear lists with used elements
    this->stations.clear();
    this->trafoParams.clear();
    this->coordSystems.clear();
    this->points.clear();
    this->lines.clear();
    this->planes.clear();
    this->spheres.clear();
    this->observations.clear();
    this->scalarEntityAngles.clear();
    this->scalarEntityDistances.clear();
    this->polarReadings.clear();
    this->cartesianReadings.clear();
    this->directionReadings.clear();
    this->distanceReadings.clear();
    //clear map with feature order
    this->featureOrder.clear();
    //delete statistic
    this->myStatistic.isValid = false;
}

/*!
 * \brief Function::clearResults
 * Clear statistic of this function
 */
void Function::clearResults(){
    //clear statistic
    Statistic emptyStatistic;
    this->myStatistic = emptyStatistic;
    //set all feature to not be used
    QMap<int, QList<InputFeature> > newFeatureOrder;
    QMapIterator<int, QList<InputFeature> > iterate(this->featureOrder);
    int k = 0;
    while(iterate.hasNext()){
        iterate.next();
        QList<InputFeature> newValue;
        QList<InputFeature> value = iterate.value();
        for(int i = 0; i < value.size(); i++){
            InputFeature f = value.at(i);
            f.isUsed = false;
            newValue.append(f);
        }
        newFeatureOrder.insert(k, newValue);
        k++;
    }
    this->featureOrder = newFeatureOrder;
}

/*!
 * \brief GaussFit::setUseState
 * Set state of feature
 * \param id
 * \param state
 */
void Function::setUseState(int id, bool state){
    for(int i = 0; i < this->getNeededElements().size(); i++){
        if(this->featureOrder.contains(i)){
            QMap<int, QList<InputFeature> >::iterator idx = this->featureOrder.find(i);
            if(idx != this->featureOrder.end()){
                QList<InputFeature> featurePosition = idx.value();
                for(int j = 0; j < featurePosition.size(); j++){
                    if(featurePosition.at(j).id == id){
                        InputFeature feature;
                        feature.id = id;
                        feature.isUsed = state;
                        feature.typeOfElement = featurePosition.at(j).typeOfElement;
                        featurePosition.removeAt(j);
                        featurePosition.insert(j, feature);
                        break;
                    }
                }
                this->featureOrder.insert(i, featurePosition);
                break;
            }
        }
    }
}

/*!
 * \brief Function::getOiEmitter
 * \return
 */
OiEmitter& Function::getOiEmitter(){
    return this->myEmitter;
}

/*!
 * \brief Function::writeToConsole
 * Write a specified message to the console
 * \param message
 */
void Function::writeToConsole(QString message){
    myEmitter.sendString(message);
}
