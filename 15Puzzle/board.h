#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <bitset>
#include <QDebug>
#include <cmath>
#include <assert.h>

using namespace std;

typedef unsigned char BYTE;
typedef unsigned short int WORD;

/*
 * For testing there are no pointers in code. They need to be added in order to create proper graph.
 */

class Board
{
private:

    vector<BYTE>state;
    WORD zeroPosition;
    WORD sqrtSize;
    WORD cost;
    WORD totalCost;

    bool isZeroRowEven();
    Board moveUp();
    Board moveDown();
    Board moveLeft();
    Board moveRight();
public:

    // Constructors && destructor //
    Board(vector<BYTE> tab);
    Board(const Board &board);
    Board();
    ~Board(){}
    // -------------------------- //
    int manhattan();
    bool swapElements(int index, int index2);
    bool isSolvable();
    vector<Board> neighbors();
    bool isEmpty()const{return state.empty()==1;}
    void clear(){state.clear();}
    int getSize()const{return state.size();}
    void setCost(WORD cost){this->cost = cost;}
    WORD getCost()const{return cost;}
    void setTotalCost(WORD cost){this->totalCost = cost;}
    WORD getTotalCost()const{return totalCost;}


protected:

    // Overloaded operators //
    friend QDebug operator<<(QDebug d, const Board &s);
    friend bool operator==(const Board &s1, const Board  &s2);
    friend bool operator<(const Board &s1, const Board &s2);

    // -------------------- //
};

#endif // BOARD_H
