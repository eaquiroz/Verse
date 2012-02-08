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
            
            inLevel=-1;
            
            addChild(textField);

            x=y=0;
            width=50;
            height=100;

            //Define our events
            menuClickCallBack.SetCallback(this, &Menu::onClick);
            addEventListener(Events::MouseEvent::MOUSE_UP, &menuClickCallBack);
            
            //Create menu from XML
            xmlNode* rootElement=xmlData->getRootNode();
            
            name= string(CHAR(xmlGetProp (rootElement,xmlCharStrdup( "name" ) )));
            textField->label=name;
            path.push_back(name);
            
            vector<xmlNode *> subList = vector<xmlNode *> ();
	    Utils::XML::searchXmlNode("item", rootElement, &subList);

            for (unsigned int i = 0; i < subList.size(); i++) {
                    MenuItem *subMenuItem = new MenuItem(subList.at(i), fontButton, NULL, this, 0);
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
            m->alpha=0.25;
            m->visible=false;
            addChild(m);
            
        }
         void Menu::onClickItem(Events::Event *ev)
        {
            
            MenuItem* item=(MenuItem*)ev->target;
            
            //Create path and text field path
            path.resize(item->level+1);
            path[item->level]=item->label;
            
            inLevel=item->level+1;
            
            string text=name;
            for(int i=0; i<path.size(); i++){
                text=text+" > "+path.at(i);
            }
            textField->label=text;

            //Get parent of item if it has and remove all subitems if visible
            MenuItem* p=item->parent;
            if(p){
                for(int i=0; i< p->items.size(); i++){
                    MenuItem *m=p->items.at(i);
                    m->hideSubmenu();
                }
            }else{
                //We are on top most menu 
                for(int i=0; i< items.size(); i++)
                {
                    MenuItem *m=items.at(i);
                    m->hideSubmenu();
                }
            }
            
            if(item->items.size()>0){
                //Have submenu, we need draw it
                item->showSubmenu();
            }else{
                //Supposse there are action
                inLevel=-1;
                //hide all submenus
                for(int i=0; i< items.size(); i++)
                {
                    MenuItem *item=items.at(i);
                    item->hideSubmenu();
                    item->visible=false;
                }
                //Dispatch Event with menu item click type
                Events::MenuEvent e;
                e.type=Events::MenuEvent::MENU_ITEM_ACTION;
                e.action=item->action;
                e.data=item->data;
                e.target=this;
                dispatchEvent(&e);
            }
            
            
        }
        void Menu::onClick(Events::Event *ev)
        {
            
            for(int i=0; i< items.size(); i++)
            {
                MenuItem *item=items.at(i);
                item->visible=true;
                inLevel=0;
            }

        }
        
        
	void Menu::draw(int selection){
                GLint viewport[4];
                glGetIntegerv(GL_VIEWPORT, viewport);
                height=viewport[3];
                int d=150*(inLevel+1);
                
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
