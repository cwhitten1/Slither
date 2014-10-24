#include "Board.h"
#include <iostream>
#include <stdbool.h>
using namespace std;

Board::Board()
{
}
Board::Board(int w, int h, ArrayList<Square>& sq)
{
    initialSquares = sq;
    width=w;
    height=h;

    makeGrid();
    hasCrosses = 0;
    markedSquares = new ArrayList<Point>();
}

Board::~Board()
{
    initialSquares.~ArrayList();
}

bool Board::isSolved()
{
    bool solved = true;
    if(areSquaresValid() == false)
        return false; //If the square values are not satisfied then the board cannot be solved.
    else
    {
        //For each marked square, make sure there are no crosses
        for(int i = 0; i< markedSquares->Getsize(); i++ )
        {
            Point p = markedSquares->get(i);
            int row = p.row;
            int column = p.column;

            Square s = grid[row][column];
            checkForCrosses(s);
        }

        if(hasCrosses)
        {
            solved = false;
            hasCrosses = false; //Reset the hasCrosses variable
        }
    }

    return solved;
}
bool Board::areSquaresValid()
{
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            Square s = grid[i][j];
            if((s.GetisValid()) == false)
                return false;
        }
    }

    return true;
}

void Board::checkForCrosses(Square s)
{
    int sRow = s.Getposition().row;
    int sColumn = s.Getposition().column;
    bool left = s.Gets_left();
    bool right = s.Gets_right();
    bool top = s.Gets_top();
    bool bottom = s.Gets_bottom();

    //Whatever corner is marked, that is the square we will move to diagonally in order to evaluate for crosses
    //i.e. top left moves row-1 and column -1
    if(top && left)
    {
        bool hasAdj = false; //hasAdj here to make sure we don't assign the square s as the adj square as well.

        if((sRow -1 >= 0) && (sColumn-1 >= 0))
        {
            sRow--;
            sColumn--;
            hasAdj = true;
        }
        else if(sRow -1 >= 0)
        {
            sRow--;
            hasAdj = true;
        }
        else if(sColumn -1 >= 0)
        {
            sColumn--;
            hasAdj = true;
        }

        if(hasAdj)
        {
            Square adj = grid[sRow][sColumn];
            bool leftConflict =((s.Gets_left() == true) && (adj.Gets_bottom() == true)) ? true:false;
            bool topConflict = ((s.Gets_top() == true) && (adj.Gets_right() == true))? true:false;
            if(leftConflict || topConflict)
                hasCrosses = true;
        }
    }
    else if(bottom && right)
    {
        bool hasAdj = false; //hasAdj here to make sure we don't assign the square s as the adj square as well.

        if((sRow +1 < height) && (sColumn+1 < width))
        {
            sRow++;
            sColumn++;
            hasAdj = true;
        }
        else if(sRow +1 < height)
        {
            sRow++;
            hasAdj = true;
        }
        else if(sColumn +1 < width)
        {
            sColumn++;
            hasAdj = true;
        }

        if(hasAdj)
        {
            Square adj = grid[sRow][sColumn];
            bool rightConflict =((s.Gets_right() == true) && (adj.Gets_top() == true)) ? true:false;
            bool bottomConflict = ((s.Gets_bottom() == true) && (adj.Gets_left() == true))? true:false;
            if(rightConflict || bottomConflict)
                hasCrosses = true;
        }
    }
    else if(bottom && left)
    {
        bool hasAdj = false; //hasAdj here to make sure we don't assign the square s as the adj square as well.

        if((sRow +1 < height) && (sColumn-1 >= 0))
        {
            sRow++;
            sColumn--;
            hasAdj = true;
        }
        else if(sRow +1 < height)
        {
            sRow++;
            hasAdj = true;
        }
        else if(sColumn -1 >= 0)
        {
            sColumn--;
            hasAdj = true;
        }

        if(hasAdj)
        {
            Square adj = grid[sRow][sColumn];
            bool leftConflict =((s.Gets_left() == true) && (adj.Gets_top() == true)) ? true:false;
            bool bottomConflict = ((s.Gets_bottom() == true) && (adj.Gets_right() == true))? true:false;
            if(leftConflict || bottomConflict)
                hasCrosses = true;
        }
    }
    else if(top && right)
    {
                bool hasAdj = false; //hasAdj here to make sure we don't assign the square s as the adj square as well.

        if((sRow - 1 >= 0) && (sColumn+1 < width))
        {
            sRow--;
            sColumn++;
            hasAdj = true;
        }
        else if(sRow -1 >= 0)
        {
            sRow--;
            hasAdj = true;
        }
        else if(sColumn +1 < width)
        {
            sColumn++;
            hasAdj = true;
        }

        if(hasAdj)
        {
            Square adj = grid[sRow][sColumn];
            bool rightConflict =((s.Gets_right() == true) && (adj.Gets_bottom() == true)) ? true:false;
            bool topConflict = ((s.Gets_top() == true) && (adj.Gets_left() == true))? true:false;
            if(rightConflict || topConflict)
                hasCrosses = true;
        }
    }
    else
    {
        cout<<"Something wrong in checkForCrosses() method"<<endl;
        return;
    }
}

