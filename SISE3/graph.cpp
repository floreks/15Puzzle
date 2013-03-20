#include "graph.h"
#include "Operators.h"

Graph::Graph()
{
    end.setNode(init(9));
    operators[0] = &up;
    operators[1] = &down;
    operators[2] = &left;
    operators[3] = &right;
}

void Graph::run()
{

}

vector<Node> Graph::generate(Node n)
{
    int pos;
    for(int i=0;i<end.getNode().size();i++)
    {
        if(n.getNode()[i] == 0)
        {
            pos = i;
            break;
        }
    }
    vector<Node>result;
    Node tmp;
    for(int i=0;i<4;i++)
    {
        tmp.setNode(operators[i]();
    }
}

bool Graph::exist(Node n)
{
    for(int i=0;i<nodes.size();i++)
    {
        if(nodes[i].equals(n))
            return 1;
    }
    return 0;
}
