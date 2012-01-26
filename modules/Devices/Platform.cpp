#include "Platform.h"

namespace Devices {

    Platform::Platform(){
        Cam1 = new cv::VideoCapture(0);
        Cam2 = new cv::VideoCapture(1);
    }
    
    cv::Mat Platform::getFrame(int cam){
        cv::Mat img;
        if(cam==0){
            if (Cam1->grab()){
                    Cam1->retrieve(img, 0);
            }
        }else{
            if (Cam2->grab()){
                    Cam2->retrieve(img, 0);
            }
        }
        
        return img;
    }
} /* End of namespace Devices */
