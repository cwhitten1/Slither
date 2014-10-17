#include "Board.h"
#include <iostream>

using namespace std;

Board::Board(int width, int height, ArrayList<Square> squares)
{
    this->squares = ArrayList<Square>();
    this->width=width;
    this->height=height;
}

Board::~Board()
{

}

void Board::drawBoard()
{
    cout<< "this is where the board will be"<<endl;
}
