#include <iostream>
#include <cstdio>
#include <bitset>

using namespace std;

#define maxN 1024*1024

long n,m,i,l,act,def,conf;
char s[maxN];
bitset< 1<<20 > B;

int main()
{
    freopen("dinti.in","r",stdin);
    freopen("dinti.out","w",stdout);

    scanf("%ld%ld%ld\n%s\n",&n,&m,&l,s+1);

    act=0; def = (1<<l)-1;
    for(i=1;i<l;i++) act = (act<<1) + s[i]-'0' ;

    for(i=l;i<=n;i++){
        act = (act<<1)&def;
        act |= s[i]-'0';

        B[act]=1;
    }

    for(conf=1;conf<=def;conf++){
        if(B[conf]) continue;
        for(i=0;i<l;i++){
            if(conf&(1<<i)){
                long newConf = conf ^ (1<<i);
                if(B[newConf]){
                    B[conf]=true;
                    break;
                }
            }
        }
    }

    for(;m;m--){
        scanf("%s\n",s+1);
        act = 0;
        for(i=1;i<=l;i++) act = (act<<1)+s[i]-'0';
        act ^= def;

        if(B[act]) printf("1\n"); else printf("0\n");
    }

    return 0;
}
