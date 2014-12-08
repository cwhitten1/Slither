#ifndef BOARDSOLVER_H
#define BOARDSOLVER_H
#include "Board.h"
#include "sPoint.h"
#include <vector>

class BoardSolver
{
    public:
        BoardSolver();
        BoardSolver(Board* b);
        virtual ~BoardSolver();
        vector<Edge> findSolution();
        void setBoard(Board* b);
    protected:
    private:
        bool trueSolutionFound;
        bool solutionAttempted;
        vector<Edge> solutionArray;
        vector<Edge> finalSolution;
        Board* b;
        void markBoardWithSolution(vector<Edge> edges); //This method will mark the squares of the input board
        bool tryEdge(Edge e, bool p1isStart, string prevDir, Point destPoint, vector<Point> visitedPoints);
        bool checkForSolution(vector<Edge> solutionArray);
};

#endif // BOARDSOLVER_H
