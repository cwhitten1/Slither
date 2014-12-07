#include "BoardSolver.h"
#include <iostream>
using namespace std;

BoardSolver::BoardSolver()
{
    trueSolutionFound = false;
    solutionAttempted = false;
    bestSolution = new ArrayList<sPoint>();
    visitedPoints = new ArrayList<sPoint>();
}
BoardSolver::BoardSolver(Board* b)
{
    trueSolutionFound = false;
    solutionAttempted = false;
    bestSolution = new ArrayList<sPoint>();
    visitedPoints = new ArrayList<sPoint>();
    this->b = b;
}
BoardSolver::~BoardSolver()
{
}

void BoardSolver::showBestSolution()
{
    //Mark the board
    if(bestSolution->Getsize() > 0)
    {
        markBoardWithSolution(bestSolution);
        //Display the board
        b->drawBoard();
    }
    else
        cout<<"A solution to the board has not been found yet"<<endl;

    //Message concerning whether or not this is the true solution
    if(trueSolutionFound)
        cout<<"This is the true solution"<<endl;
    else
        cout<<"This is not the true solution"<<endl;
}

//This method is the caller of the recursive tryPoint function
void BoardSolver::findSolution()
{
    //Initializations
    sPoint startPoint = sPoint(0,0, true);
    //visitedPoints.add(startPoint);

    tryPoint(startPoint, "T", b->getHeight(), b->getWidth());
    showBestSolution();
    solutionAttempted = true;
}

//Still need to edit this method
void BoardSolver::tryPoint(sPoint p, string prevDir, int boardHeight, int boardWidth)
{
    //Base case when all points have been checked
    int numBoardPoints = (boardHeight +1) * (boardWidth+1);
    //cout<<visitedPoints->Getsize()<<endl;
    if(visitedPoints->Getsize() >= numBoardPoints)
    {
        checkForSolution(visitedPoints);
        return;
    }


    //Prevent adding duplicate points to visitedPoints to prevent infinite loop
    if(visitedPoints->find(p) == -1)
    {
        visitedPoints->add(p);
        cout<<"Added Point: "<<p.row<<" "<<p.column<<endl;

        //Recursive steps
        int row = p.row;
        int column = p.column;

        if(row+1 < boardHeight+1 && prevDir != "B" && !trueSolutionFound)
        {
            sPoint bottomN = sPoint(row+1, column, true);
            tryPoint(bottomN, "T", boardHeight, boardWidth);
        }
        if(row -1 >= 0 && prevDir !="T" && !trueSolutionFound)
        {
             sPoint topN = sPoint(row-1, column, true);
             tryPoint(topN, "B", boardHeight, boardWidth);
        }
        if(column+1 < boardWidth+1 && prevDir != "R" && !trueSolutionFound)
        {
            sPoint rightN = sPoint(row, column+1, true);
            tryPoint(rightN, "L", boardHeight, boardWidth);
        }
        if(column -1 >= 0 && prevDir != "L" && !trueSolutionFound)
        {
             sPoint leftN = sPoint(row, column-1, true);
             tryPoint(leftN, "R", boardHeight, boardWidth);
        }

        //Remove the point from visited points once we have fully evaluated it
        visitedPoints->remove(visitedPoints->find(p));
    }
    else
    {
        cout<<"Found Point: "<<p.row<<" "<<p.column<<endl;
        return;
    }
}

//This method checks if input points form a solution and if not, it will assign it to best solution if it is better than current best solution
void BoardSolver::checkForSolution(ArrayList<sPoint>* points)
{

    markBoardWithSolution(points);
    if(b->isContLoop())
    {
        if(b->areSquaresValid())
        {
            bestSolution = new ArrayList<sPoint>();
            bestSolution->addAll(points);
            trueSolutionFound = true;
        }
        else
        {
            //If best solution has been defined, challenge it
            bool isBetter = true;
            if(bestSolution->Getsize() > 0)
                isBetter = challengeBestSolution(b->getNumValidSquares());

            if(isBetter)
            {
                bestSolution = new ArrayList<sPoint>();
                bestSolution->addAll(points);
            }
        }
    }
}

bool BoardSolver::challengeBestSolution(int numValidSquares)
{
    markBoardWithSolution(bestSolution);
    int currNum = b->getNumValidSquares();

    if(numValidSquares > currNum)
    {
        return true; //Return true if a better solution has been found
    }
    else
    {
        return false; //Return false if best solution is still the best
    }
}
void BoardSolver::markBoardWithSolution(ArrayList<sPoint>* solutionPoints)
{
    //Clear board
    b->clearBoard();

    for(int i = 0; i < b->getWidth(); i++)
    {
        for(int j = 0; j < b->getHeight(); j++)
        {
            //Make point objects
            int indexLeftP = solutionPoints->find(sPoint(i,j,false)); // Note the false does not matter here due to the way we overloaded the equality operator
            int indexRightP = solutionPoints->find(sPoint(i,j+1,false));
            int indexBLeftP = solutionPoints->find(sPoint(i+1,j,false)); // Note the false does not matter here due to the way we overloaded the equality operator
            int indexBRightP = solutionPoints->find(sPoint(i+1,j+1,false));

            sPoint leftP = solutionPoints->get(indexLeftP);
            sPoint rightP = solutionPoints->get(indexRightP);
            sPoint bleftP = solutionPoints->get(indexBLeftP);
            sPoint brightP = solutionPoints->get(indexBRightP);

            //Mark square according to which points are marked
            Square s = b->getGrid()[leftP.row][leftP.column];

            if(leftP.isMarked && rightP.isMarked && !s.Gets_top())
                grid[leftP.row][leftP.column].toggleSide("T");
            if(leftP.isMarked && bleftP.isMarked && !s.Gets_left())
                grid[leftP.row][leftP.column].toggleSide("L");
            if(brightP.isMarked && rightP.isMarked && !s.Gets_right())
                grid[leftP.row][leftP.column].toggleSide("R");
            if(brightP.isMarked && bleftP.isMarked && !s.Gets_bottom())
                grid[leftP.row][leftP.column].toggleSide("B");
        }
    }
}

void BoardSolver::setBoard(Board* b)
{
    this->b = b;
}
