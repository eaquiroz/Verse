/* 
 * File:   MarkerDetection.cpp
 * Author: damiles
 * 
 * Created on 15 de febrero de 2012, 15:22
 */

#include "MarkerDetection.h"
namespace AR{
    MarkerDetection::MarkerDetection(String intrinsicFile, Size sizeImage) {
        TheMarkerSize=1;
        The3DInfoAvailable=false;
        
        TheIntrinsicFile=intrinsicFile;
        TheInputImageSize=sizeImage;
        TheCameraParams.readFromXMLFile(TheIntrinsicFile);
        TheCameraParams.resize(TheInputImageSize);
    }

    MarkerDetection::MarkerDetection(const MarkerDetection& orig) {
    }

    MarkerDetection::~MarkerDetection() {
    }
    
    double *MarkerDetection::process(Mat image){

        TheInputImage=image;
        TheUndInputImage.create(TheInputImage.size(),CV_8UC3);
        //transform color that by default is BGR to RGB because windows systems do not allow reading BGR images with opengl properly
        cv::cvtColor(TheInputImage,TheInputImage,CV_BGR2RGB);
        //remove distorion in image
        cv::undistort(TheInputImage,TheUndInputImage, TheCameraParams.CameraMatrix, TheCameraParams.Distorsion);
        //detect markers
        PPDetector.detect(TheUndInputImage,TheMarkers, TheCameraParams.CameraMatrix,Mat(),TheMarkerSize);
        //resize the image to the size of the GL window
        cv::resize(TheUndInputImage,TheResizedImage,TheInputImageSize);
        
        double proj_matrix[16];
        TheCameraParams.glGetProjectionMatrix(TheInputImage.size(),TheInputImageSize,proj_matrix,0.05,10);
        return proj_matrix;
    }
}

