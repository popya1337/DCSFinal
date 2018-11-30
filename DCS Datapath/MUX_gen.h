#ifndef MUX_GEN
#define MUX_GEN

#include "allocate_and_bind.h"


struct MUX {


    std::vector<int> MUX_in; // input register to MUX
    int MUX_out, select, bit_width;
    op_type type;
    MUX(int n){
        MUX_in.resize(n);
    }
};


std::vector<MUX> reg_sharing(std::vector<std::vector<int>> reg_cliques);
std::vector<MUX> FU_sharing(std::vector<resource_type> op_cliques);




#endif
