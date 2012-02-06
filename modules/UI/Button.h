#ifndef UI_Button_h
#define UI_Button_h

#include <Core/DisplayObject.h>
#include <Events/Event.h>
#include <Events/MouseEvent.h>
#include "Draw2D.h"
#include "FreeType.h"
#include "TextField.h"

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

class Button : public Core::DisplayObject {
	public:
                Button();
		Button(string label, freetype::font_data* f);
		void draw(int selection=0);
		string label;
		freetype::font_data* font;
                TextField *textField;
                float overRed, overBlue, overGreen;
                int isOver;

                Core::TCallback<Button> overCallBack;
                void onOver(Events::Event *ev);
};

} /* End of namespace UI */

#endif // UI_Button_h
