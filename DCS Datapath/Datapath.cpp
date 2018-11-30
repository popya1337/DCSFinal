#include "Datapath.h"
using namespace std;

Datapath::Datapath(vector<op> &ops1, vector<reg> &regs1, vector<MUX> &FU_muxs, vector<MUX> &reg_muxs){
    cout << "COPYING FUNCTIONAL UNITS, REGISTERS, AND MUXS TO DATPATAH\n" << endl;
    // Copy over operations
    for(int i = 0; i < ops1.size(); i++){
        ops.push_back(ops1[i]);
        cout << "COPIED: " << ops[i].name << endl;
    }
    cout << "\n";
    // Copy over Registers
    for(int i = 0; i < regs1.size(); i++){
        regs.push_back(regs1[i]);
        cout << "COPIED: " << regs[i].name << endl;
    }
    cout << "\n";
    // Copy over MUX's

    int printTracker = 0;
    for(int i = 0; i < FU_muxs.size(); i++){
        MUXs.push_back(FU_muxs[i]);
        cout << "COPIED MUX OF TYPE: " << MUXs[printTracker].type << endl;
        printTracker++;
    }

    for(int i = 0; i < reg_muxs.size(); i++){
        MUXs.push_back(reg_muxs[i]);
        cout << "COPIED MUX OF TYPE: " << MUXs[printTracker].type << endl;
        printTracker++;
    }

}

void Datapath::wiring(){
    // for(int i = 0; i < MUXs.size(); i++){
    //     MUXs[i].bit_width = regs[0].width; //just makes everything all one width
    //     for(int j = 0; j < MUXs[i].MUX_in.size(); j++)
    //         if(MUXs[i].type == 4){
    //             MUXs[i].
    //         }
    //         else{
    //
    //         }
    // }



}
