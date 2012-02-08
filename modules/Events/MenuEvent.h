#ifndef Events_MenuEvent_h
#define Events_MenuEvent_h

#include "Event.h"
#include <UI/MenuItemData.h>
#include <string>
#include <vector>

namespace Events {

class MenuEvent : public Event {

 public:
    MenuEvent();
    std::vector<UI::MenuItemData> data;
    std::string action;
    
    
public:
    static const std::string MENU_ITEM_ACTION;
    
};

} /* End of namespace Events */

#endif