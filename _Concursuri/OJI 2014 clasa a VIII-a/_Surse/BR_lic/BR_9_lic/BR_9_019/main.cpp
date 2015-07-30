#include <iostream>
#include <fstream>

using namespace std;

int main()
{int a[1000],p,n,k,inv,aux,max,t,x,i,lm,s;
 ifstream f("cool111.txt");
 ofstream g("cool12.txt");
 f>>p;
 f>>n;
 f>>k;
 for(i=1;i<=n;i++)
   f>>a[i];

 do { for(i=1;i<=n;i++)
      {inv=0;
      if(a[i]>a[i+1])    {aux=a[i];
                         a[i]=a[i+1];
                         a[i+1]=aux;
                          inv=1;}
         }
  }
    while(inv!=0);

    for(i=1;i<=k;i++)
    {
    if(a[i]+1==a[i+1])    x=1;
                      else x=0;
    }
  if(x=1)       {if(p==1)  { for(i=1;i<=k;i++)
                           if(a[i+1]<a[i])    max=a[i];
                                         else max=a[i+1];
                           g<<max<<endl; }

                 if(p==2) { lm=k+1;
                           g<<lm<<endl;

                           for(i=1;i<=lm;i++)
                           s=1;
                           for(i=k;i<=lm;i++)
                           s=2;
                           g<<s;


                            }
                }

        else    if(p==1)    {   do { for(i=1;i<=k;i++)
                                    {inv=0;
                                     if(a[i]>a[i+1])    {aux=a[i];
                                                         a[i]=a[i+1];
                                                         a[i+1]=aux;
                                                            inv=1;}
                                    }
                                  }
                                 while(inv!=0);
                                  t=0;
                                for(i=1;i<=k;i++)
                                if(a[i]!=a[i+1])    t=t+1;
                                 g<<t<<endl;}

  f.close();
  g.close();
  return 0 ;

}
