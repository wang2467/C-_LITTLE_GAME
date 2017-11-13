#include "Container.h"

Container::Container(xml_node<>* a){
	for (xml_node<>* n = a -> first_node(); n; n = n -> next_sibling()){
		if (string(n -> name()) == "name"){
			name = n -> value();
		} else if (string(n -> name()) == "status"){
			status = n -> value();
		} else if (string(n -> name()) == "description"){
			description = n -> value();
		} else if (string(n -> name()) == "accept"){
			accepts.push_back(n -> value());
		} else if (string(n -> name()) == "trigger"){
			triggers.push_back(new Trigger(n));
		} else if (string(n -> name()) == "item"){
			items.push_back(n -> value());
		}
	}	 
}

Container::~Container(){
}


bool Container::hasItem(string object){
	for (int i = 0; i < items.size(); i++){
		if (object == items[i]){
			return true;
		}
	}
	return false;
}