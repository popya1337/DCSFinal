#include "Datapath.h"
using namespace std;

int main(int argc, char const *argv[])
{

    // Make a compatibility graph
    Graph comp;
    string filename = "lattice";
    comp.buildGraph(filename +".aif", true);

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
    vector<MUX> FU_muxs;
    FU_muxs = FU_sharing(bindFunctionalUnit(comp.V), comp.V);

    setRegLifeTime(comp.V, comp.E);

    vector<MUX> reg_muxs;
    reg_muxs = reg_sharing(bindRegister(comp.E), comp.E);
    Datapath dp(comp.V, comp.E, FU_muxs, reg_muxs);
    dp.printToVHDL(filename);

 //    cout << "MAIN\n" << endl;
 //    for(int i = 0; i<comp.E.size(); i++){
	// 	cout << comp.E[i].name << ": "<<comp.E[i].lifetime[1] << " - " << comp.E[i].lifetime[0];
	// 	cout << "= " << comp.E[i].real_lifetime << endl;

	// }
 //    cout << "\n\n";



//    cout << endl << endl << "Printing vertices in graph..." << endl;
//    comp.printVertices();

    return 0;
} // end main
