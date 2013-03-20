#include <iostream>
#include <bitset>
#include <vector>
#include <cmath>
#include "graph.h"

using namespace std;

typedef bitset<4> element;

ostream &operator<<(ostream &os, element e)
{
    os << e.to_ulong();
    return os;
}

vector<element> init(int size)
{
    vector<element>result(size);
    for(int i=0;i<size-1;i++)
    {
        result[i] = i+1;
    }
    return result;
}

ostream &operator<<(ostream &os, vector<element>s)
{
    for(int i=0;i<s.size();i++)
    {
        if(i % (int)sqrt(s.size())==0 && i!=0)
            os << endl;
        os << s[i] << ' ';
    }
    return os;
}

int main()
{
    Node n(init(9));
    return 0;
}
