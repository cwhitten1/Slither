#ifndef BOARDSOLVER_H
#define BOARDSOLVER_H
#include "Board.h"
#include "sPoint.h"

class BoardSolver
{
    public:
        BoardSolver();
        BoardSolver(Board* b);
        virtual ~BoardSolver();
        void findSolution();
        void showBestSolution();
        void setBoard(Board* b);
    protected:
    private:
        bool trueSolutionFound;
        bool solutionAttempted;
        Board* b;
        ArrayList<sPoint>*  bestSolution;
        ArrayList<sPoint>*  visitedPoints;
        void markBoardWithSolution(ArrayList<sPoint>* solutionPoints); //This method will mark the squares of the input board
        void tryPoint(sPoint p, string prevDir,int boardHeight, int boardWidth);
        void checkForSolution(ArrayList<sPoint>* points);
        bool challengeBestSolution(int numValidSquares); //Challenge only checks for number of valid squares not continuous loop
};

#endif // BOARDSOLVER_H
