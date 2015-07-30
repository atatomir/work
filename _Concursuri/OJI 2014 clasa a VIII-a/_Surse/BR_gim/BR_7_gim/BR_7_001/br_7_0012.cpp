//Problema 2- SCHI
#include<iostream>
#include<fstream>
#include<stdlib.h>
using namespace std;

struct clasament{long long p; long nr;};
clasament c[100000];
int main()
{
    ifstream f("schi.in");
    ofstream g("schi.out");
    long n,k,i,j,poz;
    long long x,pct,max;
    short ok;
    f>>n;
    max=0;
    poz=0;
    for (i=1; i<=n; i++){
        f>>pct;
        if (pct>max){
            poz++;
            max=pct;
            c[poz].p=pct;
            c[poz].nr=1;
        }
        else
            c[poz].nr++;
    }
    f>>k;
    for (i=1; i<=k; i++){
        f>>x;
        ok=0;
        j=0;
        while (ok==0 && j<=poz){
            j++;
            if (c[j].p==x)
                ok=1;
        }
        if (ok==0)
            g<<"0 ";
        else
            g<<c[j].nr<<' ';
    }
    g<<'\n';
    f.close();
    g.close();
    return 0;
}
