#include "TurnOn.h"

TurnOn::TurnOn(xml_node<>* a){
	for (xml_node<>* n = a -> first_node(); n; n = n -> next_sibling()){
		if (string(n -> name()) == "print"){
			print = n -> value();
		} else if (string(n -> name()) == "action"){
			action = n -> value();
		} 
	}	 
}

TurnOn::~TurnOn(){
}