#include <iostream>
#include <fstream>
using namespace std;

int main()
{int n,k,min,j,i,p,aux,d=0;
    ifstream f("cool.in");
    ofstream g("cool.out");
bool secv=true,ok=true;;
f>>p;

if (p==1)
{
f>>n>>k;
int a[n+1];
for(i=1;i<=n;i++)
f>>a[i];
for(i=1;i<=k ;i++)
for(j=1;j<=k;j++)
{if(a[j]>a[i])
{aux=a[i];
a[i]=a[j];
a[j]=aux;}}
//........................
for(i=1;i<=k;i++)
if(a[i]!=a[i+1]-1)
secv=false;
if (secv==false)
{for(i=1;i<=k ;i++)
{ok=true;
for(j=1;j<=k;j++)
if(a[i]==a[j]&& i!=j)
ok=false;
if (ok==true)
d++;}
g<<d;}

else
g<<a[k];
}
 else
 {int s=2,start=1,z,x,l=0,o;
f>>n>>k;
int a[n+1];
for(i=1;i<=n;i++)
f>>a[i];
while (start<=n)
for (i=start,o=1;i<i+s;i++,o++)
v[o]=a[i];
for(z=1;z<=s;z++)
for(j=1;j<=s;j++)
{if(v[j]>v[z])
{aux=v[z];
v[z]=v[j];
v[z]=aux;}}
for(x=1;x<=k;x++)
if(v[x]!=v[x+1]-1)
secv=false;
if (secv==true)
l++;
start++;

 }
return 0;
}
