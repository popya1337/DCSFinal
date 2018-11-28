#ifndef ALLOCATE_H
#define ALLOCATE_H

#include "DCS.h"


void bindFunctionalUnit(std::vector<op> op);

struct resource_type
{
	enum op_type {ADD,SUB,MULT,DIV};
	op_type type;

	vector<vector<int>> cliques;

};

#endif
