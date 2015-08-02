#include <fstream>

using namespace std;
long N,na,i,c,min1,max1,n;
int main()
{   ifstream f("imprimanta.in");
    ofstream g("imprimanta.out");
    f>>N;
    //a) nr min de ace
    if(c==0)na=12;
    if(c==1)na=5;
    if(c==2)na=11;
    if(c==3)na=11;
    if(c==4)na=9;
    if(c==5)na=11;
    if(c==6)na=12;
    if(c==7)na=7;
    if(c==8)na=13;
    if(c==9)na=12;
    for(i=1;i<=n;i++)
    {
        while(N>0)
        {
            c=N%10;
            N=N/10;
        }
        if(na<min1)
        min1=na;
        for(i=1;i<=n;i++)
        if(na==min1)
        for(i=1;i<=n;i++)
        if(c>max1)
        max1=c;
    }
    g<<max1<<'\n';
    f.close();
    g.close();
    return 0;
}
