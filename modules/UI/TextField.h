#ifndef UI_TextField_h
#define UI_TextField_h

#include <Core/DisplayObject.h>
#include <Devices/Platform.h>
#include "Draw2D.h"
#include "FreeType.h"

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include <string>

namespace UI {

using std::string;

class TextField : public Core::DisplayObject {
	public:
		TextField(string label, freetype::font_data* f);
		void draw();
		string label;
	private:
		freetype::font_data *font;


};

} /* End of namespace UI */

#endif // UI_Button_h
