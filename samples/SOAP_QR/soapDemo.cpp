#include <iostream>

#include "soapProductsControllerBindingProxy.h"
#include "ProductsControllerBinding.nsmap"

#include <Core/EventDispatcher.h>
#include <Core/DisplayObject.h>
#include <Core/Callback.h>

#include <Events/Event.h>
#include <Events/MouseEvent.h>
#include <Events/MenuEvent.h>
#include <Events/QREvent.h>

#include <AR/QR.h>

#include <UI/Menu.h>
#include <UI/MenuItemData.h>
#include <UI/GLBaseApp.h>
#include <UI/Button.h>
#include <UI/Image2D.h>
#include <UI/TextField.h>
#include <UI/FreeType.h>
#include <UI/DialogBalloon.h>
#include <UI/Dialog.h>

#include <Devices/Platform.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <curl/curl.h>
#include <pthread.h>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace Events;

string serverDownload= "http://augmate.net/augmate/cms/upload/";
const char server[] = "http://augmate.net/augmate/cms/index.php?r=Products/products/wsdl&ws=1";

//Soap variables
ProductsControllerBindingProxy service;
struct ns1__getProductResponse result;
struct ns1__getImagesDataResponse resultImages;
string QR_Data_ref;
int QR_Data_status;
int QR_ImagesData_status[3];
cv::Mat cvimg_min[3];

#define NODATA         0
#define DOWNLOAD        1
#define LOADED          2
#define ERROR_LOAD      3

//Thread variable tid for Download Product WSDL Data
pthread_t wsdl_tid;
//Thread variable tid for download image files
pthread_t download_file_tid;

//CURL WRITE DATA FILE
size_t writeFunction( void *ptr, size_t size, size_t nmemb, void *stream) 
{ 
	fwrite(ptr, size, nmemb, (FILE *)stream); 
	return nmemb*size; 
}; 

struct thread_args
{
	string filename;
	string url;
	int status;
};
//THREAD FUNCTION FOR DOWNLOAD FILE
static void *download_url(void *arg)
{
	CURL *curl;
	CURLcode res; 
	FILE *destFile;

	struct thread_args *url_file = (struct thread_args *)arg;

	curl = curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_URL, (const char*)url_file->url.c_str());

	curl_easy_setopt(curl, CURLOPT_VERBOSE, 1); 
	// Open the file to write the copied file to 
	destFile = fopen((const char*)url_file->filename.c_str(),"wb"); 
	// Tell libcurl where to write the file 
	curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,writeFunction); 
	curl_easy_setopt(curl,CURLOPT_WRITEDATA,destFile); 
	res = curl_easy_perform(curl); 
	/* always cleanup */ 
	fclose(destFile); 
	curl_easy_cleanup(curl); 

	return NULL;
}

//THREAD FUNCTION FOR DOWNLOAD WSDL 
//PRODUCT DATA
static void *download_product_wsdl(void *arg)
{
	struct ns1__getProductResponse *productResponse = (struct ns1__getProductResponse *)arg;

	std::string md5 = "ca72431bf6bc7729c82dbb19ed7a9f2c";
	cout << "Call web service\n";
	if (service.getProduct(2, md5, QR_Data_ref, *productResponse) == SOAP_OK){
		if(result.return_!=NULL){
			std::cout << "Product: " << result.return_->name << " With price: " << result.return_->price << "\n";
			QR_Data_status=LOADED;


			//Download Images
			if (service.getImagesData(2, md5, QR_Data_ref, resultImages) == SOAP_OK){
				for(int i=0; i<3; i++)
					QR_ImagesData_status[i]=DOWNLOAD;
				//Start downloading images
				int size=(resultImages.return_->__size>3)?3:resultImages.return_->__size;
				for(int i=0; i<size; i++){
					ns1__ProductImages *prod=resultImages.return_->__ptr[i];
					cout << serverDownload << prod->owner << "/"<<prod->idProduct << "/" <<prod->url << "\n";
					thread_args ta;
					ta.url=serverDownload + prod->owner + "/"+ prod->idProduct + "/low_"+prod->url;
					ta.filename="low_"+prod->url;
					download_url(&ta);
					cvimg_min[i]=cv::imread(ta.filename);
					QR_ImagesData_status[i]=LOADED;
				}
			}else{
				service.soap_stream_fault(std::cerr);
				for(int i=0; i<3; i++)
					QR_ImagesData_status[i]=ERROR_LOAD;
			}
		}else{
			QR_Data_status=ERROR_LOAD;
		}
	}else{
		service.soap_stream_fault(std::cerr);
		QR_Data_status=ERROR_LOAD;
	}

	cout << "End Calls web service\n";
	return NULL;
}


