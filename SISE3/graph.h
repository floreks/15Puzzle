#ifndef GRAPH_H
#define GRAPH_H

#include "Node3.h"

typedef void (*fPtr)(Node3 & , vector<Node3*> &);

class Graph
{
private:
    vector<Node3*> nodes;
    Node3 *endNode;
    Node3 *startNode;
    fPtr operators[4];
    vector<Node3*> generate(Node3 n);
    void explore(Node3 *n);
    int *tab;
public:
    Graph();
    void create();
    void printPath();
};

#endif // GRAPH_H
