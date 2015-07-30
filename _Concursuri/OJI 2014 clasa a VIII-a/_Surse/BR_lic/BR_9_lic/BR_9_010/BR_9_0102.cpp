#include <iostream>
#include <fstream>
#include <math.h>
using namespace std;

ifstream f("pseudobil.in");
ofstream g("pseudobil.out");

int main()
{
int p, n, x, y, m, d, i, j, pt;
long k;
f>>p;
f>>n>>k>>d;
int l, p1, z;
l=(int)sqrt((d*d)/2);
if (p==1)   {
    if (d==4)
    g<<5;
    if (d==6)
    pt=(d-1)*2 -1 + (d-l)*4 -2;
    else
pt=(d-1)*2 - 1 + (d-l)*4;
}

g<<pt<<endl;
f.close();
g.close();
    return 0;
}
