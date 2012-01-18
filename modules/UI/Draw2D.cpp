#include "Draw2D.h"

namespace UI {

void Draw2D::Rectangle(int x, int y, int width, int height)
{
	glBegin(GL_QUADS);
	glVertex2f(x, y);
	glVertex2f(x+width,y);
	glVertex2f(x+width, y+height);
	glVertex2f(x, y+height);
	glEnd();
}

void Draw2D::RoundedRectangle(int x, int y, int w, int h, int radius)
{
	float i;
	glBegin(GL_POLYGON);
		glVertex2i(x+radius,y);
		glVertex2i(x+w-radius,y);
		for(i=(float)M_PI*1.5f;i<M_PI*2;i+=0.1f)
			glVertex2f(x+w-radius+cos(i)*radius,y+radius+sin(i)*radius);
		glVertex2i(x+w,y+radius);
		glVertex2i(x+w,y+h-radius);
		for(i=0;i<(float)M_PI*0.5f;i+=0.1f)
			glVertex2f(x+w-radius+cos(i)*radius,y+h-radius+sin(i)*radius);
		glVertex2i(x+w-radius,y+h);
		glVertex2i(x+radius,y+h);
		for(i=(float)M_PI*0.5f;i<M_PI;i+=0.1f)
			glVertex2f(x+radius+cos(i)*radius,y+h-radius+sin(i)*radius);
		glVertex2i(x,y+h-radius);
		glVertex2i(x,y+radius);
		for(i=(float)M_PI;i<M_PI*1.5f;i+=0.1f)
			glVertex2f(x+radius+cos(i)*radius,y+radius+sin(i)*radius);
	glEnd();
}

}