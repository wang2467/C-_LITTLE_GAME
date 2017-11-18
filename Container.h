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

	//Change 1 begins
	bool open_status;
	//Change 1 ends

	vector<string> accepts;
	vector<Trigger*> triggers;
	vector<string> items;

	Container(xml_node<> *node);
	bool hasItem(string);
	virtual ~Container();
	bool doesAccept(string);

};

#endif 
