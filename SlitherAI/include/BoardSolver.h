#ifndef BOARDSOLVER_H
#define BOARDSOLVER_H
#include "Board.h"

class BoardSolver
{
    public:
        BoardSolver();
        virtual ~BoardSolver();
        ArrayList<string> findSolution(Board* b);
    protected:
    private:
        bool tryMove(int row, int column, string side);
};

#endif // BOARDSOLVER_H
