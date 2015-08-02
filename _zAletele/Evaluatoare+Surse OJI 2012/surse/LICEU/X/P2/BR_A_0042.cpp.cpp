#include <iostream>
#include<fstream>
using namespace std;
int a[100][100];
int main()
{int x,y,l,n,d,i,j,xnou,ynou,dif;
ifstream f("zona.in");
ofstream g("zona.out");
f>>x>>y>>n>>l;
for(i=1;i<=n;i++)
    for(j=1;j<=n;j++)
        a[i][j]=0;
a[x][y]=1;
for(i=1;i<=l;i++)
{
    f>>d;
 if(d==1)
       {
           x=x-1;
           if(a[x][y]==0)
                a[x][y]=a[x+1][y]+1;
           else
               {dif=a[x+1][y]-a[x][y]+1;
                g<<dif;
               }

       }
    if(d==2)
        {
            y=y+1;
           if(a[x][y]==0)
            a[x][y]=a[x][y-1]+1;
         else
         {dif=a[x][y-1]-a[x][y]+1;
                g<<dif;   }

        }
    if(d==3)
        {
            x=x+1;
            if(a[x][y]==0)
            a[x][y]=a[x-1][y]+1;
            else{
            dif=a[x-1][y]-a[x][y]+1;
                g<<dif; }
        }
    if(d==4)
    {
        y=y-1;
        if(a[x][y]==0)
        a[x][y]=a[x][y+1]+1;
        else{
            dif=a[x][y+1]-a[x][y]+1;
            g<<dif;   }
    }

}

f.close();
g.close();
return 0;
}
