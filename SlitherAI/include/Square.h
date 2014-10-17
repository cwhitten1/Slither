#ifndef SQUARE_H
#define SQUARE_H
#include <string>
using namespace std;

class Square
{
    public:
        Square();
        virtual ~Square();
        int Getvalue() { return value; }
        void Setvalue(int val) { value = val; }
        bool Gets_left() { return s_left; }
        bool Gets_right() { return s_right; }
        bool Gets_top() { return s_top; }
        bool Gets_bottom() { return s_bottom; }
        void markSide(string side); // Supports "l/r/t/b"
        bool GetisValid() { return isValid; }
        void SetisValid(bool val) { isValid = val; }
        int GetsideCount() { return sideCount; }
        void SetsideCount(int val) { sideCount = val; }
    protected:
    private:
        int value;
        bool s_left;
        bool s_right;
        bool s_top;
        bool s_bottom;
        bool isValid;
        int sideCount;
        void determineValidity();
};

#endif // SQUARE_H
