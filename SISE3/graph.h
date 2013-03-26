#ifndef GRAPH_H
#define GRAPH_H

#include "Node3.h"

typedef void (*fPtr)(Node3 *, vector<Node3> &);

class Graph
{
private:
    vector<Node3> nodes;
    Node3 endNode;
    fPtr operators[4];
    vector<Node3> generate(Node3 n);
public:
    Graph();
    void create();
};

#endif // GRAPH_H
