//
//  DCS.h
//  DCS Datapath
//
//  Created by Chad Cooper on 11/21/18.
//  Copyright © 2018 Chad Cooper. All rights reserved.
//

#ifndef DCS_h
#define DCS_h

#include <string>
#include <vector>
#include <array>
#include <iostream>
#include <fstream>
#include <sstream>
#include <set>


/*------------------------------------------------------------------------------
| Register structure definiton. A register has a specific bit width, a type
|
|
------------------------------------------------------------------------------*/
enum op_type {ADD,SUB,MULT,DIV};
enum reg_type {input, intermediate, output};


struct reg {

    int width; // Not currently used, but it's only 2 bytes, so why not store it?
    reg_type type; // register type: 0 = input, 1 = intermediate, 2 = output
    std::string name;
    std::array<int, 2> lifetime; //  lifetime[0] = first time written to, lifetime[1] = last time read.
    int real_lifetime;
    bool valid;
};

struct op
{


    std::array<reg*, 2> input_reg; // input register pointers for operation
    reg* output_reg;  // output register pointer for operation
    int start_time; // operation start time
    int delay; // operation delay
    op_type type; // operation type: 0 = ADD, 1 = SUB, 2 = MULT, 3 = DIV
    std::string name;
    int width;

    op(){
        start_time = -1;
    }

};

// Operation: op1, time: 1
// Operation: op2, time: 1
// Operation: op3, time: 2
// Operation: op4, time: 2
// Operation: op5, time: 3
// Operation: op6, time: 3
// Operation: op7, time: 4
//
// t0: 1
// t1: 1
// t2: 1
// t3: 0
// t4: 1
// t5: 1

class Graph {

public:

    std::vector<op> V;
    std::vector<reg> E;
    int**  adj;

    void buildGraph(std::string filename, bool print);

    void setVertices(std::vector<op>& V); // Assign V
    void setEdges(std::vector<reg>& E); // Assign E

    void addVertex(op& v); // Add new vertex
    void addEdge(reg& E); // Add new edge
    void buildAdjMatrix(std::vector<op> V, std::vector<reg> E); // Build adjacency matrix

    void printVertices();
    void printEdges();
};

std::vector<int> LIST_L(Graph& G,  std::array<int, 4>& a);

reg* regByName(std::vector<reg>& regs, std::string reg_name);

void printReg(reg& reg);
void printOp(op& op);

void printSet(std::set<op*>&);

bool opReady(op&);

void eraseMultiple(std::set<op*>& set, std::set<op*>& positions);

#endif /* DCS_h */
