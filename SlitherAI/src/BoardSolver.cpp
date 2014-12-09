#include "BoardSolver.h"
#include <iostream>
#include <algorithm>
using namespace std;

BoardSolver::BoardSolver()
{
    finalSolution.reserve(10);
    solutionArray.reserve(10);
    trueSolutionFound = false;
    solutionAttempted = false;
}
BoardSolver::BoardSolver(Board b)
{
    finalSolution.reserve(10);
    solutionArray.reserve(10);
    trueSolutionFound = false;
    solutionAttempted = false;
    this->b = b;
}
BoardSolver::~BoardSolver()
{
}

//We can determine a point's promise by adding the values of all of the squares it belongs to
int BoardSolver::findPointPromise(Point p)
{
    int height = b.getHeight();
    int width = b.getWidth();
    int i = p.row;
    int j = p.column;
    //Get neighbor squares values
    int tl=0, tr=0, bl=0, br=0;

    if(i-1>=0 && j-1>=0)
        tl = b.getGrid()[i-1][j-1].Getvalue();
    if(i-1>=0 && j < width)
        tr = b.getGrid()[i-1][j].Getvalue();
    if(i < height && j-1 >= 0)
        bl = b.getGrid()[i][j-1].Getvalue();
    if(i<height && j < width)
        br = b.getGrid()[i][j].Getvalue();

    return tl+tr+bl+br;
}
Point BoardSolver::findMostPromisingPoint()
{
    //First we need to find the point which will certainly be marked
    Point mostPromising = Point(0,0);
    int maxPromise = 0;
    int height = b.getHeight();
    int width = b.getWidth();
    for(int i = 0; i < height+1; i++)
    {
        for(int j = 0; j<width+1; j++)
        {
            int promise = findPointPromise(Point(i,j));
            if(promise > maxPromise)
            {
                maxPromise = promise;
                mostPromising.row = i;
                mostPromising.column = j;
            }

        }
    }

    return mostPromising;
}
Edge BoardSolver::determineStartEdge()
{
    Point p = findMostPromisingPoint();
    int pRow = p.row;
    int pCol = p.column;
    int height = b.getHeight();
    int width = b.getWidth();
    Point nextP = Point();
    int maxPromise=0; //Max promise for p's neighbors

    //Find the promise of each of p's neighbors and compare to maxPromise
    if(pRow-1>=0)
    {
        int promise = findPointPromise(Point(pRow-1, pCol));
        if(promise>maxPromise)
        {
             maxPromise = promise;
             nextP.row = pRow-1;
             nextP.column = pCol;
        }
    }
    if(pRow+1< height+1)
    {
        int promise = findPointPromise(Point(pRow+1, pCol));
        if(promise>maxPromise)
        {
             maxPromise = promise;
             nextP.row = pRow+1;
             nextP.column = pCol;
        }
    }
    if(pCol-1>=0)
    {
        int promise = findPointPromise(Point(pRow, pCol-1));
        if(promise>maxPromise)
        {
             maxPromise = promise;
             nextP.row = pRow;
             nextP.column = pCol-1;
        }
    }
    if(pCol+1< width+1)
    {
        int promise = findPointPromise(Point(pRow, pCol+1));
        if(promise>maxPromise)
        {
             maxPromise = promise;
             nextP.row = pRow;
             nextP.column = pCol+1;
        }
    }

    return Edge(p, nextP);
}
//This method is the caller of the recursive tryPoint function
vector<Edge> BoardSolver::findSolution()
{
    //Heuristics
    Point startPoint = findMostPromisingPoint();
    Edge  startEdge = determineStartEdge();
    //cout<<findPointPromise(startPoint)<<endl;
    //Initializations
    //Point startPoint = Point(0,0);
    //Point startLeadPoint = Point(1,0);
    Edge e = startEdge;

    vector<Point> visitedPoints = vector<Point>();
    visitedPoints.push_back(startPoint); //Need to add start point because recursive algorithm adds the lead points.

    tryEdge(e, true, "T", startPoint, visitedPoints);
    solutionAttempted = true;
    return solutionArray;
}

