#ifndef ATTACKCONDITION_H_
#define ATTACKCONDITION_H_

#include <string>
#include <vector>

#include "rapidxml.hpp"
#include "rapidxml_print.hpp"
#include "rapidxml_utils.hpp"

using namespace std;
using namespace rapidxml;

class AttackCondition{
public:
	string object;
	string status;

	AttackCondition(xml_node<> *node);
	virtual ~AttackCondition();
};

#endif 