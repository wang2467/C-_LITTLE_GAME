#include "Game.h"

Game::Game(xml_node<> **a){
	node = *a;
	initialize_map();
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

Game::~Game(){
}


