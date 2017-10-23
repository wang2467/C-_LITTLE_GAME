#include "Border.h"

Border::Border(xml_node<>* a){
	for (xml_node<>* n = a -> first_node(); n; n = n -> next_sibling()){
		if (string(n -> name()) == "name"){
			name = n -> value();
		} else if (string(n -> name()) == "direction"){
			direction = n -> value();
		} 
	}	
}

Border::~Border(){
}