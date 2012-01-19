#ifndef Events_Event_h
#define Events_Event_h

#include <string>

#include <Core/Object.h>

namespace Events {

class Event : public Core::Object {
	
 public:
	Event();
    Object *target;
    std::string type;

};

} /* End of namespace Events */

#endif // Events_Event_h
