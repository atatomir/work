#include <fstream>
using namespace std;
int main()
{ int i,cn,n,y;
  ifstream f("martisoare.in");
  ofstream g("martisoare.out");
  f>>n>>cn>>y;
  for(n=4;n<=100000;n++)
  for (i=1;i<=n;i++)
  for(y=1;y<=n;y++)
  if(cn=cn+n)
g<<i<<y<<cn;
//f.close;
//g.close;
return 0;
}

