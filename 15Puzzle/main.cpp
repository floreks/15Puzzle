#include "board.h"
#include "solver.h"
#include <QDebug>

int main()
{

    Board board({5,1,3,4,9,2,6,8,13,10,7,11,0,14,15,12});
    Board board2({12,1,10,2,7,11,4,14,5,0,9,15,8,13,6,3});
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
