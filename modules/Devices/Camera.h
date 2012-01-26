#ifndef _Camera_h
#define _Camera_h

namespace Devices {
    
    class Camera : public Device {
        
        
    public: 
        
        /* Constructor, the path of the image
        Camera (std::string path)
        
        /* get the image from the camera */
        char *getData () throw (int);
        
        /* Different image format */
        enum ImageFormat {
          RGB,
          RGBA,
          BGR,
          BGRA,
          YUYV411,
          YUYV422,
          MONO        
            
            
        };
        
        ImageFormat getImageFormat () { return format;}
        
    private:
        std::string cameraPath;
        ImageFormat format; 
        
    }
}


#endif
