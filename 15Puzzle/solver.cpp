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

int Solver::getLowestCost(vector<Board> &states)
{
    int pos = 0;
    int min = states[0].getCost();
    for(int i=1;i<states.size();i++)
        if(min > states[i].getCost())
        {
            min = states[i].getCost();
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

void Solver::constructPath(map<Board, Board, comparator> &cameFrom, Board &node)
{
    map<Board,Board>::iterator it;
    Board lookFor;
    it = cameFrom.find(node);
    if(it != cameFrom.end())
    {
        qDebug() << it->first << it->second;
        if(!exists(path,it->first))
            path.push_back(it->first);
        if(!exists(path,it->second))
            path.push_back(it->second);
        lookFor = it->second;
        cameFrom.erase(it);
        constructPath(cameFrom,lookFor);
    }
}

bool Solver::solve()
{
    //qDebug() << startState;
    //qDebug() << endState;
    vector<Board>openList;
    vector<Board>closedList;
    map<Board,Board,comparator>cameFrom;
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
            if(current == endState)
            {
                constructPath(cameFrom,endState);
                qDebug() << "End";
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
                    //qDebug() << i << '\n' << current << "\n----------------\n";
                    cameFrom.insert(pair<Board,Board>(i,current));
                    i.setTotalCost(tentGScore);
                    i.setCost(tentGScore + abs(i.getCost()-endState.getCost()));
                    openList.push_back(i);
                    if(i == endState)
                    {
                        qDebug() << "Inserting end node\n" << i;
                        break;
                    }
                }
            }
        }
        map<Board,Board>::iterator it;
        for(it = cameFrom.begin(); it != cameFrom.end(); it++)
            qDebug() << "Key:\n" << it->first << " Second:\n" << it->second;
        return true;
    }
    else
        return false;
}
