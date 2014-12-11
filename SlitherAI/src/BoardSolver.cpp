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
    finalSolution.reserve(40);
    solutionArray.reserve(40);
    trueSolutionFound = false;
    solutionAttempted = false;
    this->b = b;
}
BoardSolver::~BoardSolver()
{
}

vector<sPoint> BoardSolver::getAllPointsPromise()
{
    vector<sPoint> points = vector<sPoint>();
    for(int i = 0; i < b.getHeight()+1;i++)
    {
        for(int j = 0; j < b.getWidth(); j++)
        {
            int promise = findPointPromise(Point(i,j));
            points.push_back(sPoint(i,j,promise,""));
        }
    }
    return points;

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
    {
        tl = b.getGrid()[i-1][j-1].Getvalue();
        //If the square is blank, it will return -1
        //But we want no penalty for a blank square.
        //If the square is zero, there is a lot of promise because it will lead
        //to a lot of pruning.
         if(tl == 0)
            tl = 4;
         if(tl == -1)
            tl =0;

    }

    if(i-1>=0 && j < width)
    {
        tr = b.getGrid()[i-1][j].Getvalue();
         if(tr == 0)
            tr = 4;
         if(tr == -1)
            tr =0;

    }

    if(i < height && j-1 >= 0)
    {
        bl = b.getGrid()[i][j-1].Getvalue();
        if(bl == 0)
            bl = 4;
        if(bl == -1)
            bl =0;

    }

    if(i<height && j < width)
    {
        br = b.getGrid()[i][j].Getvalue();
        if(br == 0)
            br = 4;
        if(br == -1)
            br =0;

    }


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
Edge BoardSolver::determineStartEdge(Point p)
{
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


bool BoardSolver::isSolutionStillPossible(vector<Point> visitedPoints, Point destPoint, Point currPoint)
{
    int height = b.getHeight()+1;
    int width = b.getWidth()+1;
    //Assume destPoint is above and to the left of currPoint
    bool destBelow = false; //Flag for if destination point is below current point
    bool destRight = false; //Flag for if destination point is to the right of the current point

    if(currPoint.row < destPoint.row)
        destBelow = true;
    if(currPoint.column < destPoint.column)
        destRight = true;

    //If destination point is above and to the left of the current point
    if(!destBelow && !destRight)
    {
        bool lineFormed = false;
        //Check for horizontal "lines" which prevent reaching a solution
        lineFormed = checkForLinesFormed(destPoint.row+1, currPoint.row, 0, width, visitedPoints);
        if(lineFormed)
            return false;

        //Check for vertical "lines" which prevent reaching a solution
        lineFormed =checkForLinesFormed(destPoint.column+1, currPoint.column, 0, height, visitedPoints);
        if(lineFormed)
            return false;

        //Check for "boxes" which box in the destination point
        int hLineRow = checkForLinesFormed(destPoint.row+1, currPoint.row, 0, currPoint.column, visitedPoints, true);
        if(hLineRow <= b.getHeight()+1)
        {
            lineFormed = checkForLinesFormed(destPoint.column+1, currPoint.column, 0, hLineRow, visitedPoints);
            if(lineFormed)
                return false;
        }
    }

    //If destination point is above and to the right of the current point
    /*if(!destBelow && destRight)
    {
        bool lineFormed = false;
        //Check for horizontal "lines" which prevent reaching a solution
        lineFormed = checkForLinesFormed(destPoint.row+1, currPoint.row, 0, width, visitedPoints);
        if(lineFormed)
            return false;

        //Check for vertical "lines" which prevent reaching a solution
        lineFormed =checkForLinesFormed(currPoint.column+1, destPoint.column, 0, height, visitedPoints);
        if(lineFormed)
            return false;

        //Check for "boxes" which box in the destination point
        /*int hLineRow = checkForLinesFormed(destPoint.row+1, currPoint.row, currPoint.column+1, width, visitedPoints, true);
        if(hLineRow <= b.getHeight()+1)
        {
            lineFormed = checkForLinesFormed(currPoint.column+1, destPoint.column, 0, hLineRow, visitedPoints);
            if(lineFormed)
                return false;
        }
    }*/

    /*
    //If destination point is below and to the left of the current point
    if(destBelow && !destRight)
    {
        bool lineFormed = false;
        //Check for horizontal "lines" which prevent reaching a solution
        lineFormed = checkForLinesFormed(currPoint.row+1, destPoint.row, 0, width, visitedPoints);
        if(lineFormed)
            return false;

        //Check for vertical "lines" which prevent reaching a solution
        lineFormed =checkForLinesFormed(destPoint.column+1, currPoint.column, 0, height, visitedPoints);
        if(lineFormed)
            return false;

        //Check for "boxes" which box in the destination point
        /*int hLineRow = checkForLinesFormed(currPoint.row+1, destPoint.row, 0, currPoint.column, visitedPoints,false);
        if(hLineRow > -1)
        {
            lineFormed = checkForLinesFormed(destPoint.column+1, currPoint.column, hLineRow, height,  visitedPoints);
            if(lineFormed)
                return false;
        }

    }

    //If the destination point is below and to the right of the current point
    if(destBelow && destRight)
    {
        bool lineFormed = false;
        //Check for horizontal "lines" which prevent reaching a solution
        lineFormed = checkForLinesFormed(currPoint.row+1, destPoint.row, 0, width, visitedPoints);
        if(lineFormed)
            return false;

        //Check for vertical "lines" which prevent reaching a solution
        lineFormed =checkForLinesFormed(currPoint.column+1, destPoint.column, 0, height, visitedPoints);
        if(lineFormed)
            return false;

        //Check for "boxes" which box in the destination point
        /* hLineRow = checkForLinesFormed(currPoint.row+1, destPoint.row, currPoint.column +1, width, visitedPoints, false);
        if(hLineRow > -1)
        {
            lineFormed = checkForLinesFormed(destPoint.column+1, currPoint.column, hLineRow, height,  visitedPoints);
            if(lineFormed)
                return false;
        }
    }*/

    return true;

}

bool BoardSolver::checkForLinesFormed(int outerStart, int outerEnd, int innerStart, int innerEnd, vector<Point> visitedPoints)
{
    //For each row above the current point
    for(int i = outerStart; i < outerEnd; i++)
    {
        bool lineFormed = true;
        //See if a line is formed with all the points
        for(int j = innerStart; j < innerEnd; j++)
        {
            Point target = Point(i,j);
            //If any of the points are not found, we know a line has not been formed
            if(find(visitedPoints.begin(), visitedPoints.end(), target) == visitedPoints.end())
            {
                lineFormed=false;break;
            }
        }
        if(lineFormed)
            return true;
    }


    return false;
}

int BoardSolver::checkForLinesFormed(int outerStart, int outerEnd, int innerStart, int innerEnd,
                                     vector<Point> visitedPoints, bool returnMin)
{
    int minPos = b.getHeight()+5; // The closest line found to the origin
    int maxPos = -1; //The farthest line found to the origin
    //For each row above the current point
    for(int i = outerStart; i < outerEnd; i++)
    {
        bool lineFormed = true;
        //See if a line is formed with all the points
        for(int j = innerStart; j < innerEnd; j++)
        {
            Point target = Point(i,j);
            //If any of the points are not found, we know a line has not been formed
            if(find(visitedPoints.begin(), visitedPoints.end(), target) == visitedPoints.end())
            {
                lineFormed=false;break;
            }
        }
        if(lineFormed && i < minPos)
            minPos = i;
        if(lineFormed && i > maxPos)
            maxPos = i;

    }
    if(returnMin)
        return minPos;
    else
        return maxPos;
}


bool BoardSolver::doesEdgeInvalidateSquare(Edge e)
{
    markBoardWithSolution(solutionArray); //Mark the board with the current solution array
    Point sq1 = e.get1stSquareCoord();
    Point sq2 = e.get2ndSquareCoord(b.getHeight(), b.getWidth());

    //Check square one
    if(sq1.row != -1)
    {
        Square s = b.getGrid()[sq1.row][sq1.column];
        int sideCount = s.GetsideCount();
        int value = s.Getvalue();
        if(sideCount == value)
            return true;
    }

    //Check square two
    if(sq2.row != -1)
    {
        Square s = b.getGrid()[sq2.row][sq2.column];
        int sideCount = s.GetsideCount();
        int value = s.Getvalue();
        if(sideCount == value)
            return true;
    }

    return false;
}
//This method is the caller of the recursive tryPoint function
vector<Edge> BoardSolver::findSolution()
{
    //Heuristics
    vector<sPoint> allPointsPromise = getAllPointsPromise();
    sort(allPointsPromise.begin(), allPointsPromise.end());


    for(int i = allPointsPromise.size()-1; i >=0; i--)
    {
        sPoint nextStartP = allPointsPromise.at(i);
        Point startPoint = Point(nextStartP.row, nextStartP.column);
        vector<Point> visitedPoints = vector<Point>();
        visitedPoints.push_back(startPoint); //Need to add start point because recursive algorithm adds the lead points.

        Point leftN = startPoint.findNeighbor("l");
        Point rightN = startPoint.findNeighbor("r");
        Point topN = startPoint.findNeighbor("t");
        Point bottomN = startPoint.findNeighbor("b");

        Edge  startEdge = determineStartEdge(startPoint);

        //Find the initial previous direction
        string initPrevDir;
        if(startEdge.getIsHorizontal())
        {
            if(startEdge.Getp2().column > startPoint.column)
                initPrevDir = "R";
            else
                initPrevDir = "L";
        }
        else
        {
             if(startEdge.Getp2().row > startPoint.row)
                initPrevDir = "B";
             else
                initPrevDir = "T";
        }

        //cout<<findPointPromise(startPoint)<<endl;
        //Initializations
        //Point startPoint = Point(0,0);
        //Point startLeadPoint = Point(1,0);
        //Edge e = Edge(startPoint, startLeadPoint);

        cout<<startPoint.row<<" "<<startPoint.column<<endl;
        tryEdge(startEdge, true, initPrevDir, startPoint, visitedPoints);

        //If couldn't find solution with first edge try alternatives
        if(!trueSolutionFound && leftN.column >= 0)
        {
            Edge newE = Edge(startPoint, leftN);
            if(!(newE == startEdge))
            {
                solutionArray.clear();
                tryEdge(newE, true, "R", startPoint, visitedPoints);
            }

        }
        if(!trueSolutionFound && rightN.column < b.getWidth()+1)
        {
            Edge newE = Edge(startPoint, rightN);
            if(!(newE == startEdge))
            {
                solutionArray.clear();
                tryEdge(newE, true, "L", startPoint, visitedPoints);
            }

        }
        if(!trueSolutionFound && topN.row >=0)
        {
            Edge newE = Edge(startPoint, topN);
            if(!(newE == startEdge))
            {
                solutionArray.clear();
                tryEdge(newE, true, "B", startPoint, visitedPoints);
            }

        }
        if(!trueSolutionFound && bottomN.row < b.getHeight()+1)
        {
            Edge newE = Edge(startPoint, bottomN);
            if(!(newE == startEdge))
            {
                solutionArray.clear();
                tryEdge(newE, true, "T", startPoint, visitedPoints);
            }

        }

        if(trueSolutionFound)
            break;
    }

    solutionAttempted = true;
    return solutionArray;
}

//Still need to edit this method
bool BoardSolver::tryEdge(Edge e, bool p1isStart, string prevDir, Point destPoint, vector<Point> visitedPoints)
{
    //If adding this edge will invalidate an already existing square, return
    if(doesEdgeInvalidateSquare(e))
        return false;
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
    //See if a solution is still possible
    if(!isSolutionStillPossible(visitedPoints, destPoint, leadPoint))
    {
        //cout<<"Solution not still possible"<<endl<<"returned"<<endl;
        return false;
    }

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
    bool solved = false;
    if(prevDir != "T")
        solved=recurStepTop(leadPoint,destPoint,visitedPoints);
    if(prevDir != "B" && !solved)
        solved=recurStepBottom(leadPoint,destPoint,visitedPoints);
    if(prevDir != "L" && !solved)
        solved=recurStepLeft(leadPoint,destPoint,visitedPoints);
    if(prevDir != "R" && !solved)
        solved=recurStepRight(leadPoint,destPoint,visitedPoints);
    else
    {
    }

    /*vector<sPoint> nextPoints = orderNeighbors(leadPoint);
    //Vector is sorted in ascending order so we start at the end and go down
    for(int i = nextPoints.size() -1 ; i >= 0; i--)
    {
        sPoint sp = nextPoints.at(i);
        Point nextP = Point(sp.row, sp.column);
        string id = sp.id;


        if(id == "l" && prevDir != "L")
        {
            solved = recurStepLeft(leadPoint,destPoint,visitedPoints);
        }
        else if(id == "r" && prevDir != "R" && !solved)
        {
            solved = recurStepRight(leadPoint,destPoint,visitedPoints);
        }
        else if(id == "t" && prevDir != "T" && !solved)
        {
            solved = recurStepTop(leadPoint,destPoint,visitedPoints);
        }
        else if(id == "b" && prevDir != "B" && !solved)
        {
            solved=recurStepBottom(leadPoint,destPoint,visitedPoints);
        }
        else
        {
        }
    }*/
    solutionArray.pop_back();
    //cout<<"returned"<<endl;
    return solved;
}

bool BoardSolver::recurStepTop(Point leadPoint, Point destPoint, vector<Point> visitedPoints)
{
    int row = leadPoint.row;
    int column = leadPoint.column;
    if(leadPoint.row-1 >= 0)
    {
        Point topN = Point(row-1,column);
        Edge e = Edge(leadPoint, topN);
        return tryEdge(e, true, "B", destPoint, visitedPoints);
    }
    return false;
}
bool BoardSolver::recurStepBottom(Point leadPoint, Point destPoint, vector<Point> visitedPoints)
{
    int row = leadPoint.row;
    int column = leadPoint.column;
    if(row+1 < b.getHeight()+1)
    {
        Point bottomN = Point(row+1,column);
        Edge e = Edge(leadPoint, bottomN);
        return tryEdge(e, true, "T", destPoint, visitedPoints);
    }
    return false;
}
bool BoardSolver::recurStepLeft(Point leadPoint, Point destPoint, vector<Point> visitedPoints)
{
    int row = leadPoint.row;
    int column = leadPoint.column;
    if(column-1 >= 0)
    {
        Point leftN = Point(row,column-1);
        Edge e = Edge(leadPoint, leftN);
        return tryEdge(e, true, "R", destPoint, visitedPoints);
    }
    return false;
}
bool BoardSolver::recurStepRight(Point leadPoint, Point destPoint, vector<Point> visitedPoints)
{
    int row = leadPoint.row;
    int column = leadPoint.column;
    if(column+1 < b.getWidth()+1)
    {
        Point rightN = Point(row,column+1);
        Edge e = Edge(leadPoint, rightN);
        return tryEdge(e, true, "L", destPoint, visitedPoints);
    }
    return false;
}

vector<sPoint> BoardSolver::orderNeighbors(Point leadPoint)
{
    int height = b.getHeight() + 1;
    int width = b.getWidth() +1;
    vector<sPoint> neighbors = vector<sPoint>();
    Point leftN = leadPoint.findNeighbor("l");
    Point rightN = leadPoint.findNeighbor("r");
    Point topN = leadPoint.findNeighbor("t");
    Point bottomN = leadPoint.findNeighbor("b");

    if(rightN.row >=0 && rightN.row < height && rightN.column >=0 && rightN.column < width)
    {
        sPoint srightN = sPoint(rightN.row, rightN.column, findPointPromise(rightN), "r");
        neighbors.push_back(srightN);
    }
    if(leftN.row >=0 && leftN.row < height && leftN.column >=0 && leftN.column < width)
    {
        sPoint sleftN = sPoint(leftN.row, leftN.column, findPointPromise(leftN), "l");
        neighbors.push_back(sleftN);
    }
    if(bottomN.row >=0 && bottomN.row < height && bottomN.column >=0 && bottomN.column < width)
    {
        sPoint sbottomN = sPoint(bottomN.row, bottomN.column, findPointPromise(bottomN), "b");
        neighbors.push_back(sbottomN);
    }
    if(topN.row >=0 && topN.row < height && topN.column >=0 && topN.column < width)
    {
        sPoint stopN = sPoint(topN.row, topN.column, findPointPromise(topN), "t");
        neighbors.push_back(stopN);
    }

    //sort(neighbors.begin(), neighbors.end());
    return neighbors;

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
