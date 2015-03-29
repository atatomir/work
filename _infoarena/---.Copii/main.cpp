#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

#define maxN 16

long n,i,ans;
char s[maxN][maxN];

long gr[maxN],grc;
bool fr[maxN][maxN];

void Try(long pas){
    if(pas==n+1){
        long i,j;
        memset(fr,0,sizeof(fr));
        if(grc==1) return;

        for(i=1;i<=n;i++)
            for(j=1;j<=n;j++)
                if(gr[i]!=gr[j] && s[i][j]=='1') fr[gr[i]][gr[j]]=true;

        bool ok=true;
        for(i=1;i<=grc;i++){
            for(j=1;j<=grc;j++)
                if(i!=j && fr[i][j]==false) {ok=false;break;}
            if(!ok) break;
        }

        if(ok) ans++;

        return;
    }

    for(long i=1;i<=grc;i++){
        gr[pas]= i;
        Try(pas+1);
    }

    gr[pas] = ++grc;
    Try(pas+1);
    grc--;
}

int main()
{
    freopen("copii.in","r",stdin);
    freopen("copii.out","w",stdout);

    scanf("%ld\n",&n);
    for(i=1;i<=n;i++) scanf("%s\n",s[i]+1);

    Try(1);
    printf("%ld",ans);

    return 0;
}
