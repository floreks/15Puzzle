#ifndef OPERATORS_H
#define OPERATORS_H

#include <vector>
#include <cmath>
#include <Node3.h>

using namespace std;

bool exists(Node3 node, vector<Node3*> nodes)
{
    for(int i=0; i<nodes.size(); i++)
    {
        if(node.equals(nodes[i])) return true;
    }
    return false;
}

Node3 *getNode(Node3 *n, vector<Node3*>&nodes)
{
    for(Node3 *i : nodes)
    {
        if(i->equals(n))
            return i;
    }
    return NULL;
}

bool moveUp(Node3 &node, vector<Node3*>&nodes)
{
    int zeroIndex = node.getZeroIndex();
    if(zeroIndex > 5)
        return 0;

    Node3 *n = new Node3(node.getValuesTab());
    int index = zeroIndex + 3;
    int value = node.getValue(index);
    n->setValue(value,zeroIndex);
    n->setValue(0,index);

    if(!exists(*n,nodes))
    {
        nodes.push_back(n);
        node.addSuccessor(n);
        n->addPredecessor(&node);
    }
    else
    {
        Node3 *n2 = getNode(n,nodes);
        n2->addPredecessor(&node);
        node.addSuccessor(n2);
        delete n;
    }
    return 1;
}

bool moveDown(Node3 &node, vector<Node3*>&nodes)
{
    int zeroIndex = node.getZeroIndex();
    if(zeroIndex < 3)
        return 0;

    Node3 *n = new Node3(node.getValuesTab());
    int index = zeroIndex - 3;
    int value = node.getValue(index);
    n->setValue(value,zeroIndex);
    n->setValue(0,index);

    if(!exists(*n,nodes))
    {
        nodes.push_back(n);
        node.addSuccessor(n);
        n->addPredecessor(&node);
    }
    else
    {
        Node3 *n2 = getNode(n,nodes);
        n2->addPredecessor(&node);
        node.addSuccessor(n2);
        delete n;
    }
    return 1;
}

bool moveRight(Node3 &node, vector<Node3*>&nodes)
{
    int zeroIndex = node.getZeroIndex();
    if(zeroIndex % 3 == 0)
        return 0;

    Node3 *n = new Node3(node.getValuesTab());
    int index = zeroIndex - 1;
    int value = node.getValue(index);
    n->setValue(value,zeroIndex);
    n->setValue(0,index);

    if(!exists(*n,nodes))
    {
        nodes.push_back(n);
        node.addSuccessor(n);
        n->addPredecessor(&node);
    }
    else
    {
        Node3 *n2 = getNode(n,nodes);
        n2->addPredecessor(&node);
        node.addSuccessor(n2);
        delete n;
    }
    return 1;
}

bool moveLeft(Node3 &node, vector<Node3*>&nodes)
{
    int zeroIndex = node.getZeroIndex();
    if(zeroIndex % 3 == 2)
        return 0;

    Node3 *n = new Node3(node.getValuesTab());
    int index = zeroIndex + 1;
    int value = node.getValue(index);
    n->setValue(value,zeroIndex);
    n->setValue(0,index);

    if(!exists(*n,nodes))
    {
        nodes.push_back(n);
        node.addSuccessor(n);
        n->addPredecessor(&node);
    }
    else
    {
        Node3 *n2 = getNode(n,nodes);
        n2->addPredecessor(&node);
        node.addSuccessor(n2);
        delete n;
    }
    return 1;
}

#endif // OPERATORS_H
