/**
 * @file xml.cpp
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


#include <cstring>
#include "XML.h"

namespace Utils {

using namespace std;

XML::XML(string file){
	//Read file
	doc = xmlReadFile(file.c_str(), NULL, 0);

	if (doc == NULL) {
		printf("Error: cannot parse the file %s\n", file.c_str());
	}

	/* get the root element */
	root_element = xmlDocGetRootElement(doc);
}

xmlNode* XML::getRootNode()
{
	return root_element;
}

/*
 * Search the children of an xmlNode with the name specified by searchString, return
 */
void XML::searchXmlNode(std::string search_string, xmlNode *node,
		std::vector<xmlNode*> *result) {

	/* Search for all nodes in the tree with name search_string, return a result in a vector */
	/* Code structure similar to XmlTree::dumpXmlNode */
	xmlNode *trav;

	if (node == NULL) {
		return;
	}

	trav = node->xmlChildrenNode;

	/* Traverse the list of objets at this level */
	while (trav != NULL) {
		/* Check the name of this node, if it matches with search_string, add to the vector */
		const char *node_name = (const char *) (trav->name);
		if (strcmp(search_string.c_str(), node_name) == 0) {
			result->push_back(trav);
		}

		/* Traverse any children this node has */
		/* TODO: implement some sort of search level */
		//searchXmlNode (search_string, trav->xmlChildrenNode, result);

		/* Visit the next node in the list */
		trav = trav->next;

	}

}

std::string XML::getChildren(std::string search_string, xmlNode *searchNode) {
	xmlNode *child = searchNode->xmlChildrenNode;
	bool found = false;
	while (child != NULL && !found) {
		if (strcmp((const char*) (child->name), search_string.c_str()) == 0) {
			found = true;
		} else {
			child = child->next;
		}
	}

	if (child != NULL) {
		char *data = (char*) xmlNodeGetContent(child);
		string result(data);
		return result;
	} else {
		return "";
	}
}
}
