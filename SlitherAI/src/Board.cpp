#include "Board.h"
#include <iostream>
#include <Point.h>
using namespace std;

Board::Board()
{
}
Board::Board(int w, int h, ArrayList<Square>& sq)
{
    squares = sq;
    width=w;
    height=h;

    makeGrid();
}

Board::~Board()
{
    squares.~ArrayList();
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
}

void Board::makeGrid()
{
    //Initialize the grid: (0,0) - (n,n)
    grid = new Square*[height];
    for(int i = 0; i<height; i++)
        grid[i] = new Square[width];

    //Fill in grid with empty squares
    //fillGrid();

    cout<< "Size: " << squares.Getsize()<<endl;

    //Add squares to the grid
    for(int j = 0; j < squares.Getsize();j++)
    {
        Square s = squares.get(j);
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


