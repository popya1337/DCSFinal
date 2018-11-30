#ifndef MUX_GEN
#define MUX_GEN

#include "allocate_and_bind.h"


struct MUX {


    std::vector<std::string> MUX_inA; // input register to MUX
    std::vector<std::string> MUX_inB;
    int MUX_out, select, bit_width;
    op_type type;
    MUX(int n){
        MUX_inA.resize(n);
        MUX_inB.resize(n);
    }
};


std::vector<MUX> reg_sharing(std::vector<std::vector<int>> reg_cliques, std::vector<reg> regs);
std::vector<MUX> FU_sharing(std::vector<resource_type> op_cliques, std::vector<op> ops);

#endif
