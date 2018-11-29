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

vector<MUX> reg_sharing(vector<int*> reg_cliques){

	vector<MUX> MUXs;
	for(auto it: reg_cliques){
		// MUXs.push_back(MUX(it.size()));
		size(it);
	}


} 


vector<MUX> FU_sharing(vector<resource_type> op_cliques){
	
} 

