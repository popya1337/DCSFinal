#include "DCS.h"
#include "../clique_partition/clique_partition.c"
#include "allocate_and_bind.h"
#include <typeinfo>
using namespace std;

vector<resource_type> bindFunctionalUnit(vector<op> ops){
	vector<resource_type> res_cliques(4);
	array<int, 4> counter{0};
	for(int i = 0; i < ops.size(); i++){
	//opseration type: 0 = ADD, 1 = SUB, 2 = MULT, 3 = DIV
		switch(ops[i].type){
			case 0:
			counter[0]++;
			break;
			case 1:
			counter[1]++;
			break;
			case 2:
			counter[2]++;
			break;
			default:
			counter[3]++;
		}
	}
	for(int i = 0; i < counter.size(); i++){
		cout << counter[i] << endl;
	}

	for(int i = 0; i < 4; i++){
		int * matrix[counter[i]];
		for(int j = 0; j < counter[i]; j++){
			matrix[j] = new int[counter[i]];
		}
		for(int k = 0; k < counter[i]; k++){
			for(int l = 0; l < counter[i]; l++){
				if(ops[k].type == ops[l].type && ops[k].start_time != ops[l].start_time){
					matrix[k][l] = 1;
				}
				else matrix[k][l] = 0;
			}
		}
		clique_partition(matrix,counter[i]);

		res_cliques[i].type = static_cast<op_type>(i);

		for(int y = 0; clique_set[y].size != UNKNOWN; y++){
			res_cliques[i].cliques.push_back(clique_set[y].members);

		}

		for(int y = 0; y < res_cliques[i].cliques.size(); y++){
				cout << "\n\nNEW CLIQUE:" << endl;

			for(int z = 0; clique_set[y].members[z] != UNKNOWN ; z++){

				cout << res_cliques[i].cliques[y][z] << endl;
			}
		}
	}
	return res_cliques;
}


void bindRegister(vector<reg> regs){
	for(auto it : regs){
		if(it.type == intermediate){
		it.real_lifetime = it.lifetime[1] - it.lifetime[0];
		cout << it.name << ": " << it.real_lifetime << endl;
	}
	}

	// for(int i = 0; i < 4; i++){
	// 	int * matrix[counter[i]];
	// 	for(int j = 0; j < counter[i]; j++){
	// 		matrix[j] = new int[counter[i]];
	// 	}
	// 	for(int k = 0; k < counter[i]; k++){
	// 		for(int l = 0; l < counter[i]; l++){
	// 			if(ops[k].type == ops[l].type && ops[k].start_time != ops[l].start_time){
	// 				matrix[k][l] = 1;
	// 			}
	// 			else matrix[k][l] = 0;
	// 		}
	// 	}
	// 	clique_partition(matrix,counter[i]);

	// }
}

void setRegLifeTime(vector<op> ops){
	for(int i = 0; i < ops.size(); i++){
			ops[i].output_reg->lifetime[0] = ops[i].start_time;
			cout << ops[i].output_reg->lifetime[0] << endl;
	}
	for(int i = 0; i < ops.size(); i++){
		ops[i].output_reg->lifetime[1] = 0;
		for(int j = i; j < ops.size(); j++){
			if(ops[i].output_reg->name == ops[j].input_reg[0] -> name){
			//	cout << "Match found:" << ops[i].output_reg->name << " on loop: " << i << j <<endl;
			//	cout << "Setting " << 	ops[i].input_reg[0]->name << " = " << ops[j].start_time << endl;
				ops[j].input_reg[0]->lifetime[1] = ops[j].start_time;
			}
			if(ops[i].output_reg->name == ops[j].input_reg[1] -> name){
				ops[j].input_reg[1]->lifetime[1] = ops[j].start_time;
			}
		}
	}

	// for(int i = 0; i < ops.size(); i++){
	//  		cout << ops[i].output_reg->lifetime[1] << endl;
	//  }
}
