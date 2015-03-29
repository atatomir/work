#include <iostream>
#include <cstdio>

using namespace std;

#define maxN 1011

long n,i,j,t,pos;
char ans[maxN],s[maxN];
bool ok;

int main()
{
    freopen("bunicu.in","r",stdin);
    freopen("bunicu.out","w",stdout);

    scanf("%ld",&t);
    for(;t;t--){
        scanf("%ld",&n);
        for(i=1;i<=n;i++) ans[i] = '0';

        pos = 1;
        for(i=1;i<=n;i++){
            scanf("%s",s+1);
            ok = true;
            for(j=1;j<pos;j++) {
                if(ans[j] != s[j]) {
                    ok = false;
                    break;
                }
            }
            if(ok){
                if(s[pos] == '0')
                    ans[pos++] = '1';
                else
                    ans[pos++] = '0';
            }
        }

        for(i=1;i<=n;i++) printf("%c",ans[i]);
        printf("\n");
    }


    return 0;
}
