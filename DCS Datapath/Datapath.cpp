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
        MUXs[i].width = regs[0].width;
        cout << "COPIED MUX OF TYPE: " << MUXs[printTracker].type << endl;
        printTracker++;
    }

    for(int i = 0; i < reg_muxs.size(); i++){
        MUXs.push_back(reg_muxs[i]);
        MUXs[printTracker].width = regs[0].width;
        cout << "COPIED MUX OF TYPE: " << MUXs[printTracker].type << endl;
        printTracker++;
    }

}

int get_size(int MUX_size){
    int sum = 1;
    for(int i = 0; i < MUX_size; i++){
        sum *= 2;
        if(sum >= MUX_size) break;
    }
    int counter;
    for(counter = 0; sum != 2; counter++){
        sum /= 2;
    }
    return counter;
}

string print_FU_entity(op_type type){
    switch(type){
        case 0:
            return ": entity work.c_adder";
        case 1:
            return ": entity work.c_subtractor";
        case 2:
            return ": entity work.c_multiplier";
        default:
            return ": entity work.c_divider";
    }
}

string muxSplitInput(int width, int numOfInputs, vector<string> &MUX_ins, vector <MUX> &MUXs, vector<reg> &regs){
    string mux_input = "";
    bool flag = 0;
    for(int i = 0; i < numOfInputs; i++){
        int big = width*( i + 1) - 1;
        int small = big - (width - 1);
        for(int j = 0; j  < regs.size() ; j++){
            if(MUX_ins[i] == regs[j].name && regs[j].type == intermediate){
                for(int k = 0;  k < MUXs.size(); k++){
                    if(MUXs[k].type != REG){
                        for(int m = 0; m < MUXs[k].MUX_out.size(); m++){
                            if(MUX_ins[i] == MUXs[k].MUX_out[m]){
                                // mux_input += "input(" + to_string(big) +  " downto " + to_string(small) + ") => " + MUXs[k].nameA + "_OUT, ";
                                // flag = 1;
                            }
                        }
                    }
                }
            }
        }
        if(!flag){
            mux_input += "input(" + to_string(big) +  " downto " + to_string(small) + ") => " + MUX_ins[i] + ", ";
        }
    }
    return mux_input;
}



string muxSplitInput(int width, int numOfInputs, vector<string> &MUX_ins){
    string mux_input = "";
    for(int i = 0; i < numOfInputs; i++){
        int big = width*( i + 1) - 1;
        int small = big - (width - 1);
        mux_input += "input(" + to_string(big) +  " downto " + to_string(small) + ") => " + MUX_ins[i] + ", ";
    }
    return mux_input;
}

