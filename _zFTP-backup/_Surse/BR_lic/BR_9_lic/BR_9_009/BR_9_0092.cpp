#include <iostream>
#include <fstream>
using namespace std;
int p,masa[1501][1501],k,d,i1,i2,i,m,x,y,z1,z2,t,total1,n;
ifstream intrare("pseudobil.in");
ofstream iesire("pseudobil.out");
void cazul1()
{
    intrare>>n;
    for (i2=1;i2<=n;i2++)
    {
        for (i1=1;i1<=n;i1++)
        {
            masa[i2][i1]=1;
        }
    }
    intrare>>k;
    intrare>>d;
    for (i=1;i<=k;i++)
    {
        intrare>>i1;
        intrare>>i2;
        masa[i1][i2]=2;
    }
    intrare>>m;
    for (i=1;i<=m;i++)
    {
        t=0;
        intrare>>i1;
        intrare>>i2;
        z1=i1+d/2;
        for (x=i1+1;x<z1;x++){for (y=i2-t;y<=i2+t;y++){total1+=1;}t+=1;}
        for (x=z1;x<i1+d;x++){for (y=i2-t;y<=i2+t;y++){total1+=1;}t-=1;}
    }
    iesire<<total1;

}
void cazul2()
{
    intrare>>n;
    for (i2=1;i2<=n;i2++)
    {
        for (i1=1;i1<=n;i1++)
        {
            masa[i2][i1]=1;
        }
    }
    intrare>>k;
    intrare>>d;
    d+=2;
    for (i=1;i<=k;i++)
    {
        intrare>>i1;
        intrare>>i2;
        masa[i1][i2]=2;
    }
    intrare>>m;
    for (i=1;i<=m;i++)
    {
        total1=0;
        t=0;
        intrare>>i1;
        i1-=1;
        intrare>>i2;
        z1=i1+d/2;
        for (x=i1+1;x<z1;x++){for (y=i2-t;y<=i2+t;y++){if (masa[x][y]==2){total1+=1;}}t+=1;}
        for (x=z1;x<i1+d;x++){for (y=i2-t;y<=i2+t;y++){if (masa[x][y]==2){total1+=1;}}t-=1;}
        iesire<<total1<<"\n";
    }
}
int main()
{
intrare>>p;
if (p==1){cazul1();}
if (p==2){cazul2();}

}
