#include "Game.h"

Game::Game(xml_node<> **a){
	node = *a;
	game_over = false;
	initialize_map();
	setupTypeLookUpTable();
	current_room = rooms[0];
	vector<string> inventory;
}

void Game::initialize_map(){
	for(xml_node<>* n = node -> first_node(); n; n = n -> next_sibling()){
		if (string(n -> name()) == "room"){
			rooms.push_back(new Room(n));
		} else if (string(n -> name()) == "item"){
			items.push_back(new Item(n));
		} else if (string(n -> name()) == "container"){
			containers.push_back(new Container(n));
		} else if (string(n -> name()) == "creature"){
			creatures.push_back(new Creature(n));
		}
	}
}

void Game::setupTypeLookUpTable(){
	for (int i = 0; i < rooms.size(); i++){
		lookupTable[(rooms[i] -> name)] = "room";
	}
	for (int i = 0; i < items.size(); i++){
		lookupTable[(items[i] -> name)] = "item";
	}
	for (int i = 0; i < containers.size(); i++){
		lookupTable[(containers[i] -> name)] = "container";
	}
	for (int i = 0; i < creatures.size(); i++){
		lookupTable[(creatures[i] -> name)] = "creature";
	}
	lookupTable["inventory"] = "inventory";
}

Game::~Game(){
}

void Game::start(){
	string input;
	cout << current_room -> description << endl;
	while (!game_over){
		cout << "> ";
		getline(cin, input);
		go(input);
	}
}

bool Game::checkInput(string input){
	for (int i = 0; i < input.length(); i++){
		if (isupper(input[i])){
			return false;
		}
	}
	return true;
}

bool Game::checkTrigger(string input){
	bool flag = false;
	if (input == "n" || input == "s" || input == "e" || input == "w"){
		for (int i = 0; i < current_room -> trigger_list.size(); i++){
			Trigger* t = current_room -> trigger_list[i];
			if (t -> dirty == 1){
				if (t -> command == input){
					TriggerOwner* to = t -> owner;
					TriggerStatus* ts = t -> status;
					if (checkTriggerOwner(to)){
						for (int j = 0; j < (t -> prints).size(); j++){
							cout << (t -> prints)[j] << endl;  //needs to perform action
						}
						for (int j = 0; j < (t -> actions).size(); j++){
							performAction((t -> actions)[j]);
						}
						flag = true;
						if (t -> type == "single"){
							t -> dirty = 0;
						}
						return flag;
					} else if (checkTriggerStatus(ts)){
						for (int j = 0; j < (t -> prints).size(); j++){
							cout << (t -> prints)[j] << endl;  //needs to perform action
						}
						for (int j = 0; j < (t -> actions).size(); j++){
							performAction((t -> actions)[j]);
						}
						if (t -> type == "single"){
							t -> dirty = 0;
						}
						flag = true;
						return flag;					
					} 
				}
			}
		}
	}
	return flag;
}

Trigger* Game::isOverridenCreature(string input){
	for(int i = 0; i < creatures.size(); i++){
		for (int j = 0; j < creatures[i] -> trigger_list.size(); j++){
			if (input == creatures[i] -> trigger_list[j] -> command){
				creatures[i] -> trigger_list[j] -> override = true;
				return creatures[i] -> trigger_list[j];
			}
		}
	}
	return NULL;
}

bool Game::checkCreatureTrigger(string name, string input, bool override){
	Trigger* trig;
	bool judge = false;
	if (checkCreatureTrigger_help(name, &trig, input, &judge, override)){
		for (int i = 0; i < trig -> prints.size(); i++){
			cout << trig -> prints[i] << endl;
		}
		for (int i = 0; i < trig -> actions.size(); i++){
			performAction(trig -> actions[i]);
		}
	}
	return judge;
}

bool Game::checkCreatureTrigger_help(string name, Trigger** trig, string input, bool* judge, bool override){
	for (int i = 0; i < creatures.size(); i++){
		if (creatures[i] -> name == name){
			for (int j = 0; j < creatures[i] -> trigger_list.size(); j++){
				Trigger* t = creatures[i] -> trigger_list[j];
				if (t -> dirty == 1 || (t -> override && override)){
					if (t -> command == input && t -> command != ""){
						*judge = true;
						t -> override = true;
					}
					if (t -> command == "" || t -> command == input){
						TriggerStatus* ts = t -> status;
						TriggerOwner* to = t -> owner;
						if (checkTriggerStatus(ts)){
							//if (trig != NULL){
								*trig = t;
							//}
							if (t -> type == "single" || (t -> type != "single" && t -> type != "permanent")){
								t -> dirty = 0;
							}
							return true;
						} else if (checkTriggerOwner(to)){
							*trig = t;
							if (t -> type == "single" || (t -> type != "single" && t -> type != "permanent")){
								t -> dirty = 0;
							}
							return true;	
						}
					}
				}
			}
		}
	}
	return false;
}

