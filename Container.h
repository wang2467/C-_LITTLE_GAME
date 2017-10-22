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
	string descrption;
	string status;

	vector<string> accept;
	vector<Trigger*> trigger;
	vector<Item*> item;

	Container(xml_node<> *node);
	virtual ~Container();
};

#endif 