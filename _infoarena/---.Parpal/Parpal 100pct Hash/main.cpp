#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

#define maxN 1000011
#define mod1 197359

long t,i,beg;
char s[maxN];
long Hash1,Hash2,aPow;

bool check(long l,long r){
    for(;l<=r;l++,r--)
        if(s[l]!=s[r]) return false;
    return true;
}

int main()
{
    freopen("parpal.in","r",stdin);
    freopen("parpal.out","w",stdout);

    scanf("%ld\n",&t);
    for(;t;t--){
        memset(s,0,sizeof(s));
        gets(s+1); Hash1 = Hash2 = 0; aPow =1; beg=1;
        for(i=1;s[i]!='\0';i++){
            Hash1 = (Hash1*26+s[i]-'a')%mod1;
            Hash2 = (Hash2+aPow*(s[i]-'a'))%mod1;
            aPow = (aPow*26)%mod1;

            if(Hash1==Hash2 && (i-beg+1)%2==0){
                if(!check(beg,i)) continue;
                beg = i+1;
                aPow = 1; Hash1 = Hash2 = 0;
            }
        }
        if(beg==i) printf("DA\n"); else printf("NU\n");
    }


    return 0;
}
