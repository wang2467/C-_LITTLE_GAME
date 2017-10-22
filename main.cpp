#include "rapidxml_utils.hpp"
#include <iostream>
using namespace std;
using namespace rapidxml;

int main(){
	file<> xmlFile("itemsample.xml");
	xml_document<> doc;
	doc.parse<0>(xmlFile.data());

	xml_node<> *mapnode = doc.first_node();
	for (xml_node<> *node = mapnode -> first_node(); node; node = node -> next_sibling()){
		cout << string(node -> name()) <<endl;
		for (xml_node<> *n_node = node -> first_node(); n_node; n_node= n_node -> next_sibling()){
			cout << string(n_node -> value()) << endl;
		}
	}
}