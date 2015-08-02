#include <iostream>
#include <fstream>
#define maxv 2001
#define inf 36200
#include <cmath>
#include<vector>
using namespace std;

ifstream f("fractii2.in");
ofstream g("fractii2.out");
int p,n;
int v[maxv];

void citire()
{
    f>>p>>n;
    for(int i=1;i<n;i++)
    v[i] = i;
    v[n-1] = n-1;
}

void pctA()
{
    for(int i=1;i<n;i++)
        g<<i<<' ';
    g<<n-1;
}

int pctB(int q[maxv])
{
    int sol=0;
    for(int i=1;i<n;i++)
    {
        while(v[i] > 0)
        {
            v[i]--;
            v[i+1]+=2;
            for(int i=1;i<=n;i++)
            sol+=pctB(q);
        }
    }
    int s=0;
    for(int i=1;i<=n;i++)
    s+=q[i];

    if(n==s)
        return sol%100003;
}

long fibo(long a,long b)
{
    if(n>2)
    {
        n--;
        return fibo(b, a+b) % 100003;
    }
    else return b;
}
int main()
{
    citire();
    for(int i=1;i<n;i++)
    v[i] = 1;
    v[n-1] = 2;
    if(p==1)
        pctA();
    else
    {
        if(n==2)
            g<<1;
        if(n>2)
        g<<fibo(0,1);
    }
    return 0;
}
