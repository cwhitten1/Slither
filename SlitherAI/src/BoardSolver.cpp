#include "BoardSolver.h"
#include <iostream>
using namespace std;
BoardSolver::BoardSolver()
{
    trueSolutionFound = false;
}
BoardSolver::~BoardSolver()
{
    delete bestSolution;
}

//Constructor for sPoint
BoardSolver::sPoint::sPoint():Point()
{
    isMarked = false;
}
BoardSolver::sPoint::sPoint(int row, int column, bool val): Point(row, column)
{
    setIsMarked(val);
}

void BoardSolver::showBestSolution()
{
    Board* b = new Board();

    //Mark the board
    if(bestSolution != NULL)
        markBoardWithSolution(b, *bestSolution);
    else
        cout<<"A solution to the board has not been found yet"<<endl;

    //Display the board
    b->drawBoard();

    //Message concerning whether or not this is the true solution
    if(trueSolutionFound)
        cout<<"This is the true solution"<<endl;
    else
        cout<<"This is not the true solution"<<endl;

    delete b;
}

//This method is the caller of the recursive tryPoint function
void BoardSolver::findSolution(Board* b)
{
    //Initializations
    int numBoardPoints = (b->getHeight()+1)*(b->getWidth()+1);
    sPoint startPoint = sPoint(0,0, true);
    ArrayList<sPoint> visitedPoints = ArrayList<sPoint>();
    visitedPoints.add(startPoint);

    //tryPoint(startPoint, visitedPoints, numBoardPoints);

}

//Still need to edit this method
void BoardSolver::tryPoint(sPoint p, ArrayList<sPoint> visitedPoints, int numBoardPoints)
{
    if(visitedPoints.Getsize() >= numBoardPoints)
    {
        checkForSolution(visitedPoints);
        return;
    }
}

//This method checks if input points form a solution and if not, it will assign it to best solution if it is better than current best solution
void BoardSolver::checkForSolution(ArrayList<sPoint> points)
{
    Board* b = new Board();

    markBoardWithSolution(b, points);
    if(b->isContLoop())
    {
        if(b->areSquaresValid())
        {
            *bestSolution = points;
            trueSolutionFound = true;
        }
        else
        {
            bool isBetter = challengeBestSolution(b->getNumValidSquares());
            if(isBetter)
                *bestSolution = points;
        }
    }

    //Memory cleanup
    delete b;
}

bool BoardSolver::challengeBestSolution(int numValidSquares)
{
    Board* b = new Board();

    markBoardWithSolution(b, *bestSolution);
    int currNum = b->getNumValidSquares();

    if(numValidSquares > currNum)
    {
        delete b;
        return true; //Return true if a better solution has been found
    }
    else
    {
        delete b;
        return false; //Return false if best solution is still the best
    }
}
void BoardSolver::markBoardWithSolution(Board* b, ArrayList<sPoint> solutionPoints)
{
    for(int i = 0; i < b->getWidth(); i++)
    {
        for(int j = 0; j < b->getHeight(); j++)
        {
            //Make point objects
            int indexLeftP = solutionPoints.find(sPoint(i,j,false)); // Note the false does not matter here due to the way we overloaded the equality operator
            int indexRightP = solutionPoints.find(sPoint(i,j+1,false));
            int indexBLeftP = solutionPoints.find(sPoint(i+1,j,false)); // Note the false does not matter here due to the way we overloaded the equality operator
            int indexBRightP = solutionPoints.find(sPoint(i+1,j+1,false));

            sPoint leftP = solutionPoints.get(indexLeftP);
            sPoint rightP = solutionPoints.get(indexRightP);
            sPoint bleftP = solutionPoints.get(indexBLeftP);
            sPoint brightP = solutionPoints.get(indexBRightP);

            //Mark square according to which points are marked
            Square s = b->getGrid()[leftP.row][leftP.column];

            if(leftP.isMarked && rightP.isMarked && !s.Gets_top())
                s.toggleSide("T");
            if(leftP.isMarked && bleftP.isMarked && !s.Gets_left())
                s.toggleSide("L");
            if(brightP.isMarked && rightP.isMarked && !s.Gets_right())
                s.toggleSide("R");
            if(brightP.isMarked && bleftP.isMarked && !s.Gets_bottom())
                s.toggleSide("B");
        }
    }
}

void BoardSolver::sPoint::setIsMarked(bool val)
{
    isMarked = val;
}
