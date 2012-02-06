#include "TextField.h"

namespace UI {
    
const int TextField::HORIZONTAL=0;
const int TextField::VERTICAL=1;

TextField::TextField(string l, freetype::font_data* f, int v )
{
	type="TextField";
	
	label=l;
	font=f;
	fred=fgreen=fblue=1;
        vertical=v;
}

void TextField::draw(int selection)
{
		
	setOrthographicProjection(selection);
	
	glColor3f(fred, fgreen, fblue);	
	glRasterPos2f(x, y+font->h);
	freetype::print(*font, vertical,label.c_str() );
	glColor3f(255,255,255);	
	restorePerspectiveProjection();
	
}

} /* End of namespace UI */
