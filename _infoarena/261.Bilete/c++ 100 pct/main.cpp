#include <iostream>
#include <fstream>
#include <cstdio>

using namespace std;

ifstream fin("bilete.in");
//ofstream fout("bilete.out");

long n,k,i,j,l,dim;
int ap[570000];

inline long hashing(long a,long b,long c){
    return (a+(dim+1)*b+(dim+1)*(dim+1)*c);
}

inline long compress(long i,long j){
    return (n*(i-1)+j);
}

inline void sort3(long& a,long& b,long& c){
    static long t;
    if(b==0) return;
    if(c==0){
        if(a > b) {t=a; a=b; b=t;}
        return;
    }
    if(a > b) {t=a; a=b; b=t;}
    if(a > c) {t=a; a=c; c=t;}
    if(b > c) {t=b; b=c; c=t;}
}

inline void check(long a,long b,long c){
    static long hash,i1,i2,i3,j1,j2,j3;
    hash = hashing(a,b,c);
    if(ap[hash]) return;

    i1 = (a+n-1)/n; j1 = a % n; if(j1 == 0) j1 = n;
    i2 = (b+n-1)/n; j2 = b % n; if(j2 == 0) j2 = n;
    i3 = (c+n-1)/n; j3 = c % n; if(j3 == 0) j3 = n;

    printf("%d%d",i1,j1);
    if(k >= 2) printf("%d%d",i2,j2);
    if(k >= 3) printf("%d%d",i3,j3);
    printf("\n");
    /*fout << i1 << j1 ;
    if(k >= 2) fout << i2<<j2;
    if(k >= 3) fout << i3<<j3;
    fout << '\n'; */

    j1 = n - j1+1;
    j2 = n - j2+1;
    j3 = n - j3+1;

    if(a) a = compress(i1,j1);
    if(b) b = compress(i2,j2);
    if(c) c = compress(i3,j3);
    sort3(a,b,c);
    hash = hashing(a,b,c);

    ap[hash]++;
}

int main()
{
    fin >> n >> k;
    dim = n*n;

    freopen("bilete.out","w",stdout);

    switch (k) {
        case 1: {
                    for(i=1;i<=dim;i++) check(i,0,0);
                    break;
                }
        case 2: {
                    for(i=1;i<=dim-1;i++)
                        for(j=i+1;j<=dim;j++)
                            check(i,j,0);
                    break;
                }
        case 3: {
                    for(i=1;i<=dim-2;i++)
                        for(j=i+1;j<=dim-1;j++)
                            for(l=j+1;l<=dim;l++)
                                check(i,j,l);
                    break;
                }
    }




    fin.close();
    //fout.close();
    return 0;
}
