#include "DialogBalloon.h"

namespace UI {

DialogBalloon::DialogBalloon(freetype::font_data* f, freetype::font_data* ftext )
{
	type="DialogBallon"; 
        
        font=f;
	fontText=ftext;

        red=green=blue=0;
	alpha=0.4;

	textField=new TextField("", fontText, TextField::HORIZONTAL);
	addChild(textField);
	
	titleTextField=new TextField("", f, TextField::HORIZONTAL);
	addChild(titleTextField);
	
	headerHeight=30;
	footerHeight=20;

}

void DialogBalloon::setTitle(string t)
{
	title=t;
	titleTextField->label=title;
}
void DialogBalloon::setText(string t)
{
	text=t;
	textField->label=text;
}


void DialogBalloon::draw(int selection)
{
	if(textField){
		textField->x=x+8-(width/2);
		textField->y=y-height-footerHeight+8;
	}

	if(titleTextField){
		titleTextField->x=x+8-(width/2);
		titleTextField->y=y-height-footerHeight-headerHeight+8;
	}

	setOrthographicProjection(selection);
        glColor4f(red, green, blue, alpha);	
	//Draw body background
	Draw2D::Rectangle(x-(width/2), y-footerHeight-height, width, height);
	
	//Draw Header background
	Draw2D::Rectangle(x-(width/2), y-footerHeight-headerHeight+1-height, width, headerHeight);

	//Create triangle point
	glBegin(GL_POLYGON);
	glVertex2f(x, y);
	glVertex2f(x-20, y-footerHeight);
	glVertex2f(x+20, y-footerHeight);
	glEnd();

	glColor3f(255,255,255);
	restorePerspectiveProjection();
	
}

} /* End of namespace UI */
