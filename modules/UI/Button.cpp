#include "Button.h"

namespace UI {

Button::Button(string l, freetype::font_data* f )
{
	type="Button"; 
	
	label=l;
	textField=new TextField(label, f);
	
	addChild(textField);
	
}

void Button::draw(int selection)
{
	textField->x=x+4;
	textField->y=y+4;
	setOrthographicProjection(selection);
	
	glColor4f(red, green, blue, alpha);	
	Draw2D::RoundedRectangle(x,y,width,height,height/4);
	
	restorePerspectiveProjection();
	
}

} /* End of namespace UI */
