#include "graph.h"
#include "Operators.h"
#include "Node3.h"

Graph::Graph(QObject *parent) : QObject(parent)
{
    vector<int> endValues;
    for(int i=1; i<9; i++) endValues.push_back(i);
    endValues.push_back(0);
    endNode = new Node3();
    endNode->setValues(endValues);
}

void Graph::create(int tab[9])
{
    startNode = new Node3(tab);
    nodes.push_back(startNode);

    bool end = false;

    do
    {
        for(int i=0;i<nodes.size();i++)
        {
            emit update(nodes.size());
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

vector<Node3*> Graph::getPath()
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

    vector<Node3*> ret;

    for(int i=vec.size()-1;i>=0;i--)
    {
        for(Node3 *j : nodes)
            if(vec[i] == j->getNr())
            {
                ret.push_back(j);
                break;
            }
    }
    return ret;
}
