#ifndef POINT_H
#define POINT_H


class Point
{
    public:
        Point(int row, int column);
        virtual ~Point();
        int row;
        int column;
        int findNeighbor(String direction); //Use "l/r/t/b"
    protected:
    private:
};

#endif // POINT_H
