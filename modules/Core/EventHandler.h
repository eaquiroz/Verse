#ifndef Core_EventHandler_h
#define Core_EventHandler_h

#include <string.h>
#include <vector>

#include "Object.h"
#include "Callback.h"
#include <Events/Event.h>

namespace Core {

class EventCallback{
	public:
		Callback *callback;
		std::string type;
		Object *target;	
};

class EventHandler : public Object {

 public:
 	static EventHandler* Instance();
    
    std::vector<EventCallback> eventList;
	void dispatchEvent(Events::Event event);
	void registerEvent(Object *target, std::string eventType, Callback *callback);
 
 protected:
 	EventHandler();
 	EventHandler(const EventHandler &);
 	EventHandler &operator= (const EventHandler &);
 	
 private:
 	static EventHandler* pinstance;
 	
};

} /* End of namespace Core */

#endif // Core_EventHandler_h
