#include "Attack.h"

Attack::Attack(xml_node<>* a){
	for (xml_node<>* n = a -> first_node(); n; n = n -> next_sibling()){
		if (string(n -> name()) == "print"){
			prints.push_back(n -> value());
		} else if (string(n -> name()) == "action"){
			actions.push_back(n -> value());
		} else if (string(n -> name()) == "condition"){
			if(determineConditionType(n)){
				owner = new TriggerOwner(n);
				status = NULL;
			} else{
				status = new TriggerStatus(n);
				owner = NULL;
			}
		}
	}	
}

Attack::~Attack(){
}

bool Attack::determineConditionType(xml_node<>* a){
	for (xml_node<>* n = a -> first_node(); n; n = n -> next_sibling()){
		if (string(n -> name()) == "owner"){
			return true;
		}
	}
	return false;
}