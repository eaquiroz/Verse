/* 
 * File:   Image2D.h
 * Author: damiles
 *
 * Created on 23 de enero de 2012, 22:11
 */

#ifndef IMAGE2D_H
#define	IMAGE2D_H

#include "Draw2D.h"
#include <Core/DisplayObject.h>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif

namespace UI {
    
    using namespace cv;
    
class Image2D: public Core::DisplayObject  {
public:
    Image2D();
    Image2D(const Image2D& orig);
    virtual ~Image2D();
    void draw(int selection=0);
    void loadImage(const char* file);
    void loadImage(Mat img);
    void refreshTexture();
    
private:
    GLuint texture;
    Mat image;

};
}
#endif	/* IMAGE2D_H */

