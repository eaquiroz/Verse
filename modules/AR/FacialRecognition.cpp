/*
 * FacialRecognition.cpp
 *
 *  Created on: 12.03.2011
 *      Author: Peter
 */

#include "FacialRecognition.h"

namespace AR{

FacialRecognition::FacialRecognition() {
        
        database_file=	"facesdb/database.txt";
	train_file=	"facesdb/facedata.xml";
	HaarCascade = 	"facesdb/haarcascade_frontalface_alt.xml";
	database_path=	"facesdb/train_base/";
	if(!loadTrainingData()) learn();

}

void  FacialRecognition::process(IplImage *in)
		{

    img=cvCloneImage(in);

	IplImage* greyImg = convertImageToGreyscale(img);
	CvFont font;
	cvInitFont(&font,CV_FONT_VECTOR0, 0.5f , 0.5f ,0,1);

	std::vector<CvRect> rc=detectFacesInImage(greyImg);

            facesDetected.clear();
            
    for (std::vector<CvRect>::const_iterator i=rc.begin(); i!=rc.end();++i)
	{
		IplImage* faceImg = cropImage(greyImg, *i);	// Get the detected face image.
		IplImage* sizedImg = resizeImage(faceImg, 120, 90);
		IplImage* equalizedImg = cvCreateImage(cvGetSize(sizedImg), 8, 1);	// Create an empty greyscale image
		cvEqualizeHist(sizedImg, equalizedImg);

		float* projectedTestFace = (float *)cvAlloc( nEigens*sizeof(float) );

					if (nEigens > 0) {
						// project the test image onto the PCA subspace
						cvEigenDecomposite(
							equalizedImg,
							nEigens,
							eigenVectArr,
							0, 0,
							pAvgTrainImg,
							projectedTestFace);
						float confidence;
						// Check which person it is most likely to be.
						int iNearest = findNearestNeighbor(projectedTestFace, &confidence);

						int nearest  = personNumTruthMat->data.i[iNearest];

                        //Add face to deteceted faces vector
                        Face face;
                        face.name=persons_names[nearest-1];
                        face.faceRect=*i;
                        
                        facesDetected.push_back(face);
                        
                        //CvScalar textColor = CV_RGB(255,0,0);
						//cvPutText(img, persons_names[nearest-1].c_str(), cvPoint(i->x, i->y + i->height + 15), &font, textColor);
						/*cvRectangle( img, cvPoint( i->x, i->y ),
								cvPoint( i->x + i->width, i->y + i->height ),
												 CV_RGB( 255, 0, 0 ), 1, 8, 0 );
                         */
					}

					cvReleaseImage( &faceImg );
					cvReleaseImage( &sizedImg );
					cvReleaseImage( &equalizedImg );

	}


	cvReleaseImage( &greyImg );


			//return img;
		}


// Open the training data from the file 'facedata.xml'.
int FacialRecognition::loadTrainingData()
{
	CvFileStorage * fileStorage;


	// create a file-storage interface
	fileStorage = cvOpenFileStorage( train_file, 0, CV_STORAGE_READ );
	if( !fileStorage ) {
		fprintf( stderr,"Can't open training database file 'facedata.xml'.\n");
		return 0;
	}

	// Load the person names.
	persons_names.clear();
	nPersons = cvReadIntByName( fileStorage, 0, "nPersons", 0 );
	if (nPersons == 0) {
		 fprintf( stderr,"No people found in the training database 'facedata.xml'.\n");
		return 0;
	}

	// Load each person's name.
	for (int i=0; i<nPersons; i++) {
		string sPersonName;
		string varname="personName_";
		std::stringstream num;
		num<<(i+1);
		varname+=num.str();
		sPersonName = cvReadStringByName(fileStorage, 0, varname.c_str() );
		persons_names.push_back( sPersonName );
	}

	// Load the data
	nEigens = cvReadIntByName(fileStorage, 0, "nEigens", 0);
	nTrainFaces = cvReadIntByName(fileStorage, 0, "nTrainFaces", 0);

	personNumTruthMat = (CvMat *)cvReadByName(fileStorage, 0, "trainPersonNumMat", 0);

	eigenValMat  = (CvMat *)cvReadByName(fileStorage, 0, "eigenValMat", 0);

	projectedTrainFaceMat = (CvMat *)cvReadByName(fileStorage, 0, "projectedTrainFaceMat", 0);
	pAvgTrainImg = (IplImage *)cvReadByName(fileStorage, 0, "avgTrainImg", 0);
	eigenVectArr = (IplImage **)cvAlloc(nTrainFaces*sizeof(IplImage *));
	for(int i=0; i<nEigens; i++)
	{
		string varname="eigenVect_";
				std::stringstream num;
				num<<i;
				varname+=num.str();
		eigenVectArr[i] = (IplImage *)cvReadByName(fileStorage, 0, varname.c_str(), 0);
	}
	cvReleaseFileStorage( &fileStorage );
	return 1;
}

// Train from the data in the given text file, and store the trained data into the file 'facedata.xml'.
void FacialRecognition::learn()
{
	nTrainFaces = loadFaceImgArray();

	if( nTrainFaces < 2 )
	{
		fprintf(stderr,
		        "Need 2 or more training faces\n"
		        "Input file contains only %d\n", nTrainFaces);
		return;
	}

	// do PCA on the training faces
	doPCA();

	// project the training images onto the PCA subspace
	projectedTrainFaceMat = cvCreateMat( nTrainFaces, nEigens, CV_32FC1 );
	int offset = projectedTrainFaceMat->step / sizeof(float);
	for(int i=0; i<nTrainFaces; i++)
	{

		cvEigenDecomposite(
			faceImgArr[i],
			nEigens,
			eigenVectArr,
			0, 0,
			pAvgTrainImg,
		  projectedTrainFaceMat->data.fl + i*offset);
	}

	// store the recognition data as an xml file
	storeTrainingData();

}

// Read the names & image filenames of people from a text file, and load all those images listed.
int FacialRecognition::loadFaceImgArray()
{
	FILE * imgListFile = 0;
	char imgFilename[512];
	int iFace, nFaces=0;

	// open the input file
	if( !(imgListFile = fopen(database_file, "r")) )
	{
		fprintf(stderr, "Can\'t open file %s\n", database_file);
		return 0;
	}

	// count the number of faces
	while( fgets(imgFilename, 512, imgListFile) ) ++nFaces;
	rewind(imgListFile);

	// allocate the face-image array and person number matrix
	faceImgArr        = (IplImage **)cvAlloc( nFaces*sizeof(IplImage *) );
	personNumTruthMat = cvCreateMat( 1, nFaces, CV_32SC1 );

	persons_names.clear();	// Make sure it starts as empty.
	nPersons = 0;

	// store the face images in an array
	for(iFace=0; iFace<nFaces; iFace++)
	{
		char personName[256];
		char ImgName[512];
		string full_path, sPersonName;
		int personNumber;

		// read person number (beginning with 1), their name and the image filename.
		fscanf(imgListFile, "%d %s %s", &personNumber, personName,ImgName);
		full_path=database_path;
		full_path+=ImgName;
		//Prepare the image to store in array
		IplImage* grey_image=cvLoadImage(full_path.c_str(), CV_LOAD_IMAGE_GRAYSCALE);
		if( !grey_image )
			{
			fprintf(stderr, "Can\'t load image from %s\n", full_path.c_str());
			continue;
			}
		CvRect faceRect = detectFaceInImage(grey_image);
		if(faceRect.width>0)
		{
		IplImage* croped_img  = cropImage(grey_image,faceRect);
		IplImage* resized_img = resizeImage(croped_img, 120, 90);
		IplImage* equalizedImg = cvCreateImage(cvGetSize(resized_img), 8, 1);	// Create an empty greyscale image
		cvEqualizeHist(resized_img, equalizedImg);
		cvReleaseImage( &croped_img);
		cvReleaseImage( &resized_img);
		// load the face image
		faceImgArr[iFace] = equalizedImg;
		}
		else
		{
			cvReleaseImage( &grey_image);
			fprintf(stderr, "The human face wasn't found in image %s\n", full_path.c_str());
			continue;
		}
		cvReleaseImage( &grey_image);
		sPersonName = personName;


		// Check if a new person is being loaded.
		if (personNumber > nPersons) {
			// Allocate memory for the extra person (or psibly multiple), using this new person's name.
			for (int i=nPersons; i < personNumber; i++) {
				persons_names.push_back( sPersonName );
			}
			nPersons = personNumber;
		}

		// Keep the data
		personNumTruthMat->data.i[iFace] = personNumber;
	}
	return nFaces;
}


// Perform face detection on the input image, using the given Haar cascade classifier.
// Returns a rectangle for the detected region in the given image.
CvRect FacialRecognition::detectFaceInImage(const IplImage *inputImg)
{
    // Create a new Haar classifier
static CvHaarClassifierCascade* cascade = 0;
// Load the HaarClassifierCascade
cascade = (CvHaarClassifierCascade*)cvLoad( HaarCascade, 0, 0, 0 );

// Check whether the cascade has loaded successfully. Else report and error and quit
if( !cascade )
{
	fprintf(stderr,"ERROR: Could not load classifier cascade\n");
    return cvRect(-1,-1,-1,-1);
}

	const CvSize minFeatureSize = cvSize(30, 30);
	const int flags = CV_HAAR_FIND_BIGGEST_OBJECT | CV_HAAR_DO_ROUGH_SEARCH;	// Only search for 1 face.
	const float search_scale_factor = 1.1f;
	IplImage *detectImg;
	IplImage *greyImg = 0;
	CvMemStorage* storage;
	CvRect rc;

	CvSeq* rects;

	storage = cvCreateMemStorage(0);
	cvClearMemStorage( storage );

	// If the image is color, use a greyscale copy of the image.
	detectImg = (IplImage*)inputImg;	// Assume the input image is to be used.
	if (inputImg->nChannels > 1)
	{
		greyImg = cvCreateImage(cvSize(inputImg->width, inputImg->height), IPL_DEPTH_8U, 1 );
		cvCvtColor( inputImg, greyImg, CV_BGR2GRAY );
		detectImg = greyImg;	// Use the greyscale version as the input.
	}

	// Detect all the faces.

	rects = cvHaarDetectObjects( detectImg, (CvHaarClassifierCascade*)cascade, storage,
				search_scale_factor, 3, flags, minFeatureSize );



	// Get the first detected face (the biggest).
	if (rects->total > 0) {
        rc = *(CvRect*)cvGetSeqElem( rects, 0 );
    }
	else
		rc = cvRect(-1,-1,-1,-1);	// Couldn't find the face.


	if (greyImg)
		cvReleaseImage( &greyImg );
	cvReleaseMemStorage( &storage );

	return rc;	// Return the biggest face found, or (-1,-1,-1,-1).
}

// Perform multiple faces detection on the input image for detecting faces for recognition
//
std::vector<CvRect> FacialRecognition::detectFacesInImage(const IplImage *inputImg)
{
    // Create a new Haar classifier
static CvHaarClassifierCascade* cascade = 0;
// Load the HaarClassifierCascade
cascade = (CvHaarClassifierCascade*)cvLoad( HaarCascade, 0, 0, 0 );
std::vector<CvRect> rc;
// Check whether the cascade has loaded successfully. Else report and error and quit
if( !cascade )
{
	fprintf(stderr,"ERROR: Could not load classifier cascade\n");
    return rc;
}

	const CvSize minFeatureSize = cvSize(30, 30);
	const int flags = CV_HAAR_DO_ROUGH_SEARCH;	// Only search for 1 face.
	const float search_scale_factor = 1.3f;
	IplImage *detectImg;
	IplImage *greyImg = 0;
	CvMemStorage* storage;


	CvSeq* rects;

	storage = cvCreateMemStorage(0);
	cvClearMemStorage( storage );

	// If the image is color, use a greyscale copy of the image.
	detectImg = (IplImage*)inputImg;	// Assume the input image is to be used.
	if (inputImg->nChannels > 1)
	{
		greyImg = cvCreateImage(cvSize(inputImg->width, inputImg->height), IPL_DEPTH_8U, 1 );
		cvCvtColor( inputImg, greyImg, CV_BGR2GRAY );
		detectImg = greyImg;	// Use the greyscale version as the input.
	}

	// Detect all the faces.

	rects = cvHaarDetectObjects( detectImg, (CvHaarClassifierCascade*)cascade, storage,
				search_scale_factor, 3, flags, minFeatureSize );



	// Get the first detected face (the biggest).
	for( int i = 0 ; i < ( rects ? rects->total : 0 ) ; i++ )
	{
	CvRect r = *( CvRect* )cvGetSeqElem( rects, i );
	rc.push_back(r);
	}
	return rc;
}



// Return a new image that is always greyscale, whether the input image was RGB or Greyscale.
IplImage* FacialRecognition::convertImageToGreyscale(const IplImage *imageSrc)
{
	IplImage *imageGrey;

	if (imageSrc->nChannels == 3) {
		imageGrey = cvCreateImage( cvGetSize(imageSrc), IPL_DEPTH_8U, 1 );
		cvCvtColor( imageSrc, imageGrey, CV_BGR2GRAY );
	}
	else {
		imageGrey = cvCloneImage(imageSrc);
	}
	return imageGrey;
}

// Creates a new image copy that is of a desired size.
IplImage* FacialRecognition::resizeImage(const IplImage *origImg, int newWidth, int newHeight)
{
	IplImage *outImg = 0;
	int origWidth;
	int origHeight;
	if (origImg) {
		origWidth = origImg->width;
		origHeight = origImg->height;
	}
	if (newWidth <= 0 || newHeight <= 0 || origImg == 0 || origWidth <= 0 || origHeight <= 0) {
		printf("ERROR in resizeImage: Bad desired image size of %dx%d\n.", newWidth, newHeight);
		return NULL;
	}

	// Scale the image to the new dimensions, even if the aspect ratio will be changed.
	outImg = cvCreateImage(cvSize(newWidth, newHeight), origImg->depth, origImg->nChannels);
	if (newWidth > origImg->width && newHeight > origImg->height) {
		// Make the image larger
		cvResetImageROI((IplImage*)origImg);
		cvResize(origImg, outImg, CV_INTER_LINEAR);
	}
	else {
		// Make the image smaller
		cvResetImageROI((IplImage*)origImg);
		cvResize(origImg, outImg, CV_INTER_AREA);
	}

	return outImg;
}


// Returns a new image that is a cropped version of the original image.
IplImage* FacialRecognition::cropImage(const IplImage *img, const CvRect region)
{
	IplImage *imageTmp;
	IplImage *imageRGB;
	CvSize size;
	size.height = img->height;
	size.width = img->width;

	if (img->depth != IPL_DEPTH_8U) {
		fprintf(stderr,"ERROR in cropImage: Unknown image depth of %d given in cropImage() instead of 8 bits per pixel.\n", img->depth);
		return NULL;
	}

	// First create a new (color or greyscale) IPL Image and copy contents of img into it.
	imageTmp = cvCreateImage(size, IPL_DEPTH_8U, img->nChannels);
	cvCopy(img, imageTmp, NULL);

	// Create a new image of the detected region
	// Set region of interest to that surrounding the face
	cvSetImageROI(imageTmp, region);
	// Copy region of interest (i.e. face) into a new iplImage (imageRGB) and return it
	size.width = region.width;
	size.height = region.height;
	imageRGB = cvCreateImage(size, IPL_DEPTH_8U, img->nChannels);
	cvCopy(imageTmp, imageRGB, NULL);	// Copy just the region.

    cvReleaseImage( &imageTmp );
	return imageRGB;
}

// Do the Principal Component Analysis, finding the average image
// and the eigenfaces that represent any image in the given dataset.
void FacialRecognition::doPCA()
{
	CvTermCriteria calcLimit;
	CvSize faceImgSize;

	// set the number of eigenvalues to use
	nEigens = nTrainFaces-1;

	// allocate the eigenvector images
	faceImgSize.width  = faceImgArr[0]->width;
	faceImgSize.height = faceImgArr[0]->height;
	eigenVectArr = (IplImage**)cvAlloc(sizeof(IplImage*) * nEigens);
	for(int i=0; i<nEigens; i++)
		eigenVectArr[i] = cvCreateImage(faceImgSize, IPL_DEPTH_32F, 1);

	// allocate the eigenvalue array
	eigenValMat = cvCreateMat( 1, nEigens, CV_32FC1 );

	// allocate the averaged image
	pAvgTrainImg = cvCreateImage(faceImgSize, IPL_DEPTH_32F, 1);

	// set the PCA termination criterion
	calcLimit = cvTermCriteria( CV_TERMCRIT_ITER, nEigens, 1);

	// compute average image, eigenvalues, and eigenvectors
	cvCalcEigenObjects(
		nTrainFaces,
		(void*)faceImgArr,
		(void*)eigenVectArr,
		CV_EIGOBJ_NO_CALLBACK,
		0,
		0,
		&calcLimit,
		pAvgTrainImg,
		eigenValMat->data.fl);

	cvNormalize(eigenValMat, eigenValMat, 1, 0, CV_L1, 0);
}


// Save the training data to the file 'facedata.xml'.
void FacialRecognition::storeTrainingData()
{
	CvFileStorage * fileStorage;


	// create a file-storage interface
	fileStorage = cvOpenFileStorage( train_file, 0, CV_STORAGE_WRITE );


	cvWriteInt( fileStorage, "nPersons", nPersons );
	for (int i=0; i<nPersons; i++) {
		char varname[200];
		sprintf( varname, "personName_%d", (i+1) );
		cvWriteString(fileStorage, varname,persons_names[i].c_str(), 0);
	}

	// store all the data
	cvWriteInt( fileStorage, "nEigens", nEigens );
	cvWriteInt( fileStorage, "nTrainFaces", nTrainFaces );
	cvWrite(fileStorage, "trainPersonNumMat", personNumTruthMat, cvAttrList(0,0));
	cvWrite(fileStorage, "eigenValMat", eigenValMat, cvAttrList(0,0));
	cvWrite(fileStorage, "projectedTrainFaceMat", projectedTrainFaceMat, cvAttrList(0,0));
	cvWrite(fileStorage, "avgTrainImg", pAvgTrainImg, cvAttrList(0,0));
	for(int i=0; i<nEigens; i++)
	{
		char varname[200];
		sprintf( varname, "eigenVect_%d", i );
		cvWrite(fileStorage, varname, eigenVectArr[i], cvAttrList(0,0));
	}


	cvReleaseFileStorage( &fileStorage );
}

// Find the most likely person based on a detection. Returns the index, and stores the confidence value into pConfidence.
int FacialRecognition::findNearestNeighbor(float * projectedTestFace, float *pConfidence)
{
	//double leastDistSq = 1e12;
	double leastDistSq = DBL_MAX;
	int i, iTrain, iNearest = 0;

	for(iTrain=0; iTrain<nTrainFaces; iTrain++)
	{
		double distSq=0;

		for(i=0; i<nEigens; i++)
		{
			float d_i = projectedTestFace[i] - projectedTrainFaceMat->data.fl[iTrain*nEigens + i];

			distSq += d_i*d_i / eigenValMat->data.fl[i];  // Mahalanobis distance (might give better results than Eucalidean distance)

		}

		if(distSq < leastDistSq)
		{
			leastDistSq = distSq;
			iNearest = iTrain;
		}
	}

	// Return the confidence level based on the Euclidean distance,
	// so that similar images should give a confidence between 0.5 to 1.0,
	// and very different images should give a confidence between 0.0 to 0.5.
	*pConfidence = 1.0f - sqrt( leastDistSq / (float)(nTrainFaces * nEigens) ) / 255.0f;

	// Return the found index.
	return iNearest;
}


}
