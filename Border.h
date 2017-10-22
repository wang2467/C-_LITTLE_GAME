#ifndef BORDER_H_
#define BORDER_H_

#include <string>
#include <vector>

#include "rapidxml.hpp"
#include "rapidxml_print.hpp"
#include "rapidxml_utils.hpp"

using namespace std;
using namespace rapidxml;

class Border{
public:
	string name;
	string direction;

	Border(xml_node<> *node);
	virtual ~Border();
};

#endif 