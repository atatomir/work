//! Brut - ce are ?

#include <iostream>
#include <fstream>

using namespace std;

ifstream fin("rk.in");
ofstream fout("rk.out");

#define maxN 200011

int main()
{
    long n,i,q,r,k;
    long v[maxN];

    fin >> n;
    for(i=1;i<=n;i++) fin >> v[i];

    fin >> q;
    for(;q--;){
        fin >> r >> k;

        long ans = 0;
        for(i=1;i<=n;i++)
            if(v[i]%(1<<k) == r) ans++;

        fout << ans << '\n';
    }

    fin.close();
    fout.close();

    return 0;
}
