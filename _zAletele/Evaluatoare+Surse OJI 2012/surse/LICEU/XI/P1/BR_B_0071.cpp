#include <iostream>
#include<fstream>
using namespace std;
ifstream f("biperm.in");
ofstream g("biperm.out");
struct biperm
{
    long int x1,x2;
}a[10002];
int n,nr1,nr2,max,i,j,aux,st[10002];
void citire()
{
    f>>n;
    for(i=1;i<=n;i++)
    f>>a[i].x1;
    for(i=1;i<=n;i++)
    f>>a[i].x2;
}

int main()
{
    citire();
    for(i=1;i<=n;i++)
    for(j=1;j<=n;j++)
    if(a[i].x1==a[j].x1&&i!=j)
    nr1++;
    for(i=1;i<=n;i++)
    for(j=1;j<=n;j++)
    if(a[i].x2==a[j].x2&&i!=j)
    nr2++;
    if(nr1>nr2) g<<nr1*nr1<<" "<<nr1-1<<endl;
    else g<<nr2*nr2<<" "<<nr2-1<<endl;
    for(i=1;i<=n;i++)
    for(j=i;j<=n;j++)
    if(a[i].x1==a[j].x1&&i!=j)
    if(a[j].x1!=a[j].x2)
    {
        aux=a[j].x1;
        a[j].x1=a[j].x2;
        a[j].x2=aux;
        break;
    }
    else
     {
        aux=a[i].x1;
        a[i].x1=a[i].x2;
        a[i].x2=aux;
        break;
    }
    for(i=1;i<=n;i++)
    g<<a[i].x1<<" ";
    g<<endl;
    for(i=1;i<=n;i++)
    g<<a[i].x2<<" ";
}
