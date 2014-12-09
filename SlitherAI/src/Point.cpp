#include "Point.h"
#include <iostream>
#include <string>

using namespace std;

Point::Point()
{
}

Point::Point(int row, int column)
{
    this->row = row;
    this->column = column;
}

Point::~Point()
{
    //dtor
}

Point Point::findNeighbor(string direction)
{
    Point p = Point(-1,-1);

    if(direction == "l")
    {
        p.column = column -1;
        p.row = row;
    }
    else if(direction == "r")
    {
        p.column = column +1;
        p.row = row;
    }
    else if(direction == "t")
    {
        p.column = column +1;
        p.row = row -1;
    }
    else if(direction == "b")
    {
        p.column = column;
        p.row = row +1;
    }
    else
        cout<<"Invalid point direction"<<endl;

    return p;
}
