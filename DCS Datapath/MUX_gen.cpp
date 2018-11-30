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

int size(int* arr){
	for(int i = 0; i < 20; i++){
		cout << arr[i] << endl;
	}
}

vector<MUX> reg_sharing(vector<vector<int>> reg_cliques){

	vector<MUX> MUXs;
	for(int i = 0; i < reg_cliques.size(); i++){
		MUXs.push_back(MUX(reg_cliques[i].size()));
        for(int j = 0; j < reg_cliques[i].size(); j++){
            
            MUXs[i].MUX_in[j] = reg_cliques[i][j];
            cout << MUXs[i].MUX_in[j];
        }
        cout << "\n";
	}
    return MUXs;
}

vector<MUX> FU_sharing(vector<resource_type> op_cliques){

	vector<MUX> MUXs;

	for(int i = 0; i < 4; i++){

		for(int j = 0; j < op_cliques[i].cliques.size(); j++){

			MUXs.push_back(MUX(op_cliques[i].cliques[j].size()));

			switch(i){
				case 0:
				MUXs[i].type = ADD;
				break;
				case 1:
				MUXs[i].type = SUB;
				break;
				case 2:
				MUXs[i].type = MULT;
				break;
				default:
				MUXs[i].type = DIV;
			}

	        for(int k = 0; k < op_cliques[i].cliques[j].size(); k++){
	            
	            MUXs[j].MUX_in[k] = op_cliques[i].cliques[j][k];
	            cout << MUXs[j].MUX_in[k];
	        }
	        cout << "\n";
		}
	}
}
