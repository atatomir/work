#include <fstream>
using namespace std;
int main()
{ifstream f("arc.in");
ofstream g("arc.out");
int n,i,a[100000],V,c=0,ok=1,c1=1,j;
f>>V;
f>>n;
for(i=1;i<=n;i++)
f>>a[i];
if(V==1)
    {for(i=1;i<=n;i++)
       {if(a[i+1]==a[i])ok=0;
        if(a[i+1]!=a[i])ok=1;
        if(ok==1)c=c+1;}
        g<<c;}
if(V==2)
{for(i=1;i<=n;i++)
if(a[i]==a[i+1]) c=c+1;
if(a[i]!=a[i+1]){if(c=0)ok=0;
                 if(c>=3){for(j=i-c;j<=n;j++)
                              a[j]=a[j+c];
                            c=0;};
                    n=n-c;}

for(i=1;i<=n;i++)
    g<<a[i]<<endl;}
return 0;
}
