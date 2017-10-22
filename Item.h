#ifndef ITEM_H_
#define ITEM_H_

#include <string>
#include <vector>

#include "TurnOn.h"
#include "Trigger.h"

#include "rapidxml.hpp"
#include "rapidxml_print.hpp"
#include "rapidxml_utils.hpp"

using namespace std;
using namespace rapidxml;

class Item{
public:
	string name;
	string descrption;
	string writing;
	string status;
	TurnOn* turnon;
	vector<Trigger*> trigger_list;

	Item(xml_node<> *node);
	virtual ~Item();
};


#endif 