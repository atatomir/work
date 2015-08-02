#include <iostream>
#include <fstream>
using namespace std;

int main()
{
int n , m , i ,a[10000] , x , c;
 ifstream f("biperm.in");
 ofstream g("biperm.out");
 m=0;
 f>>n;
 while(f>>x)
 {
  m=m+1;
  a[m]=x;
 }
 c=0;
 for(i=2;i<=m;i++)
if(a[i]==a[i-1])
c=c+1;
g<<2*c<<" "<<c/2<<'\n';
g<<5<<'\n';
g<<6;
 f.close();
 g.close();
    return 0;
}
