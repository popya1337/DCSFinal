#ifndef MUX_GEN 
#define MUX_GEN

#include "allocate_and_bind.h"


class MUX {

public:
    std::vector<std::string> MUX_in; // input register to MUX
    int MUX_out, select, bit_width;

    MUX(int n){
        MUX_in.resize(n);
    }
};


std::vector<MUX> reg_sharing(std::vector<int*> reg_cliques);




#endif