bool Game::checkContainerTrigger(string name, string input){
	Trigger* trig;
	bool judge = false;
	if (checkContainerTrigger_help(name, &trig, input, &judge)){
		for (int i = 0; i < trig -> prints.size(); i++){
			cout << trig -> prints[i] << endl;
		}
		for (int i = 0; i < trig -> actions.size(); i++){
			performAction(trig -> actions[i]);
		}
	}
	return judge;	
}


bool Game::checkContainerTrigger_help(string name, Trigger** trig, string input, bool* judge){
	for(int i = 0; i < containers.size(); i++){
		if (containers[i] -> name == name){
			for (int j = 0; j < containers[i] -> triggers.size(); j++){
				Trigger* t = containers[i] -> triggers[j];
				if (t -> dirty == 1){
					if (t -> command == input){
						*judge = true;
					}
					if (t -> command == "" || t -> command == input){
						TriggerStatus* ts = t -> status;
						TriggerOwner* to = t -> owner;
						if (checkTriggerStatus(ts)){
							*trig = t;
							if (t -> type == "single" || (t -> type != "single" && t -> type != "permanent")){
								t -> dirty = 0;
							}
							return true;						
						} else if (checkTriggerOwner(to)){
							*trig = t;
							if (t -> type == "single" || (t -> type != "single" && t -> type != "permanent")){
								t -> dirty = 0;
							}
							return true;	
						}
					}	
				}
			}
		}
	}
	return false;
}

bool Game::checkTriggerOwner(TriggerOwner* to){
	if (to != NULL){
		string type = lookupTable[to -> owner];
		string object = to -> object;
		string has = to -> has;	
		return checkCondition(to -> owner, type, object, has);
	}
	return false;
}

bool Game::checkTriggerStatus(TriggerStatus* ts){
	if (ts != NULL){
		string object = ts -> object;
		string status = ts -> status;
		string object_type = lookupTable[object];
		bool judge = checkConditionStatus(object, object_type, status);
		return judge;
	}
	return false;
}

bool Game::checkCondition(string owner, string type, string object, string has){
	if (type == "inventory"){
		if (has == "yes"){
			for (int i = 0; i < inventory.size(); i++){
				if (object == inventory[i]){
					return true;
				}
			}
			return false;
		} 
		else{
			for (int i = 0; i < inventory.size(); i++){
				if (object == inventory[i]){
					return false;
				}
			}
			return true;
		}
	}
	 else if (type == "room"){
		string object_type = lookupTable[object];
		bool con;
		
		if (has == "yes"){
			con = true;
		} else{
			con = false;
		}

		if (object_type == "item"){
			return (current_room -> hasItem(object) == con);
		} 
		else if (object_type == "creature"){
			return (current_room -> hasCreature(object) == con);
		} 
		else if (object_type == "container"){
			return (current_room -> hasContainer(object) == con);
		}
	}
	else if (type == "container"){
		string object_type = lookupTable[object];
		bool con;
		
		if (has == "yes"){
			con = true;
		} else{
			con = false;
		}

		if (object_type == "item"){
			for (int i = 0; i < containers.size(); i++){
				if (containers[i] -> name == owner){
					return (containers[i] -> hasItem(object) == con);
				}
			}
		} else{
			return false;
		}
	}
	return false;
}

bool Game::checkConditionStatus(string object, string object_type, string status){
	if (object_type == "room"){
		for (int i = 0; i < rooms.size(); i++){
			if (rooms[i] -> name == object){
				if (rooms[i] -> status == status){
					return true;
				} else {
					return false;
				}
			}
		}
	} else if (object_type == "item"){
		for (int i = 0; i < items.size(); i++){
			if (items[i] -> name == object){
				if (items[i] -> status == status){
					return true;
				} else {
					return false;
				}
			}
		}		
	} else if (object_type == "container"){
		for (int i = 0; i < containers.size(); i++){
			if (containers[i] -> name == object){
				if (containers[i] -> status == status){
					return true;
				} else {
					return false;
				}
			}
		}
	} else if (object_type == "creatures"){
		for (int i = 0; i < creatures.size(); i++){
			if (creatures[i] -> name == object){
				if (creatures[i] -> status == status){
					return true;
				} else {
					return false;
				}
			}
		}
	}
	return false;

}


