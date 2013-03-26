#include "graph.h"
#include "Operators.h"
#include "Node3.h"

Graph::Graph()
{
    // tworzenie wezla koncowego
    vector<int> endValues;
    for(int i=1; i<9; i++) endValues.push_back(i);
    endValues.push_back(0);
    endNode.setValues(endValues);

    // dodanie wezla koncowego do wektora wierzcholkow
    nodes.push_back(endNode);

    // ustawianie operatorow
    operators[0] = &tryMoveUp;
    operators[1] = &tryMoveDown;
    operators[2] = &tryMoveLeft;
    operators[3] = &tryMoveRight;
}

void Graph::create()
{
    vector<Node3>::iterator it;
    bool end = false;

    do
    {
        for(it=nodes.begin(); it<nodes.end(); it++)
        {
            if((*it).getVisited()) continue;

            tryMoveUp(&(*it),nodes);
            //tryMoveDown(&(*it),nodes);
            tryMoveLeft(&(*it),nodes);
            //tryMoveRight(&(*it),nodes);

            //if(nodes.size()==3)
                end = true;

            (*it).setVisited(true);
        }
    } while(!end);

    for(int i=0; i<nodes.size(); i++) cout << nodes[i] << endl << endl;
}

vector<Node3> Graph::generate(Node3 n)
{

}
