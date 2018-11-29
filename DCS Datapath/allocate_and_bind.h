#ifndef ALLOCATE_H
#define ALLOCATE_H

#include "DCS.h"

struct resource_type
{

	op_type type;
	std::vector<int*> cliques;

};

std::vector<resource_type> bindFunctionalUnit(std::vector<op>& ops);
void bindRegister(std::vector<reg> regs);
void setRegLifeTime(std::vector<op> ops, std::vector<reg> &regs);

#endif
