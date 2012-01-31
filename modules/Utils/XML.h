/**
 * @file xml.h
 * @author  Augmate <info@augmate.com>
 * @version 0.1
 *
 * @section LICENSE
 *
 * Copyright © 2011, Augmate Corporation LLC.
 * This file is part of VERSE.
 * 
 * VERSE is free software: you can redistribute it and/or 
 * modify it under the terms of the GNU General Public License 
 * as published by the Free Software Foundation, either version 3 
 * of the License, or (at your option) any later version.
 * 
 * VERSE is distributed in the hope that it will be useful, 
 * but WITHOUT ANY WARRANTY; without even the implied warranty 
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License 
 * along with VERSE. If not, see <http://www.gnu.org/licenses/>.
 *
 * @section DESCRIPTION
 *
 * ToDo Description.
 */

#ifndef XML_H_
#define XML_H_

#include <vector>
#include <string>
//libxml2
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xmlstring.h>

#include <Core/EventDispatcher.h>

namespace Utils {

/**
 * Helper functions for xml *
 */
class XML: public Core::EventDispatcher
{
public:
	//Constructor
	XML(std::string file);

	//Gets the root element
	xmlNode* getRootNode();

	/*
	 * Search the children of an xmlNode with the name specified by searchString, return results in a
	 * vector. NOTE: only direct children r searched, not grand children.
	 */
	static void searchXmlNode (std::string search_string, xmlNode *node, std::vector <xmlNode *> *result);

	/*
	 * Search the children elements and return the text node contents
	 */
	static std::string getChildren (std::string search_nmae, xmlNode *searchNode);
private:
	xmlDoc *doc;
	xmlNode *root_element;
	
};
}
#endif /* XML_H_ */
