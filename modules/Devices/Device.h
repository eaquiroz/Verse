
#ifndef _Device_h
#define _Device_h

namespace Devices {
    
class Device {

 public:
    std::string name;
    
    /* There are 3 types of Devices supported: sensors (orientation, location), camera, and serial devices */
    
    /* This is for camera devices, returning the image as char */
    virtual char* getData () throw (int);
    
    /* This is for serial devices. read(..) read from the serial stream to the data char pointer, each block of data is of (size) size and 
        there are (count) block of data to read. Similar to write, char* data
        contains the data to write out to serial stream */
    virtual int read (char *data, int size, int count) throw (int);
    virtual int write (char *data, int size, int count) throw (int);
    
    /* This is for orientation and location sensors */
    virtual double getSensorValue (int valueID) throw (int);
    
    /* Update the values of Sensors for Orientation/Location sensors
     or update the frames for the camera */
    virtual void update ();
        
}
    
}



#endif
