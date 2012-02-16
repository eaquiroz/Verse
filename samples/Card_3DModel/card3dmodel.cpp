#include <iostream>

#include <Core/EventDispatcher.h>
#include <Core/DisplayObject.h>
#include <Core/Callback.h>

#include <Events/Event.h>
#include <Events/MouseEvent.h>
#include <Events/MenuEvent.h>
#include <Events/QREvent.h>

#include <UI/Menu.h>
#include <UI/MenuItemData.h>
#include <UI/GLBaseApp.h>
#include <UI/Button.h>
#include <UI/Image2D.h>
#include <UI/TextField.h>
#include <UI/FreeType.h>
#include <UI/DialogBalloon.h>
#include <UI/Dialog.h>
#include <UI/Model3D.h>

#include <AR/MarkerDetection.h>

#include <Devices/Platform.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace Events;

class MyApp: public UI::GLBaseApp{
	public:
		MyApp(Devices::Platform *p)
		{ 
                    platform=p;
		}
		
		void init()
		{
                        showCamera=0;
			
                        background=cv::imread("osx-back.png");
			
                        //Create fonts to use;
			font11.init("Signika-Regular.ttf", 11);			
			font.init("Signika-Regular.ttf", 14);
			font2.init("Signika-Regular.ttf", 18);	
	
			//Define our callback events
			menuCallBack.SetCallback(this, &MyApp::onClick);
                        
                        image=new UI::Image2D();
                        image->loadImage(background);
                        image->x=0;
                        image->y=0;
                        image->width=platform->resolutionX;
                        image->height=platform->resolutionY;
                        addChild(image);
                        
                        logo3d.loadModel("logo.blend");
                        logo3d.z=-150;
                        logo3d.rotationx=-90;
                        logo3d.rotationy=0;
                        logo3d.rotationz=0;
                        addChild(&logo3d);
                        
			menu=new UI::Menu("menu1.xml", &font2, &font);
			menu->setBackgroundColor(0,0,0);
			menu->alpha=0.5;
                        menu->addEventListener(MenuEvent::MENU_ITEM_ACTION, &menuCallBack);
			addChild(menu);
                        
			db=new UI::DialogBalloon(&font, &font11);
			db->height=120;
			db->width=250;
			db->x=400;
			db->y=300;
			db->setTitle("Augmate");
			db->setText("");
                        db->hide();
			addChild(db);
                        
			dialog=new UI::Dialog(&font, &font11);
			dialog->height=150;
			dialog->width=300;
			dialog->x=100;
			dialog->y=100;
			dialog->hide();
			addChild(dialog);
                        
                        cv::Mat img=platform->getFrame();
                        markerDetection=new AR::MarkerDetection("camera.yml",img.size());
                        
                       	
		}			
		
		void draw(int selection){
                    if(showCamera)
                    {
                        cv::Mat img=platform->getFrame();
                        image->loadImage(img);
                        
                        glMatrixMode(GL_PROJECTION);
                        double *proj_matrix;
                        proj_matrix=markerDetection->process(img);
                        glLoadIdentity();
                        glLoadMatrixd(proj_matrix);
                        vector<aruco::Marker> TheMarkers=markerDetection->TheMarkers;
                        //now, for each marker,
                        double modelview_matrix[16];
                        for (unsigned int m=0;m<TheMarkers.size();m++)
                        {
                            TheMarkers[m].glGetModelViewMatrix(modelview_matrix);
                            logo3d.setModelMatrix(modelview_matrix);                            
                        }

                    }
			
		}

                void onClick(Event *ev)
		{
                    MenuEvent *e=(MenuEvent*) ev;
                    
                    if(e->action.compare("cam")==0){
                        showCamera=!showCamera;
                    }else if(e->action.compare("about")==0){
                        string tit="";
                        string text="";
                        for(int i=0; i<e->data.size(); i++){
                            UI::MenuItemData dat=e->data.at(i);
                            if(dat.key.compare("title")==0)
                                tit=dat.value;
                            if(dat.key.compare("text")==0)
                                text=dat.value;
                            
                        }
                        dialog->show(tit, text);
                    }else if(e->action.compare("exit")==0){
                        exit(0);
                    }
                    if(!showCamera)
                        image->loadImage(background);
                        
		}
                
		void run()
		{
					
		}

	private:
		Core::TCallback<MyApp> menuCallBack;
                freetype::font_data font;
		freetype::font_data font11;
		freetype::font_data font2;
                Devices::Platform *platform;
                UI::Image2D *image;
		UI::DialogBalloon *db;
		UI::Dialog *dialog;
                cv::Mat background;
                int showCamera;
                UI::Model3D logo3d;
                AR::MarkerDetection *markerDetection;
                
		UI::Menu *menu;
                
		
};

MyApp *app;
Devices::Platform	platform;

void renderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	app->render();
	glutSwapBuffers();
}

void initGL()
{
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
        
        float global_ambient[] = { 0.5f, 0.5f, 0.5f, 1.0f };
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);
        glEnable(GL_LIGHT0);

}
void mouse(int button, int state, int x, int y)
{
    app->mouseEvent(button, state, x, y);
}
void mousemotion(int x, int y)
{
    app->mouseEvent(-1, 0, x, y);
}
int main (int argc, char **argv)
{
	cout << "OpenGL-GLUT Sample Basic APP\n";

	int width=800;
	int height=600;
	
	//Start Device now is manuall and is to do
	platform.resolutionX=width;
	platform.resolutionY=height;
	
	//Start our app and set the Device configuration/platform
	app= new MyApp(&platform);
	
	// init GLUT and create Window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(width,height);
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
