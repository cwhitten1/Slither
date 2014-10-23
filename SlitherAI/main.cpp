#include <iostream>
#include <fstream>
#include <string>
#include <Square.h>
#include <ArrayList.h>
#include <Board.h>

using namespace std;

Board* parseBoardFile(string filePath)
{
    int width;
    int height;
    ArrayList<Square> squares = ArrayList<Square>();
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
        while(getline(boardFile, line))
        {
            int row = line.at(1) - '0' - 1; // -1 b/c input start at (1,1) and grid in program starts at (0,0)
            int column = line.at(3) - '0' - 1;
            int value = line.at(5) - '0';

            Square s = Square(value, Point(row,column));
            squares.add(s);
        }
        board = new Board(width, height, squares);
    }
    boardFile.close();

    if(board != NULL)
        return board;
    else
    {
        cout<<"Error parsing board data"<<endl;
        throw new exception();
    }
}


bool promptForMove(Board* b)
{
    cout<<endl<<"Specify move (row column 'L/R/T/B') (0 0 X to end): ";

    int row;
    int column;
    string side;

    try{
        cin>>row;
        cin>>column;
        cin>>side;

        if(cin.fail())
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout<<"Please use numbers for row and column!!!"<<endl;
            return true;
        }

        //Decrement to adjust for grid indexes which start at 0
        row--;
        column--;

        if(row == -1 && column == -1 && side == "X")
            return false;
        else
        {
            b->makeMove(row, column, side);
            return true;
        }

    }
    catch(int e)
    {
        cout<<endl<<"Error reading your move!";

    }
}



int main()
{
    Board* b = parseBoardFile("PracBoard.txt");
    b->drawBoard();

    cout<<"Begin making moves (use 0 0 X to end)"<<endl;

    bool keepMoving = true;
    while(keepMoving)
        keepMoving = promptForMove(b);
}
