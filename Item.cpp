#include "Item.h"

Item::Item(xml_node<>* a){
	for (xml_node<>* n = a -> first_node(); n; n = n -> next_sibling()){
		if (string(n -> name()) == "name"){
			name = n -> value();
		} else if (string(n -> name()) == "writing"){
			writing = n -> value();
		} else if (string(n -> name()) == "description"){
			description = n -> value();
		} else if (string(n -> name()) == "status"){
			status = n -> value();
		} else if (string(n -> name()) == "turn on"){
			turnon = new TurnOn(n);
		} else if (string(n -> name()) == "trigger"){
			triggers.push_back(new Trigger(n));
		}
	}	 
}

Item::~Item(){
}