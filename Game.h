#ifndef GAME_H_
#define GAME_H_

#include "rapidxml.hpp"
#include "rapidxml_print.hpp"
#include "rapidxml_utils.hpp"

#include "Room.h"
#include "Container.h"
#include "Item.h"
#include "Trigger.h"
#include "Creature.h"

#include <iostream>
#include <string.h>
#include <stdio.h>
#include <string>
#include <vector>

using namespace std;
using namespace rapidxml;

class Game{
public:
	xml_node<> *node;
	
	vector<Room*> rooms;
	vector<Container*> containers;
	vector<Creature*> creatures;
	vector<Item*> items;

	Game(xml_node<> **node);
	virtual ~Game();

private:
	void initialize_map();
};

#endif 