void Datapath::printToVHDL(string filename){
    ofstream out("../VHDL/" + filename + "_output_test.vhd" );

    out << "library IEEE;\n";
	out << "use IEEE.STD_LOGIC_1164.ALL;\n";
	out << "use ieee.numeric_std.all;\n\n\n";
	out << "entity datapath_" << filename << " is\n";
	out << "port\n(\n";

    for (int i = 0; i < regs.size(); i++){
		if (regs[i].type == input)
			out << "\t" << regs[i].name << " : in std_logic_vector(" << regs[i].width - 1 << " downto 0);\n";
		else if (regs[i].type == output)
            out << "\t" << regs[i].name << " : out std_logic_vector(" << regs[i].width - 1 << " downto 0);\n";
    }

    for (int i = 0; i < MUXs.size(); i++){
        if(MUXs[i].type == REG){
            out << "\t" << MUXs[i].nameA << "_MUX_SEL" << " : in std_logic_vector(" << get_size(MUXs[i].MUX_inA.size()) << " downto 0);\n";
        }
        else{
            out << "\t" << MUXs[i].nameA << "_MUX_A_SEL" << " : in std_logic_vector(" << get_size(MUXs[i].MUX_inA.size()) << " downto 0);\n";
            out << "\t" << MUXs[i].nameB << "_MUX_B_SEL" << " : in std_logic_vector(" << get_size(MUXs[i].MUX_inB.size())  << " downto 0);\n";
        }
    }

    out << "\tclear : in std_logic;\n\tclock : in std_logic);\nend datapath_" << filename << ";\n";
    out << "\narchitecture " << filename << "_arch of datapath_" << filename << " is\n";

    for(int i = 0; i < regs.size(); i++){

    }

    out << "\n--BEGINNING OF REGS\n\n";

    for(int i = 0; i < MUXs.size(); i++){
        if(MUXs[i].type == REG){
            out << "\tsignal " << MUXs[i].nameA << "_IN" << " : std_logic_vector(" << regs[i].width - 1 << " downto 0);\n";
            out << "\tsignal " << MUXs[i].nameA << "_OUT" << " : std_logic_vector(" << regs[i].width - 1 << " downto 0);\n";
        }
        else{
            out << "\tsignal " << MUXs[i].nameA << "_A_IN" << " : std_logic_vector(" << regs[i].width - 1 << " downto 0);\n";
            out << "\tsignal " << MUXs[i].nameB << "_B_IN" << " : std_logic_vector(" << regs[i].width - 1 << " downto 0);\n";
            out << "\tsignal " << MUXs[i].nameB << "_OUT" << " : std_logic_vector(" << regs[i].width - 1 << " downto 0);\n";
        }
    }

    out << "\nbegin\n\n";

    out << "\n--BEGINNING OF FUNCTIONAL UNITS\n\n";


    for(int i = 0; i < MUXs.size(); i++){
        if(MUXs[i].type != REG){
            out << "\t" << MUXs[i].nameA << print_FU_entity(MUXs[i].type) << "\n\tgeneric map(width => " << MUXs[i].width << ")\n"
                << "\tport map(input1 => " << MUXs[i].nameA << "_A_IN, input2 => " << MUXs[i].nameB << "_B_IN, output => " << MUXs[i].nameA << "_OUT);\n\n";
        }
    }

    out << "\n--BEGINNING OF REGS\n\n";

    for(int i = 0; i < MUXs.size(); i++){
        if(MUXs[i].type == REG){
            out << "\t" << MUXs[i].nameA << ": entity work.c_register" << "\n\tgeneric map(width => " << MUXs[i].width << ")\n"
                << "\tport map(input => " << MUXs[i].nameA << "_IN, output => " << MUXs[i].nameA << "_OUT, clear => clear, clock => clock);\n\n";
        }
    }


    out << "\n--BEGINNING OF MUXES FOR FUNCTIONAL UNITS\n\n";

    for(int i = 0; i < MUXs.size(); i++){
        if(MUXs[i].type != REG){
            out << "\t" << MUXs[i].nameA << "_MUX_A : entity work.c_multiplexer" << "\n\tgeneric map(width => " << MUXs[i].width << ", no_of_inputs => "<<
            MUXs[i].MUX_inA.size() << ", select_size => " << get_size(MUXs[i].MUX_inA.size()) << ")\n" << "\tport map ("
            << muxSplitInput(MUXs[i].width, MUXs[i].MUX_inA.size(), MUXs[i].MUX_inA, MUXs, this->regs)
            << "output => " << MUXs[i].nameA << "_A_IN);\n\n";

            out << "\t" << MUXs[i].nameB << "_MUX_B : entity work.c_multiplexer" << "\n\tgeneric map(width => " << MUXs[i].width << ", no_of_inputs => "<<
            MUXs[i].MUX_inB.size() << ", select_size => " << get_size(MUXs[i].MUX_inB.size()) << ")\n" << "\tport map ("
            << muxSplitInput(MUXs[i].width, MUXs[i].MUX_inA.size(), MUXs[i].MUX_inA, MUXs, this->regs)
            << "output => " << MUXs[i].nameB << "_B_IN);\n\n";
        }
    }

    out << "\n--BEGINNING OF MUXES FOR REGISTERS\n\n";

    for(int i = 0; i < MUXs.size(); i++){
        if(MUXs[i].type == REG){
            out << "\t" << MUXs[i].nameA << "_MUX : entity work.c_multiplexer" << "\n\tgeneric map(width => " << MUXs[i].width << ", no_of_inputs => "<<
            MUXs[i].MUX_inA.size() << ", select_size => " << get_size(MUXs[i].MUX_inA.size()) << ")\n" << "\tport map ("
            << muxSplitInput(MUXs[i].width, MUXs[i].MUX_inA.size(), MUXs[i].MUX_inA, MUXs, this->regs)
            << "output => " << MUXs[i].nameA << "_IN);\n\n";
        }
    }



    out << "end " << filename << "_arch;";

    out.close();
}
