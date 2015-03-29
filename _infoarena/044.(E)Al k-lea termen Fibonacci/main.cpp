#include <iostream>
#include <fstream>

#define mod 666013

using namespace std;

ifstream fin("kfib.in");
ofstream fout("kfib.out");

long long k;
long long a[2][2]={{1,1},{1,0}},aux[2][2],r[2][2]={{1,0},{0,1}};

inline void inmultire(long long x[2][2],long long y[2][2],long n,long m,long dim){
    long i,j,p;
    for(i=0;i<n;i++){
        for(j=0;j<m;j++){
            aux[i][j] = 0;
            for(p=0;p<dim;p++) aux[i][j] = (aux[i][j] + x[i][p]*y[p][j])% mod;
        }
    }
    for(i=0;i<n;i++)
        for(j=0;j<m;j++)
            x[i][j] = aux[i][j];
}

int main()
{
    fin >> k; k--,k--;

    if(k <= 0){
        fout << 1;
        fout.close();
        return 0;
    }

    while(k){
        if(k&1){
            inmultire(r,a,2,2,2);
        }
        inmultire(a,a,2,2,2);
        k >>= 1;
    }

    a[0][0] = 1; a[1][0] = 1;

    inmultire(r,a,2,1,2);

    fout << r[0][0];

    fin.close();
    fout.close();
    return 0;
}
