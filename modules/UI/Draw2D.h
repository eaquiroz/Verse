#ifndef UI_Draw2D_h
#define UI_Draw2D_h

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include <stdio.h>
#include <math.h>

namespace UI {

class Draw2D{
	public:
		static void Rectangle(int x, int y, int width, int height);
		static void RoundedRectangle(int x, int y, int width, int height, int radius);
};

}

#endif // UI_Button_h
