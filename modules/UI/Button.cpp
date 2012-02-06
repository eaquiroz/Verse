#include "Button.h"

namespace UI {

    Button::Button()
    {
        textField=NULL;
        
        overRed=overGreen=overBlue=0;
        //Define our events
        overCallBack.SetCallback(this, &Button::onOver);
        addEventListener(Events::MouseEvent::MOUSE_OVER, &overCallBack);
        isOver=false;
    }
    
Button::Button(string l, freetype::font_data* f )
{
	type="Button"; 
        
        font=f;
        
	label=l;
	textField=new TextField(label, f, TextField::HORIZONTAL);
	
	addChild(textField);
	
        overRed=overGreen=overBlue=0;
       //Define our events
        overCallBack.SetCallback(this, &Button::onOver);
        addEventListener(Events::MouseEvent::MOUSE_OVER, &overCallBack);
        isOver=false;
        
}

void Button::onOver(Events::Event *ev){
    isOver=true;
}

void Button::draw(int selection)
{
    if(textField){
	textField->x=x+4;
	textField->y=y+4;
    }
	setOrthographicProjection(selection);
        if(isOver)
            glColor4f(overRed, overGreen, overBlue, alpha);	
        else
            glColor4f(red, green, blue, alpha);	
	Draw2D::RoundedRectangle(x,y,width,height,height/4);
	glColor3f(255,255,255);
	restorePerspectiveProjection();
	
}

} /* End of namespace UI */
