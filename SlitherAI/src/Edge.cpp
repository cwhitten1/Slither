#include "Edge.h"
using namespace std;
Edge::Edge()
{
}
Edge::Edge(Point p1, Point p2)
{
    this->p1 = p1;
    this->p2 = p2;

    if(p1.row == p2.row)
        isHorizontal = true;
    else
        isHorizontal = false;
}

Edge::~Edge()
{
}

Point Edge::get1stSquareCoord()
{
    if(isHorizontal)
    {
        if(p1.row-1 >= 0)
        {
            int col = min(p1.column, p2.column);
            return Point(p1.row-1, col);
        }
        else
            return Point(-1,-1);
    }
    else
    {
        if(p1.column-1 >= 0)
        {
            int row = min(p1.row, p2.row);
            return Point(row, p1.column-1);
        }
        else
            return Point(-1,-1);
    }
}

Point Edge::get2ndSquareCoord(int maxHeight, int maxWidth)
{
    if(isHorizontal)
    {
        if(p1.row < maxWidth)
        {
            int col = min(p1.column, p2.column);
            return Point(p1.row, col);
        }
        else
            return Point(-1,-1);
    }
    else
    {
        if(p1.column+1 < maxHeight)
        {
            int row = min(p1.row, p2.row);
            return Point(row, p1.column);
        }
        else
            return Point(-1,-1);
    }
}

