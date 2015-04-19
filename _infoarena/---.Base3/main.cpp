#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>

using namespace std;

#define maxN 16384
#define INF 2000000000

long v[6],i,ans;
char s[3][maxN];

queue<long> Q;
long us[maxN];
bool inQueue[maxN];

long abss(long x){
    if(x<0) return -x;
    return x;
}

int main()
{
    freopen("base3.in","r",stdin);
    freopen("base3.out","w",stdout);

    scanf("%s\n%s\n%s",s[0]+1,s[1]+1,s[2]+1);
    v[0] = strlen(s[0]+1); v[3]=-v[0];
    v[1] = strlen(s[1]+1); v[4]=-v[1];
    v[2] = strlen(s[2]+1); v[5]=-v[2];

    us[0] = 1; Q.push(0); inQueue[0]=true;
    while(!Q.empty()){
        long val = Q.front(); Q.pop(); inQueue[val]=false;
        for(i=0;i<6;i++){
            long newVal = val + v[i];
            if(newVal < 0) newVal = -newVal;

            if(newVal >= maxN) continue;
            if(us[newVal] && us[newVal] <= us[val]+abss(v[i])) continue;

            us[newVal] = us[val]+abss(v[i]); if(!inQueue[newVal])Q.push(newVal);
            inQueue[newVal] = true;
        }
    }

    ans = INF;
    for(long id=0;id<3;id++){
        for(i=1;i<=v[id];i++){
            if(s[id][i]!='1') continue;
            if(us[ abss( (i-1)-(v[id]-i) ) ] == 0) continue;
            if(us[ abss( (i-1)-(v[id]-i) ) ] < ans-v[id]) ans = v[id]+us[ abss( (i-1)-(v[id]-i) ) ];
        }
    }

    if(ans==INF) printf("0"); else
    printf("%ld",ans-1);

    return 0;
}
