#ifndef OPERATORS_H
#define OPERATORS_H

#include <vector>
#include <cmath>
#include <Node3.h>

using namespace std;

bool exists(Node3 node, vector<Node3> nodes)
{
    for(int i=0; i<nodes.size(); i++)
    {
        if(node.equals(nodes[i])) return true;
    }
    return false;
}

void tryMoveUp(Node3 *currentNode, vector<Node3> &nodes)
{
    // wczytuje i sprawdzam pozycje pustego elementu
    int zeroIndex = currentNode->getZeroIndex();
    if(zeroIndex>8 || zeroIndex<0) return;

    // obliczam i sprawdzam pozycje docelowa
    int targetIndex = zeroIndex - 3;
    if(targetIndex<0) return;

    // tworze nowy wezel ze zmienionymi na bazie obecnego
    Node3 newNode;
    newNode.setValues(currentNode->getValuesVect());

    // zamieniam miejscami pusty element z elementem docelowym (nad nim)
    newNode.setValue(currentNode->getValue(targetIndex),zeroIndex);
    newNode.setValue(0,targetIndex);

    // jesli utworzony wezel jest niepowtarzalny
    if(!exists(newNode,nodes))
    {
        // jako poprzednik nowego ustawiamy obecny
        //newNode.addPredecessor(currentNode);

        // i nawzajem
        //currentNode->addSuccessor(&newNode);

        // dodajemy nowy wezel do listy wezlow
        nodes.push_back(newNode);
    }
    else return;
}

void tryMoveDown(Node3 *currentNode, vector<Node3> &nodes)
{
    int zeroIndex = currentNode->getZeroIndex();
    if(zeroIndex>8 || zeroIndex<0) return;

    int targetIndex = zeroIndex + 3;
    if(targetIndex>8) return;

    Node3 newNode;
    newNode.setValues(currentNode->getValuesVect());
    newNode.setValue(currentNode->getValue(targetIndex),zeroIndex);
    newNode.setValue(0,targetIndex);

    if(!exists(newNode,nodes))
    {
        //newNode.addPredecessor(currentNode);
        //currentNode->addSuccessor(&newNode);
        nodes.push_back(newNode);
    }
    else return;
}

void tryMoveLeft(Node3 *currentNode, vector<Node3> &nodes)
{
    int zeroIndex = currentNode->getZeroIndex();
    if(zeroIndex>8 || zeroIndex<0) return;

    int targetIndex = zeroIndex - 1;
    if(targetIndex<0) return;

    Node3 newNode;
    newNode.setValues(currentNode->getValuesVect());
    newNode.setValue(currentNode->getValue(targetIndex),zeroIndex);
    newNode.setValue(0,targetIndex);

    if(!exists(newNode,nodes))
    {

        //newNode.addPredecessor(currentNode);
        //currentNode->addSuccessor(&newNode);
        nodes.push_back(newNode);
    }
    else
    {
        return;
    }
}

void tryMoveRight(Node3 *currentNode, vector<Node3> &nodes)
{
    int zeroIndex = currentNode->getZeroIndex();
    if(zeroIndex>8 || zeroIndex<0) return;

    int targetIndex = zeroIndex + 1;
    if(targetIndex>8) return;

    Node3 newNode;
    newNode.setValues(currentNode->getValuesVect());
    newNode.setValue(currentNode->getValue(targetIndex),zeroIndex);
    newNode.setValue(0,targetIndex);

    if(!exists(newNode,nodes))
    {
        //newNode.addPredecessor(currentNode);
        //currentNode->addSuccessor(&newNode);
        nodes.push_back(newNode);
    }
    else return;
}

#endif // OPERATORS_H
