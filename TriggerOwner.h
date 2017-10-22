#ifndef TRIGGEROWNER_H_
#define TRIGGEROWNER_H_

#include <string>
#include <vector>

#include "rapidxml.hpp"
#include "rapidxml_print.hpp"
#include "rapidxml_utils.hpp"

using namespace std;
using namespace rapidxml;

class TriggerOwner{
public:
	string owner;
	string object;
	string has;

	TriggerOwner(xml_node<> *node);
	virtual ~TriggerOwner();
};

#endif 