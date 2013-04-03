#include "solver.h"

Solver::Solver(Board start)
{
    startState = start;
    vector<BYTE>state(start.getSize());
    for(WORD i=0;i<state.size()-1;i++)
    {
        state[i] = i+1;
    }
    state[state.size()-1] = 0;
    endState = state;
}

int Solver::getLowestCost(vector<Board> &states)
{
    int pos = 0;
    int min = states[0].manhattan();
    for(WORD i=1;i<states.size();i++)
        if(min > states[i].manhattan())
        {
            min = states[i].manhattan();
            pos = i;
        }
    return pos;
}

bool Solver::exists(vector<Board> &states,const Board &board)
{
    for(Board i : states)
        if(board == i)
            return 1;
    return 0;
}

map<Board,Board>::iterator Solver::find(map<Board,Board> &cameFrom, Board &node)
{
    map<Board,Board>::iterator it;
    for(it = cameFrom.begin(); it != cameFrom.end(); it++)
        if(it->first == node)
            return it;
    return cameFrom.end();
}

void Solver::constructPath(map<Board, Board> &cameFrom, Board &node)
{
    map<Board,Board>::iterator it;
    Board tmp(node);
    path.push_back(endState);
    while((it = find(cameFrom,tmp)) != cameFrom.end())
    {
        path.push_back(it->second);
        tmp = it->second;
    }
}

bool Solver::solve()
{
    bool endFound = false;
    vector<Board>openList;
    vector<Board>closedList;
    map<Board,Board>cameFrom;
    WORD lowestCostPos,tentGScore;
    startState.setTotalCost(0);
    startState.setCost(abs(startState.getCost() - endState.getCost()));
    openList.push_back(startState);
    Board current;
    if(startState.isSolvable())
    {
        while(openList.empty() == 0)
        {
            lowestCostPos = getLowestCost(openList);
            current = openList[lowestCostPos];
            if(current == endState || endFound)
            {
                qDebug() << "Graph size: " << cameFrom.size();
                constructPath(cameFrom,endState);
                break;
            }
            openList.erase(openList.begin()+lowestCostPos);
            closedList.push_back(current);
            for(Board &i : current.neighbors())
            {
                tentGScore = current.getCost() + (abs(current.getCost()-i.getCost()));
                if(exists(closedList,i))
                    if(tentGScore >= i.getCost())
                        continue;

                if(!exists(openList,i) || tentGScore < i.getCost())
                {
                    cameFrom.insert(pair<Board,Board>(i,current));
                    i.setTotalCost(tentGScore);
                    i.setCost(tentGScore + abs(i.getCost()-endState.getCost()));
                    openList.push_back(i);
                    if(i == endState)
                    {
                        endFound = 1;
                        break;
                    }
                }
            }
        }
        return true;
    }
    else
        return false;
}
