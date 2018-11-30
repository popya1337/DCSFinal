#include "DCS.h"

reg* regByName(std::vector<reg>& regs, std::string reg_name){

    for(int i= 0; i < regs.size(); i++){
        if (regs[i].name == reg_name) {
            return &regs[i];
        }
    }

    return nullptr;
}

void printReg(reg& reg){
    std::cout << "name: " << reg.name << std::endl;
    std::cout << "type: " <<  reg.type << std::endl;
    std::cout << "width: " <<  reg.width << std::endl;
    std::cout << "valid: " << reg.valid << std::endl;
    std::cout << "lifetime: " << reg.lifetime[1] -  reg.lifetime[0] << std::endl;
}

void printOp(op& op){
    std::cout << "name: " << op.name << std::endl;
    std::cout << "type: " <<  op.type << std::endl;
    std::cout << "width: " <<  op.width << std::endl;
    std::cout << "start time: " << op.start_time << std::endl;
    std::cout << "inputs: " << op.input_reg[0]->name << ", " << op.input_reg[1]->name << std::endl;
    std::cout << "output(s): " << op.output_reg->name << std::endl;
}


// MARK: Graph methods
// Assign V
void Graph::setVertices(std::vector<op>& V) {
    this->V = V;
}

// Assign E
void Graph::setEdges(std::vector<reg>& E) {
    this->E = E;
}

// Add new vertex
void Graph::addVertex(op& v){
    this->V.push_back(v);
}

// Add new edge
void Graph::addEdge(reg& E){
    this->E.push_back(E);
}

//void buildAdjMatrix(std::vector<op> V, std::vector<reg> E); // Build adjacency matrix


void Graph::printVertices(){
    for (op V : this->V) {
        printOp(V);
        std::cout << std::endl;
    }
}

void Graph::printEdges(){
    for (reg E : this->E) {
        printReg(E);
        std::cout << std::endl;
    }
}

void Graph::buildGraph(std::string filename, bool print){

    // Establish delays for each resource type:
    std::array<int, 4> delay = {1, 1, 1, 1};

    std::string discard, line, reg_name, op_name, op_type, in1, in2, out;
    int width;

    std::ifstream graphFile (filename);
    std::istringstream iss;

    getline(graphFile, line); // INPUTS

    if (print) (std::cout << line << std::endl);

    iss.str(line); // Extract information from line

    iss >> discard; // throwaway 'inputs'

    while (iss >> reg_name >> width){
        reg temp_reg;
        temp_reg.name = reg_name;
        temp_reg.type = input;
        temp_reg.width = width;
        temp_reg.valid = true;
        temp_reg.lifetime[0] = 0;
        temp_reg.lifetime[1] = 0;
        this->addEdge(temp_reg);
    }

    getline(graphFile, line); // OUTPUTS
    if (print) std::cout << line << std::endl;
    iss.clear();
    iss.str(line);

    iss >> discard; // throw away 'outputs'

    while (iss >> reg_name >> width){
        reg temp_reg;
        temp_reg.name = reg_name;
        temp_reg.type = output;
        temp_reg.width = width;
        temp_reg.valid = false;
        temp_reg.lifetime[0] = 0;
        temp_reg.lifetime[1] = 0;
        this->addEdge(temp_reg);
    }

    getline(graphFile, line); // Intermediate registers
    if (print) std::cout << line << std::endl;

    iss.clear();
    iss.str(line);

    iss >> discard; // throw away 'regs'

    while (iss >> reg_name >> width) {
        reg temp_reg;
        temp_reg.name = reg_name;
        temp_reg.type = intermediate;
        temp_reg.width = width;
        temp_reg.valid = false;
        temp_reg.lifetime[0] = 0;
        temp_reg.lifetime[1] = 0;
        this->addEdge(temp_reg);
    }

    getline(graphFile, line);
    while(line != "end"){

        iss.clear();
        iss.str(line);

        if (print) std::cout << iss.str() << std::endl;

        while(iss >> op_name >> op_type >> width >> in1 >> in2 >> out){
            op temp_op;
            temp_op.name = op_name;
            temp_op.width = width;

            switch (op_type[0]) {
                case 'A':
                    temp_op.type = ADD;
                    temp_op.delay = delay[temp_op.type];
                    break;
                case 'S':
                    temp_op.type = SUB;
                    temp_op.delay = delay[temp_op.type];
                    break;
                case 'M':
                    temp_op.type = MULT;
                    temp_op.delay = delay[temp_op.type];
                    break;
                case 'D':
                    temp_op.type = DIV;
                    temp_op.delay = delay[temp_op.type];
                    break;
            }

            temp_op.input_reg[0] = regByName(this->E, in1);
            temp_op.input_reg[1] = regByName(this->E, in2);
            temp_op.output_reg = regByName(this->E, out);
            this->addVertex(temp_op);
        }

        getline(graphFile, line);

        // If line contains end, make sure it is end
        if(line.find("end") != std::string::npos){
            line = "end";
        }

    }

    if (print) std::cout << "end" << std::endl;
    graphFile.close(); // graph read
}

