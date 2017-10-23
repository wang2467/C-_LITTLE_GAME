#ifndef CONTAINER_H_
#define CONTAINER_H_

#include <string>
#include <vector>

#include "Trigger.h"
#include "Item.h"

#include "rapidxml.hpp"
#include "rapidxml_print.hpp"
#include "rapidxml_utils.hpp"

using namespace std;
using namespace rapidxml;

class Container{
public:
	string name;
	string description;
	string status;

	vector<string> accepts;
	vector<Trigger*> triggers;
	vector<Item*> items;

	Container(xml_node<> *node);
	virtual ~Container();
};

#endif 