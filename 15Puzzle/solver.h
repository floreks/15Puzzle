#ifndef SOLVER_H
#define SOLVER_H

#include "board.h"
#include <map>

struct comparator
{
    bool operator()(const Board &s1, const Board &s2)
    {
        return (s1 == s2);
    }
};

class Solver
{
private:
    Board endState;
    Board startState;
    vector<Board>path;
    int getLowestCost(vector<Board>&states);
    bool exists(vector<Board>&states, const Board &board);
    void constructPath(map<Board, Board, comparator> &cameFrom, Board &node);
public:
    Solver(Board start);
    bool solve();
    vector<Board> getPath()const{return path;}
};

#endif // SOLVER_H
