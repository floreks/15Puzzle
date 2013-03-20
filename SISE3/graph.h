#ifndef GRAPH_H
#define GRAPH_H

#include "node.h"

typedef vector<element> (*fPtr)(int, vector<element>&);

class Graph
{
private:
    vector<Node>nodes;
    Node end;
    fPtr operators[4];
    vector<Node> generate(Node n);

public:
    Graph();
    void run();
    bool exist(Node n);
};

#endif // GRAPH_H
