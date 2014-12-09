#ifndef BOARD_H
#define BOARD_H
#include "ArrayList.h"
#include "Square.h"
#include "Point.h"
#include "Edge.h"
#include <vector>

class Board
{
    public:
        Board();
        Board(int width, int height, vector<Square> initialSquares);
        virtual ~Board();
        int getWidth(){ return width;}
        int getHeight(){ return height;}
        bool areSquaresValid(); //Checks if all squares have a valid # of edges.
        int getNumValidSquares();
        int getNumEdges();
        bool checkForCrosses(Square s); //Checks if the marked edges of squares form a continuous loop.
        void makeMove(int row, int column, string side);
        void drawBoard();// Draws the board based on the grid.
        Square** getGrid() {return grid;} //Makes a 2d array based on squares values.
        bool isContLoop(); // Returns true if loop is continuous
        vector<Square> getInitSquares(){return initialSquares;}
        void clearBoard(); //This method removes all marked edges from the board.
    protected:
    private:
        int width;
        int height;
        Square** grid;
        void makeGrid();
        void fillGrid();
        vector<Square> initialSquares;
        ArrayList<Point> generateMarkedSquares();
        ArrayList<Edge> generateMarkedEdges(ArrayList<Point>& markedSquares); //Gets the marked edges with no duplicates using markedSquares.
};

#endif // BOARD_H
