#ifndef Devices_Device_h
#define Devices_Device_h

#include <Core/EventDispatcher.h>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>


namespace Devices {

class Platform : public Core::EventDispatcher {

 public:
     Platform();
     cv::Mat getFrame(int cam=0);

 public:
    int resolutionX;
    int resolutionY;
    
    //OpenCV capture Inputs
    cv::VideoCapture* Cam1;
    cv::VideoCapture* Cam2;
};

} /* End of namespace Devices */

#endif // Devices_Device_h
