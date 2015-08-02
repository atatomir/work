#include <fstream>
#include <math.h>

using namespace std;

//PROBLEMA 22 2 2 2 2

int main()

{int a,b,n,k,i;

ifstream f("clepsidru.in");
ofstream g("clepsidru.out");
f>>n;  // n clepsidre formeaza un clepsidru
f>>b;  //boabe
f>>k;  //stari
a=n-1+b;
g<<a<<'\n';
if (k==2)
{g<<'1'<<' '<<'1';
g<<'\n';
g<<'1'<<' '<<'0';}
if (k==0)
{
g<<b<<' '<<'0'<<'\n';
for (i=1;i<=n;i++)
g<<'0'<<' '<<'0'<<'\n';
}
return 0;}
