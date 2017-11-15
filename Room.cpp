#include "Room.h"
#include <iostream>

Room::Room(xml_node<>* a){
	for (xml_node<>* n = a -> first_node(); n; n = n -> next_sibling()){
		if (string(n -> name()) == "name"){
			name = n -> value();
		} else if (string(n -> name()) == "status"){
			status = n -> value();
		} else if (string(n -> name()) == "description"){
			description = n -> value();
		} else if (string(n -> name()) == "type"){
			type = n -> value();
		} else if (string(n -> name()) == "border"){
			border_list.push_back(new Border(n));
		} else if (string(n -> name()) == "container"){
			container_list.push_back(n -> value());
		} else if (string(n -> name()) == "item"){
			item_list.push_back(n -> value());
		} else if (string(n -> name()) == "creature"){
			creature_list.push_back(n -> value());
		} else if (string(n -> name()) == "trigger"){
			trigger_list.push_back(new Trigger(n));
		}
	}	
}

Room::~Room(){
}

Room* Room::updateRoom(string input){
	for (unsigned int i = 0; i < border_list.size(); i++){
		if (border_list[i] -> name == input){
			return this;
		}
	}
	return NULL;
}

bool Room::hasItem(string object){
	for(unsigned int i = 0; i < item_list.size(); i++){
		if (item_list[i] == object){
			return true;
		}
	}
	return false;
}

bool Room::hasContainer(string object){
	for (unsigned int i = 0; i < container_list.size(); i++){
		if (container_list[i] == object){
			return true;
		}
	}
	return false;
}

bool Room::hasCreature(string object){
	for (unsigned int i = 0; i < creature_list.size();i++){
		if (creature_list[i] == object){
			return true;
		}
	}
	return false;
}