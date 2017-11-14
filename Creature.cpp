#include "Creature.h"

Creature::Creature(xml_node<>* a){
	for (xml_node<>* n = a -> first_node(); n; n = n -> next_sibling()){
		if (string(n -> name()) == "name"){
			name = n -> value();
		} else if (string(n -> name()) == "status"){
			status = n -> value();
		} else if (string(n -> name()) == "description"){
			description = n -> value();
		} else if (string(n -> name()) == "attack"){
			attack = new Attack(n);
		} else if (string(n -> name()) == "vulnerability"){
			vulnerability.push_back(n -> value());
		} else if (string(n -> name()) == "trigger"){
			trigger_list.push_back(new Trigger(n));
		}
	}	 
}

Creature::~Creature(){
}

bool Creature::isVulnerableTo(string object){
	for (int i = 0; i < vulnerability.size(); i++){
		if (object == vulnerability[i]){
			return true;
		}	
	}
	return false;
}