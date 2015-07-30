#include <fstream>
using namespace std;
long c,v[10001],n,x,i,aux,nr,nr2,bun,ok;
int main()
{ifstream f("imprimanta.in");
 ofstream g("imprimanta.out");
 f>>n;
 n=x;
 while(n>0)
 {
c=x%10;
x=x/10;
for(i=1;i<=n;i++)
{c=v[i];
f>>v[i];
 }
 }
 while(ok=0)
 {
if(v[i]<v[i+1])
{
do{
aux=v[i+1];
v[i+1]=v[i];
v[i]=aux;
}
ok=1;
}
 while(v[i]=3)
{
 bun=v[i];
 if(v[i]==9)
 nr=12;
 if(v[i]==8)
 nr=13;
 if(v[i]==7)
 nr=7;
 if(v[i]==6)
 nr=12;
 if(v[i]==5)
 nr=11;
 if(v[i]==4)
 nr=9;
 if(v[i]==3)
 nr=11;
 if(v[i]==2)
 nr=11;
 if(v[i]==1)
 nr=5;
 if(v[i]==0)
 nr=11;

 if(v[i]==9)
 nr2=12;
 if(v[i]==8)
 nr2=13;
 if(v[i]==7)
 nr2=7;
 if(v[i]==6)
 nr2=12;
 if(v[i]==5)
 nr2=11;
 if(v[i]==4)
 nr2=9;
 if(v[i]==3)
 nr2=11;
 if(v[i]==2)
 nr2=11;
 if(v[i]==1)
 nr2=5;
 if(v[i]==0)
 nr2=11;
 if(nr2<nr)
 bun=v[i+1];
 else
 bun=v[i];}
 g<<bun}
 f.close();
 g.close();

    return 0;
}
