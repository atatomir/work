#include <iostream>
#include<fstream>
using namespace std;

int main()
{ifstream f ("cool.in");
  ofstream g("cool.out");
  int p,n,k,i,v[5000],ok=0,aux=0,j,x,l,nr,y[5000];

   f>>p;
   f>>n>>k;

   for(i=1;i<=n;i++)  {f>>v[i]; y[i]=v[i];}
   x=2;
  if(p==1)
    {for(i=1;i<=k-1;i++)
      if(v[i]>v[i+1]) {aux=v[i]; v[i]=v[i+1]; v[i+1]=v[i];}
     for(i=1;i<=k;i++) if(v[i]+1==v[i+1]) ok=0;
                        else ok=1;
        if(ok==0) g<<v[k];
         else {for(i=1;i<=k;i++) if(v[i]==v[i+1]){ for(j=i;j<=k;j++) {v[j]=v[j+1]; k--;}}
               g<<k;}}


   else{  while(x<=n)
    {for(i=1;i<=x;i++)
      if(v[i]>v[i+1]) {{aux=v[i]; v[i]=v[i+1]; v[i+1]=v[i];}}
    for(i=1;i<=x;i++) if(v[i]+1==v[i+1]) ok=0;
                        else ok=1;
     if(ok==0) {l=x; nr=1;}
      x++;
      }
      x=1;
     while(x<=n)
     {for(i=1;i<=x;i++)   if(y[i]>y[i+1]) {{aux=y[i]; y[i]=y[i+1]; y[i+1]=y[i];}}

     for(i=1;i<=x;i++) if(y[i]+1==y[i+1]) ok=0;
                        else ok=1;
       if(ok==0) if(x==l) nr++;
       x++;}


   g<<l-1<<'\n'<<nr;}
  f.close();

    g.close();
    return 0;
}
