#include <iostream>
#include <fstream>
using namespace std;
int n,i,bb,k,p,verificare[1001],f,r,i1=1,i2=1,curent,maxim=1,l,sir[5001];
    ifstream intrare("cool.in");
    ofstream iesire("cool.out");
bool adevar=true;
void elementedistincte()
{
    if (sir[1]!=sir[2]){r+=1;}
    if (sir[k]!=sir[k-1]){r+=1;}
    for (i=2;i<k;i++)
    {
        if (sir[i]!=sir[i-1]&&sir[i]!=sir[i+1]){r+=1;}
    }
    iesire<<r;
}
void cazul1()
{
    intrare>>n;
    n=2;
    intrare>>k;
    for (i=1;i<=k;i++)
    {
        intrare>>sir[i];
    }
    while (adevar==true)
    {
        adevar=false;
    for (i=2;i<k;i++)
    {
        if (sir[i]<sir[i-1]){f=sir[i];sir[i]=sir[i-1];sir[i-1]=f;adevar=true;}
        if (sir[i]>sir[i+1]){f=sir[i];sir[i]=sir[i+1];sir[i+1]=f;adevar=true;}
    }
    }
    for (i=1;i<k;i++)
    {
        if (sir[i+1]!=sir[i]+1){elementedistincte();n=1;}
    }
    if (n==2){
    iesire<<sir[k];
    }

}
void cazul2()
{
     intrare>>n;
     intrare>>k;
     for (i=1;i<=n;i++)
    {
        intrare>>sir[i];
    }
    while (i2<=n&&i1<=n){
        for (l=1;l<=1000;l++)
        {
            verificare[l]=0;
        }
    for (i=i1;i<=i2;i++)
    {
        verificare[i-i1+1]=sir[i];
    }
    while (adevar==true)
    {
        adevar=false;
    for (i=2;i<i2-i1+1;i++)
    {
        if (verificare[i]<verificare[i-1]){f=verificare[i];verificare[i]=verificare[i-1];verificare[i-1]=f;adevar=true;}
        if (verificare[i]>verificare[i+1]){f=verificare[i];verificare[i]=verificare[i+1];verificare[i+1]=f;adevar=true;}
    }
    }
    adevar=true;
    bb=2;
    for (i=1;i<i2-i1+1;i++)
    {
        if (verificare[i+1]!=verificare[i]+1){bb=1;}
    }
    if (bb==1){i2+=1;}
    if (bb==2){
        curent=i2-i1+1;
        if (curent>maxim){bb=1;maxim=curent;}
        if (curent==maxim){bb+=1;}
    i2+=1;
    }
    if (i2==n){i2=i1+1;i1=i1+1;}
    if (i2>n||i1>n){break;}
    }
    iesire<<maxim<<"\n"<<bb;
}
int main()
{
    intrare>>p;
    if (p==1){cazul1();}
    if (p==2){cazul2();}
}
