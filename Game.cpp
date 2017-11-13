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
}

Game::~Game(){
}

void Game::start(){
	string input;
	cout << current_room -> description << endl;

	while (!game_over){
		getline(cin, input);
		if (!checkInput(input)){
			cout << "Error" << endl;
			continue;
		}
		if (checkTrigger(input)){
			continue;
		}
		Act(input);
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
				if (t -> type == "single"){
					t -> dirty = 0;
				}
				if (t -> command == input){
					TriggerOwner* to = t -> owner;
					TriggerStatus* ts = t -> status;
					if (to != NULL){
						string type = lookupTable[to -> owner];
						string object = to -> object;
						string has = to -> has;
						if (checkCondition(to -> owner, type, object, has)){
							for (int j = 0; j < (t -> prints).size(); j++){
								cout << (t -> prints)[j] << endl;
							}
							flag = true;
						}
					}
				}
			}
		}
	}
	return flag;
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
void Game::Act(string input){
	/*
		check the direction assuming there's no trigger
	*/
	istringstream iss(input);
	vector<string> results ((istream_iterator<string>(iss)), istream_iterator<string>());

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
			cout << "empty" << endl;
		} else{
			for (int i = 0; i < inventory.size(); i++){
				cout << inventory[i] << endl;
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
							containers[j] -> items.erase(containers[j] -> items.begin()+i);
							cout << "Item " << containers[j] -> items[k] << " added to inventory" << endl;
							return;							
						}
					}
				}
			}
		}
		cout << "does not have this item" << endl;
	}
	else if (results[0] == "open"){
		for (int i = 0; i < current_room -> container_list.size(); i++){
			if (results[1] == current_room -> container_list[i]){
				for (int j = 0; j < containers.size(); j++){
					if (containers[j] -> name == current_room -> container_list[i]){
						containers[j] -> status = "unlocked";
						cout << containers[j] -> name << " contains ";
						for (int k = 0; k < (containers[j] -> items).size();k++){
							cout << containers[j] -> items[k] << ", ";
						}
						cout << endl;
						return;
					}
				}
			}
		}
	}
	else if (results[0] == "read"){
		for (int i = 0; i < inventory.size(); i++){
			if (results[1] == inventory[i]){
				for (int j = 0; j < items.size(); j++){
					if (items[j] -> name == results[1] && (items[j] -> writing).length() != 0){
						cout << items[j] -> writing << endl;
						return;
					}
				}
			}
		}
		cout << "Nothing written" << endl;
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

}

