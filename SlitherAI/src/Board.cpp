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
        bool hasCrosses = false;
        //For each marked square, make sure there are no crosses
        for(int i = 0; i< markedSquares->Getsize(); i++ )
        {
            Point p = markedSquares->get(i);
            int row = p.row;
            int column = p.column;

            Square s = grid[row][column];
            hasCrosses = checkForCrosses(s);
            //cout<<row<<" "<<column<<":"<<hasCrosses<<endl;
            //cout<<s.Gets_top()<<" "<<s.Gets_right()<<" "<<s.Gets_bottom()<<" "<<s.Gets_left()<<endl;
            if(hasCrosses)
                break; //No need for further eval if even one cross is found.
        }

        //If the grid has crosses or does not make a continuous loop, the board is not solved.
        if(hasCrosses || !traceLoop())
            solved = false;
    }

    return solved;
}

bool Board::traceLoop()
{
    //This algorithm will match an edge's points with other edges' points
    ArrayList<Point> edgePoints = ArrayList<Point>(); //

    //Start algorithm
    for(int i = 0; i< markedSquares->Getsize(); i++ )
    {
        Point p = markedSquares->get(i);
        int row = p.row;
        int column = p.column;

        Square s = grid[row][column];

        //Get the points for this square
        Point tl_p = Point(row, column);
        Point tr_p = Point(row, column+1);
        Point bl_p = Point(row+1, column);
        Point br_p = Point(row+1, column+1);

        //Get the marked sides
        bool left = s.Gets_left();
        bool right = s.Gets_right();
        bool top = s.Gets_top();
        bool bottom = s.Gets_bottom();

        //Logic to decide which points to add
        if(top)
        {
             int matchIndex_tl = edgePoints.find(tl_p); //Will return -1 if no match
             int matchIndex_tr = edgePoints.find(tr_p); //Will return -1 if no match

             //If either point can't find a match, then we know that we are not looking at a side which already exists.
             if(matchIndex_tl == -1 || matchIndex_tr == -1)
             {
                //Top left point
                if(matchIndex_tl == -1)
                    edgePoints.add(tl_p);
                else
                    edgePoints.remove(matchIndex_tl);

                //Top right point
                if(matchIndex_tr == -1)
                    edgePoints.add(tr_p);
                else
                    edgePoints.remove(matchIndex_tr);
             }
        }
        if(bottom)
        {
            int matchIndex_bl = edgePoints.find(bl_p); //Will return -1 if no match
            int matchIndex_br = edgePoints.find(br_p); //Will return -1 if no match

            if(matchIndex_bl == -1 || matchIndex_br == -1)
             {
                //Bottom left point
                if(matchIndex_bl == -1)
                    edgePoints.add(bl_p);
                else
                    edgePoints.remove(matchIndex_bl);

                //Bottom right point
                if(matchIndex_br == -1)
                    edgePoints.add(br_p);
                else
                    edgePoints.remove(matchIndex_br);
             }
        }
        if(left)
        {
            int matchIndex_tl = edgePoints.find(tl_p); //Will return -1 if no match
            int matchIndex_bl = edgePoints.find(bl_p); //Will return -1 if no match

             if(matchIndex_tl == -1 || matchIndex_bl == -1)
             {
                //Top left point
                if(matchIndex_tl == -1)
                    edgePoints.add(tl_p);
                else
                    edgePoints.remove(matchIndex_tl);

                //Bottom left point
                if(matchIndex_bl == -1)
                    edgePoints.add(bl_p);
                else
                    edgePoints.remove(matchIndex_bl);
             }
        }
        if(right)
        {
            int matchIndex_tr = edgePoints.find(tr_p); //Will return -1 if no match
            int matchIndex_br = edgePoints.find(br_p); //Will return -1 if no match

            if(matchIndex_tr == -1 || matchIndex_br == -1)
             {
                //Top right point
                if(matchIndex_tr == -1)
                    edgePoints.add(tr_p);
                else
                    edgePoints.remove(matchIndex_tr);

                //Bottom right point
                if(matchIndex_br == -1)
                    edgePoints.add(br_p);
                else
                    edgePoints.remove(matchIndex_br);
             }
        }
    cout<<edgePoints.Getsize()<<" ";
    }
    cout<<endl;
    //If the loop is continuous, then each edgePoint should have eventually been matched
    //when another edge was added. When a match occurs, we remove the edgePoint from the arraylist.
    //Therefore, if every edgePoint has exactly one match (which is the def. of a continuous loop)
    //the edgePoints arraylist will be empty.
    cout<<edgePoints.Getsize()<<endl;
    if(edgePoints.Getsize() == 0)
        return true;
    else
        return false;
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
                cout<<"Invalid square: "<<i<< " "<< j<<endl;
                return false;
            }
        }
    }

    return true;
}

