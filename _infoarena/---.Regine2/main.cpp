#include <iostream>
#include <cstdio>

using namespace std;

#define maxN 10

struct Point{
    long x,y;
};
Point mp(long xx,long yy){
    Point ans; ans.x=xx; ans.y=yy;
    return ans;
}

const long defX[4]={0,1,1,1};
const long defY[4]={1,1,0,-1};

long t,n,i,j,cnt;
char s[maxN][maxN];
long dp[maxN][maxN];

long aMax,aCnt;

void Back(long x,long y){
    if(y==n+1){
        if(x==n){
            if(aMax==cnt) aCnt++;
            if(aMax<cnt) {aMax=cnt;aCnt=1;}
            return;
        }
        y=1; x++;
    }

    Back(x,y+1);
    if(dp[x][y]==0 && s[x][y]=='.'){
        cnt++;
        for(i=0;i<4;i++){
            Point p=mp(x,y);
            while(s[p.x][p.y]=='.'){
                p.x += defX[i]; p.y += defY[i];
                dp[p.x][p.y]++;
            }
        }

        Back(x,y+1);

        for(i=0;i<4;i++){
            Point p=mp(x,y);
            while(s[p.x][p.y]=='.') {
                p.x += defX[i]; p.y += defY[i];
                dp[p.x][p.y]--;
            }
        }

        cnt--;
    }

}

int main()
{
    freopen("regine2.in","r",stdin);
    freopen("regine2.out","w",stdout);

    scanf("%ld",&t);
    for(;t;t--){
        scanf("%ld\n",&n);
        for(i=1;i<=n;i++) {
            scanf("%s",s[i]+1);
            s[i][0]=s[i][n+1]=s[0][i]=s[n+1][i]='#';
        }
        s[0][0]=s[0][n+1]=s[n+1][0]=s[n+1][n+1]='#';
        aMax = 0; aCnt=0; cnt=0;
        Back(1,1);

        printf("%ld %ld\n",aMax,aCnt);
    }

    return 0;
}
