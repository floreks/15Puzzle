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
    void explore(Node3 *n);
    int *tab;
public:
    Graph();
    void create(int tab[9]);
    vector<Node3*> getPath();
};

#endif // GRAPH_H
