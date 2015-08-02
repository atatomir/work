#include <fstream>

using namespace std;
ifstream f("triunghi.in");
ofstream g("triunghi.out");
unsigned long a[50],b[50];
int n,k,i,v;
int main()
{unsigned long max=0,min=2000000000,max2=0;
f>>v;
if(v==2)
{
f>>n;
f>>k;
for(i=1;i<=n;i++)
{f>>a[i];
if(a[i]<max && a[i]>max2) max2=a[i];
if(max<a[i]){ max2=max;
            max=a[i];}
            }
for(i=n+1;i<=k;i++)
{a[i]=max+max2+1;
max2=max;
max=a[i];
}
for(i=1;i<=k;i++)
g<<a[i]<<" ";}
if(v==1)
{
f>>n;
f>>k;
for(i=1;i<=n;i++)
{f>>a[i];
if(min>a[i]) min=a[i];}
b[1]=min;
b[2]=b[1]+1;
for(i=3;i<=k;i++)
b[i]=b[i-1]+b[i-2]+1;
for(i=1;i<=k;i++)
g<<b[i]<<" ";
}


    return 0;
}
