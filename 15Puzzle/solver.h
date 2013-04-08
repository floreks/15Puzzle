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
    map<Board,Board>linkedList;
    string pathString;
    bool IDFSend;
    int strategyID;
    int heuristicID;
    int getLowestCost(vector<Board>&states);
    bool exists(vector<Board>&states, const Board &board);
    void constructPath(map<Board, Board> &cameFrom, Board &node);
    map<Board,Board>::iterator find(map<Board, Board> &cameFrom, Board &node);
    Board DLS(Board &node, Board &endNode, WORD depth, string order);
public:
    Solver(Board start);
    Solver(){}
    bool solveAStar(int sid, int hid);
    bool solveIDFS(string order);
    bool solveDFS(string order);
    bool solveBFS(string order);
    vector<Board> getPath()const{return path;}
    string getPathString()const{return pathString;}
    void setBoard(Board start);
};

#endif // SOLVER_H
