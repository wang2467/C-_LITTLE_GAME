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
		} else if (string(n -> name()) == "vulnerablility"){
			vulnerablility.push_back(n -> value());
		} else if (string(n -> name()) == "trigger"){
			trigger.push_back(new Trigger(n));
		}
	}	 
}

Creature::~Creature(){
}