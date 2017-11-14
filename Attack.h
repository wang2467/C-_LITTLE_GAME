#ifndef ATTACK_H_
#define ATTACK_H_

#include <string>
#include <vector>

#include "AttackCondition.h"
#include "TriggerOwner.h"
#include "TriggerStatus.h"

#include "rapidxml.hpp"
#include "rapidxml_print.hpp"
#include "rapidxml_utils.hpp"

using namespace std;
using namespace rapidxml;

class Attack{
public:
	vector<string> prints;
	vector<string> actions;
	//AttackCondition* condition;
	TriggerOwner* owner;
	TriggerStatus* status;

	Attack(xml_node<> *node);
	bool determineConditionType(xml_node<>*);
	
	virtual ~Attack();
};

#endif 