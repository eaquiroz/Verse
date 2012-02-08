#ifndef UI_Dialog_h
#define UI_Dialog_h

#include <Core/DisplayObject.h>
#include <Events/Event.h>
#include <Events/MouseEvent.h>
#include "Draw2D.h"
#include "Button.h"
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

class Dialog : public Core::DisplayObject {
	public:
                Dialog(freetype::font_data* f, freetype::font_data* ftext);
		void draw(int selection=0);
		void setTitle(string t);
		void setText(string t);
		void show(string t, string txt);
		void hide();
		freetype::font_data* font;
		freetype::font_data* fontText;
                TextField *titleTextField;
		TextField *textField;
		Button *okButton;
		Button *cancelButton;
	private:
		int headerHeight, footerHeight ;
		string title;
		string text;
};

} /* End of namespace UI */

#endif
