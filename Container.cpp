#include "Container.h"

Container::Container(xml_node<>* a){
	for (xml_node<>* n = a -> first_node(); n; n = n -> next_sibling()){
		if (string(n -> name()) == "name"){
			name = n -> value();
		} else if (string(n -> name()) == "status"){
			status = n -> value();
			//Change 1 begins
			//if(status == "locked"){
		//	}
		//	else{
			//	lock_status = false;
		//	}
			//Change 1 ends
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
	open_status = false;

}

Container::~Container(){
}


bool Container::hasItem(string object){
	for (unsigned int i = 0; i < items.size(); i++){
		if (object == items[i]){
			return true;
		}
	}
	return false;
}

bool Container::doesAccept(string object){
	if (accepts.size() == 0){
		return true;
	}
	for (unsigned int i = 0; i < accepts.size(); i++){
		if (object == accepts[i]){
			return true;
		}
	}
	return false;
}
