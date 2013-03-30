#include "board.h"
#include "solver.h"
#include <QDebug>

int main()
{
    Board board({12,1,10,2,7,11,4,14,5,0,9,15,8,13,6,3});
    Board board2({12,1,10,2,7,11,4,14,5,0,9,15,8,13,6,3});
    qDebug() << "Is board solvable: " << board.isSolvable();
    qDebug() << "Board == Board2: " << (board == board2);
    qDebug() << "Neighbors";
    for(Board i : board.neighbors())
        qDebug() << i;
    Solver solve(board);
    return 0;
}
