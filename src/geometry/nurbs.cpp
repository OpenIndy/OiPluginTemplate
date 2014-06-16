#include "nurbs.h"

#include "function.h"

Nurbs::Nurbs(bool isNominal, QObject *parent) : Geometry(isNominal, parent)
{
    this->id = Configuration::generateID();
    this->myNominalCoordSys = NULL;
    this->isSolved = false;
    this->isUpdated = false;
    this->isDrawn = true;
}

/*!
 * \brief Nurbs::Nurbs
 * \param copy
 */
Nurbs::Nurbs(const Nurbs &copy) : Geometry(copy.isNominal){
    this->id = copy.id;
    this->name = copy.name;
    this->isSolved = copy.isSolved;
}

void Nurbs::recalc(){

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

bool Nurbs::toOpenIndyXML(QXmlStreamWriter &stream){

    return false;
}

ElementDependencies Nurbs::fromOpenIndyXML(QXmlStreamReader &xml){

    ElementDependencies dependencies;

    return dependencies;
}
