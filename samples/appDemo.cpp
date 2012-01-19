#include <iostream>
#include <Core/EventDispatcher.h>
#include <Core/DisplayObject.h>
#include <Core/Callback.h>
#include <Events/Event.h>
#include <Events/MouseEvent.h>
#include <UI/Button.h>
#include <UI/TextField.h>
#include <UI/FreeType.h>
#include <Devices/Platform.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

using namespace std;
using namespace Events;

class MyApp: public Core::DisplayObject{
	public:
		MyApp(Devices::Platform *p)
		{ 
                    platform=p;
		}
		
		void init()
		{
			framenum=0;
			
			//Create fonts to use;
			font.init("Signika-Regular.ttf", 14);
			font2.init("Arial.ttf", 11);	
	
			//Define our events
			myCallBack.SetCallback(this, &MyApp::onClick);
			addEventListener("click", &myCallBack);

			//Init Button
			b=new UI::Button("Button 1",&font);
			b->x=-200;
			b->y=0;
			b->width=200;
			b->height=24;
			b->setBackgroundColor(75,185, 225);
			b->addEventListener("click", &myCallBack);
			//Add to scene
			addChild(b);
			
			//Init Button
			b1=new UI::Button("Button 2",&font );
			b1->x=-200;
			b1->y=25;
			b1->width=200;
			b1->height=24;
			b1->setBackgroundColor(75,185, 225);
			//Add to scene
			addChild(b1);
			
			//Init Button
			b2=new UI::Button("Button 3",&font );
			b2->x=-200;
			b2->y=50;
			b2->width=200;
			b2->height=24;
			b2->setBackgroundColor(75,185, 225);
			cout << b2->toString() << "\n";
			//Add to scene
			addChild(b2);
			
			text=new UI::TextField("Augmate", &font2);
			text->x=0;
			text->y=platform->resolutionY-20;
			//text->setColor(75, 80, 85);
			text->setColor(0, 255, 0);
			cout << text->toString() << "\n";
			addChild(text);
		}			
		
		void animate(){
			framenum++;
			if(framenum>100)
				b->x=b->x + ((platform->resolutionX-b->x-100)/100);
			if(framenum>200)
				b1->x=b1->x + ((platform->resolutionX-b1->x-100)/100);
			if(framenum>300)
				b2->x=b2->x + ((platform->resolutionX-b2->x-100)/100);
		}

		void onClick(Events::Event e)
		{
			
			cout << "Event fired\n";
			cout << "Event type: " << e.type << "\n";
		}
		
                void mouseEvent(int button, int state, int x, int y)
                {
                    stringstream mouseInfo;
                    mouseInfo << "Position: " << x << "," << y << " | State: " << state << " | Button: "<< button;
                    text->label=mouseInfo.str();
                    
                    MouseEvent e;
                    
                    e.x=x;
                    e.y=y;
                    
                    if(button==0){
                        if(state)
                            e.type=MouseEvent::MOUSE_UP;
                        else
                            e.type=MouseEvent::MOUSE_DOWN;
                    }else if(button==1){
                        if(state)
                            e.type=MouseEvent::MIDDLE_MOUSE_UP;
                        else
                            e.type=MouseEvent::MIDDLE_MOUSE_DOWN;
                    }else if(button==2){
                        if(state)
                            e.type=MouseEvent::RIGHT_MOUSE_UP;
                        else
                            e.type=MouseEvent::RIGHT_MOUSE_DOWN;
                    }
                    
                    dispatchEvent(e);
                    
                }
                
		void run()
		{
			//Create event
			Events::Event e;
			e.type="click";
			dispatchEvent(e);			
			
		}

	private:
		Core::TCallback<MyApp> myCallBack;
		UI::Button *b;
		UI::Button *b1;
		UI::Button *b2;
		UI::TextField *text;
		int framenum;
		freetype::font_data font;
		freetype::font_data font2;
                Devices::Platform *platform;
		
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
}
void mouse(int button, int state, int x, int y)
{
    app->mouseEvent(button, state, x, y);
}
int main (int argc, char **argv)
{
	cout << "OpenGL-GLUT Sample Basic APP\n";

	int width=640;
	int height=480;
	
	//Start Device now is manuall and is to do
	platform.resolutionX=width;
	platform.resolutionY=height;
	
	//Start our app and set the Device configuration/platform
	app= new MyApp(&platform);
	app->init();
	
	// init GLUT and create Window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(width,height);
	glutCreateWindow("OpenGL-GLUT Sample Basic APP");

	initGL();
        
        glutMouseFunc(mouse);		
	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);
	// enter GLUT event processing cycle
	glutMainLoop();

	return 0;
}
