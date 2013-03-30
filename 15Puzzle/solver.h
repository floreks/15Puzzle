#ifndef SOLVER_H
#define SOLVER_H

#include "board.h"

class Solver
{
private:
    Board endState;
    Board startState;
public:
    Solver(Board start);
};

#endif // SOLVER_H