void Game::Act(string input){
	/*
		check the direction assuming there's no trigger
	*/
	istringstream iss(input);
	vector<string> results ((istream_iterator<string>(iss)), istream_iterator<string>());

	if (results.size() == 0){
		return;
	}
	if (input == "n" || input == "s" || input == "e" || input == "w"){
		string dir;
		int flag = 0;
		if (input == "n"){
			dir = "north";
		} else if (input == "s"){
			dir = "south";
		} else if (input == "w"){
			dir = "west";
		} else if (input == "e"){
			dir = "east";
		}
		for (int i = 0; i < (current_room -> border_list).size(); i++){
			if (current_room -> border_list[i] -> direction == dir){
				flag = 1;
				for (int j = 0; j < rooms.size(); j++){
					if (rooms[j] -> name == current_room -> border_list[i] -> name){
						current_room = rooms[j];
						cout << current_room -> description << endl;
						break;
					}
				}
				break;
			}
		}
		if (flag == 0){
			cout << "Can't go that way" << endl;
		}
	} 
	else if (input == "i"){
		if (inventory.size() == 0){
			cout << "Inventory: empty" << endl;
		} else{
			cout << "Inventory: ";
			for (int i = 0; i < inventory.size(); i++){
				if (i != inventory.size() - 1){
					cout << inventory[i] << ", ";
				} else {
					cout << inventory[i] << endl;
				}
			}
		}
	}
	else if (results[0] == "take"){
		for (int i = 0; i < (current_room -> item_list).size(); i++){
			if (results[1] == (current_room -> item_list)[i]){
				inventory.push_back((current_room -> item_list)[i]);
				current_room -> item_list.erase(current_room -> item_list.begin()+i);
				cout << "Item " << current_room -> item_list[i] << " added to inventory" << endl;
				return;
			} 
		}
		for (int i = 0; i < (current_room -> container_list).size(); i++){
			for (int j = 0; j < containers.size(); j++){
				if (current_room -> container_list[i] == containers[j] -> name && containers[j] -> status == "unlocked"){
					for (int k = 0; k < containers[j] -> items.size(); k++){
						if (containers[j] -> items[k] == results[1]) {
							inventory.push_back(containers[j] -> items[k]);
							containers[j] -> items.erase(containers[j] -> items.begin()+k);
							cout << "Item " << containers[j] -> items[k] << " added to inventory" << endl;
							return;							
						}
					}
				}
			}
		}
		cout << "Error" << endl;
	}
	else if (results[0] == "open"){
		for (int i = 0; i < current_room -> container_list.size(); i++){
			if (results[1] == current_room -> container_list[i]){
				for (int j = 0; j < containers.size(); j++){
					if (containers[j] -> name == current_room -> container_list[i]){
						containers[j] -> status = "unlocked";
						if ((containers[j] -> items).size() == 0){
							cout << containers[j] -> name << " is empty" << endl;
						} else {
							cout << containers[j] -> name << " contains ";
							for (int k = 0; k < (containers[j] -> items).size();k++){
								if (k != (containers[j] -> items).size()-1){
									cout << containers[j] -> items[k] << ", ";									
								} else{
									cout << containers[j] -> items[k];
								}
							}
							cout << endl;
						}	
						return;
					}
				}
			}
		}
		if (current_room -> type == "exit" && results[1] == "exit"){
			cout << "Game Over" << endl;
			game_over = true;
			return;
		}
		cout << "Error" << endl;
	}
	else if (results[0] == "read"){
		for (int i = 0; i < inventory.size(); i++){
			if (results[1] == inventory[i]){
				for (int j = 0; j < items.size(); j++){
					if (items[j] -> name == results[1] && (items[j] -> writing).length() != 0){
						cout << items[j] -> writing << endl;
						return;
					} else if (items[j] -> name == results[1]){
						cout << "Nothing written" << endl;
						return;
					}
				}
			}
		}
		cout << "Error" << endl;
	}
	else if (results[0] == "drop"){
		for (int i = 0; i < inventory.size(); i++){
			if (results[1] == inventory[i]){
				inventory.erase(inventory.begin()+i);
				current_room -> item_list.push_back(results[1]);
				cout << results[1] << " dropped" << endl;
				return;
			}
		}
		cout << "Error" << endl;
	} 
	else if (results[0] == "turn" && results[1] == "on"){
		string item = results[2];
		for (int k = 0; k < inventory.size(); k++){
			if (inventory[k] == item){
				for (int i = 0; i < items.size(); i++){
					if (items[i] -> name == item){
						cout << "You activate the " << item << endl; 
						cout << items[i] -> turnon -> print << endl; //needs to perfrom action
						performAction(items[i] -> turnon -> action);
						for (int j = 0; j < current_room -> creature_list.size(); j++){
							checkCreatureTrigger((current_room -> creature_list)[j], input, false);
						}
						return;
					}				
				}
			}
		}
		cout << "Error" << endl;
	} else if (results[0] == "put" && results[2] == "in"){
		string item_new = results[1];
		string container_new = results[3];
		for (int i = 0; i < containers.size(); i++){
			if (containers[i] -> name == container_new){
				for (int j = 0; j < inventory.size(); j++){
					if (item_new == inventory[j] && containers[i] -> doesAccept(item_new)){
						containers[i] -> items.push_back(item_new);		
						inventory.erase(inventory.begin()+j);	
						cout << "Item " << item_new << " added to " << container_new << endl;
						checkContainerTrigger(container_new, input);
						return;			
					}
				}
			}
		}
		cout << "Error" << endl;
	} 
	else if (results[0] == "attack" && results[2] == "with"){
			for(int i = 0; i < current_room -> creature_list.size(); i++){
				checkCreatureTrigger(current_room -> creature_list[i], input, false);
			}
			for (int i = 0; i < current_room -> container_list.size(); i++){
				checkContainerTrigger(current_room -> container_list[i], input);
			}
			if (current_room -> hasCreature(results[1])){
				for (int i = 0; i < creatures.size(); i++){
					if (results[1] == creatures[i] -> name){
						if (creatures[i] -> isVulnerableTo(results[3])){
							bool n = false;
							if ((creatures[i] -> attack != NULL && (creatures[i] -> attack -> status == NULL || checkTriggerStatus(creatures[i] -> attack -> status)))){
								n = true;
							}
							else if (creatures[i] -> attack == NULL && creatures[i] -> trigger_list.size() != 0 && checkTriggerStatus(creatures[i] -> trigger_list[0] -> status)){
								n = true;
							}
							if (n == true){
								for (int k = 0; k < inventory.size(); k++){
									if (results[3] == inventory[k]){
										cout << "You assult the " << results[1] << " with " << results[3] << endl;
										if (creatures[i] -> attack != NULL){
											for (int j = 0; j < creatures[i] -> attack -> prints.size(); j++){
												cout << creatures[i] -> attack -> prints[j] << endl;  //needs to perform action
											}
											for (int j = 0; j < creatures[i] -> attack -> actions.size(); j++){
												performAction(creatures[i] -> attack -> actions[j]);
											}
										}
										return;
									}
								}
							}
						}
					}
				}
			}	 
			cout << "Error" << endl;
	} 
	else{
		cout << "Error" << endl;
	}

}

