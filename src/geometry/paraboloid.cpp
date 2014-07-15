#include "paraboloid.h"

#include "function.h"

Paraboloid::Paraboloid(bool isNominal, QObject *parent) : Geometry(isNominal, parent)
{
    this->id = Configuration::generateID();
    this->myNominalCoordSys = NULL;
    this->isSolved = false;
    this->isUpdated = false;
    this->isDrawn = true;
}

/*!
 * \brief Paraboloid::Paraboloid
 * \param copy
 */
Paraboloid::Paraboloid(const Paraboloid &copy) : Geometry(copy.isNominal){
    this->id = copy.id;
    this->name = copy.name;
    this->isSolved = copy.isSolved;
}

void Paraboloid::recalc(){

    if(this->functionList.size() > 0){

        bool solved = true;
        foreach(Function *f, this->functionList){

            //execute the function if it exists and if the last function was executed successfully
            if(f != NULL && solved == true){
                solved = f->exec(*this);
            }

        }
        this->setIsSolved(solved);

    }else if(this->isNominal == false){

        this->setIsSolved(false);

    }

}

bool Paraboloid::toOpenIndyXML(QXmlStreamWriter &stream){

    return false;
}

ElementDependencies Paraboloid::fromOpenIndyXML(QXmlStreamReader &xml){
    ElementDependencies dependencies;

    return dependencies;
}

bool Paraboloid::saveSimulationData()
{
    return false;
}
