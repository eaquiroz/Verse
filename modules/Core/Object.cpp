#include "Object.h"

namespace Core {

int Object::idCount=0;

Object::Object()
{
        id=Object::getId();    
}

std::string Object::toString()
{
        std::stringstream result; 
        result << "[" << id << "]" << type;
        return result.str();
}

} /* End of namespace Core */
