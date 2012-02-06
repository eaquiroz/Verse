#include "Menu.h"

namespace UI {

	Menu::Menu(string xmlfile, freetype::font_data* f, freetype::font_data* f1)
	{
            font=f;
            fontButton=f1;
            show=false;
            xmlData=new Utils::XML(xmlfile);
            //ToDo Load data and create menu items
            textField=new TextField("Augmate menu", f, TextField::VERTICAL);

            addChild(textField);

            x=y=0;
            width=50;
            height=100;

            //Define our events
            menuClickCallBack.SetCallback(this, &Menu::onClick);
            addEventListener(Events::MouseEvent::MOUSE_UP, &menuClickCallBack);
            
            //Create menu from XML
            xmlNode* rootElement=xmlData->getRootNode();
            
            string name= string(CHAR(xmlGetProp (rootElement,xmlCharStrdup( "name" ) )));
            textField->label=name;
            
            vector<xmlNode *> subList = vector<xmlNode *> ();
	    Utils::XML::searchXmlNode("item", rootElement, &subList);

            for (unsigned int i = 0; i < subList.size(); i++) {
                    MenuItem *subMenuItem = new MenuItem(subList.at(i), fontButton);
                    //subMenuItem->setParent(this);
                    addMenuSubitem(subMenuItem);
            }
            
	}
        
        void Menu::addMenuSubitem(MenuItem *m)
        {
            items.push_back(m);
            m->x=0;
            m->y=(items.size()-1)*25;
            m->width=148;
            m->height=24;
            m->setBackgroundColor(0,0,0);
            m->alpha=.25;
            m->visible=false;
            addChild(m);
            
        }
        
        void Menu::onClick(Events::Event *ev)
        {
            
            show=!show;
            
            for(int i=0; i< items.size(); i++)
            {
                MenuItem *item=items.at(i);
                item->visible=show;
            }
            

        }

	void Menu::draw(int selection){
                GLint viewport[4];
                glGetIntegerv(GL_VIEWPORT, viewport);
                height=viewport[3];
                int d=0;
                if(show){
                    d=150;
                }
                textField->x=x+15+d;
                textField->y=viewport[3]-50;
                
		//ToDo
                setOrthographicProjection(selection);
	
                glColor4f(red, green, blue, alpha);	
                Draw2D::Rectangle(x,y,width+d,height);
                
                //Draw2D::drawLine2D(x-1+d,0,x-1+d,height);
                glBegin(GL_LINES);
                glColor4f(1,1,1,0.4);glVertex2f(x-1+d , 0);
                glColor4f(1,1,1,0.0);glVertex2f(x-1+d , height);
                glEnd();
                glColor3f(255,255,255);
                
                restorePerspectiveProjection();

	}

} /* End of namespace UI */
