#include <iostream>
#include<fstream>

int a[1001][1001];
int b[150][2];
using namespace std;
ifstream f("betasah.in ");
ofstream g("betasah.out ");
int main()
{int i,j,q,n,m,p,M,k,d,max=0,dif,rez2=0;
f>>n>>d>>k;
M=d+k;
if(d>k)
    dif=d-k;
if(d<k)
    dif=k-d;
if(d==k)
    dif=k;

p=2;
for(m=1;m<=M;m++)
{

    for(p=1;p<=2;p++)
       {
           f>>b[m][p];
           if(m<=d)
               {
                   if(p==1)
                    {
                        i=b[m][p];
                    }
                    if(p==2)
                    {
                        j=b[m][p];
                        a[i][j]=1;
                    }
               }
         if(m==d)
           M=d+dif+m;
        if(m>d)
         {
                   if(p==1)
                    {
                        i=b[m][p];
                    }
                    if(p==2)
                    {
                        j=b[m][p];
                        a[i][j]=2;
                    }
        }
        }
}


max=0;
int pmax=0;
for(i=1;i<=n;i++)
   {{
       q=i;


    }
   for(j=1;j<=q;j++)
        {if(a[i][j]==0)
            pmax++;}



    if(pmax>max)
           {max=pmax;
            pmax=0;}
        if(pmax<max)
            pmax=0;
        if(pmax==max)
           {max=pmax;
            pmax=0;}
   }
g<<max;g<<'\n';
for(i=1;i<=n;i++)
{
    q=i;
    for(j=1;j<=q;j++)
        if(a[i][j]==0)
            a[i][j]=5;
    }

for(i=1;i<=n;i++)
{
    q=i;
    for(j=1;j<=q;j++)
        if(a[i][j]==1)
            {
                if(a[i-1][j]==5)
                    {rez2++;
                        a[i-1][j]=3;}
                if(a[i-1][j+1]==5 )
                    {rez2++;
                        a[i-1][j+1]=3;}
                if(a[i][j+1]==5)
                   {rez2++;
                    a[i][j+1]=3;

                   }
                if(a[i+1][j+1]==5 )
                   {rez2++; a[i+1][j+1]=3;

                   }
                if(a[i+1][j]==5)
                    {rez2++; a[i+1][j]=3;}
                if(a[i+1][j-1]==5 )
                    {rez2++;a[i+1][j-1]=3;}
                if(a[i][j-1]==5 )
                    {rez2++;a[i][j-1]=3;}
                if(a[i-1][j-1]==5 )
                   {rez2++;
                    a[i-1][j-1]=3;

                   }
            }
}
g<<rez2;
    f.close();
    g.close();
    return 0;
}
