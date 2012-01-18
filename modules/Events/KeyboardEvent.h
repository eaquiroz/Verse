#ifndef Events_KeyboardEvent_h
#define Events_KeyboardEvent_h

#include "Event.h"


namespace Events {

class KeyboardEvent : public Event {

 public:
    bool altKey;
    char charCode;
    bool commandKey;
    bool ctrlKey;
    bool shiftKey;
};

} /* End of namespace Events */

#endif // Events_KeyboardEvent_h
