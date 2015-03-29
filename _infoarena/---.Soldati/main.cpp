#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

#define maxS 100011

long t,n,i,bg,en;
char s[maxS];

int main()
{
    freopen("soldati.in","r",stdin);
    freopen("soldati.out","w",stdout);

    scanf("%ld",&t);
    for(;t;t--){
        memset(s,0,sizeof(s));
        scanf("%s\n",s+1);

        bg=1;en=strlen(s+1);
        while(s[bg]=='<') bg++;
        while(s[en]=='>') en--;
        if(bg>en){
            printf("0\n");
            continue;
        }

        long time=0,wait=0,rr=0;
        for(i=bg;i<=en;i++){
            if(s[i]=='>'){
                rr++;
                if(--wait<0) wait=0;
            } else {
                time = rr+wait;
                wait++;
            }
        }

        printf("%ld\n",time);
    }


    return 0;
}