//MARK: Resource constrained scheduling algorithm

std::vector<int> LIST_L(Graph& G,  std::array<int, 4>& a) {

/* PSEUDOCODE
LIST_L( G(V, E), a) {
    l = 1;
    repeat {
        for each resource type k = 1, 2, ..., nres {
            Determine ready operations U_(l,k);
            Determine unfinished operations T_(l,k);
            Select S_k subset U_(l,k) vertices, s.t. |S_k| + |T_(l,k)| ≤ a_k;
            Schedule the S_k operations at step l;
        }
        l=l+1;
    }
    until (v_n is scheduled) ;
    return (t);
 }
*/

    std::array<int, 4> nec = {0, 0, 0, 0};
    for(auto it : G.V){
        nec[it.type]++;
    }

    for(int i = 0; i < nec.size(); i++){
        if (nec[i] > 0 && a[i] < 1){
            throw std::invalid_argument("There must be at least one of each necessary functional unit.\n");
        }
    }

    std::array<int,4> avail_res(a);

    std::set<op*> unscheduled;
    std::set<op*> ready;
    std::set<op*> unfinished;
    std::set<op*> erase;


    // Add pointer to all vertices to set of unscheduled operations
    for(int i = 0; i < G.V.size(); i++){
        unscheduled.insert(&G.V[i]);
    }


    int l = 1;

    do {

        // Remove finished operations
        for(std::set<op*>::iterator set_it = unfinished.begin(); set_it != unfinished.end(); ++set_it){
            if((**set_it).start_time + (**set_it).delay == l){
                // Release the resource
                avail_res[(**set_it).type]++;

                // Set output register to valid
                (**set_it).output_reg->valid = true;

                // Remove from unfinished
                erase.insert(*set_it);
            }

        }
        eraseMultiple(unfinished, erase);

        // Determine ready operations
        // An operation is ready if its input registers is valid
        for(std::set<op*>::iterator set_it = unscheduled.begin();  set_it != unscheduled.end(); set_it++){

            // If operation is ready, add it to ready set.
            if(opReady(**set_it)) {
                ready.insert(*set_it);
            }
        } // end determine ready operations

        // For each resource type...
        for(int res_type = 0; res_type < avail_res.size(); res_type++){

            //std::cout << "Resource type: " << res_type << std::endl;

            // Check running operations for this resource
            int in_use = 0;
            for(std::set<op*>::iterator set_it = unfinished.begin(); set_it != unfinished.end(); set_it++ ){
                // If unfinished operations of this type are running, count how many
                if((**set_it).type == res_type){
                    in_use++;
                }
            }

            // Adjust the number of available resources of this type
            avail_res[res_type] = a[res_type] - in_use;

            // Schedule operations
            for(std::set<op*>::iterator set_it = ready.begin(); set_it != ready.end(); set_it++){

                // If the operation uses this resource, and there are available resources of this type,
                if((**set_it).type == res_type && avail_res[res_type] > 0){
                    (**set_it).start_time = l;
                    unfinished.insert(*set_it); // set it

                    // Reduce the available resources of this type
                    avail_res[res_type]--;

                    // This operation has now been scheduled, so
                    // remove from ready set and unscheduled set
                    erase.insert(*set_it);
                    unscheduled.erase(unscheduled.find(*set_it));
                }


            }

            // Erase from ready set
            eraseMultiple(ready, erase);


        } // end for each type of resource

        // Increment the time step, l
        l = l + 1;

    } while (!unscheduled.empty());

    std::cout << "\nAll operations scheduled!\n" << std::endl;

    std::vector<int> t;
    for(auto it:G.V){
        t.push_back(it.start_time);
    }

    return t;
}


bool opReady(op& op){
    return op.input_reg[0]->valid && op.input_reg[1]->valid;
}


void printSet(std::set<op*>& s){
    for(auto it:s){
        printOp(*it);
        std::cout << std::endl;
    }
}

void eraseMultiple(std::set<op*>& set, std::set<op*>& positions ){

    for(auto it:positions){
        set.erase(set.find(it));
    }

    positions.clear();

}