//VERSE Application CODE
class MyApp : public UI::GLBaseApp {
	public:

		MyApp(Devices::Platform *p) {
			platform = p;
		}

		void init() {
			//Initialize Service
			service.soap_endpoint = server;
			QR_Data_status=NO_DATA;
			for(int i=0; i<3; i++)
				QR_ImagesData_status[i]=NO_DATA;
			QR_Data_ref="";

			showCamera = 0;

			background = cv::imread("osx-back.png");

			//Create fonts to use;
			font11.init("Signika-Regular.ttf", 11);
			font.init("Signika-Regular.ttf", 14);
			font2.init("Signika-Regular.ttf", 18);

			//Define our callback events
			menuCallBack.SetCallback(this, &MyApp::onClick);
			qrCallBack.SetCallback(this, &MyApp::qrDetected);

			//Init qr;
			qr = new AR::QR();
			qr->addEventListener(Events::QREvent::QR_DETECTED, &qrCallBack);
			qr->addEventListener(Events::QREvent::QR_NO_DETECTED, &qrCallBack);

			image = new UI::Image2D();
			image->loadImage(background);
			image->x = 0;
			image->y = 0;
			image->width = platform->resolutionX;
			image->height = platform->resolutionY;
			addChild(image);

			for(int i=0; i<3; i++){
				img_min[i] = new UI::Image2D();
				img_min[i]->loadImage(background);
				img_min[i]->x = 0;
				img_min[i]->y = 0;
				img_min[i]->width = 40;
				img_min[i]->height = 40;
				img_min[i]->visible=false;
				addChild(img_min[i]);
			}


			menu = new UI::Menu("menu.xml", &font2, &font);
			menu->setBackgroundColor(0, 0, 0);
			menu->alpha = 0.5;
			menu->addEventListener(MenuEvent::MENU_ITEM_ACTION, &menuCallBack);
			addChild(menu);

			db = new UI::DialogBalloon(&font, &font11);
			db->height = 120;
			db->setWidth(250);
			db->x = 400;
			db->y = 300;
			db->setTitle("Augmate");
			db->setText("");
			db->hide();
			addChild(db);

			dialog = new UI::Dialog(&font, &font11);
			dialog->height = 150;
			dialog->setWidth(300);
			dialog->x = 100;
			dialog->y = 100;
			dialog->hide();
			addChild(dialog);

		}

		void animate() {
			if (showCamera) {
				cv::Mat img = platform->getFrame();
				image->loadImage(img);
				IplImage imgIpl = img;
				qr->process(&imgIpl);
			}

		}

		void downloadQRData(string prod){
			//Downloading data status
			QR_Data_status=DOWNLOAD;
			for(int i=0; i<3; i++)
				QR_ImagesData_status[i]=DOWNLOAD;
			QR_Data_ref=prod;
			//create thread
			int error=pthread_create(&wsdl_tid,
					NULL, /* default attributes please */
					download_product_wsdl,
					(void *)&result);
			if(0 != error)
				fprintf(stderr, "Couldn't run WSDL thread, errno %d\n", error);
			else
				std::cout << "WSDL Thread running " << QR_Data_ref << " status " << QR_Data_status << "\n";

		}

