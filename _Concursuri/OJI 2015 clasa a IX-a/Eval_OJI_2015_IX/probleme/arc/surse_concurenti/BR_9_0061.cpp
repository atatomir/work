#include <iostream>
#include <fstream>
using namespace std;

int main()
{int a[10000],v,n,i,k=0,q=0,c=10,p,o,t,z;
    ifstream f ("arc.in");
    ofstream g ("arc.out");
    f>>v;
    f>>n;
    for (i=1;i<=n;i++)
    {f>>a[i];}
    if (v==1)
        {for (i=1;i<=n;i++)
          {while (a[i]=a[i+1])
           {k=k+1;}
     if (k!=0)
          q=q+1;}
    for(i=1;i<=n;i++)
    {
     if (a[i]!=a[i+1])
          {k=0;
           q=q+1;}
     }}
    if (v==1)
        g<<q;
    if (v==2)
   {while (c>0)
    {for(i=1;i<=n;i++)
        {while (a[i]==a[i+1])
           {k=k+1;
            p=i;
           }
       if (k==1)
            o=i;
       if (k>=3)
        {for(t=o;t<=p;t++)
           {a[t]=0;
            a[t]=a[i+1];}
         for(z=n-k;z<=n;z++)
          {a[z]=0;
          }
        }
        }
     c=c-1;}
    for(i=1;i<=n;i++)
         g<<a[i]<<'\n';}
    return 0;
}
