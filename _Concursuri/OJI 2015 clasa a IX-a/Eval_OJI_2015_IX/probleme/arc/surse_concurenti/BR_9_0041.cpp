#include<iostream>
#include<fstream>
using namespace std;
ifstream f("arc.in");
ofstream g("arc.out");
int main()
{int n,i=0,v,n1=1,ok=1,b[10000],k=1,max=0,l=0,s=0,n2=0,aux=0,ok2=1,j=0;
long int a[10000];
f>>v;
f>>n;
for(i=1;i<=n;i++)
   {f>>a[i];
    b[i]=1;
   }
if(v==1)
  {for(i=2;i<=n;i++)
      if(a[i]!=a[i-1])n1=n1+1;
   g<<n1;
  }
if(v==2)
 {while(ok==1)
  {k=1;
   max=0;
   ok2=1;
   for(i=2;i<=n;i++)
       if(a[i]==a[i-1]) b[k]=b[k]+1;
                  else{k=k+1;
                       b[k]=1;
                      }
   for(i=1;i<=k;i++)
       if(b[i]>max){max=b[i];
                    l=i;
                   }
   for(i=1;i<=n;i++)
    for(j=1;j<=n;j++)
       if(a[i]==a[j]) ok2=ok2+1;
   if(ok2!=n*n)
   {if(max>=3) {s=0;
               for(i=1;i<=l;i++)
                   s=s+b[i];
               for(i=s+1;i<=n;i++)
               {aux=a[i-max];
                a[i-max]=a[i];
                a[i]=aux;
               }
               n=n-max;
              }
   if(max<3) ok=0;
   }
  }
if(n>0)
   for(i=1;i<=n;i++)
       n2=n2+1;
   g<<n2<<endl;;
   for(i=1;i<=n;i++)
       g<<a[i]<<endl;
 if(ok2==n*n)
    g<<"0";
 }
return 0;
}

