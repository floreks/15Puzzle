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
    cost = manhattan();
    totalCost = 0;
    sqrtSize = sqrt(state.size());
    position = 'S';
}

Board::Board(const Board &board)
{
    this->position = board.position;
    this->state = board.state;
    this->cost = board.cost;
    this->totalCost = board.totalCost;
    this->zeroPosition = board.zeroPosition;
    this->sqrtSize = board.sqrtSize;
}

Board::Board()
{
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

/* Returns sum of Manhattan distances between blocks and goal,
 * which is counted by summing up distances to end state for all puzzles
 */

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
    return sum;
}

/* Returns count of all misplaced puzzles
 */

int Board::linear()
{
    int sum = 0;

    for(WORD i=0;i<state.size();i++)
        if(state[i]!=(i+17)%(state.size())) // dla 0 1 2 ... 15 mamy 1 2 3 ... 0
            sum++;

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
    Board tmp;
    tmp = moveDown();
    tmp.setPositon('G');
    if(!tmp.isEmpty())
        result.push_back(tmp);
    tmp = moveRight();
    tmp.setPositon('L');
    if(!tmp.isEmpty())
        result.push_back(tmp);
    tmp = moveUp();
    tmp.setPositon('D');
    if(!tmp.isEmpty())
        result.push_back(tmp);
    tmp = moveLeft();
    tmp.setPositon('P');
    if(!tmp.isEmpty())
        result.push_back(tmp);

    return result;
}

vector<Board> Board::neighbors(string order)
{
    vector<Board>result;
    Board tmp;

    for(int i=0;i<order.size();i++)
    {
        if(order[i]=='D' || order[i]=='d')
        {
            tmp = moveUp();
            tmp.setPositon('D'); //dol
            if(!tmp.isEmpty())
                result.push_back(tmp);
        }
        if(order[i]=='G' || order[i]=='g')
        {
            tmp = moveDown();
            tmp.setPositon('G'); //gora
            if(!tmp.isEmpty())
                result.push_back(tmp);
        }
        if(order[i]=='L' || order[i]=='l')
        {
            tmp = moveRight();
            tmp.setPositon('L'); //lewo
            if(!tmp.isEmpty())
                result.push_back(tmp);
        }
        if(order[i]=='P' || order[i]=='p')
        {
            tmp = moveLeft();
            tmp.setPositon('P'); //prawo
            if(!tmp.isEmpty())
                result.push_back(tmp);
        }
    }

    return result;
}

void Board::setBoard(vector<BYTE> tab)
{
    zeroPosition = 0xFFFF;
    for(WORD i=0;i<tab.size();i++)
    {
        if(tab[i] == 0)
            zeroPosition = i;
        state.push_back(tab[i]);
    }
    assert(zeroPosition != 0xFFFF);
    cost = manhattan();
    totalCost = 0;
    sqrtSize = sqrt(state.size());
    position = 'S';
}

// ----------------------------------------- //

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

ostream &operator<<(ostream &os, const Board &s)
{
    for(WORD i=0;i<s.state.size();i++)
        os << static_cast<WORD>(s.state[i]) << (i%s.sqrtSize == s.sqrtSize-1 && i ? '\n' : ' ');
    os << endl;
    return os;
}
