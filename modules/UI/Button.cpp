#include "Button.h"

namespace UI {

Button::Button(string l, freetype::font_data* f ,Devices::Platform *p):DisplayObject(p)
{
	type="Button"; 
	
	label=l;
	textField=new TextField(label, f, p);
	
	addChild(textField);
	
}

void Button::draw()
{
	textField->x=x+4;
	textField->y=y+4;
	setOrthographicProjection();
	
	glColor4f(red, green, blue, alpha);	
	Draw2D::RoundedRectangle(x,y,width,height,height/4);
	
	restorePerspectiveProjection();
	
}

} /* End of namespace UI */
