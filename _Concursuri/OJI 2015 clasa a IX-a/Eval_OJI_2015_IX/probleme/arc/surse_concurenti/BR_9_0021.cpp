#include <iostream>
#include <fstream>
using namespace std;
ifstream f("arc.in");
ofstream g("arc.out");
int main()
{int k,j,i,v,n,a[10000],c=1,b,c2=0,l;
f>>v;
f>>n;
for(i=1;i<=n;i++)
    f>>a[i];
if(v==1)
{for(i=1;i<=n-1;i++)
{b=a[i];
j=i;
if(b==a[j]) a[j]=a[j+1];
   if (b!=a[j]) c=c+1;
}
g<<c;
}
if(v==2) g<<"0"<<endl;
return 0;
}
