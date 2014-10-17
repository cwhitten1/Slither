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
    cout << "Hello world!" << endl;

    ofstream boardFile;
    boardFile.open("PracBoard.txt");
    string line;

    if(boardFile.is_open())
    {
        getLine(boardFile, line);
        cout<<line<<endl;
    }
    boardFile.close();


    return 0;
}
