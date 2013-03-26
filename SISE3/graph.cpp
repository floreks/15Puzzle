#include "graph.h"
#include "Operators.h"
#include "Node3.h"

Graph::Graph()
{
    //tworzenie wezla koncowego
    vector<int> endValues;
    for(int i=1; i<9; i++) endValues.push_back(i);
    endNode.setValues(endValues);

    //ustawianie operatorow
    operators[0] = &tryMoveUp;
    operators[1] = &tryMoveDown;
    operators[2] = &tryMoveLeft;
    operators[3] = &tryMoveRight;
}

void Graph::create()
{
    cout << endNode;
}

vector<Node3> Graph::generate(Node3 n)
{

}
