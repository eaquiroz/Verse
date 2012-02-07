#include "MenuItem.h"

namespace UI {
	MenuItem::MenuItem(xmlNode* node, freetype::font_data* f, MenuItem* p, Menu* m)
	{
            font=f;
            parent=p;
            menu=m;
            
            //Get label option
            vector<xmlNode *> *labelNode = new vector<xmlNode *> ();
            Utils::XML::searchXmlNode("label", node, labelNode);

            string label="";
            if (labelNode->size() > 0) {
                    label = string(CHAR (xmlNodeGetContent (labelNode->at(0))));
            }
            
            textField=new TextField(label, font, TextField::HORIZONTAL);
            addChild(textField);
            
            //Get Data
            vector<xmlNode *> *dataNode = new vector<xmlNode *> ();
            Utils::XML::searchXmlNode("data", node, dataNode);
            if (dataNode->size() > 0) {
                    xmlNode* dataNodes=dataNode->at(0);
                    
                    xmlNode* trav = dataNodes->xmlChildrenNode;
                    std::cout << "[" << id << "]"<<"label: "<< label << "\n";
                    /* Traverse the list of objets at this level */
                    while (trav != NULL) {
                            /* Check the name of this node, if it matches with search_string, add to the vector */
                            MenuItemData itemData;
                            itemData.key=(const char*)trav->name;
                            itemData.value = string(CHAR(xmlNodeGetContent(trav)));
                            data.push_back(itemData);
                            /* Visit the next node in the list */
                            trav = trav->next;
                            std::cout << "[" << itemData.key << "]" << itemData.value << "\n";
                    }
                    
            }
            
            
            //Get the action
            action= string(CHAR(xmlGetProp (node,xmlCharStrdup( "action" ) )));
            
            
            //Search submenus
            vector<xmlNode *> *subNode = new vector<xmlNode *> ();
            Utils::XML::searchXmlNode("submenu", node, subNode);

            if (subNode->size() > 0) {
                searchChilds(subNode->at(0));
            }
            
            
            //Define our events
            menuItemClickCallBack.SetCallback(menu, &Menu::onClickItem);
            addEventListener(Events::MouseEvent::MOUSE_UP, &menuItemClickCallBack);
            
	}
        
        void MenuItem::searchChilds(xmlNode* node)
        {
            vector<xmlNode *> subList = vector<xmlNode *> ();
            
            Utils::XML::searchXmlNode("item", node, &subList);

            for (unsigned int i = 0; i < subList.size(); i++) {
                    MenuItem *subMenuItem = new MenuItem(subList.at(i), font, this, menu);
                    //subMenuItem->setParent(this);
                    addMenuSubitem(subMenuItem);
            }
        }
        void MenuItem::addMenuSubitem(MenuItem *m)
        {
            items.push_back(m);
            m->x=0;
            m->y=(items.size()-1)*25;
            m->width=148;
            m->height=24;
            m->setBackgroundColor(0,0,0);
            m->visible=false;
            addChild(m);
            
        }
        
        void MenuItem::draw(int selection)
        {
            if(textField){
                textField->x=x+4;
                textField->y=y+4;
            }
                setOrthographicProjection(selection);

                glColor4f(red, green, blue, alpha);	
                Draw2D::Rectangle(x,y,width,height);
                
                glBegin(GL_LINES);
                glColor4f(1,1,1,0);glVertex2f(x , y+height);
                glColor4f(1,1,1,0.2);glVertex2f(x+width/2 , y+height);
                glEnd();
                
                glBegin(GL_LINES);
                glColor4f(1,1,1,0.2);glVertex2f(x+width/2 , y+height);
                glColor4f(1,1,1,0.0);glVertex2f(width , y+height);
                glEnd();
                
                glColor3f(255,255,255);
                restorePerspectiveProjection();

        }
	
	
} /* End of namespace UI */
