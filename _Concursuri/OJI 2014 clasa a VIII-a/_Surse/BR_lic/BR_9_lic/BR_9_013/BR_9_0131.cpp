#include <iostream>
#include <fstream>
using namespace std;
ifstream f("cool.in");
ofstream g("cool.out");
int main()
{ int n,k,p,i,j,aux,q,dist=0,mi,maxmi,l=0,i2,j2;
  f>>p;
  f>>n>>k;
  int v[n+1];
  q=0;
  for(i=1;i<=n;i++)
    f>>v[i];
  if(p==1)
   {for(i=1;i<=k-1;i++)
    for(j=i+1;j<=k;j++)
       if(v[i]>v[j])
        {
            aux=v[i];
            v[i]=v[j];
            v[j]=aux;
        }
   for(i=1;i<=k-1;i++)
       if(v[i+1]==v[i]+1)
          q=1;
       else for(i=1;i<=k-1;i++)
               for(j=i+1;j<=k;j++)
                 if(v[i]==v[j])
                   l++;
       }
   dist=k-2*l;
  if(q==1)
     g<<v[k];
  else g<<dist;
    if(p==2)
{
    maxmi=k;
 for(mi=n;mi>=k;mi--)
    {for(i=1;i<=mi-1;i++)
     for(j=i+1;j<=mi;j++)
            if(v[i]>v[j])
              {
               aux=v[i];
               v[i]=v[j];
               v[j]=aux;
              }
    for(i=1;i<=mi;i++)
        if(v[i]==v[i+1])
          {q=1;maxmi=mi;}
        else q=0;
           }
  g<<maxmi;
  g<<'\n';
  g<<l;
  }
  f.close();
  g.close();
    return 0;
}
