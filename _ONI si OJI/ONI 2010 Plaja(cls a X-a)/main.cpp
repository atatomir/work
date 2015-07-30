#include <iostream>
#include <cstdio>

using namespace std;

#define maxN 2010
#define x1 x
#define y1 y

long n,m,u,i,j,x,y,x2,y2,nr;
long sU[maxN][maxN],sT[maxN][maxN];
long ansA,ansB;

bool noUmbrela() {
    long val=0;
    val = sU[x2][y2] - sU[x1-1][y2] - sU[x2][y1-1] + sU[x1-1][y1-1];
    if(val == 0) return true;
    return false;
}

bool noTurist() {
    long val=0;
    val = sT[x2][y2] - sT[x1-1][y2] - sT[x2][y1-1] + sT[x1-1][y1-1];
    if(val == 0) return true;
    return false;
}

void putT(){
    sT[x1][y1]++; sT[x2+1][y2+1]++;
    sT[x2+1][y1]--; sT[x1][y2+1]--;
}

int main()
{
    freopen("plaja.in","r",stdin);
    freopen("plaja.out","w",stdout);

    scanf("%ld %ld %ld",&n,&m,&u);
    for(i=1;i<=u;i++){
        scanf("%ld %ld",&x,&y);
        sU[x][y]++;
        sT[x][y]++; sT[x+1][y+1]++; sT[x+1][y]--; sT[x][y+1]--;
    }

    for(i=1;i<=n;i++)
        for(j=1;j<=m;j++)
            sU[i][j] += sU[i-1][j] + sU[i][j-1] - sU[i-1][j-1];

    scanf("%ld",&nr);
    for(i=1;i<=nr;i++){
        scanf("%ld %ld %ld %ld",&x,&y,&x2,&y2);
        if(noUmbrela()){
            ansA++;
            putT();
        }
    }

    for(long rep=2;rep;rep--)
    for(i=1;i<=n;i++)
        for(j=1;j<=m;j++)
            sT[i][j] += sT[i-1][j] + sT[i][j-1] - sT[i-1][j-1];

    scanf("%ld",&nr);
    for(i=1;i<=nr;i++){
        scanf("%ld %ld %ld %ld",&x,&y,&x2,&y2);
        if(noTurist()) ansB++;
    }

    printf("%ld %ld",ansA,ansB);

    return 0;
}
