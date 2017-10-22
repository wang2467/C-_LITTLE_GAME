#ifndef TURNON_H_
#define TURNON_H_

#include <string>
#include <vector>

#include "rapidxml.hpp"
#include "rapidxml_print.hpp"
#include "rapidxml_utils.hpp"

using namespace std;
using namespace rapidxml;

class TurnOn{
public:
	string print;
	string action;

	TurnOn(xml_node<> *node);
	virtual ~TurnOn();
};

#endif 