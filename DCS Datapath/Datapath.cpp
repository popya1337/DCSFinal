#include "Datapath.h"
using namespace std;

Datapath::Datapath(vector<op> &ops1, vector<reg> &regs1){
    for(int i = 0; i < ops1.size(); i++){
        ops.push_back(ops1[i]);
        cout << ops[i].name;
    }

    for(int i = 0; i < regs1.size(); i++){
        regs.push_back(regs1[i]);
        cout << regs[i].name;
    }
}
