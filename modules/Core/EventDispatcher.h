#ifndef Core_EventDispatcher_h
#define Core_EventDispatcher_h

#include <string>

#include "Object.h"
#include "EventHandler.h"
#include "Callback.h"
#include <Events/Event.h>


namespace Core {

class EventDispatcher : public Object {

 public:

    void addEventListener(std::string eventType,Callback *callback);

    void removeEventListener(std::string eventType,Callback *callback);

    void dispatchEvent(Events::Event event);
};

} /* End of namespace Core */

#endif // Core_EventDispatcher_h
