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
	size_t found, lastFound;
	lastFound=0;
	found=label.find('\n');
	int line=0;

	if(found==string::npos)
		//not found
		freetype::print(*font, vertical,label.c_str() );
	else{
		while(found!=string::npos){
			glRasterPos2f(x, y+font->h+(line*(font->h+5)));
			string str=label.substr(lastFound, found-lastFound);
			freetype::print(*font, vertical,str.c_str() );		
			lastFound=found;
			found=label.find('\n', lastFound+1);
			line++;
		}
	}
	
	glColor3f(255,255,255);	
	restorePerspectiveProjection();
	
}

} /* End of namespace UI */
