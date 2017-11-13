#include "rapidxml_utils.hpp"
#include "Game.h"
#include <iostream>
using namespace std;
using namespace rapidxml;

int main(){
	file<> xmlFile("sample.txt.xml");
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
	// for (int i = 0; i < (g->creatures).size(); i++){
	// 	vector<Trigger*> it = (g -> creatures)[i] -> trigger_list;
	// 	// for (int j = 0; j < it.size(); j++){
	// 	// 	vector<string> p = it[j] -> s;
	// 	// 	for (int k = 0; k < p.size(); k++){
	// 	// 		cout << p[k] << endl;
	// 	// 	}
	// 	// }
	// 	for (int j = 0; j < it.size(); j++){
	// 		TriggerOwner* o = it[j] -> owner;
	// 		TriggerStatus* s = it[j] -> status;
	// 		if (o != NULL){
	// 			cout << o -> owner << o -> object << o -> has << endl;
	// 		} else {
	// 			cout << s -> object << s -> status << endl;
	// 		}
	// 	}
	// }
	g -> start();

	// for(int i = 0; i < (g -> items).size(); i++){
	// 	cout << (g -> items)[i] -> name << endl;
	// 	if (i == 0){
	// 		cout << (g -> items)[i] -> turnon -> action << endl;
	// 	}
	// }
}