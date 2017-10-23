#include "TriggerStatus.h"

TriggerStatus::TriggerStatus(xml_node<>* a){
	for (xml_node<>* n = a -> first_node(); n; n = n -> next_sibling()){
		if (string(n -> name()) == "object"){
			object = n -> value();
		} else if (string(n -> name()) == "status"){
			status = n -> value();
		} 
	}	
}

TriggerStatus::~TriggerStatus(){

}