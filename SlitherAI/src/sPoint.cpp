#include "sPoint.h"

sPoint::sPoint()
{
    isMarked = false;
}
sPoint::sPoint(int row, int column, bool val)
{
    this->row = row;
    this->column = column;
    setIsMarked(val);
}
sPoint::~sPoint()
{
}

void sPoint::setIsMarked(bool val)
{
    isMarked = val;
}
