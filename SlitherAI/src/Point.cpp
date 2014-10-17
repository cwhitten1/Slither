#include "Point.h"

Point::Point(int row, int column)
{
    this->row = row;
    this->column = column;
}

Point::~Point()
{
    //dtor
}

Point findNeighbor(String direction)
{
    Point p;

    if(direction == "l")
    {
        p.column = this->column -1;
        p.row = this->row;
    }
    else if(direction == "r")
    {
        p.column = this->column +1;
        p.row = this->row;
    }
    else if(direction == "t")
    {
        p.column = this->column +1;
        p.row = this->row -1;
    }
    else if(direction == "b")
    {
        p.column = this->column;
        p.row = this->row +1;
    }
    else
        cout<<"Invalid point direction"<<endl;

    if((p.row <= 0) || (p.column <= 0))
        throw exception;
    else
        return p;
}
