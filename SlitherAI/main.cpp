#include <iostream>
#include <fstream>
#include <string>
#include <Square.h>
#include <ArrayList.h>
#include <Board.h>

using namespace std;

int main()
{
    int width;
    int height;
    int squares;
    cout << "Hello world!" << endl;



    return 0;
}

Board parseBoardFile(String filePath)
{
    ifstream boardFile;
    boardFile.open("PracBoard.txt");
    string line;

    if(boardFile.is_open())
    {
        //Get dimensions
        getline(boardFile, line);

        width = (int) line.at(0);
        height = (int) line.at(4);
        //Skip lines
        getline(boardFile, line);
        getline(boardFile, line);

        while(getline(boardFile, line))
        {
            //Make squares
        }
        cout<<line<<endl;
    }
    boardFile.close();

}
