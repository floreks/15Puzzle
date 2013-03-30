#include "solver.h"

Solver::Solver(Board start)
{
    startState = start;
    vector<BYTE>state(start.getSize());
    for(int i=0;i<state.size()-1;i++)
    {
        state[i] = i+1;
    }
    state[state.size()-1] = 0;
    endState = state;
}
