#include <iostream>
#include <cstdio>

using namespace std;

#define maxN 1000111

long n,m,q,i,j,x,y;
char s[maxN*2];
long z[2][maxN*2];

void algoZ(long id){
    long i,bg,en=0;
    for(i=2;i<=n+m+1;i++){
        if(en>=i) z[id][i] = min(en-i+1,z[id][i-bg+1]);
        while(s[z[id][i]+1] == s[i+z[id][i]]) z[id][i]++;
        if(en < i+z[id][i]-1){
            bg = i; en = bg+z[id][i]-1;
        }
    }
}

void Reverse(long i,long j){
    while(i<j) swap(s[i++],s[j--]);
}

int main()
{
    freopen("x.in","r",stdin);
    freopen("x.out","w",stdout);

    scanf("%ld %ld %ld\n",&n,&m,&q);
    scanf("%s\n%s\n",s+m+2,s+1);
    s[m+1] = '+';

    algoZ(0);
    Reverse(m+2,m+n+1);
    algoZ(1);

    for(;q;q--){
        scanf("%ld %ld",&x,&y);
        long v1 = z[1][m+1+n-(x-1)+1];
        long v2 = z[0][m+1+y+1];

        printf("%ld\n",min(v1,v2));
    }


    return 0;
}
