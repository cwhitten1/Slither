#ifndef BOARDSOLVER_H
#define BOARDSOLVER_H
#include "Board.h"
#include "sPoint.h"
#include <vector>

class BoardSolver
{
    public:
        BoardSolver();
        BoardSolver(Board b);
        virtual ~BoardSolver();
        vector<Edge> findSolution();
        void setBoard(Board b){this->b = b;}
        Board getBoard(){return b;}
        bool getTrueSolutionFound(){return trueSolutionFound;}
    protected:
    private:
        bool trueSolutionFound;
        bool solutionAttempted;
        vector<Edge> solutionArray;
        vector<Edge> finalSolution;
        Board b;
        void markBoardWithSolution(vector<Edge> edges); //This method will mark the squares of the input board
        bool tryEdge(Edge e, bool p1isStart, string prevDir, Point destPoint, vector<Point> visitedPoints);
        bool checkForSolution(vector<Edge> solutionArray);
        Edge determineStartEdge();
        Point findMostPromisingPoint();
        int findPointPromise(Point p);
        bool isSolutionStillPossible(vector<Point> visitedPoints, Point destPoint, Point currPoint); //Check if a solution can still be found
        //These method check to see if single lines have been formed that prevent reaching the destination point
        bool checkForLinesFormed(int outerStart, int outerEnd, int innerStart, int innerEnd, vector<Point> visitedPoints);
        int checkForLinesFormed(int outerStart, int outerEnd, int innerStart, int innerEnd, vector<Point> visitedPoints, bool returnMin);
};

#endif // BOARDSOLVER_H
