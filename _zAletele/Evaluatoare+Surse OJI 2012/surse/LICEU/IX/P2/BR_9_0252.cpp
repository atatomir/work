#include <iostream>
#include <fstream>
using namespace std;
int clep[2001];
int main()
{
    ifstream f("clepsidru.in");
    ofstream g("clepsidru.out");
int n,k,p[1001],i,i1,j,t=0,s[1001],x;
long b;
bool rw;
rw=0;
f>>n>>b>>k;
for(i=1;i<=k;i++)
f>>s[i]>>p[i];
x=1;
clep[1]=b;
for(i=clep[x];i>0;i--)
for(j=1;j<=n;j++)
{clep[j]--;
if(j=n*2-1)
clep[j+1]++;
else
clep[j+2]++;
t++;
if(clep[x]==0)
x++;
}
 g<<t<<'\n';
 for(i=1;i<=k;i++)
 if(p[i]==1)
  for(i1=clep[1];i1>=0;i1--)
for(j=1;j<=n;j++&&s[i]--)
{clep[j]--;
if(j=(n*2)-1)
clep[j+1]++;
else
clep[j+2]++;}
else
 for(i1=clep[n];i1>=0;i1--)
for(j=1;j<=n;j++&&s[i]--)
{if(s[i]==0)
break;
clep[j]--;
if(j=(n*2)-1)
clep[j-1]++;
else
clep[j-2]++;}
for(i=1;i<=2*n;i++)
g<<clep[i]<<" ";
if(i%2==0)
g<<clep[i]<<'\n';
    return 0;
}
