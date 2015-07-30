#include <fstream>
using namespace std;
int main()
{ int v,n,x,i,k,b[10],c=0,d=0,m=1,j;
ifstream f("arc.in");
ofstream g("arc.out");
f>>v;
f>>n;
for(i=1;i<n;i++)
    {g<<x<<" ";
    b[k++]=x;}
for(k=1;k<=n;k++)
    if(v==1)
        {if(b[k]!=b[k+1]) c=c+1;
                  else for(k=k+1;k<=n;k++)
                          if(b[k]!=b[k-1]) c=c+1;}
        g<<c;
    if(v==2)
      {k=m;
       j=n;
       for(k=m;k<=n;k++)
          if(b[k]==b[k+1]){d=d+1;
                           if(d>=2) n=n-d-1;
                           m=1;}
            else d=0;
       if(j==n) g<<0;
            else  {g<<n;
                  for(k=1;k<=n;k++)
                  g<<b[k]<<endl;}
      }
return 0;
}
