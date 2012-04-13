#include "TextField.h"

namespace UI {
    
const int TextField::HORIZONTAL=0;
const int TextField::VERTICAL=1;

TextField::TextField(string l, freetype::font_data* f, int v )
{
	type="TextField";
	
	font=f;
	fred=fgreen=fblue=1;
    vertical=v;
    width=300;
    setText(l);
}
void TextField::setText(string text){
	label=text;

	//split text in white spaces
	char * pch;
	char tmpstr[255];
	strcpy(tmpstr, text.c_str());
	pch= strtok(tmpstr," ");
	int line=0;
	lines.clear();
	lines.push_back("");
	int lineSize=0;
	//for each word check word size
	while(pch != NULL)
	{
		int w=freetype::getWidthSize(*font, pch);
		if(lineSize + w < width){
			lineSize+=w;
		}else{
			lineSize=w;
			lines.push_back("");
			line++;
		}
		lines[line]=lines[line]+" "+pch;
		pch= strtok(NULL, " ");
	}
}
void TextField::setWidth(int w)
{
	width=w;
	setText(label);
}
void TextField::draw(int selection)
{
		
	setOrthographicProjection(selection);
	
	glColor3f(fred, fgreen, fblue);	
	glRasterPos2f(x, y+font->h);
	size_t found, lastFound;
	lastFound=0;
	found=label.find("\\n");
	int line=0;
/*
	if(found==string::npos)
		//not found
		freetype::print(*font, vertical,label.c_str() );
	else{
		while(found!=string::npos){
			glRasterPos2f(x, y+font->h+(line*(font->h+5)));
			string str=label.substr(lastFound, found-lastFound);
			freetype::print(*font, vertical,str.c_str() );		
			lastFound=found+2;
			found=label.find("\\n", lastFound+1);
			line++;
		}
	}
*/
	for( line=0;line < lines.size(); line++){
		glRasterPos2f(x, y+font->h+(line*(font->h+5)));
		string str=lines[line];
		freetype::print(*font, vertical,str.c_str() );		
	}	
	glColor3f(255,255,255);	
	restorePerspectiveProjection();
	
}

} /* End of namespace UI */
