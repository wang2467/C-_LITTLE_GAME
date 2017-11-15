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
#include <sstream>
#include <iterator>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <ctype.h>
#include <map>

using namespace std;
using namespace rapidxml;

class Game{
public:
	xml_node<> *node;
	bool game_over;
	Room* current_room;
	map<string, string> lookupTable;

	vector<Room*> rooms;
	vector<Container*> containers;
	vector<Creature*> creatures;
	vector<Item*> items;
	vector<string> inventory;

	Game(xml_node<> **node);
	void start();
	bool checkTrigger(string);
	bool checkInput(string);
	void Act(string);
	void setupTypeLookUpTable();
	bool checkCondition(string, string, string, string);
	void Add(string, string);
	void Update(string, string);
	void Delete(string);
	void GameOver();
	bool checkCreatureTrigger_help(string, Trigger**, string, bool*, bool);
	bool checkCreatureTrigger(string, string, bool);
	bool checkTriggerOwner(TriggerOwner*);
	bool checkTriggerStatus(TriggerStatus*);
	bool checkConditionStatus(string, string, string);
	void performAction(string);
	bool checkContainerTrigger(string, string);
	bool checkContainerTrigger_help(string, Trigger**, string, bool*);
	Trigger* isOverridenCreature(string);
	void implementTrigger(Trigger*);
	void go(string);
	void go2(string);
	
	virtual ~Game();

private:
	void initialize_map();
};

#endif 