void Board::makeMove(int row, int column, string side)
{
    //Check row and column
    if(row >= height || column >= width || row < 0 || column < 0)
    {
        cout<<"Invalid move please try again"<<endl;
        return;
    }
    Square* s = &grid[row][column];

    if(side == "L")
    {
        s->toggleSide(side);

        //A left mark on square s will also mark the right side on the left adjacent square
        if(column -1 >= 0)
            grid[row][column -1].toggleSide("R");

        drawBoard();
    }
    else if(side == "R")
    {
        s->toggleSide(side);

        //A right mark on square s will also mark the left side on the right adjacent square
        if(column+1 < width)
            grid[row][column +1].toggleSide("L");

        drawBoard();
    }
    else if(side == "T")
    {
        s->toggleSide(side);

        //A top mark on square s will also mark the bottom side on the top adjacent square
        if(row - 1 >= 0)
            grid[row - 1][column].toggleSide("B");

        drawBoard();
    }
    else if(side == "B")
    {
        s->toggleSide(side);

        //A bottom mark on square s will also mark the top side on the bottom adjacent square
        if(row+1 < height)
        {
            grid[row +1][column].toggleSide("T");
        }

        drawBoard();
    }
    else
        cout<<"Invalid move please try again"<<endl;

    if(s->GetsideCount() > 0)
        addToMSquares(Point(row,column));
}

void Board::makeGrid()
{
    //Initialize the grid: (0,0) - (n,n)
    grid = new Square*[height];
    for(int i = 0; i<height; i++)
        grid[i] = new Square[width];

    //Fill in grid with empty squares
    //fillGrid();

    //Add initialSquares to the grid
    for(int j = 0; j < initialSquares.Getsize();j++)
    {
        Square s = initialSquares.get(j);
        Point tlCorner = s.Getposition();
        int row = tlCorner.row;
        int column = tlCorner.column;

        cout<< row << "," <<column<<endl;
        grid[row][column].Setvalue(s.Getvalue());
        grid[row][column].Setposition(tlCorner);
    }
    cout<<endl<<endl;
}

void Board::fillGrid()
{
    for(int i = 0; i <height;i++)
    {
        for(int j =0; j<width; j++)
        {
            grid[i][j] = Square();
        }
    }
}

void Board::drawBoard()
{
    cout<<endl<<endl; //Make space
    //Print column numbers
    cout<<" ";
    for(int j = 0; j < width; j++)
        cout<<j+1<<" ";
    cout<<endl;

    //Print the grid
    for(int i = 0; i<height; i++)
    {
        //Print top row of '+' and '-'
        cout<<"+";
        for(int j = 0; j < width; j++)
        {
            Square s = grid[i][j];

            if(s.Gets_top())
                cout<<"-";
            else
                cout<<" ";

            cout<<"+";
        }
        cout<<endl;

        //Print first left side for row if it is marked
        if(grid[i][0].Gets_left())
            cout<<"|";
        else
            cout<<" ";

        //Print values and right sides
        for(int j =0; j < width; j++)
        {
            Square s = grid[i][j];

            //Print value
            int val = s.Getvalue();
            if(val != -1)
                cout<<val;
            else
                cout<<" ";

            //Print right side
            if(s.Gets_right())
                cout<<"|";
            else
                cout<<" ";
        }

        // Print row number and go to next line
        cout<<"  "<<i+1<<endl;
    }

    //Print the last line of '+' and '-'
    cout<<"+";
    for(int j = 0; j < width; j++)
    {
        Square s = grid[height-1][j];
        if(s.Gets_bottom())
            cout<<"-";
        else
            cout<<" ";

        cout<<"+";
    }
    cout<<endl<<endl<<endl;
}


void Board::addToMSquares(Point p)
{
    int row = p.row;
    int column = p.column;

    //Make sure point does not already exist in markedSquares
    for(int i = 0; i < markedSquares->Getsize(); i++)
    {
        Point pt = markedSquares->get(i);
        if((pt.row == row) && (pt.column == column))
            return;
    }

    markedSquares->add(p); //This will only be reached if point does not already exist.
}
