#ifndef UI_Menu_h
#define UI_Menu_h

#include <Core/DisplayObject.h>
#include <Utils/XML.h>
#include <UI/MenuItem.h>

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include <string>
#include <vector>

namespace UI {

using std::string;
using std::vector;

template <class buttonTye>
class Menu : public Core::DisplayObject {
	public:
		Menu(string xmlfile);
		void draw(int selection=0);
		
	private:
		vector<MenuItem> items;		
		XML *xmlData;
};

} /* End of namespace UI */

#endif // UI_Menu_h
