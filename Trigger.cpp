#include "Trigger.h"

Trigger::Trigger(xml_node<>* a){
	dirty = 1;
	for(xml_node<>* n = a -> first_node(); n; n = n -> next_sibling()){
		if (string(n -> name()) == "type"){
			type = n -> value();
		} else if (string(n -> name()) == "command"){
			command = n -> value();
		} else if (string(n -> name()) == "print"){
			prints.push_back(n -> value());
		} else if (string(n -> name()) == "action"){
			actions.push_back(n -> value());
		} else if (string(n -> name()) == "condition"){
			if (determineConditionType(n)){
				owner = new TriggerOwner(n);
			} else {
				status = new TriggerStatus(n);
			}
		}
	}
}

bool Trigger::determineConditionType(xml_node<>* a){
	for (xml_node<>* n = a -> first_node(); n; n = n -> next_sibling()){
		if (string(n -> name()) == "owner"){
			return true;
		}
	}
	return false;
}

Trigger::~Trigger(){
}