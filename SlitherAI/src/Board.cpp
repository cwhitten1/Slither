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
    squares.removeAll();
    squares.~ArrayList();
}

void Board::makeGrid()
{
    //Initialize the grid: (0,0) - (n,n)
    Square** grid;
    grid = new Square*[height];
    for(int i = 0; i<height; i++)
        grid[i] = new Square[width];

    cout<< "Size" << squares.Getsize()<<endl;
    //Add squares to the grid
    for(int j = 0; j < squares.Getsize();j++)
    {
        cout<< j<<endl;
        Square s = squares.get(j);
        Point tlCorner = s.GettopLeftPt();
        int row = tlCorner.row;
        int column = tlCorner.column;

        grid[row][column].Setvalue(s.Getvalue());
        grid[row][column].SettopLeftPt(tlCorner);
    }

    //Fill in grid with empty squares
    fillGrid();
}

void Board::fillGrid()
{
    for(int i = 0; i <height;i++)
    {
        for(int j =0; j<width; j++)
        {
            Square s = grid[i][j];
            //If the position is empty, add a blank square.
            if(!s.Getvalue())
            {
                s.Setvalue(-1);
                s.SetsideCount(0);
                s.SettopLeftPt(Point(i,j));
            }
        }
    }
}
void Board::drawBoard()
{
    cout<< "this is where the board will be"<<endl;
}
