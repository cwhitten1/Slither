#include "Square.h"
#include <iostream>

Square::Square()
{
    value = -1;
    //False means that sides are not marked
    s_left= false;
    s_right = false;
    s_top = false;
    s_bottom = false;

    sideCount = 0;
    isValid = true;
}
Square::Square(int val, Point topLeft)
{
    value = val; //A value of -1 denotes no value
    position = topLeft;

    //False means that sides are not marked
    s_left= false;
    s_right = false;
    s_top = false;
    s_bottom = false;

    sideCount = 0;
    determineValidity();
}

Square::~Square()
{
    //dtor
}

void Square:: toggleSide(string side)
{
    if(side == "L")
    {
        if(s_left == true)
        {
            s_left = false;
            sideCount--;
        }
        else
        {
            s_left = true;
            sideCount++;
        }
    }
    else if(side == "R")
    {
        if(s_right)
        {
            s_right  = false;
            sideCount--;
        }
        else
        {
            s_right = true;
            sideCount++;
        }
    }
    else if(side == "T")
    {
        if(s_top)
        {
            s_top  = false;
            sideCount--;
        }
        else
        {
            s_top = true;
            sideCount++;
        }
    }
    else if(side == "B")
    {
        if(s_bottom)
        {
            s_bottom  = false;
            sideCount--;
        }
        else
        {
            s_bottom = true;
            sideCount++;
        }
    }
    else
    {
        cout<< "Invalid side type"<< endl;
        return;
    }

    determineValidity();
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
        if(sideCount == value)
            isValid = true;
        else
            isValid = false;
    }
    //If the square does not have a value, return true
    else
        isValid = true;
}
