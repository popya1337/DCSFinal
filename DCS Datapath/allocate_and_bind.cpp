#include "DCS.h"
#include "../clique_partition/clique_partition.c"
#include "allocate_and_bind.h"
#include <typeinfo>
using namespace std;

vector<resource_type> bindFunctionalUnit(vector<op>& ops){
	vector<resource_type> res_cliques(4);
	array<int, 4> counter{0};
	array<vector<int>, 4> op_tracker;
	for(int i = 0; i < ops.size(); i++){
	//opseration type: 0 = ADD, 1 = SUB, 2 = MULT, 3 = DIV
		switch(ops[i].type){
			case 0:
			counter[0]++;
			op_tracker[0].push_back(i);
			break;
			case 1:
			counter[1]++;
			op_tracker[1].push_back(i);
			break;
			case 2:
			counter[2]++;
			op_tracker[2].push_back(i);
			break;
			default:
			counter[3]++;
			op_tracker[3].push_back(i);
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
				if(ops[op_tracker[i][k]].type == ops[op_tracker[i][l]].type && ops[op_tracker[i][k]].start_time != ops[op_tracker[i][l]].start_time){
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
	for(int i = 0; i<regs.size(); i++){

		regs[i].real_lifetime = regs[i].lifetime[1] - regs[i].lifetime[0];
		cout << regs[i].name << ": "<<regs[i].lifetime[1] << " - " << regs[i].lifetime[0];
		cout << "= " << regs[i].real_lifetime << endl;

	}
	//int * matrix[counter[i]];

}

void setRegLifeTime(vector<op> ops, vector<reg> &regs){
	for(int i = 0; i < ops.size(); i++){
			ops[i].output_reg->lifetime[0] = ops[i].start_time;
			//cout << ops[i].output_reg -> name <<": " <<  ops[i].output_reg->lifetime[0] << endl;
	}

	for(int i = 0; i < ops.size(); i++){
		ops[i].output_reg->lifetime[1] = 0;
		for(int j = i; j < ops.size(); j++){
			if(ops[i].output_reg->name == ops[j].input_reg[0] -> name && ops[j].start_time > ops[i].output_reg-> lifetime[1]){
			//	cout << "Match found:" << ops[i].output_reg->name << " on loop: " << i << j <<endl;
			//	cout << "Setting " << 	ops[i].input_reg[0]->name << " = " << ops[j].start_time << endl;
				ops[j].input_reg[0]->lifetime[1] = ops[j].start_time;
			}
			if(ops[i].output_reg->name == ops[j].input_reg[1] -> name &&  ops[j].start_time > ops[i].output_reg -> lifetime[1]){
				ops[j].input_reg[1]->lifetime[1] = ops[j].start_time;
			}

		}
	}

	int largest_TS = 0;

	for(int i = 0; i < ops.size(); i++){
		if(largest_TS < ops[i].start_time){
			largest_TS = ops[i].start_time;
		}
	}

	for(int i =0 ; i < ops.size(); i++){
		if(ops[i].input_reg[0] -> type == input && ops[i].start_time > ops[i].input_reg[0] -> lifetime[1] ){
			ops[i].input_reg[0] -> lifetime[1] = ops[i].start_time;
		}
		if(ops[i].input_reg[1] -> type == input && ops[i].start_time > ops[i].input_reg[1] -> lifetime[1] ){
			ops[i].input_reg[1] -> lifetime[1] = ops[i].start_time;
		}
	}

	for(int i = 0; i < regs.size(); i++){
		if(regs[i].type == output){
			regs[i].lifetime[1] = largest_TS;
			cout << regs[i].name << ": " <<regs[i].lifetime[1] << endl;
		}
	}
}
