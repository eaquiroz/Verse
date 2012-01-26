#ifndef _OrientationSensor_h
#define _OrientationSensor_h

namespace Devices {
    class OrientationSensor : public Device {
        
    public:
        
        /* Read the sensor values with the valueID (
         used for X, Y, Z, or Pitch, Roll, Yaw */
        double getSensorValue (int valueID) throw (int);
        
        /* update the values from the sensor */
        void update ();
        
    private:
        
        /* update frequency */
        double frequency;
                
    }
}

#endif
