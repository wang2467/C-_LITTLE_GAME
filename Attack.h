#ifndef ATTACK_H_
#define ATTACK_H_

#include <string>
#include <vector>

#include "rapidxml.hpp"
#include "rapidxml_print.hpp"
#include "rapidxml_utils.hpp"

using namespace std;
using namespace rapidxml;

class Attack{
public:
	vector<string> print;
	vector<string> action;

	Attack(xml_node<> *node);
	virtual ~Attack();
};

#endif 