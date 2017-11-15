#include "Trigger.h"

Trigger::Trigger(xml_node<>* a){
	dirty = 1;
	override = false;
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
				status = NULL;
			} else {
				status = new TriggerStatus(n);
				owner = NULL;
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