#ifndef Devices_Device_h
#define Devices_Device_h

#include <Core/EventDispatcher.h>

namespace Devices {

class Platform : public Core::EventDispatcher {

 public:


 public:
    int resolutionX;
    int resolutionY;
};

} /* End of namespace Devices */

#endif // Devices_Device_h
