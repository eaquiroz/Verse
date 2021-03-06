/* 
 * File:   GLBaseApp.cpp
 * Author: damiles
 * 
 * Created on 23 de enero de 2012, 21:40
 */

#include "GLBaseApp.h"


namespace UI {


GLBaseApp::GLBaseApp() {
    
}

GLBaseApp::GLBaseApp(const GLBaseApp& orig) {
}

GLBaseApp::~GLBaseApp() {
}

void GLBaseApp::render()
{
    //Draw buffer
    DisplayObject::render();
    
}

void GLBaseApp::mouseEvent(int button, int state, int x, int y)
{
    mouse_x=x;
    mouse_y=y;

    Events::MouseEvent e;

    e.x=x;
    e.y=y;
    e.state=state;
    e.button=button;

    if(button==0){
        if(state)
            e.type=Events::MouseEvent::MOUSE_UP;
        else
            e.type=Events::MouseEvent::MOUSE_DOWN;
    }else if(button==1){
        if(state)
            e.type=Events::MouseEvent::MIDDLE_MOUSE_UP;
        else
            e.type=Events::MouseEvent::MIDDLE_MOUSE_DOWN;
    }else if(button==2){
        if(state)
            e.type=Events::MouseEvent::RIGHT_MOUSE_UP;
        else
            e.type=Events::MouseEvent::RIGHT_MOUSE_DOWN;
    }else if(button==-1){
        e.type=Events::MouseEvent::MOUSE_OVER;
    }

    selection(e);

}

void GLBaseApp::selection(Events::MouseEvent e)
{
     //Chec for selection
    GLuint selectBuf[512];
    
    glSelectBuffer(512,selectBuf);
    glRenderMode(GL_SELECT);
    
    //Get viewport resolution
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    
    glInitNames();
    glPushName(0);
    
    glMatrixMode(GL_PROJECTION);                        // Selects The Projection Matrix
    glPushMatrix();                             // Push The Projection Matrix
    glLoadIdentity();     
    
    gluPickMatrix((GLdouble) mouse_x, (GLdouble) (viewport[3]-mouse_y), 1.0f, 1.0f, viewport);
    
    glMatrixMode(GL_MODELVIEW);
    
    if(visible)
    {
	draw(1);
	for(int i=0; i<childs.size(); i++)
	{
		DisplayObject* child=childs[i];
                child->mouse_x=mouse_x;
                child->mouse_y=mouse_y;
		child->render(1);	
	}
    }
    
    glPopName();
    
    // restoring the original projection matrix
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glFlush();
    
    // returning to normal rendering mode
    int hits = glRenderMode(GL_RENDER);
	
    // if there are hits process them
    if (hits != 0)
    {
        //if(e.type==Events::MouseEvent::MOUSE_UP)
        //        std::cout << "there are hits: " << hits << "\n";
        int theid=0;//selectBuf[3];
        //std::cout << theid << ", ";
        for (int loop = 0; loop < hits; loop++)              // Loop Through All The Detected Hits
        {
            // If This Object Is Closer To Us Than The One We Have Selected
            //if (buffer[loop*4+1] < GLuint(depth))
            //{
            //    choose = buffer[loop*4+3];          // Select The Closer Object
            //    depth = buffer[loop*4+1];           // Store How Far Away It Is
            //} 
            theid= selectBuf[loop*4+3];
            //if(e.type==Events::MouseEvent::MOUSE_UP)
            //    std::cout << theid << ", ";
            //Search object with theid
            DisplayObject *objectSel=searchChildId(theid);
            //Create mouseEvent
            if(objectSel!=NULL){
                e.target=objectSel;
                dispatchEvent(&e);
                
            }
        }
        //if(e.type==Events::MouseEvent::MOUSE_UP)
        //    std::cout << "\n";
	//dispatchEvent(&e);
    }
    
    
}


}

