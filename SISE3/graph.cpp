#include "graph.h"
#include "Operators.h"
#include "Node3.h"

Graph::Graph()
{
    // tworzenie wezla koncowego
    vector<int> endValues;
    for(int i=1; i<9; i++) endValues.push_back(i);
    endValues.push_back(0);
    endNode = new Node3();
    endNode->setValues(endValues);

    int tab[] = {4,1,3,0,2,5,7,8,6};
    startNode = new Node3(tab);


    // dodanie wezla koncowego do wektora wierzcholkow
    nodes.push_back(startNode);

    // ustawianie operatorow
}

void Graph::create()
{
    bool end = false;

    do
    {
        for(int i=0;i<nodes.size();i++)
        {
            if(nodes[i]->getVisited()) continue;

            moveUp(*nodes[i],nodes);
            if(nodes.back()->equals(endNode))
            {
                end = true;
                break;
            }
            moveDown(*nodes[i],nodes);
            if(nodes.back()->equals(endNode))
            {
                end = true;
                break;
            }
            moveLeft(*nodes[i],nodes);
            if(nodes.back()->equals(endNode))
            {
                end = true;
                break;
            }
            moveRight(*nodes[i],nodes);
            if(nodes.back()->equals(endNode))
            {
                end = true;
                break;
            }

            nodes[i]->setVisited(true);
        }
    } while(!end);

}

vector<Node3 *> Graph::generate(Node3 n)
{

}

void Graph::explore(Node3 *n) // DFS
{
    n->setVisited(1);
    for(Node3 *i : n->getSuccessors())
    {
        if(!i->getVisited())
        {
            tab[i->getNr()] = n->getNr();
            explore(i);
        }
    }
}

void Graph::printPath()
{
    int j = 0;
    for(Node3 *i : nodes)
    {
        i->setVisited(0);
        i->setNr(j++);
    }
    tab = new int[nodes.size()];
    for(int i=0;i<nodes.size();i++)
        tab[i] = -1;
    explore(startNode);
    endNode = getNode(endNode,nodes);

    int cur = endNode->getNr();
    vector<int>vec;
    while(cur != -1)
    {
        vec.push_back(cur);
        cur = tab[cur];
    }

    for(int i=vec.size()-1;i>=0;i--)
    {
        for(Node3 *j : nodes)
            if(vec[i] == j->getNr())
            {
                cout << j << endl << endl;
                break;
            }
    }

//    Node3* cur;
//    vector<Node3*> finalPath;
//    cur = startNode;
//    finalPath.push_back(cur);
//    while(!cur->equals(endNode))
//    {
//        cur = path[cur->getNr()];
//        finalPath.push_back(cur);
//    }
//    cout << finalPath.size() << endl;
//    for(int i=finalPath.size()-1;i>=0;i--)
//        cout << finalPath[i] << endl << endl;
//    cout << endl;
}
