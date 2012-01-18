#ifndef Events_MouseEvent_h
#define Events_MouseEvent_h

#include "Event.h"


namespace Events {

class MouseEvent : public Event {

 public:
    int localX;
    int localY;
    bool ctrlKey;
    bool altKey;
};

} /* End of namespace Events */

#endif // Events_MouseEvent_h
