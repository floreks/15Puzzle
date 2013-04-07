#include "board.h"
#include "solver.h"
#include <iostream>
#include <cstring>
#include <sstream>

using namespace std;

void printPath(vector<Board>path)
{
    for(int i=path.size()-1;i>=0;i--)
        cout << path[i];
}

void printPath(string path)
{
    for(int i=path.size()-1;i>=0;i--)
        cout << path[i];
}

bool contains(string searchFor, string searched)
{
    vector<bool>check;
    for(char i : searched)
        for(char j : searchFor)
            if(i == j)
            {
                check.push_back(1);
                break;
            }
    if(check.size() == 4)
        return 1;
    return 0;
}

int main(int argc, char *argv[])
{
    int strategyID, heuristicID;
    string order;
    int width, height, boardSize;
    vector<BYTE>boardIn;
    stringstream ss;
    Solver solver;
    Board board;
    if(argc == 4)
    {
        string arg(argv[1]);
        if(arg == "-a" || arg == "--a")
        {
            ss << argv[2];
            ss >> strategyID;

            ss.clear();
            ss.str("");

            ss << argv[3];
            ss >> heuristicID;

            cin >> width >> height;
            boardSize = width * height;
            for(int i=0;i<boardSize;i++)
            {
                cin >> width;
                boardIn.push_back(width);
            }
            board.setBoard(boardIn);
            solver.setBoard(board);
            solver.solveAStar();
            cout << endl;
            if(board.isSolvable())
            {
                cout << solver.getPath().size()-1 << '\n';
                printPath(solver.getPathString());
            }
            else
                cerr << -1;
        }

    }
    else if(argc == 3)
    {
        string arg(argv[1]);
        if(arg == "-b" || arg == "--bfs")
        {
            order = string(argv[2]);
            if(order.size() != 4)
                cerr << "Wrong order input.";
            else
            {
                if(!contains(order,"LPDG"))
                    cerr << "Wrong order input.";
                else
                {
                    cin >> width >> height;
                    boardSize = width * height;
                    for(int i=0;i<boardSize;i++)
                    {
                        cin >> width;
                        boardIn.push_back(width);
                    }
                    board.setBoard(boardIn);
                    solver.setBoard(board);
                    solver.solveBFS();
                    cout << endl;
                    if(board.isSolvable())
                    {
                        cout << solver.getPath().size()-1 << '\n';
                        printPath(solver.getPathString());
                    }
                    else
                        cerr << -1;
                }
            }
        }
        else if(arg == "-d" || arg == "--dfs")
        {
            order = string(argv[2]);
            if(order.size() != 4)
                cerr << "Wrong order input.";
            else
            {
                if(!contains(order,"LPDG"))
                    cerr << "Wrong order input.";
                else
                {
                    cin >> width >> height;
                    boardSize = width * height;
                    for(int i=0;i<boardSize;i++)
                    {
                        cin >> width;
                        boardIn.push_back(width);
                    }
                    board.setBoard(boardIn);
                    solver.setBoard(board);
                    solver.solveDFS();
                    cout << endl;
                    if(board.isSolvable())
                    {
                        cout << solver.getPath().size()-1 << '\n';
                        printPath(solver.getPathString());
                    }
                    else
                        cerr << -1;
                }
            }
        }
        else if(arg == "-i" || arg == "--idfs")
        {
            order = string(argv[2]);
            if(order.size() != 4)
                cerr << "Wrong order input.";
            else
            {
                if(!contains(order,"LPDG"))
                    cerr << "Wrong order input.";
                else
                {
                    cout << order;
                }
            }
        }
    }
    else
    {
        cerr << "Wrong parameters.\nUSAGE:\n"
                "-b/--bfs order - BFS search\n"
                "-d/--dfs order - DFS search"
                "-i/--idfs order - IDA* search\n"
                "-a/--a strategyID heuristicID - A* search";
    }
    return 0;
}
