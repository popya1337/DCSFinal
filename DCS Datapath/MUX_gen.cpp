// Register Sharingfor each register R do
//Let n be the number of carriers mapped to R
// 	Generate a multiplexor M with n inputs
// end for

// Functional Unit Sharing
// for each FU do
// 	Let n be the number of operations bound to FU
// 	for each input of FU do
// 		Create a multiplexor with n inputs
// 	end for
// end for


#include "MUX_gen.h"

using namespace std;

vector<MUX> reg_sharing(vector<vector<int>> reg_cliques, vector<reg> regs){

	vector<MUX> MUXs;
	for(int i = 0; i < reg_cliques.size(); i++){
		cout << "NEW REG MUX" << endl;
		MUXs.push_back(MUX(reg_cliques[i].size()));
		MUXs[i].type = REG;
        for(int j = 0; j < reg_cliques[i].size(); j++){
            MUXs[i].MUX_inA[j] = regs[reg_cliques[i][j]].name;
			MUXs[i].nameA = "REG_" + to_string(i);
			MUXs[i].MUX_out[j] = regs[reg_cliques[i][j]].name;
			cout << MUXs[i].nameA  << endl;

		}
	}

    return MUXs;
}



vector<MUX> FU_sharing(vector<resource_type> op_cliques, vector<op> ops){

	vector<MUX> MUXs;
	int tracker = 0;
	int tracker2 = 0;
	for(int i = 0; i < 4; i++){

		for(int j = 0; j < op_cliques[i].cliques.size(); j++){
			MUXs.push_back(MUX(op_cliques[i].cliques[j].size()));

			switch(i){
				case 0:
				MUXs[tracker].type = ADD;
				tracker++;
				cout << "Case ADD" << endl;
				break;
				case 1:
				MUXs[tracker].type = SUB;
				tracker++;
				cout << "Case SUB" << endl;
				break;
				case 2:
				MUXs[tracker].type = MULT;
				tracker++;
				cout << "Case MULT" << endl;
				break;
				default:
				MUXs[tracker].type = DIV;
				tracker++;
				cout << "Case DIV" << endl;
			}
			vector<op> curr_type;
			for(int k = 0; k < ops.size(); k++){
				if(ops[k].type == i){
					curr_type.push_back(ops[k]);
				}
			}
	        for(int k = 0; k < op_cliques[i].cliques[j].size(); k++){
	            MUXs[tracker2].MUX_inA[k] = curr_type[op_cliques[i].cliques[j][k]].input_reg[0]->name; 
				MUXs[tracker2].MUX_inB[k] = curr_type[op_cliques[i].cliques[j][k]].input_reg[1]->name;
				MUXs[tracker2].MUX_out[k] = curr_type[op_cliques[i].cliques[j][k]].input_reg[0]->name; 
				MUXs[tracker2].nameA = "FU_" + to_string(tracker2);
				cout << MUXs[tracker2].nameA  << endl;
				MUXs[tracker2].nameB = "FU_" + to_string(tracker2);
				cout << MUXs[tracker2].nameB  << endl;
	        }
			tracker2++;
		}

	}
	return MUXs;
}
