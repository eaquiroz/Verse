/*
 * FacialRecognition.h
 *
 *	The class for recognizing faces from the store
 *  Modified from Cognotics eigenface example (http://www.cognotics.com/opencv/servo_2007_series/part_5/index.html)
 *  and http://www.shervinemami.co.cc/faceRecognition.html
 *  Created on: 12.03.2011
 *      Author: Peter
 */
//TODO: 1)Improve the speed of face detection. There are several ways to do that:
//      a) By improving the algorithm of HaarDetection (like here http://www.morethantechnical.com/2009/08/09/near-realtime-face-detection-on-the-iphone-w-opencv-port-wcodevideo/)
//      b) Use HaarDetection to detect face and after use CamShift to track it
//      c) Use another than HaarDetection algorithm
//
//	2) Change face recognition algorithm!!!
//

#ifndef FACIALRECOGNITION_H_
#define FACIALRECOGNITION_H_

#include <Core/EventDispatcher.h>

#include <cv.h>
#include <cvaux.h>
#include <highgui.h>

namespace AR{

class Face{
public:
    std::string name;
    CvRect faceRect;
};

class FacialRecognition: public Core::EventDispatcher  {

public:
	FacialRecognition();
	void process(IplImage* img);

private:
        std::vector<Face> facesDetected;
        IplImage* img;
	typedef std::string string;
	std::vector<string> persons_names;
	int nPersons; //Number of persons in database (5)
	int nEigens ; //Nuber of EigenValues
	int nTrainFaces; // the number of training images
	CvMat * eigenValMat; // eigenvalues
	CvMat * projectedTrainFaceMat; // projected training faces
	CvMat * personNumTruthMat; // array of person numbers
	IplImage * pAvgTrainImg; // the average image
	IplImage ** eigenVectArr; // eigenvectors
	IplImage ** faceImgArr; //face img array
	int loadTrainingData();
	int loadFaceImgArray();
	int findNearestNeighbor(float * projectedTestFace, float *pConfidence);
	void learn();
	void doPCA();
	void storeTrainingData();
	CvRect detectFaceInImage(const IplImage *inputImg);
	std::vector<CvRect> detectFacesInImage(const IplImage *inputImg);
	IplImage* convertImageToGreyscale(const IplImage *imageSrc);
	IplImage* resizeImage(const IplImage *origImg, int newWidth, int newHeight);
	IplImage* cropImage(const IplImage *img, const CvRect region);
	const char* database_file;
	const char* train_file;
	const char* HaarCascade;
	const char* database_path;

};
}
#endif /* FACIALRECOGNITION_H_ */
