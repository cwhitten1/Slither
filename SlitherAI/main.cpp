#include <iostream>
#include <fstream>
#include <string>
#include "Square.h"
#include "ArrayList.h"
#include "Board.h"

using namespace std;

Board* parseBoardFile(string filePath)
{
    int width;
    int height;
    ArrayList<Square> initialSquares = ArrayList<Square>();
    Board* board;

    ifstream boardFile;
    boardFile.open(filePath.c_str());
    string line;
    if(boardFile.is_open())
    {
        //Get dimensions
        getline(boardFile, line);

        width =  line.at(0) - '0';
        height =  line.at(4) - '0';

        //Skip lines
        getline(boardFile, line);

        //Load all initialSquares
        while(getline(boardFile, line))
        {
            int row = line.at(1) - '0' - 1; // -1 b/c input start at (1,1) and grid in program starts at (0,0)
            int column = line.at(3) - '0' - 1;
            int value = line.at(5) - '0';

            Square s = Square(value, Point(row,column));
            initialSquares.add(s);
        }
        board = new Board(width, height, initialSquares);
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
            //Check row and column
        else if(row >= b->getHeight() || column >= b->getWidth() || row < 0 || column < 0)
        {
            cout<<"Invalid move please try again"<<endl;
            promptForMove(b); //Need to keep making moves (this will be expensive on stack if a massive # of incorrect moves are made)
        }
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

    return true;
}

void startGame(Board *b)
{
    //Move loop
    bool keepMoving = true;
    while(keepMoving)
    {
        keepMoving = promptForMove(b);

        if(b->areSquaresValid())
        {
            if(b->isContLoop())
            {
                cout<<endl<<" YOU HAVE FOUND A SOLUTION! CONGRATULATIONS!!!!"<<endl<<endl;
                keepMoving = false;
            }
            else
            {
                cout<<endl<<" SORRY THAT IS NOT A SOLUTION!"<<endl;
            }
        }
    }
}
int main()
{
    //Description
    cout<<"\t\t\t   Welcome to Slither!!!"<<endl<<endl<<"~ You will be given a 2D grid that is full of squares with unmarked sides."<<endl;
    cout<<"~ You must try to form a continuous loop";
    cout<<" by marking sides on the squares."<<endl<<"~ Squares with a value specify the";
    cout<<" exact # of sides it must have around it."<<endl<<endl;
    cout<<"NOTE: Crosses are not allowed i.e. _|_"<<endl<<endl;
    cout<<"NOTE: You must input the path for the grid files"<<endl<<" \t(see README.txt for proper format of data files)"<<endl<<endl;
    cout<<"Good luck!!!"<<endl<<endl;

    //Read initial grid
    string filePath;
    cout<<"Please enter grid filepath: ";
    cin>>filePath;

    //Create and draw initial board
    Board* b = parseBoardFile(filePath);
    b->drawBoard();

    //Game loop
    bool keepPlaying = true;
    cout<<"Begin making moves (use 0 0 X to end)"<<endl;
    while(keepPlaying)
    {
        startGame(b);
        string pAgain;
        cout<<endl<<"Would you like to play again? (Y/N): ";
        cin>> pAgain;
        if(pAgain != "Y")
        {
            cout<<endl<<"Exiting game!"<<endl;
            return 0;
        }
        else
        {
            string filePath;
            cout<<endl<<endl<<"Please enter grid filepath: ";
            cin>>filePath;

            b = parseBoardFile(filePath);
            b->drawBoard();
        }
    }

}
