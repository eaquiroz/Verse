#include "TextField.h"

namespace UI {

TextField::TextField(string l, freetype::font_data* f )
{
	type="TextField";
	
	label=l;
	font=f;
	fred=fgreen=fblue=1;
}

void TextField::draw()
{
		
	setOrthographicProjection();
	
	glColor3f(fred, fgreen, fblue);	
	glRasterPos2f(x, y+font->h);
	freetype::print(*font, label.c_str() );
	
	restorePerspectiveProjection();
	
}

} /* End of namespace UI */
