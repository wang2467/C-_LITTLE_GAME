#include "rapidxml_utils.hpp"
#include "Game.h"
#include <iostream>
using namespace std;
using namespace rapidxml;

int main(){
	file<> xmlFile("containersample.xml");
	xml_document<> doc;
	doc.parse<0>(xmlFile.data());

	xml_node<> *mapnode = doc.first_node();
	// for (xml_node<> *node = mapnode -> first_node(); node; node = node -> next_sibling()){
	// 	cout << string(node -> name()) <<endl;
	// 	for (xml_node<> *n_node = node -> first_node(); n_node; n_node= n_node -> next_sibling()){
	// 		cout << string(n_node -> value()) << endl;
	// 	}
	// }
	Game* g = new Game(&mapnode);
	for (int i = 0; i < (g->containers).size(); i++){
		vector<string> it = (g -> containers)[i] -> accepts;
		for (int i = 0; i < it.size(); i++){
			cout << it[i] << endl;
		}
	}

	// for(int i = 0; i < (g -> items).size(); i++){
	// 	cout << (g -> items)[i] -> name << endl;
	// 	if (i == 0){
	// 		cout << (g -> items)[i] -> turnon -> action << endl;
	// 	}
	// }
}