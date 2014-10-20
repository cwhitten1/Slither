#include "Square.h"
#include <iostream>

Square::Square()
{ value = -1;
}
Square::Square(int val, Point topLeft)
{
    value = val; //A value of -1 denotes no value
    topLeftPt = topLeft;

    //False means that sides are not marked
    s_left= false;
    s_right = false;
    s_top = false;
    s_bottom = false;

    sideCount = 0;
    isValid = true;
}

Square::~Square()
{
    //dtor
}

void Square:: markSide(string side)
{
    if(side == "l")
        s_left = true;
    else if(side == "r")
        s_right = true;
    else if(side == "t")
        s_top = true;
    else if(side == "b")
        s_bottom = true;
    else
    {
        cout<< "Invalid side type"<< endl;
        return;
    }

    determineValidity();
    sideCount++;
}

 void Square::determineValidity()
{
    //A square cannot have all four sides marked.
    if(sideCount == 4)
    {
        isValid = false;
        return;
    }

    //If the square has a value, check the sideCount
    if(value != -1)
    {
        if((sideCount == value))
            isValid = true;
        else
            isValid = false;
    }
    //If the square does not have a value, return true
    else
        isValid = true;
}
