#include <fstream>
using namespace std;
int main()
{ int n,x,k,c1,c2,ck,p,m,max,nef,a,c;
ifstream f("piramide.in");
ofstream g("piramide.out");
f>>n>>x>>k>>c1>>c2>>ck>>p;
n=3;n<=100000;
k=1;k<=n;
c1=1,c1<c2;
c2<ck;
ck<=n;
x=1;x<=n;
x=p;
m=max;
c=nef=m-1;
g<<p<<m<<c<<a;
f .close;
g.close;
return 0; }
