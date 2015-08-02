#include<iostream>
#include<fstream>
#define nmax 1000
#define bmax 1000
using namespace std;
ifstream f("clepsidru.in");
ofstream g("clepsidru.out");
int main()
{int n[nmax]={0},k[nmax]={0},s[nmax]={0},p[2],i;long long b[bmax]={0};
for(i=1;i<=nmax;i++)
    f>>n[i];
for(i=1;i<=bmax;i++)
    f>>b[i];
for(i=1;i<=nmax;i++)
f>>k[i];
    f.close();
    g.close();
    return 0;
}
