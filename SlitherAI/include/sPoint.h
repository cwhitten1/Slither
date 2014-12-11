#ifndef SPOINT_H
#define SPOINT_H
#include <string>
using namespace std;
class sPoint
{
    public:
        sPoint();
        sPoint(int row, int column, int promise, string id);
        virtual ~sPoint();
        string id;
        int row;
        int column;
        int promise;
        bool operator== (sPoint &p){return (row == p.row && column == p.column);};//Override equality operator}:
        bool operator< (const sPoint& p) const {return (promise < p.promise);}
    protected:
    private:
};

#endif // SPOINT_H
