#include "Button.h"

namespace UI {

    Button::Button()
    {
        textField=NULL;
    }
    
Button::Button(string l, freetype::font_data* f )
{
	type="Button"; 
        
        font=f;
        
	label=l;
	textField=new TextField(label, f, TextField::HORIZONTAL);
	
	addChild(textField);
	
}

void Button::draw(int selection)
{
    if(textField){
	textField->x=x+4;
	textField->y=y+4;
    }
	setOrthographicProjection(selection);
	
	glColor4f(red, green, blue, alpha);	
	Draw2D::RoundedRectangle(x,y,width,height,height/4);
	glColor3f(255,255,255);
	restorePerspectiveProjection();
	
}

} /* End of namespace UI */
