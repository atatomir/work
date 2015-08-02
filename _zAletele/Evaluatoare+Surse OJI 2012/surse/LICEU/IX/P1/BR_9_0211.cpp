#include <fstream>
#include<iostream>
int n,d,k,j;

using namespace std;
ifstream f(".in");
ofstream g(".out");

int main()
{f>>n;
f>>d;
f>>k;
j=(d+k)+(d=k)-n;
g<<j;
f.close();
g.close();
return 0;
}
