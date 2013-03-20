#ifndef OPERATORS_H
#define OPERATORS_H

#include <bitset>
#include <vector>
#include <cmath>

typedef bitset<4> element;
using namespace std;

vector<element> up(int pos, vector<element>&s)
{
    vector<element>result;
    static int a = pos - (int)sqrt(s.size());
    if(a < 0)
        return result;

    if(s[a] != 0)
        return result;

    result = s;
    result[pos] = 0;
    result[a] = s[pos];
    return result;
}

vector<element> down(int pos, vector<element>&s)
{
    vector<element>result;
    static int a = pos + (int)sqrt(s.size());
    if(a > s.size())
        return result;

    if(s[a] != 0)
        return result;

    result = s;
    result[pos] = 0;
    result[a] = s[pos];
    return result;
}

vector<element> left(int pos, vector<element>&s)
{
    vector<element>result;
    static int a = pos - 1;
    if(pos % (int)sqrt(s.size()) == 0)
        return result;

    if(s[a] != 0)
        return result;

    result = s;
    result[pos] = 0;
    result[a] = s[pos];
    return result;
}

vector<element> right(int pos, vector<element>&s)
{
    vector<element>result;
    static int a = pos + 1;
    if(pos % (int)sqrt(s.size()) == (int)sqrt(s.size())-1)
        return result;

    if(s[a] != 0)
        return result;

    result = s;
    result[pos] = 0;
    result[a] = s[pos];
    return result;
}

#endif // OPERATORS_H
