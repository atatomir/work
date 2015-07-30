#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

#define maxS 3000011

long cnt['z'+20];
long n,m,i,j,def;
char s[maxS],c;
long score=0,ans=0;

void addValue(char cc,long v){
    if(cnt[cc]==0) score--;
    cnt[cc]+=v;
    if(cnt[cc]==0) score++;
}

int main()
{
    //freopen("test.in","r",stdin);

    scanf("%ld %ld\n%s\n",&n,&m,s+1);
    for(i=1;i<=n;i++) cnt[ s[i] ]++;

    scanf("%s",s+1);
    for(i=1;i<=n;i++) cnt[ s[i] ]--;

    def = 'z'-'A'+1;
    for(c='A';c<='z';c++) if(cnt[c]==0) score++;

    if(score==def)ans++;
    for(i=n+1;i<=m;i++){
        addValue(s[i],-1);
        addValue(s[i-n],+1);
        if(score==def) ans++;
    }

    printf("%ld",ans);

    return 0;
}
