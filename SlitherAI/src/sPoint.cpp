#include "sPoint.h"

sPoint::sPoint()
{
}
sPoint::sPoint(int row, int column, int promise, string id)
{
    this->row = row;
    this->column = column;
    this->promise = promise;
    this->id = id;
}
sPoint::~sPoint()
{
}
