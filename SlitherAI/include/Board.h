#ifndef BOARD_H
#define BOARD_H
#include <ArrayList.h>
#include <Square.h>
class Board
{
    public:
        Board(int width);
        virtual ~Board();
        int getWidth(){ return width;}
        int getHeight(){ return height;}
        ArrayList<Square> squares = ArrayList();
    protected:
        void drawBoard();
    private:
        int width;
        int height;
};

#endif // BOARD_H
