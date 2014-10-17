#include <iostream>
#include <Square.h>
#include <ArrayList.h>
using namespace std;

int main()
{
    cout << "Hello world!" << endl;

    ArrayList<int> a = ArrayList<int>();
    a.add(4);
    cout<< a.get(0)<<endl;
    a.set(a.GetnextIndex(), 5);
    cout << a.get(1) << endl;
    return 0;
}
