#ifndef Devices_Device_h
#define Devices_Device_h

#include <Core/EventDispatcher.h>

namespace Devices {

class Platform : public Core::EventDispatcher {

 public:
    int resolutionX;
    int resolutionY;
    const std::string getGLVersion() {return GLversion;}

    Device *getDevice (int id);
    
 private:
    std::string GLVersion;
    std::vector<Device *> devices; 
    
};

} /* End of namespace Devices */

#endif // Devices_Device_h
