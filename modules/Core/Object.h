#ifndef Core_Object_h
#define Core_Object_h

#include <string>

namespace Core {

class Object {

 public:

    virtual std::string toString();

 public:
    bool enabled;
    std::string type;
};

} /* End of namespace Core */

#endif // Core_Object_h
