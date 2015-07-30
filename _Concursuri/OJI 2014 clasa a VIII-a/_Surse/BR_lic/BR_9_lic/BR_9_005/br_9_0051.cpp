#include <iostream>
#include <fstream>
using namespace std;
ifstream f("cool.in");
ofstream g("cool.out");
int v[5001],k,n,i,p,max1=-1,min1=1001,s=0,s1,j,ok=0,nr=0,max2=-1,min2=1001,poz=0;
int main()
{ f>>p>>n>>k;
 for(i=1;i<=n;i++)
 {f>>v[i];
   if(i<=k) {if(v[i]>max1)max1=v[i];
             if(v[i]<min1)min1=v[i];}
 }

 if(p==1)
  {for(i=1;i<=k;i++)
      s=s+v[i];
    s1=(max1*(max1+1)/2)-((min1-1)*min1/2);

    if(s==s1)
      g<<max1;
    else
   {for(i=k;i>=1;i--)
      {ok=1;
       for(j=1;j<i;j++)
        {if(v[i]==v[j])ok=0;}
    if(ok==0)nr++;
      }
    g<<nr<<'\n';
   }
  }
  else
  {for(j=1;j<=n;j++)


     for(i=j;i<=n;i++)
     {s=s+v[i];
          if(v[i]<min2)min2=v[i];
          if(v[i]>max2)max2=v[i];
          s1=(max2*(max2+1)/2)-((min2-1)*min2/2);
          if(s==s1){poz=i;nr++;}
      }
g<<poz;
  }


f.close();
g.close();


    return 0;
}
