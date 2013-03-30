#include "board.h"
#include "solver.h"
#include <QDebug>

int main()
{
    Board board({1,2,3,4,5,6,7,8,9,10,0,11,13,14,15,12});
    Board board2({12,1,10,2,7,11,4,14,5,0,9,15,8,13,6,3});
    qDebug() << "Is board solvable: " << board.isSolvable();
    qDebug() << "Board == Board2: " << (board == board2);
    Solver solver(board);
    qDebug() << solver.solve();
    qDebug() << solver.getPath().size();
    for(int i=solver.getPath().size()-1;i>=0;i--)
    {
        qDebug() << solver.getPath()[i];
    }
    return 0;
}
