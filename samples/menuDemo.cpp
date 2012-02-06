#include <iostream>

#include <Core/EventDispatcher.h>
#include <Core/DisplayObject.h>
#include <Core/Callback.h>

#include <Events/Event.h>
#include <Events/MouseEvent.h>

#include <UI/Menu.h>
#include <UI/GLBaseApp.h>
#include <UI/Button.h>
#include <UI/Image2D.h>
#include <UI/TextField.h>
#include <UI/FreeType.h>

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
			framenum=0;
			
                        background=cv::imread("osx-back.png");
			
                        //Create fonts to use;
			font.init("Signika-Regular.ttf", 14);
			font2.init("Signika-Regular.ttf", 18);	
	
			//Define our events
			myCallBack.SetCallback(this, &MyApp::onClick);
                        
			//addEventListener(MouseEvent::MOUSE_UP, &myCallBack);

                        image=new UI::Image2D();
                        image->loadImage(background);
                        image->x=0;
                        image->y=0;
                        image->width=platform->resolutionX;
                        image->height=platform->resolutionY;
                        addChild(image);
                        
                        
			menu=new UI::Menu("menu.xml", &font2, &font);
			menu->setBackgroundColor(0,0,0);
			menu->alpha=0.5;
			addChild(menu);
                        
                        //Init Button
			b=new UI::Button("Button 1",&font);
			b->x=-200;
			b->y=0;
			b->width=200;
			b->height=24;
			b->setBackgroundColor(75,185, 225);
			b->addEventListener(MouseEvent::MOUSE_UP, &myCallBack);
                        b->addEventListener(MouseEvent::MOUSE_DOWN, &myCallBack);
			//Add to scene
			addChild(b);
			
			
                        
		}			
		
		void animate(){
                    if(showCamera)
                    {
                        cv::Mat img=platform->getFrame();
                        image->loadImage(img);
                    }
			framenum++;
			if(framenum>10)
				b->x=b->x + ((platform->resolutionX-b->x-100)/10);
			
		}

		void onClick(Event *ev)
		{
                    MouseEvent *e=(MouseEvent*) ev;
			
			cout << "Event fired\n";
			cout << "Event type: " << e->type << "\n";
                        
                        stringstream mouseInfo;
                        mouseInfo << "Position: " << e->x << "," << e->y << " | State: " << e->state << " | Button: "<< e->button;
                         
                        showCamera=!showCamera;
                        if(!showCamera)
                            image->loadImage(background);
                        
		}
                
		void run()
		{
			//Create event
			Events::Event e;
			e.type="click";
			dispatchEvent(&e);			
			
		}

	private:
		Core::TCallback<MyApp> myCallBack;
		UI::Button *b;
		int framenum;
		freetype::font_data font;
		freetype::font_data font2;
                Devices::Platform *platform;
                UI::Image2D *image;
                cv::Mat background;
                int showCamera;

		UI::Menu *menu;
                
		
};

MyApp *app;
Devices::Platform	platform;

void renderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	app->animate();
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
