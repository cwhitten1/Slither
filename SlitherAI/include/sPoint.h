#ifndef SPOINT_H
#define SPOINT_H

class sPoint
{
    public:
        sPoint();
        sPoint(int row, int column, bool isMarked);
        virtual ~sPoint();
        int row;
        int column;
        bool isMarked;
        void setIsMarked(bool val);
        bool operator== (sPoint &p){return (row == p.row && column == p.column);};//Override equality operator}:
    protected:
    private:
};

#endif // SPOINT_H