//Still need to edit this method
bool BoardSolver::tryEdge(Edge e, bool p1isStart, string prevDir, Point destPoint, vector<Point> visitedPoints)
{
    //The lead point is the point which will be "looking" for another point to form an edge with
    Point leadPoint;
    Point basePoint;

    if(p1isStart)
    {
        leadPoint = e.Getp2();
        basePoint = e.Getp1();
    }
    else
    {
        leadPoint = e.Getp1();
        basePoint = e.Getp2();
    }
    //cout<<"Lead: "<< leadPoint.row<< " "<<leadPoint.column<<" "<<"Base: "<<basePoint.row<<" "<<basePoint.column<<endl;


    //Add edge to solution array prematurely but remember the index where we put it
    solutionArray.push_back(e);


    //Base case when leadPoint is the startPoint (with check for a sufficiently sized solution array)
    //cout<< solutionArray.size()<<endl;
    if(leadPoint == destPoint && solutionArray.size() >= 2)
    {
        //cout<<"Checking for solution"<<endl;
        bool solved = checkForSolution(solutionArray);
        if(solved)
            finalSolution = solutionArray;
        solutionArray.pop_back();
        //cout<<"returned"<<endl;
        return solved;
    }

    //If we have already visited a lead point (provided it is not the destPoint), remove current edge from the solutionArray.
    if(find(visitedPoints.begin(), visitedPoints.end(), leadPoint) != visitedPoints.end())
    {
        //cout<<"Already have point "<<leadPoint.row<<" "<<leadPoint.column<<" in stack"<< endl;
        solutionArray.pop_back();
        //cout<<"returned"<<endl;
        return false;
    }
    else
        visitedPoints.push_back(leadPoint);

    //Recursive steps
    int row = leadPoint.row;
    int column = leadPoint.column;
    bool solved = false;
    if(row-1 >= 0 && prevDir != "T")
    {
        Point topN = Point(row-1,column);
        Edge e = Edge(leadPoint, topN);
        solved = tryEdge(e, true, "B", destPoint, visitedPoints);
    }
    if(row+1 < b.getHeight()+1  && !solved && prevDir != "B")
    {
        Point bottomN = Point(row+1,column);
        Edge e = Edge(leadPoint, bottomN);
        solved = tryEdge(e, true, "T", destPoint, visitedPoints);
    }
    if(column-1 >= 0 && !solved && prevDir != "L")
    {
        Point leftN = Point(row,column-1);
        Edge e = Edge(leadPoint, leftN);
        solved = tryEdge(e, true, "R", destPoint, visitedPoints);
    }
    if(column+1 < b.getWidth()+1 && !solved && prevDir != "R")
    {
        Point rightN = Point(row,column+1);
        Edge e = Edge(leadPoint, rightN);
        solved = tryEdge(e, true, "L", destPoint, visitedPoints);
    }

    solutionArray.pop_back();
    //cout<<"returned"<<endl;
    return solved;
}

//This method checks if input points form a solution and if not, it will assign it to best solution if it is better than current best solution
bool BoardSolver::checkForSolution(vector<Edge> solutionArray)
{
    markBoardWithSolution(solutionArray);
    //cout<<b.isContLoop()<<endl;
    if(b.isContLoop())
    {
        if(b.areSquaresValid())
        {
            trueSolutionFound = true;
            return true;
        }
        else
        {
            return false;
        }
    }
    else
        return false;
}

void BoardSolver::markBoardWithSolution(vector<Edge> edges)
{
    //If we have already found the solution, don't bother.
    if(trueSolutionFound)
        return;
    //Clear board
    b.clearBoard();

    for(unsigned i = 0; i < edges.size(); i++)
    {
       Edge e = edges.at(i);

       //Get square it belongs to//
       Point p1 = e.Getp1();
       Point p2 = e.Getp2();
       int sqRow, sqCol;

       //The square will be in the row: min(p1.row,p2.row)
       if(p1.row > p2.row)
            sqRow = p2.row;
       else
            sqRow = p1.row;

       //The square will be in the column: min(p1.column,p2.column)
       if(p1.column > p2.column)
            sqCol = p2.column;
       else
            sqCol = p1.column;


        //Based on the way we found square pos, we will mark top if edge is horizontal and mark left if edge is vertical
        if(p1.row==p2.row)
        {
            //Check for when edge is on the very bottom
            if(sqRow < b.getHeight())
                b.makeMove(sqRow,sqCol,"T");
            else
                b.makeMove(sqRow-1, sqCol, "B");
        }

        else if(p1.column == p2.column)
        {
            //Check for when edge is on the far right
            if(sqCol < b.getWidth())
                b.makeMove(sqRow, sqCol, "L");
            else
                b.makeMove(sqRow, sqCol-1, "R");
        }

        else
            cout<<"Bad edge found when marking board"<<endl;
    }
}
