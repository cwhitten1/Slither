#include "Board.h"
#include <iostream>
#include <stdbool.h>
#include <algorithm>
using namespace std;

Board::Board()
{
}
Board::Board(int w, int h, vector<Square> sq)
{
    initialSquares=sq;
    width=w;
    height=h;

    makeGrid();
}

Board::~Board()
{
}

bool Board::isContLoop()
{
    ArrayList<Point> markedSquares = generateMarkedSquares();
    ArrayList<Edge> markedEdges = generateMarkedEdges(markedSquares);
    ArrayList<Point> edgePoints = ArrayList<Point>();

    int loopCounter = 0; //This variable keeps track of the number of continuous loops in the board
    for(int i = 0; i < markedEdges.Getsize(); i++)
    {
        if(edgePoints.Getsize() == 0)
            loopCounter++;

        Edge e = markedEdges.get(i);
        //cout<< "Edge " << i <<endl;
        //If point 1 has not been added, add it, else remove it
        int index1 = edgePoints.find(e.Getp1());
        if(index1 == -1)
        {
            edgePoints.add(e.Getp1());
            //cout<<"Added point: "<< e.Getp1().row <<" "<<e.Getp1().column<<endl;
        }
        else
        {
            edgePoints.remove(index1);
            //cout<<"Removed point: "<< e.Getp1().row <<" "<<e.Getp1().column<<endl;
        }

        //If point 2 has not been added, add it, else remove it
        int index2 = edgePoints.find(e.Getp2());
        if(index2 == -1)
        {
            edgePoints.add(e.Getp2());
            //cout<<"Added point: "<< e.Getp2().row <<" "<<e.Getp2().column<<endl;
        }
        else
        {
            edgePoints.remove(index2);
            //cout<<"Removed point: "<< e.Getp2().row <<" "<<e.Getp2().column<<endl;
        }
    }
    if(edgePoints.Getsize() > 0 || loopCounter != 1)
        return false;
    else
        return true;
}

bool Board::areSquaresValid()
{
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            Square s = grid[i][j];
            if((s.GetisValid()) == false)
            {
                //cout<<"Invalid square: "<<i<< " "<< j<<endl;
                return false;
            }
        }
    }

    return true;
}

int Board::getNumValidSquares()
{
    int num = 0;
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            Square s = grid[i][j];
            if((s.GetisValid()) == true)
                num++;
        }
    }

    return num;
}

int Board::getNumEdges()
{
    return height*(width+1) + width*(height+1);
}

void Board::makeMove(int row, int column, string side)
{
    Square* s = &grid[row][column];
    Square* adj;
    if(side == "L")
    {
        s->toggleSide(side);

        //A left mark on square s will also mark the right side on the left adjacent square
        if(column -1 >= 0)
        {
            adj = &(grid[row][column -1]);
            adj->toggleSide("R");
        }
    }
    else if(side == "R")
    {
        s->toggleSide(side);

        //A right mark on square s will also mark the left side on the right adjacent square
        if(column+1 < width)
        {
            adj = &(grid[row][column +1]);
            adj->toggleSide("L");
        }
    }
    else if(side == "T")
    {
        s->toggleSide(side);

        //A top mark on square s will also mark the bottom side on the top adjacent square
        if(row - 1 >= 0)
        {
            adj = &(grid[row - 1][column]);
            adj->toggleSide("B");
        }
    }
    else if(side == "B")
    {
        s->toggleSide(side);

        //A bottom mark on square s will also mark the top side on the bottom adjacent square
        if(row+1 < height)
        {
           adj = &(grid[row +1][column]);
           adj->toggleSide("T");
        }
    }
    else
    {
        cout<<"Invalid move please try again"<<endl;
        return; //Return so that the null adj is not addedToMSquares
    }
}

void Board::makeGrid()
{
    //Initialize the grid: (0,0) - (n,n)
    grid = new Square*[height];
    for(int i = 0; i<height; i++)
        grid[i] = new Square[width];

    //Fill in grid with empty squares
    fillGrid();

    //Add initialSquares to the grid
    for(unsigned int j = 0; j < initialSquares.size();j++)
    {
        Square s = initialSquares.at(j);
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
            grid[i][j] = Square(-1,Point(i,j)); //Fill grid with empty squares
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


void Board::clearBoard()
{
    for(int i = 0; i <height;i++)
        {
            for(int j =0; j<width; j++)
            {
                Square s = grid[i][j];
                if(s.Gets_bottom())
                    grid[i][j].toggleSide("B");
                if(s.Gets_top())
                    grid[i][j].toggleSide("T");
                if(s.Gets_left())
                    grid[i][j].toggleSide("L");
                if(s.Gets_right())
                    grid[i][j].toggleSide("R");
            }
        }
}

ArrayList<Point> Board::generateMarkedSquares()
{
    ArrayList<Point> markedSquares = ArrayList<Point>();
    for(int i = 0; i < height; i++)
    {
        for(int j=0; j < width; j++)
        {
            Square s = grid[i][j];
            Point pos = s.Getposition();

            if(s.Gets_bottom() || s.Gets_left() || s.Gets_right() || s.Gets_top())
                markedSquares.add(pos);
        }
    }

    return markedSquares;
}

ArrayList<Edge> Board::generateMarkedEdges(ArrayList<Point>& markedSquares)
{
    ArrayList<Edge> markedEdges = ArrayList<Edge>();
    //For every marked square
    for(int i =0; i < markedSquares.Getsize(); i++)
    {
        Point sqPos = markedSquares.get(i);
        Square s = grid[sqPos.row][sqPos.column];

       //If one of it's edges is marked and is not yet in the list of edges, add it
       if(s.Gets_top())
       {
           Edge top = Edge( Point(sqPos.row, sqPos.column), Point(sqPos.row, sqPos.column+1) );
           if(markedEdges.find(top) == -1)
                markedEdges.add(top);
       }
       if(s.Gets_bottom())
       {
           Edge bottom = Edge( Point(sqPos.row+1, sqPos.column), Point(sqPos.row+1, sqPos.column+1) );
           if(markedEdges.find(bottom) == -1)
                markedEdges.add(bottom);
       }
       if(s.Gets_left())
       {
           Edge left = Edge( Point(sqPos.row, sqPos.column), Point(sqPos.row+1, sqPos.column) );
           if(markedEdges.find(left) == -1)
                markedEdges.add(left);
       }
       if(s.Gets_right())
       {
           Edge right = Edge( Point(sqPos.row, sqPos.column+1), Point(sqPos.row+1, sqPos.column+1) );
           if(markedEdges.find(right) == -1)
                markedEdges.add(right);
       }
    }

    return markedEdges;
}
