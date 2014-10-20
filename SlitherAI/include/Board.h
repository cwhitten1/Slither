#ifndef BOARD_H
#define BOARD_H
#include <ArrayList.h>
#include <Square.h>
class Board
{
    public:
        Board();
        Board(int width, int height, ArrayList<Square>* squares);
        virtual ~Board();
        int getWidth(){ return width;}
        int getHeight(){ return height;}
        ArrayList<Square>* squares;
        void drawBoard();// Draws the board based on the grid.
        Square** getGrid() {return grid;} //Makes a 2d array based on squares values
    protected:
    private:
        int width;
        int height;
        Square** grid;
        void makeGrid();
        void fillGrid();
};

#endif // BOARD_H
