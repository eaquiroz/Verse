/* 
 * File:   MarkerDetection.h
 * Author: damiles
 *
 * Created on 15 de febrero de 2012, 15:22
 */

#ifndef MARKERDETECTION_H
#define	MARKERDETECTION_H

#include "aruco.h"

using namespace cv;
using namespace aruco;

namespace AR{

class MarkerDetection {
public:
    MarkerDetection(String intrinsicFile, Size sizeImage);
    MarkerDetection(const MarkerDetection& orig);
    virtual ~MarkerDetection();
    double *process(Mat image);
    vector<Marker> TheMarkers;
    
private:
    string TheIntrinsicFile;
    bool The3DInfoAvailable;
    float TheMarkerSize;
    MarkerDetector PPDetector;
    Mat TheInputImage,TheUndInputImage,TheResizedImage;
    CameraParameters TheCameraParams;
    Size TheInputImageSize;
};
}
#endif	/* MARKERDETECTION_H */

