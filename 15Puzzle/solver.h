#ifndef SOLVER_H
#define SOLVER_H

#include "board.h"
#include <map>

class Solver
{
private:
    Board endState;
    Board startState;
    vector<Board>path;
    string pathString;

    int getLowestCost(vector<Board>&states);
    bool exists(vector<Board>&states, const Board &board);
    void constructPath(map<Board, Board> &cameFrom, Board &node);
    map<Board,Board>::iterator find(map<Board, Board> &cameFrom, Board &node);
public:
    Solver(Board start);
    Solver(){}
    bool solveAStar();
    //bool solveIDAStart();
    bool solveDFS();
    bool solveBFS();
    vector<Board> getPath()const{return path;}
    string getPathString()const{return pathString;}
    void setBoard(Board start);
};

#endif // SOLVER_H
