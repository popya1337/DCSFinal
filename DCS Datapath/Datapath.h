#ifndef DATAPATH_H
#define DATAPATH_H

#include "MUX_gen.h"

class Datapath{
public:
    std::vector<op> ops;
    std::vector<reg> regs;
    std::vector<MUX> MUXs;

    Datapath(std::vector<op> &ops1, std::vector<reg> &regs1);

};

#endif
