#ifndef BOARD_H
#define BOARD_H
#include "ArrayList.h"
#include "Square.h"
#include "Point.h"
class Board
{
    public:
        Board();
        Board(int width, int height, ArrayList<Square>& initialSquares);
        virtual ~Board();
        int getWidth(){ return width;}
        int getHeight(){ return height;}
        bool areSquaresValid(); //Checks if all squares have a valid # of edges.
        bool checkForCrosses(Square s); //Checks if the marked edges of squares form a continuous loop.
        void makeMove(int row, int column, string side);
        void drawBoard();// Draws the board based on the grid.
        Square** getGrid() {return grid;} //Makes a 2d array based on squares values.
        bool isSolved();
        bool traceLoop();// Returns true if loop is continuous
    protected:
    private:
        int width;
        int height;
        Square** grid;
        void makeGrid();
        void fillGrid();
        void addToMSquares(Point p);
        void removeFromMSquares(Point p);
        ArrayList<Square> initialSquares;
        ArrayList<Point>* markedSquares; //Holds the positions of any squares that have been marked.
};

#endif // BOARD_H
