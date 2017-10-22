#ifndef CREATURE_H_
#define CREATURE_H_

#include <string>
#include <vector>

#include "Attack.h"
#include "Trigger.h"

#include "rapidxml.hpp"
#include "rapidxml_print.hpp"
#include "rapidxml_utils.hpp"

using namespace std;
using namespace rapidxml;

class Creature{
public:
	string name;
	string descrption;
	string status;
	string attack;
	vector<string> vulnerablility;
	vector<Trigger*> trigger;

	Creature(xml_node<> *node);
	virtual ~Creature();
};

#endif 