#ifndef TRIGGERSTATUS_H_
#define TRIGGERSTATUS_H_

#include <string>
#include <vector>

#include "rapidxml.hpp"
#include "rapidxml_print.hpp"
#include "rapidxml_utils.hpp"

using namespace std;
using namespace rapidxml;

class TriggerStatus{
public:
	string object;
	string status;

	TriggerStatus(xml_node<> *node);
	virtual ~TriggerStatus();
};

#endif 