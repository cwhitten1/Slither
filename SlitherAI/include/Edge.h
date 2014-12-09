#ifndef EDGE_H
#define EDGE_H

#include "Point.h"

class Edge
{
    public:
        Edge();
        Edge(Point p1, Point p2);
        virtual ~Edge();
        Point Getp1() { return p1; }
        void Setp1(Point val) { p1 = val; }
        Point Getp2() { return p2; }
        void Setp2(Point val) { p2 = val; }
        bool getIsHorizontal(){return isHorizontal;}
        Point get1stSquareCoord();
        Point get2ndSquareCoord(int maxHeight, int maxWidth);
        bool operator== (Edge e) {return ((e.p1 == p1 && e.p2 == p2) || (e.p2 == p1 && e.p1 == p2)) ;}; //Override equality operator
    protected:
    private:
        Point p1;
        Point p2;
        bool isHorizontal;
};

#endif // EDGE_H
