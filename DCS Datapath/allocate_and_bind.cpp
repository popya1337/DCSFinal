#include "DCS.h"
#include "../clique_partition/clique_partition.c"
#include "allocate_and_bind.h"
using namespace std;

void bindFunctionalUnit(vector<op> op){

  array<int, 4> counter{0};
  for(int i = 0; i < op.size(); i++){
      //operation type: 0 = ADD, 1 = SUB, 2 = MULT, 3 = DIV
      switch(op[i].type){
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
        if(op[k].type == op[l].type && op[k].start_time != op[l].start_time){
          matrix[k][l] = 1;
        }
        else matrix[k][l] = 0;
      }
    }
    clique_partition(matrix,counter[i]);
  }
}
