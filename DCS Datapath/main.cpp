//
//  main.cpp
//  DCS Datapath
//
//  Created by Chad Cooper on 11/21/18.
//  Copyright © 2018 Chad Cooper. All rights reserved.
//

#include "allocate_and_bind.h"
using namespace std;

int main(int argc, char const *argv[])
{

    // Make a compatibility graph
    Graph comp;

    comp.buildGraph("toyexample.aif", true);

    cout << endl << endl << "Printing vertices in graph..." << endl;
    comp.printVertices();

    cout << endl << "Printing edges in graph..." << endl;
    comp.printEdges();

    vector<int> t;

    array<int, 4> resource_list = {2,2,2,2};
    try{
        t = LIST_L(comp, resource_list);
    } catch (const std::invalid_argument& e) {
        cout << e.what();
        return 1;
    }

    cout << "Printing schedule..." << endl;

    for (int i = 0; i < t.size(); i++){
        cout << "Operation: " << comp.V[i].name << ", time: " << t[i] << endl;
    }

    bindFunctionalUnit(comp.V);
    setRegLifeTime(comp.V, comp.E);
 //    cout << "MAIN\n" << endl;
 //    for(int i = 0; i<comp.E.size(); i++){
	// 	cout << comp.E[i].name << ": "<<comp.E[i].lifetime[1] << " - " << comp.E[i].lifetime[0];
	// 	cout << "= " << comp.E[i].real_lifetime << endl;

	// }
 //    cout << "\n\n";
    bindRegister(comp.E);
//    cout << endl << endl << "Printing vertices in graph..." << endl;
//    comp.printVertices();

    return 0;
} // end main
