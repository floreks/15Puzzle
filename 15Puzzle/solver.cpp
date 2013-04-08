#include "solver.h"

Solver::Solver(Board start)
{
    strategyID = 1;
    heuristicID = 1;
    startState = start;
    vector<BYTE>state(start.getSize());
    for(WORD i=0;i<state.size()-1;i++)
    {
        state[i] = i+1;
    }
    state[state.size()-1] = 0;
    endState = state;
    IDFSend = false;
}

void Solver::setBoard(Board start)
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


    if(heuristicID==1) //manhattan
    {
        int min = states[0].manhattan();
        for(WORD i=1;i<states.size();i++)
            if(min > states[i].manhattan())
            {
                min = states[i].manhattan();
                pos = i;
            }
    }
    else //linear
    {
        int min = states[0].linear();
        for(WORD i=1;i<states.size();i++)
            if(min > states[i].linear())
            {
                min = states[i].linear();
                pos = i;
            }
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
        pathString.push_back(it->first.getPosition());
        tmp = it->second;
        cameFrom.erase(it);
    }
}

Board Solver::DLS(Board &node, Board &endNode, WORD depth, string order)
{
    Board board;
    if(node == endState && depth == 0)
    {
        IDFSend = true;
        return node;
    }
    else if(depth > 0)
        for(Board &i : node.neighbors(order))
        {
            linkedList.insert(pair<Board,Board>(i,node));
            DLS(i,endNode,depth-1,order);
        }
    if(IDFSend)
        return endNode;
    return board;
}

bool Solver::solveIDFS(string order)
{
    path.clear();
    pathString.clear();
    linkedList.clear();
    WORD depth = 0;
    Board result;
    while(depth < 8)
    {
        result = DLS(startState,endState,depth,order);
        if(result == endState && !result.isEmpty())
        {
            constructPath(linkedList,endState);
            break;
        }
        depth++;
    }
}

bool Solver::solveBFS(string order)
{
    path.clear();
    pathString.clear();
    vector<Board>openList; // list to search
    vector<Board>closedList;
    map<Board,Board>cameFrom; // path
    openList.push_back(startState);
    Board current;
    if(startState.isSolvable())
    {
        while(openList.empty() == 0)
        {
            current = openList.front();
            if(openList.back() == endState)
            {
                constructPath(cameFrom,endState);
                break;
            }
            openList.erase(openList.begin());
            closedList.push_back(current);
            for(Board &i : current.neighbors(order))
            {
                if(!exists(closedList,i))
                {
                    cameFrom.insert(pair<Board,Board>(i,current));
                    openList.push_back(i);
                    if(i == endState)
                    {
                        break;
                    }
                }
            }
        }
        return 1;
    }
    return 0;
}

bool Solver::solveDFS(string order)
{
    path.clear();
    pathString.clear();
    vector<Board>openList; // list to search
    map<Board,Board>cameFrom; // path
    openList.push_back(startState);
    Board current;
    if(startState.isSolvable())
    {
        while(openList.empty() == 0)
        {
            current = openList.back();
            if(exists(openList,endState))
            {
                constructPath(cameFrom,endState);
                break;
            }
            for(Board &i : current.neighbors(order))
            {
                if(!exists(openList,i))
                {
                    cameFrom.insert(pair<Board,Board>(i,current));
                    openList.push_back(i);
                    if(i == endState)
                    {
                        break;
                    }
                }
            }
        }
        return 1;
    }
    return 0;
}

bool Solver::solveAStar(int sid, int hid)
{
    heuristicID = hid;
    strategyID = sid;

    path.clear();
    pathString.clear();
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
