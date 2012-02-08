#include "Dialog.h"

namespace UI {

Dialog::Dialog(freetype::font_data* f, freetype::font_data* ftext )
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
	footerHeight=40;

	okButton=new UI::Button("Ok",fontText);
	okButton->width=80;
	okButton->height=24;
	okButton->setBackgroundColor(0,0,0);
	addChild(okButton);

	cancelButton=new UI::Button("Cancel",fontText);
	cancelButton->width=80;
	cancelButton->height=24;
	cancelButton->setBackgroundColor(0,0,0);
	addChild(cancelButton);

}

void Dialog::setTitle(string t)
{
	title=t;
	titleTextField->label=title;
}
void Dialog::setText(string t)
{
	text=t;
	textField->label=text;
}

void Dialog::show(string t, string txt)
{
	setTitle(t);
	setText(txt);
	visible=true;
}
void Dialog::hide(){
	visible=false;
}

void Dialog::draw(int selection)
{
	if(textField){
		textField->x=x+8;
		textField->y=y+headerHeight+8;
	}

	if(titleTextField){
		titleTextField->x=x+8;
		titleTextField->y=y+8;
	}

	setOrthographicProjection(selection);
        glColor4f(red, green, blue, alpha);	

	//Draw Header background
	Draw2D::Rectangle(x, y, width, headerHeight);

	//Draw body background
	Draw2D::Rectangle(x, y+headerHeight+1, width, height);
	
	//Draw Header background
	Draw2D::Rectangle(x, y+headerHeight+1+height+1, width, footerHeight);

	okButton->x=x+8;
	okButton->y=y+headerHeight+1+height+1+8;

	cancelButton->x=x+8+80+8;
	cancelButton->y=y+headerHeight+1+height+1+8;

	glColor3f(255,255,255);
	restorePerspectiveProjection();
	
}

} /* End of namespace UI */
