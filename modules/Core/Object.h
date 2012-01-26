#ifndef Core_Object_h
#define Core_Object_h

#include <string>
#include <iostream>
#include <sstream>

namespace Core {

class Object {

 public:
    Object();
    virtual std::string toString();

 public:
    bool enabled;
    std::string type;
    int id;
    
private:
    static int idCount;
    static int getId(){Object::idCount++; return Object::idCount;};
};

} /* End of namespace Core */

#endif // Core_Object_h
