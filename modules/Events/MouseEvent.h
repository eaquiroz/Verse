#ifndef Events_MouseEvent_h
#define Events_MouseEvent_h

#include "Event.h"
#include <string>

namespace Events {

class MouseEvent : public Event {

 public:
    int x;
    int y;
    bool ctrlKey;
    bool altKey;
    int button;
    int state;
    
    
public:
    static const std::string MOUSE_DOWN;
    static const std::string MOUSE_UP;
    
    static const std::string MOUSE_OVER;
    
    static const std::string RIGHT_MOUSE_DOWN;
    static const std::string RIGHT_MOUSE_UP;
    
    static const std::string MIDDLE_MOUSE_DOWN;
    static const std::string MIDDLE_MOUSE_UP;
    
    
};

} /* End of namespace Events */

#endif // Events_MouseEvent_h
