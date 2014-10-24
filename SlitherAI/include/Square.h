#ifndef SQUARE_H
#define SQUARE_H
#include <string>
#include <Point.h>
using namespace std;

class Square
{
    public:
        Square();
        Square(int value, Point position);
        virtual ~Square();
        int Getvalue() { return value; }
        void Setvalue(int val) { value = val; }
        bool Gets_left() { return s_left; } //Get whether or not left side is marked.
        bool Gets_right() { return s_right; }
        bool Gets_top() { return s_top; }
        bool Gets_bottom() { return s_bottom; }
        void toggleSide(string side); // Supports "L/R/T/B"
        bool GetisValid() { return isValid; }
        void SetisValid(bool val) { isValid = val; }
        int GetsideCount() { return sideCount; }
        void SetsideCount(int val) { sideCount = val; }
        Point Getposition() { return position;}
        void Setposition(Point p) { position = p;}
        void determineValidity();
    protected:
    private:
        int value;
        int sideCount;
        bool s_left;
        bool s_right;
        bool s_top;
        bool s_bottom;
        bool isValid;
        Point position;

};

#endif // SQUARE_H
