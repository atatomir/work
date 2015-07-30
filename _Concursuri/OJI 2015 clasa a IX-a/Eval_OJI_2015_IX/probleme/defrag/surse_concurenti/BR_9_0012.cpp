#include <iostream>
#include <fstream>
using namespace std;
ifstream f ("defrag.in");
ofstream g ("defrag.out");
int main()
{int v;
f>>v;
if (v==1)
{
g<<"1";
}


return 0;
}
