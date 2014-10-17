#include <iostream>
#include <Square.h>
using namespace std;

int main()
{
    cout << "Hello world!" << endl;
    Square s;
    s.Setvalue(1);
    cout << s.GetisValid() <<endl;
    s.markSide("l");
    cout<<s.GetisValid()<<endl;
    return 0;
}
