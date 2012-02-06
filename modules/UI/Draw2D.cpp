#include "Draw2D.h"

namespace UI {

void Draw2D::Rectangle(int x, int y, int width, int height)
{
	glBegin(GL_QUADS);
	glTexCoord2d(0.0,0.0); glVertex2f(x, y);
	glTexCoord2d(1.0,0.0); glVertex2f(x+width,y);
	glTexCoord2d(1.0,1.0); glVertex2f(x+width, y+height);
	glTexCoord2d(0.0,1.0); glVertex2f(x, y+height);
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

void Draw2D::drawLine2D(int x1, int y1, int x2, int y2) {

	glBegin(GL_LINES);
	glVertex2f(x1 , y1);
	glVertex2f(x2 , y2);
	glEnd();
}

}