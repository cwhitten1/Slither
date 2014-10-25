#ifndef POINT_H
#define POINT_H
#include <string>
using namespace std;

class Point
{
    public:
        Point();
        Point(int row, int column);
        virtual ~Point();
        int row;
        int column;
        Point findNeighbor(string direction); //Use "l/r/t/b"
        bool operator== (Point &p2){return (row == p2.row && column == p2.column);};//Override equality operator
    protected:
    private:
};


#endif // POINT_H
