#include <iostream>
using namespace std;

    class cls {
public:
    int x;
    cls() { x = 3; }
    void f(cls& c) { cout << c.x; }
};

void main()
{
    const cls d;
    f(d);
}
