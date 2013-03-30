#include "board.h"

Board::Board(vector<BYTE> tab)
{
    zeroPosition = 0xFFFF;
    for(WORD i=0;i<tab.size();i++)
    {
        if(tab[i] == 0)
            zeroPosition = i;
        state.push_back(tab[i]);
    }
    assert(zeroPosition != 0xFFFF);
    cost = 0;
    totalCost = 0;
    sqrtSize = sqrt(state.size());
}

// ----------- OPERATORS --------------- //

Board Board::moveUp()
{
    Board result(this->state);
    if(zeroPosition >= state.size()-sqrtSize)
    {
        result.clear();
        return result;
    }

    result.swapElements(zeroPosition,zeroPosition+sqrtSize);
    return result;
}

Board Board::moveDown()
{
    Board result(this->state);
    if(zeroPosition < sqrtSize)
    {
        result.clear();
        return result;
    }

    result.swapElements(zeroPosition,zeroPosition-sqrtSize);
    return result;
}

Board Board::moveLeft()
{
    Board result(this->state);
    if(zeroPosition % sqrtSize == sqrtSize-1)
    {
        result.clear();
        return result;
    }

    result.swapElements(zeroPosition,zeroPosition+1);
    return result;
}

Board Board::moveRight()
{
    Board result(this->state);
    if(zeroPosition % sqrtSize == 0)
    {
        result.clear();
        return result;
    }

    result.swapElements(zeroPosition,zeroPosition-1);
    return result;
}

// -------------- OPERATORS ------------- //

bool Board::swapElements(int index, int index2)
{
    if(state[index] != 0 && state[index2] != 0)
        return 0;

    if(state[index] == 0)
        zeroPosition = index2;
    else
        zeroPosition = index;
    int mem = state[index];
    state[index] = state[index2];
    state[index2] = mem;
    return 1;
}

/*
 * Returns sum of Manhattan distances between blocks and goal
 **/

int Board::manhattan()
{
    int sum = 0, destination, start;
    for(WORD i=0;i<state.size();i++)
    {
        if(state[i] != i+1 && state[i]!=0)
        {
            start = i+1;
            destination = state[i];
            start = (destination > start) ? destination : start;
            while(start-3>= (i+1 < state[i] ? i+1 : state[i]))
            {
                sum++;
                start -= 3;
            }
            while(start != (i+1 < state[i] ? i+1 : state[i]))
            {
                start--;
                sum++;
            }
        }
    }
    cost = sum;
    return sum;
}

bool Board::isZeroRowEven()
{
    if(zeroPosition >= sqrtSize && zeroPosition < sqrtSize*2)
        return 1;
    if(zeroPosition >= sqrtSize*3 && zeroPosition < sqrtSize*4)
        return 1;
    return 0;
}

bool Board::isSolvable()
{
    // number of inversion determines whether board is solvable or not
    WORD inversionsNumber = 0;
    for(WORD i=0;i<state.size();i++)
    {
        for(WORD j=i+1;j<state.size();j++)
            if(state[i] > state[j] && j != zeroPosition)
                inversionsNumber++;
    }

    if(sqrtSize % 2 == 1 && inversionsNumber % 2 == 0)
        return 1;
    if((sqrtSize % 2 == 0) && ((isZeroRowEven() != 0) == (inversionsNumber % 2 == 0)))
        return 1;
    return 0;
}

vector<Board> Board::neighbors()
{
    vector<Board>result;

    Board tmp = moveUp();
    if(!tmp.isEmpty())
        result.push_back(tmp);
    tmp = moveDown();
    if(!tmp.isEmpty())
        result.push_back(tmp);
    tmp = moveLeft();
    if(!tmp.isEmpty())
        result.push_back(tmp);
    tmp = moveRight();
    if(!tmp.isEmpty())
        result.push_back(tmp);

    return result;
}

// ----------------------------------------- //

QDebug operator<<(QDebug d, const Board &s)
{
    for(WORD i=0;i<s.state.size();i++)
        d.nospace() << static_cast<WORD>(s.state[i]) << (i%s.sqrtSize == s.sqrtSize-1 && i ? '\n' : ' ');
    return d;
}

bool operator==(const Board &s1, const Board &s2)
{
    for(WORD i=0;i<s1.state.size();i++)
        if(s1.state[i] != s2.state[i])
            return 0;
    return 1;
}

bool operator<(const Board &s1, const Board &s2)
{
    return !(s1 == s2);
}
