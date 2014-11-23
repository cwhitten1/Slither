#ifndef EDGE_H
#define EDGE_H

#include "Point.h"

class Edge
{
    public:
        Edge();
        Edge(Point& p1, Point& p2);
        virtual ~Edge();
        Point Getp1() { return p1; }
        void Setp1(Point val) { p1 = val; }
        Point Getp2() { return p2; }
        void Setp2(Point val) { p2 = val; }
    protected:
    private:
        Point p1;
        Point p2;
};

#endif // EDGE_H
