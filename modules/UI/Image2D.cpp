/* 
 * File:   Image2D.cpp
 * Author: damiles
 * 
 * Created on 23 de enero de 2012, 22:11
 */

#include "Image2D.h"
namespace UI {
    
Image2D::Image2D() 
{
    
}

Image2D::Image2D(const Image2D& orig) 
{
}

Image2D::~Image2D() 
{
}

void Image2D::loadImage(const char* file)
{
    //Load image
    image=imread(file);
    refreshTexture();
}

void Image2D::loadImage(Mat img)
{
    image=img;
    refreshTexture();
}

void Image2D::refreshTexture()
{
    //Delete texture if exist
    if (&texture)
	glDeleteTextures(1, &texture);
    
    //Generate Texture
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    int dataSize=image.cols*image.rows*3;
    unsigned char* data=new unsigned char[dataSize];
    int j=0;
    for( int y = 0; y < image.rows; y++ )
    { 
        for( int x = 0; x < image.cols; x++ )
                 { 
                    for( int c = 0; c < 3; c++ )
                    {
                         data[j] = image.at<Vec3b>(y,x)[c];
                         j++;           
                    }
                 }
    }
    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, image.cols, image.rows, GL_BGR, GL_UNSIGNED_BYTE, data);
    delete data;    
}
void Image2D::draw(int selection)
{
    setOrthographicProjection(selection);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBindTexture( GL_TEXTURE_2D, texture ); //bind the texture
    Draw2D::Rectangle(x, y, width, height);
    glBindTexture(GL_TEXTURE_2D, 0);
    restorePerspectiveProjection();

}

}