void Game::Add(string object, string destination){
	string destination_type = lookupTable[destination];
	string object_type = lookupTable[object];
	if (destination_type == "room"){
		if (object_type == "item"){
			for (int i = 0; i < rooms.size(); i++){
				if (rooms[i] -> name == destination){
					(rooms[i] -> item_list).push_back(object);
				}
			}
		} else if (object_type == "creature"){
			for (int i = 0; i < rooms.size(); i++){
				if (rooms[i] -> name == destination){
					(rooms[i] -> creature_list).push_back(object);
				}
			}			
		} else if (object_type == "container"){
			for (int i = 0; i < rooms.size(); i++){
				if (rooms[i] -> name == destination){
					(rooms[i] -> container_list).push_back(object);
				}
			}
		}
	} else if (destination_type == "container"){
		for (int i = 0; i < containers.size(); i++){
			if (containers[i] -> name == destination){
				(containers[i] -> items).push_back(object);
			}
		}
	}
}

void Game::Update(string object, string newStatus){
	string object_type = lookupTable[object];
	if (object_type == "item"){
		for (int i = 0; i < items.size(); i++){
			if (items[i] -> name == object){
				items[i] -> status = newStatus;
			}
		}
	} 
	else if (object_type == "container"){
		for (int i = 0; i < containers.size(); i++){
			if (containers[i] -> name == object){
				containers[i] -> status = newStatus;
			}
		}
	}
	else if (object_type == "creature"){
		for (int i = 0; i < creatures.size(); i++){
			if (creatures[i] -> name == object){
				creatures[i] -> status = newStatus;
			}
		}
	} 
	else if (object_type == "room"){
		for (int i = 0; i < rooms.size(); i++){
			if (rooms[i] -> name == object){
				rooms[i] -> status = newStatus;
			}
		}
	} 
}

