#include <iostream>
#include <cstdio>
#include <bitset>

using namespace std;

#define maxN 512

long n,i,j,x;
long ans;

bitset<maxN> m[maxN];
bitset<maxN> cL,cC;

int main()
{
    freopen("panou.in","r",stdin);
    freopen("panou.out","w",stdout);

    cL.reset(); cC.reset();
    scanf("%ld",&n);
    for(i=1;i<=n;i++){
        for(j=1;j<=n;j++){
            scanf("%ld",&x);
            if(x==0) m[i][j]=0; else m[i][j]=1;
        }
    }
    for(i=1;i<=n;i++){
        for(j=1;j<=n;j++){
            scanf("%ld",&x);
            if(x==1) m[i][j]=m[i][j]^1;
        }
    }

    for(i=n;i;i--){
        if(m[i][i]^cL[i]^cC[i]==1){
            ans++;
            cL[i]=cL[i]^1; cC[i]=cC[i]^1;
        }

        for(j=i-1;j;j--){
            if(m[j][i]^cL[j]^cC[i]==1){
                ans++;
                cL[j]=cL[j]^1; cC[i]=cC[i]^1;
            }
        }

        for(j=i-1;j;j--){
            if(m[i][j]^cL[i]^cC[j]==1){
                ans++;
                cL[i]=cL[i]^1; cC[j]=cC[j]^1;
            }
        }
    }

    printf("%ld",ans);

    return 0;
}
