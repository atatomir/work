#include <iostream>
#include <cstdio>

using namespace std;

#define maxS 100011
#define nope printf("NU\n")
#define yep printf("DA\n")

long q,n,i;
char s[maxS];

int main()
{
    freopen("colier.in","r",stdin);
    freopen("colier.out","w",stdout);

    scanf("%ld\n",&q);
    for(;q;q--){
        scanf("%ld %s\n",&n,s+1);
        if(n==1){
            if(s[1]=='0') nope; else yep;
            continue;
        }
        long cnt=0,one=0;
        for(i=1;i<=n;i++) if(s[i]=='0') cnt++; else one++;
        if((cnt&1)&&one) yep; else nope;
    }

    return 0;
}
