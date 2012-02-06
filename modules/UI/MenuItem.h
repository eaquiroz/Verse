#ifndef UI_MenuItem_h
#define UI_MenuItem_h

#include <Core/DisplayObject.h>
#include <UI/Button.h>
#include <Utils/XML.h>

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif

//libxml2
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xmlstring.h>

#include <string>
#include <vector>

namespace UI {

using std::string;
using std::vector;

struct MenuItemData{
    string key;
    string value;
};

class MenuItem : public Button {
	public:
		MenuItem(xmlNode* node , freetype::font_data* f);
                void searchChilds(xmlNode* node);
                void addMenuSubitem(MenuItem *m);
                void draw(int selection=0);
                string action;
                vector<MenuItemData> data;
	private:
		vector<MenuItem*> items;	

};

} /* End of namespace UI */

#endif // UI_Menu_h
