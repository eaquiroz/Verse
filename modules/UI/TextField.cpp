#include "TextField.h"

namespace UI {

TextField::TextField(string l, freetype::font_data* f )
{
	type="TextField";
	
	label=l;
	font=f;
	fred=fgreen=fblue=1;
}

void TextField::draw(int selection)
{
		
	setOrthographicProjection(selection);
	
	glColor3f(fred, fgreen, fblue);	
	glRasterPos2f(x, y+font->h);
	freetype::print(*font, label.c_str() );
	glColor3f(255,255,255);	
	restorePerspectiveProjection();
	
}

} /* End of namespace UI */
