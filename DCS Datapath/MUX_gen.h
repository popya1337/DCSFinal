#ifndef MUX_GEN 
#define MUX_GEN

#include "allocate_and_bind.h"


class MUX {
	
public:
    std::vector<std::string> MUX_in; // input register to MUX
    int MUX_out;

    op_type type; // operation type: 0 = ADD, 1 = SUB, 2 = MULT, 3 = DIV

    int width;

    MUX(int n){
    	std::vector<std::string> dummy(n);
        MUX_in = dummy;
    }
};





#endif