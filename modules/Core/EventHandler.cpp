#include "EventHandler.h"

namespace Core {

EventHandler* EventHandler::pinstance=0;
EventHandler* EventHandler::Instance()
{
	if (pinstance == 0 )
	{
			pinstance = new EventHandler;
	}
	return pinstance;	
}

EventHandler::EventHandler()
{
	//Init Event Handler.		
}

void EventHandler::dispatchEvent(Events::Event *event)
{
	//For each event registered on list, check the event and launch 
	//callback function.
	for(int i=0; i< eventList.size(); i++){
		EventCallback ec=eventList[i];
		if(strcmp(ec.type.c_str(), event->type.c_str())==0){
			if(event->target==0 || (event->target==ec.target))
			{
				Callback *callback=ec.callback;
				callback->Execute(event);
			}
		}	
	}
}

void EventHandler::registerEvent(Object *target, std::string eventType, Callback *callback)
{
	//Add to event list the callback and type
	EventCallback ec;
	ec.callback=callback;
	ec.type=eventType;
	ec.target=target;
	eventList.push_back(ec);
}

} /* End of namespace Core */
