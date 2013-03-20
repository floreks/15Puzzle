#ifndef NODE_H
#define NODE_H

#include <bitset>
#include <vector>
#include <algorithm>

using namespace std;

typedef bitset<4> element;

class Node
{
private:
    vector<element> state;
public:
    Node(){}
    Node(vector<element>s) : state(s){}
    vector<element> getNode()const{return state;}
    void setNode(vector<element>s){state = s;}
    bool equals(Node n);
};

ostream &operator<<(ostream &os, element e);
ostream &operator<<(ostream &os, vector<element>s);
vector<element> init(int size);

#endif // NODE_H
