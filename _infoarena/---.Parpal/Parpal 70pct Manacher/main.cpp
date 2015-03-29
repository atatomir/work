#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

#define maxN 1000011
#define act dp[i]

long t,i,n;
char s[maxN];
char ss[maxN<<1];
long dp[maxN<<1];
long beg;
long C,fC;

int main()
{
    freopen("parpal.in","r",stdin);
    freopen("parpal.out","w",stdout);

    scanf("%ld\n",&t);
    for(;t;t--){
        memset(s,0,sizeof(s));
        gets(s+1); beg = 1; n=0; fC = 0;
        for(i=1;s[i]!='\0';i++){
            ss[++n] = s[i];
            ss[++n] = ',';
        } ss[0] = '@' ; ss[n--] = '#';

        for(i=1;i<=n;i++){
            dp[i] = 0;
            if(i<=fC) dp[i] = min(fC-i,dp[2*C-i]);
            while(ss[i-act-1] == ss[i+act+1]) act++;

            if((i&1)==0 && act>=i-beg && i>beg){
                beg = i+i-beg+1;
                if((beg&1)==0) beg++;
            }

            if(i+act > fC){
                fC = i+act; C = i;
            }

        }

        if(beg <= n) printf("NU\n"); else printf("DA\n");
    }

    return 0;
}
