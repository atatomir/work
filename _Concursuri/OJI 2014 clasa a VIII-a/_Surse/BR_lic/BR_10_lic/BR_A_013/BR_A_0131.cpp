#include <iostream>
#include <fstream>

using namespace std;

int main()
{
   int m,n,i,j,v1,nr=0,t,r,max=0,nrs=0;
   char a[401][401];
   ifstream f("ferma.in");
   ofstream g("ferma.out");
   f>>v1;
   f>>m>>n;
   if(v1==1)
       {for(i=1;i<=m;i++)
        for(j=1;j<=n;j++)
            f>>a[i][j];
       for(i=1;i<=m;i++)
        for(j=1;j<=n;j++)
            {r=i;
            t=j;
            while(r<=m&&t<=n)
                {if(a[r][t]==a[r][t+1])
                   {nr++;
                   t++;
                    if(nr>max)
                        {max=nr;
                        nrs=max/r-(i-1);}}
                else
                    if(a[r][t]==a[r+1][t])
                        {
                            nr++;
                            r++;
                            if(nr>max)
                                {max=nr;
                                nrs=max/r-(i-1);}
                             }
                     else
                        if(a[r][t]==a[r-1][t])
                            {
                                nr++;
                                i--;
                                if(nr>max)
                                    {max=nr;
                                    nrs=max/r-(i-1);}}
                         else
                            if(a[r][t]==a[r][t-1])
                                {
                                    nr++;
                                    t--;
                                    if(nr>max)
                                        {max=nr;
                                        nrs=max/r-(i-1);}
                            }

           }}
        g<<nrs;}
    if(v1==2)
        g<<"nope";

    return 0;
}
