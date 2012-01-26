#include <iostream>
#include <Devices/Device.h>

namespace Devices {
    
    char *Device::getData() throw (int) {
        // unimplemented
        throw -1;        
    }
    
    int Device::read (char *data, int size, int count) throw (int) {
        throw -1;
    }
    
    int Device::write (char *data, int size, int count) throw (int) {
        throw -1;
        
    }
    
    double Device::getSensorValue (int valueID) throw (int) {
        throw -1;
    }
    
    void Double::update() {
        throw -1;
    }
    
    
    
    
}