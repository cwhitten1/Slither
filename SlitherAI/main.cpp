#include <iostream>
#include <fstream>
#include <string>
#include <Square.h>
#include <ArrayList.h>
#include <Board.h>

using namespace std;

Board parseBoardFile(string filePath)
{
    int width;
    int height;
    ArrayList<Square>* squares;
    Board* board;

    ifstream boardFile;
    boardFile.open("PracBoard.txt");
    string line;
    if(boardFile.is_open())
    {
        //Get dimensions
        getline(boardFile, line);

        width =  line.at(0) - '0';
        height =  line.at(4) - '0';

        //Skip lines
        getline(boardFile, line);

        //Load all squares
        squares = new ArrayList<Square>();
        while(getline(boardFile, line))
        {
            int row = line.at(1) - '0' - 1; // -1 b/c input start at (1,1) and grid in program starts at (0,0)
            int column = line.at(3) - '0' - 1;
            int value = line.at(5) - '0';

            Square s = Square(value, Point(row,column));
            squares->add(s);
        }
        board = new Board(width, height, squares);
    }
    boardFile.close();

    if(board != NULL)
        return *board;
    else
    {
        cout<<"Error parsing board data"<<endl;
        throw new exception();
    }
}

int main()
{
    cout << "Hello world!" << endl;
    Board b = parseBoardFile("PracBoard.txt");
    b.drawBoard();

    return 0;
}

