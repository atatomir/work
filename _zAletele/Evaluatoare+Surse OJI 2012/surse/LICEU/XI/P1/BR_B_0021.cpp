#include<iostream>
#include<fstream>
using namespace std;

ifstream f("biperm.in");
ofstream g("biperm.out");
int main ()
{int a[3][100],i,j,k,l,n,c,nr=0,rep[100]={0},viz[100]={0},nrp=0;
f>>n;
for(i=1;i<=2;i++)
{
    for(j=1;j<=n;j++)
    {
        f>>a[i][j];
    }
}
for(i=1;i<=2;i++)
{
    for(j=1;j<=n-1;j++)
    {
        for(k=j+1;k<=n;k++)
        {
            if(a[i][j]==a[i][k])
            {
                rep[a[i][j]]++;
            }
        }
    }
}
int aux;
for(i=1;i<=2;i++)
{
    for(j=1;j<=n;j++)
    {
        if(rep[a[i][j]]==1)
        {
            nrp=nrp+rep[a[i][j]];
        }
    }

}
for(i=1;i<=2;i++)
{
    for(j=1;j<=n-1;j++)
    {
        for(k=j+1;k<=n;k++)
        {
            if(a[i][j]=a[i][k])
            {
                aux=a[1][j];
                a[1][j]=a[2][j];
                a[2][j]=aux;
                nr++;
            }
        }
    }
}
nrp=nrp/2;
g<<nrp;
//for(i=1;i<=2;i++)
//{
   // g<<endl;
    //for(j=1;j<=n;j++)
    //{
        //g<<a[i][j]<<' ';
   // }
//}
f.close ();
g.close ();
}