void Game::Delete(string object){
	string object_type = lookupTable[object];
	if (object_type == "creature"){
		for (int i = 0; i < rooms.size(); i++){
			for(int j = 0; j < rooms[i] -> creature_list.size(); j++){
				if (object == rooms[i] -> creature_list[j]){
					rooms[i] -> creature_list.erase(rooms[i] -> creature_list.begin()+j);
				}
			}
		}
	}
	else if (object_type == "container"){
		for (int i = 0; i < rooms.size(); i++){
			for(int j = 0; j < rooms[i] -> container_list.size(); j++){
				if (object == rooms[i] -> container_list[j]){
					rooms[i] -> container_list.erase(rooms[i] -> container_list.begin()+j);
				}
			}
		}		
	}
	else if (object_type == "item"){
		for (int i = 0; i < rooms.size(); i++){
			for(int j = 0; j < rooms[i] -> item_list.size(); j++){
				if (object == rooms[i] -> item_list[j]){
					rooms[i] -> item_list.erase(rooms[i] -> item_list.begin()+j);
				}
			}
		}
		for (int i = 0; i < containers.size(); i++){
			for (int j = 0; j < containers[i] -> items.size(); j++){
				if (object == containers[i] -> items[j]){
					containers[i] -> items.erase(containers[i] -> items.begin()+j);
				}
			}
		}
		for (int i = 0; i < inventory.size(); i++){
			if (object == inventory[i]){
				inventory.erase(inventory.begin()+i);
			}
		}			
	} else if (object_type == "room"){
		for (int i = 0; i < rooms.size(); i++){
			if (object == rooms[i] -> name){
				rooms.erase(rooms.begin()+i);
			}
		}
	}
	return;

}

void Game::GameOver(){
	game_over = true;
	cout << "Victory" << endl;
}

void Game::performAction(string action){
	istringstream iss(action);
	vector<string> result ((istream_iterator<string>(iss)), istream_iterator<string>());	
	if (result[0] == "Add" && result[2] == "to"){
		Add(result[1], result[3]);
	} else if (result[0] == "Update" && result[2] == "to"){
		Update(result[1], result[3]);
	} else if (result[0] == "Delete"){
		Delete(result[1]);
	} else if (result[0] == "Game" && result[1] == "Over"){
		GameOver();
	} 
	else{
		if (isOverridenCreature(action) == NULL){
			go(action);
		} else{
			go2(action);
		}
	}
	return;
}

void Game::go(string input){
	if (!checkInput(input)){
		cout << "Error" << endl;
		return;
	}
	if (checkTrigger(input)){
		return;
	}
	bool judge;
	bool k = false;
	bool override;
	Trigger* t1;
	Trigger* t = isOverridenCreature(input);
	for (int i = 0; i < creatures.size(); i++){
		for (int j = 0; j < creatures[i] -> trigger_list.size(); j++){
			if (t == creatures[i] -> trigger_list[j]){
				judge = checkCreatureTrigger_help(creatures[i] -> name, &t1, input, &k, override);
				override = judge;
			}
		}
	}
	if (t == NULL || !judge){
		Act(input);
	}
	for(int i = 0; i < current_room -> creature_list.size(); i++){
		checkCreatureTrigger(current_room -> creature_list[i], input, override);
	}
	for (int i = 0; i < current_room -> container_list.size(); i++){
		checkContainerTrigger(current_room -> container_list[i], input);
	}
}

void Game::go2(string input){
	if (!checkInput(input)){
		cout << "Error" << endl;
		return;
	}
	if (checkTrigger(input)){
		return;
	}
	Act(input);
	// for(int i = 0; i < current_room -> creature_list.size(); i++){
	// 	checkCreatureTrigger(current_room -> creature_list[i], input, false);
	// }
	// for (int i = 0; i < current_room -> container_list.size(); i++){
	// 	checkContainerTrigger(current_room -> container_list[i], input);
	// }
}
