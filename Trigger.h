#ifndef TRIGGER_H_
#define TRIGGER_H_

#include <string>
#include <vector>

#include "rapidxml.hpp"
#include "rapidxml_print.hpp"
#include "rapidxml_utils.hpp"

#include "TriggerOwner.h"
#include "TriggerStatus.h"

using namespace std;
using namespace rapidxml;

class Trigger{
public:
	string type;
	string command;
	vector<string> print;
	vector<string> action;
	TriggerOwner* owner;
	TriggerStatus* status; 

	Trigger(xml_node<> *node);
	virtual ~Trigger();
};

#endif 