#include "Menu.h"

namespace UI {

	Menu::Menu(string xmlfile)
	{
		xmlData=new XML(xmlfile);
		//ToDo Load data and create menu items
	}

	void Menu::draw(int selection){
		//ToDo
	}

} /* End of namespace UI */