bool Board::checkForCrosses(Square s)
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
        //Try to go up and left
        if((sRow -1 >= 0) && (sColumn-1 >= 0))
        {
            int row = sRow-1;
            int col = sColumn-1;

            Square adj = grid[row][col];
            bool leftConflict =((s.Gets_left() == true) && (adj.Gets_bottom() == true)) ? true:false;
            bool topConflict = ((s.Gets_top() == true) && (adj.Gets_right() == true))? true:false;
            if(leftConflict || topConflict)
                return true;
        }
        //Try to go just up
        else if(sRow -1 >= 0)
        {
            int row = sRow-1;

            Square adj = grid[row][sColumn];
            bool leftConflict =((s.Gets_left() == true) && (adj.Gets_left() == true)) ? true:false;
            if(leftConflict)
                return true;
        }
        //Try to go just left
        else if(sColumn -1 >= 0)
        {
            int col = sColumn-1;

            Square adj = grid[sRow][col];
            bool topConflict = ((s.Gets_top() == true) && (adj.Gets_top() == true))? true:false;
            if(topConflict)
                return true;

        }

    }
    if(bottom && right)
    {
        //Try to go down and right
        if((sRow +1 < height) && (sColumn+1 < width))
        {
            int row  = sRow+1;
            int col = sColumn+1;

            //Perform check
            Square adj = grid[row][col];
            bool rightConflict =(adj.Gets_top() == true) ? true:false;
            bool bottomConflict = (adj.Gets_left() == true)? true:false;
            if(rightConflict || bottomConflict)
            {
                cout<<"Conflict in right or bottom"<<endl;
                return true;
            }
        }
        //Try to go just down
        else if(sRow +1 < height)
        {
             int row  = sRow+1;

            //Perform check
            Square adj = grid[row][sColumn];
            bool rightConflict =((s.Gets_right() == true) && (adj.Gets_right() == true)) ? true:false;
            if(rightConflict)
            {
                    cout<<"Conflict in right"<<endl;
                    return true;
            }
        }
        //Try to go just right
        else if(sColumn +1 < width)
        {
            int col = sColumn+1;

            //Perform check
            Square adj = grid[sRow][col];
            bool bottomConflict = ((s.Gets_bottom() == true) && (adj.Gets_bottom() == true))? true:false;
            if(bottomConflict)
            {
                    cout<<"Conflict in bottom"<<endl;
                    return true;
            }
        }
    }
    if(bottom && left)
    {
        //Try to go down and left
        if((sRow +1 < height) && (sColumn-1 >= 0))
        {
            int row = sRow+1;
            int col = sColumn-1;

            //Perform check
            Square adj = grid[row][col];
            bool leftConflict =((s.Gets_left() == true) && (adj.Gets_top() == true)) ? true:false;
            bool bottomConflict = ((s.Gets_bottom() == true) && (adj.Gets_right() == true))? true:false;
            if(leftConflict || bottomConflict)
                return true;
        }
        //Try to go just down
        else if(sRow +1 < height)
        {
            int row = sRow+1;

            //Perform check
            Square adj = grid[row][sColumn];
            bool leftConflict =((s.Gets_left() == true) && (adj.Gets_left() == true)) ? true:false;
            if(leftConflict)
                return true;
        }
        //Try to go just left
        else if(sColumn -1 >= 0)
        {
            int col = sColumn-1;

            //Perform check
            Square adj = grid[sRow][col];
            bool bottomConflict = ((s.Gets_bottom() == true) && (adj.Gets_bottom() == true))? true:false;
            if(bottomConflict)
                return true;
        }
    }
    if(top && right)
    {
        //Try to go up and right
        if((sRow - 1 >= 0) && (sColumn+1 < width))
        {
            int row = sRow-1;
            int col = sColumn+1;
            Square adj = grid[row][col];

            //Perform check
            bool rightConflict =((s.Gets_right() == true) && (adj.Gets_bottom() == true)) ? true:false;
            bool topConflict = ((s.Gets_top() == true) && (adj.Gets_left() == true))? true:false;
            if(rightConflict || topConflict)
                return true;

        }
        //Try to go just up
        else if(sRow -1 >= 0)
        {
            int row = sRow-1;
            Square adj = grid[row][sColumn];

            //Perform check
            bool rightConflict = ((s.Gets_right() == true) && (adj.Gets_right() == true))? true:false;
            if(rightConflict)
                return true;
        }
        //Try to go just right
        else if(sColumn +1 < width)
        {
            int col = sColumn+1;
            Square adj = grid[sRow][col];

            //Perform check
            bool topConflict = ((s.Gets_top() == true) && (adj.Gets_top() == true))? true:false;
            if(topConflict)
                return true;
        }
    }

    return false; //Only reached if no crosses exist
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
            if(adj->GetsideCount() > 0)
                addToMSquares(Point(row,column-1));
            else
                removeFromMSquares(Point(row,column-1));
        }

        drawBoard();
    }
    else if(side == "R")
    {
        s->toggleSide(side);

        //A right mark on square s will also mark the left side on the right adjacent square
        if(column+1 < width)
        {
            adj = &(grid[row][column +1]);
            adj->toggleSide("L");
            if(adj->GetsideCount() > 0)
                addToMSquares(Point(row,column+1));
            else
                removeFromMSquares(Point(row,column+1));
        }

        drawBoard();
    }
    else if(side == "T")
    {
        s->toggleSide(side);

        //A top mark on square s will also mark the bottom side on the top adjacent square
        if(row - 1 >= 0)
        {
            adj = &(grid[row - 1][column]);
            adj->toggleSide("B");
            if(adj->GetsideCount() > 0)
                addToMSquares(Point(row-1,column));
            else
                removeFromMSquares(Point(row-1,column));
        }

        drawBoard();
    }
    else if(side == "B")
    {
        s->toggleSide(side);

        //A bottom mark on square s will also mark the top side on the bottom adjacent square
        if(row+1 < height)
        {
           adj = &(grid[row +1][column]);
           adj->toggleSide("T");
           if(adj->GetsideCount() > 0)
                addToMSquares(Point(row+1,column));
            else
                removeFromMSquares(Point(row+1,column));
        }

        drawBoard();
    }
    else
    {
        cout<<"Invalid move please try again"<<endl;
        return; //Return so that the null adj is not addedToMSquares
    }

    if(s->GetsideCount() > 0)
        addToMSquares(Point(row,column));
    else
        removeFromMSquares(Point(row,column));
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

void Board::removeFromMSquares(Point p)
{
    int index = markedSquares->find(p);
    if(index != -1)
        markedSquares->remove(index);
}
