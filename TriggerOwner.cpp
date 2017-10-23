#include "TriggerOwner.h"

TriggerOwner::TriggerOwner(xml_node<>* a){
	for (xml_node<>* n = a -> first_node(); n; n = n -> next_sibling()){
		if (string(n -> name()) == "object"){
			object = n -> value();
		} else if (string(n -> name()) == "owner"){
			owner = n -> value();
		} else if (string(n -> name()) == "has"){
			has = n -> value();
		}
	}	
}

TriggerOwner::~TriggerOwner(){
}