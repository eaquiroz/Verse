#include "EventDispatcher.h"

namespace Core {

void EventDispatcher::addEventListener(std::string eventType,Callback *callback)
{
	EventHandler *eh=EventHandler::Instance();
	eh->registerEvent(eventType, callback);
}

void EventDispatcher::removeEventListener(std::string eventType,Callback *callback)
{
	EventHandler *eh=EventHandler::Instance();
}

void EventDispatcher::dispatchEvent(Events::Event event)
{
	EventHandler *eh=EventHandler::Instance();
	eh->dispatchEvent(event);
}

} /* End of namespace Core */