		void qrDetected(Event *ev) {
			QREvent *e = (QREvent*) ev;
			if (ev->type.compare(QREvent::QR_DETECTED) == 0) {
				db->x = e->x * platform->resolutionX;
				db->y = e->y * platform->resolutionY;
				for(int i=0; i<3; i++){

					img_min[i]->x=db->x+130;
					img_min[i]->y=db->y-120+i*45;
				}
				string qrInfo = e->data;
				//Check qr first word is Reference:
				string check = e->data;
				if (check.compare(0, 10, "Reference:") == 0) {
					//Get reference Product
					string prod = check.substr(11);
					if (QR_Data_status==NODATA || prod.compare(QR_Data_ref)!=0){
						cout << "is new QR data for download prod: "<< prod << " last :" << QR_Data_ref <<" status "<< QR_Data_status << "\n";
						if(QR_Data_status==DOWNLOAD ){
							//stop threads
							cout << "stop thread\n";
							pthread_cancel(wsdl_tid);
						}

						downloadQRData(prod);
					}
					if(QR_Data_status==LOADED && prod.compare(QR_Data_ref)==0 && result.return_!=NULL){
						stringstream ss(stringstream::in | stringstream::out);
						ss << "Price" << result.return_->price << result.return_->description;
						db->show(result.return_->name, ss.str());
						//Check for images downloaded and show
						for(int i=0; i<3; i++){
							if(QR_ImagesData_status[i]==LOADED){
								img_min[i]->loadImage(cvimg_min[i]);
								img_min[i]->visible=true;
							}else{
								img_min[i]->visible=false;
							}
						}	
					}else if(QR_Data_status==DOWNLOAD){
						db->show(qrInfo, "Downloading Qr Data Info.");
						for(int i=0; i<3; i++)
							img_min[i]->visible=false;
					}else if(QR_Data_status==ERROR_LOAD){
						db->show(qrInfo, "ERROR Downloading Qr Data Info.");
						for(int i=0; i<3; i++)
							img_min[i]->visible=false;
					}
				}

			} else {
				db->hide();
				for(int i=0; i<3; i++)
					img_min[i]->visible=false;
			}
		}

		void onClick(Event *ev) {
			MenuEvent *e = (MenuEvent*) ev;

			if (e->action.compare("cam") == 0) {
				showCamera = !showCamera;
			} else if (e->action.compare("about") == 0) {
				string tit = "";
				string text = "";
				for (int i = 0; i < e->data.size(); i++) {
					UI::MenuItemData dat = e->data.at(i);
					if (dat.key.compare("title") == 0)
						tit = dat.value;
					if (dat.key.compare("text") == 0)
						text = dat.value;

				}
				dialog->show(tit, text);
			} else if (e->action.compare("exit") == 0) {
				exit(0);
			}
			if (!showCamera)
				image->loadImage(background);

		}

		void run() {
			//Create event
			Events::Event e;
			e.type = "click";
			dispatchEvent(&e);

		}

	private:
		Core::TCallback<MyApp> menuCallBack;
		Core::TCallback<MyApp> qrCallBack;
		freetype::font_data font;
		freetype::font_data font11;
		freetype::font_data font2;
		Devices::Platform *platform;
		UI::Image2D *image;
		UI::Image2D *img_min[3];
		UI::DialogBalloon *db;
		UI::Dialog *dialog;
		cv::Mat background;
		int showCamera;

		UI::Menu *menu;
		AR::QR *qr;

};


MyApp *app;
Devices::Platform platform;

void renderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	app->animate();
	app->render();
	glutSwapBuffers();
}

void initGL() {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_TEXTURE_2D);
	float ar = (GLfloat) 800 / 600;
	glMatrixMode(GL_PROJECTION);
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glLoadIdentity();
	gluPerspective(45, ar, .1, 1000);
	glMatrixMode(GL_MODELVIEW);
}

void mouse(int button, int state, int x, int y) {
	app->mouseEvent(button, state, x, y);
}

void mousemotion(int x, int y) {
	app->mouseEvent(-1, 0, x, y);
}

int main(int argc, char **argv) {
	cout << "OpenGL-GLUT Sample Basic APP\n";

	int width = 800;
	int height = 600;

	//Start Device now is manuall and is to do
	platform.resolutionX = width;
	platform.resolutionY = height;

	//Start our app and set the Device configuration/platform
	app = new MyApp(&platform);

	// init GLUT and create Window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(width, height);
	glutCreateWindow("OpenGL-GLUT Sample Basic APP");

	initGL();
	app->init();

	glutMouseFunc(mouse);
	glutPassiveMotionFunc(mousemotion);
	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);
	// enter GLUT event processing cycle
	glutMainLoop();

	return 0;
}
