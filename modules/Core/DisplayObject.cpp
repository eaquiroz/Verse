#include "DisplayObject.h"

namespace Core {

DisplayObject::DisplayObject()
{
	type="DisplayObject";
	alpha=1;
}

int DisplayObject::hitTestObject()
{
    return 0;
}

int DisplayObject::hitTestPoint()
{
    return 0;
}

void DisplayObject::draw()
{
	
}

void DisplayObject::render()
{
	draw();
	for(int i=0; i<childs.size(); i++)
	{
		DisplayObject* child=childs[i];
		child->render();	
	}
}

void DisplayObject::addChild(DisplayObject* object)
{
	childs.push_back(object);
}

void DisplayObject::removeChild(DisplayObject* object)
{
	int i=0;
	for(i=0; i<childs.size(); i++)
	{
		DisplayObject* testChild=childs[i];
		if(testChild==object)
			break;
	}	
	childs.erase(childs.begin()+i);
}

void DisplayObject::setBackgroundColor(int r, int g, int b)
{
	red=(float)r/255.0f;
	green=(float)g/255.0f;
	blue=(float)b/255.0f;
}

void DisplayObject::setColor(int r, int g, int b)
{
	fred=(float)r/255.0f;
	fgreen=(float)g/255.0f;
	fblue=(float)b/255.0f;
}


void DisplayObject::setOrthographicProjection() {
    
    //Get viewport resolution
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);

    // switch to projection mode
    glMatrixMode(GL_PROJECTION);

    // save previous matrix which contains the
    //settings for the perspective projection
    glPushMatrix();

    // reset matrix
    glLoadIdentity();

    // set a 2D orthographic projection
    gluOrtho2D(0, viewport[2], 0, viewport[3]);

    // invert the y axis, down is positive
    glScalef(1, -1, 1);

    // mover the origin from the bottom left corner
    // to the upper left corner
    glTranslatef(0, -viewport[3], 0);

    // switch back to modelview mode
    glMatrixMode(GL_MODELVIEW);
}

void DisplayObject::restorePerspectiveProjection() {

	glMatrixMode(GL_PROJECTION);
	// restore previous projection matrix
	glPopMatrix();
	// get back to modelview mode
	glMatrixMode(GL_MODELVIEW);
}

} /* End of namespace Core */
