#ifndef ROOM_H_
#define ROOM_H_

#include <string>
#include <vector>

#include "Item.h"
#include "Trigger.h"
#include "Border.h"
#include "Creature.h"
#include "Container.h"

#include "rapidxml.hpp"
#include "rapidxml_print.hpp"
#include "rapidxml_utils.hpp"

using namespace std;
using namespace rapidxml;

class Room{
public:
	string name;
	string descrption;
	string type;
	string status;
	vector<Border*> border_list;
	vector<Container*> container_list;
	vector<Item*> item_list;
	vector<Creature*> creature_list;
	vector<Trigger*> trigger_list;

	Room(xml_node<> *node);
	virtual ~Room();
};


#endif 