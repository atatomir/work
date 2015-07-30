#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

#define ana_are_mere true
#define maxW 80
#define copyArray(d,s) for(long tt=0;tt<maxW;tt++) d[tt]=s[tt]

long i,ans,lim;
long cnt[maxW];
char S[maxW],tmp[maxW];

char sAns[maxW];
long cAns[maxW];

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("test.in","r",stdin);
    #endif // ONLINE_JUDGE

    while( ana_are_mere ){
        memset(tmp,0,sizeof(tmp));
        scanf("%s",tmp+1);
        if(tmp[1]=='.') break;

        for(i=0;i<maxW-1 && tmp[i+1]==S[i+1] ;i++); lim=i;
        while(cnt[0] && cnt[cnt[0]] >lim) cnt[0]--;
        copyArray(S,tmp);
        cnt[ ++cnt[0] ] = strlen(S+1);

        if(cnt[0]>ans){
            ans = cnt[0];
            copyArray(sAns,S);
            copyArray(cAns,cnt);
        }
    }

    for(i=1;i<=cAns[0];i++){
        for(long tt=1;tt<=cAns[i];tt++) printf("%c",sAns[tt]);
        printf("\n");
    }


    return 0;
}
