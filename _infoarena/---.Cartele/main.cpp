#include <iostream>
#include <cstdio>

using namespace std;

#define maxN 55
#define s typ[ss]
#define d typ[dd]

long n,c,i,j;
bool typ[8][maxN][maxN];
bool tmp[maxN][maxN];
bool found;

void Rotate(long ss,long dd){
    for(long i=1;i<=n;i++)
        for(long j=1;j<=n;j++) d[n-j+1][i] = s[i][j];
}
void Mirror(long ss,long dd){
    for(long i=1;i<=n;i++)
        for(long j=1;j<=n;j++) d[i][n-j+1] = s[i][j];
}
bool check(long ss){
    for(long i=1;i<=n;i++)
        for(long j=1;j<=n;j++)
            if(tmp[i][j] != s[i][j]) return 0;
    return true;
}

int main()
{
    freopen("cartele.in","r",stdin);
    freopen("cartele.out","w",stdout);

    scanf("%ld %ld",&n,&c);
    for(i=1;i<=n;i++)
        for(j=1;j<=n;j++) scanf("%ld",&typ[0][i][j]);

    Rotate(0,1);
    Rotate(1,2);
    Rotate(2,3);
    Mirror(0,4);
    Rotate(4,5);
    Rotate(5,6);
    Rotate(6,7);

    for(;c;c--){
        for(i=1;i<=n;i++)
            for(j=1;j<=n;j++)
                scanf("%ld",&tmp[i][j]);

        found = false;
        for(i=0;i<8;i++) {
            if(check(i)){
                printf("1\n"); found = true;
                break;
            }
        }
        if(!found) printf("0\n");
    }

    return 0;
}
