#ifndef UI_MenuItem_h
#define UI_MenuItem_h

#include <Core/DisplayObject.h>

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

template <class buttonTye>
class MenuItem : public Core::DisplayObject {
	public:
		MenuItem(xmlNode* node);
		void draw(int selection=0);
		buttonTye button;
		
	private:
		vector<MenuItem> items;	

};

} /* End of namespace UI */

#endif // UI_Menu_h
