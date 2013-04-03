#include "board.h"
#include "solver.h"
#include <QDebug>

int main()
{
    Board board({2,10,3,4,1,14,6,0,5,13,7,8,9,11,15,12});
    Board board2({2,4,0,5,6,3,1,7,8});
    qDebug() << "Is board solvable: " << board.isSolvable();
    qDebug() << "Board == Board2: " << (board == board2);
    Solver solver(board);
    solver.solve();
    qDebug() << "Steps: " << solver.getPath().size();
    for(int i=solver.getPath().size()-1;i>=0;i--)
    {
        qDebug() << solver.getPath()[i];
    }
    return 0;
}
