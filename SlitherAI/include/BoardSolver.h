#ifndef BOARDSOLVER_H
#define BOARDSOLVER_H
#include "Board.h"

class BoardSolver
{
    public:
        BoardSolver();
        virtual ~BoardSolver();
        void findSolution(Board* b);
        void showBestSolution();
    protected:
    private:
        bool trueSolutionFound;
        class sPoint: public Point
        {
            public:
                sPoint();
                sPoint(int row, int column, bool isVisited);
                virtual ~sPoint(){}
                bool isMarked;
                void setIsMarked(bool val);
                bool operator== (sPoint &p){return (row == p.row && column == p.column);};//Override equality operator}:

        };
        ArrayList<sPoint>*  bestSolution;
        void markBoardWithSolution(Board* b, ArrayList<sPoint> solutionPoints); //This method will mark the squares of the input board
        void tryPoint(sPoint p, ArrayList<sPoint> visitedPoints, int numBoardPoints);
        void checkForSolution(ArrayList<sPoint> points);
        bool challengeBestSolution(int numValidSquares); //Challenge only checks for number of valid squares not continuous loop
};

#endif // BOARDSOLVER_H
