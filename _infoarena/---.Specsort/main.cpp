#include <iostream>
#include <cstdio>

using namespace std;

#define maxN 50011
#define maxBit 16

long n,i,s,d,bit;
long v[2][maxN];
bool useful;

int main()
{
    freopen("specsort.in","r",stdin);
    freopen("specsort.out","w",stdout);

    scanf("%ld",&n);
    s=0;d=1;
    for(i=1;i<=n;i++) scanf("%ld",&v[s][i]);

    for(bit=0;bit<=maxBit;bit++){
        long mask = (1<<bit);

        long cnt=0;
        for(i=1;i<=n;i++)
            if((v[s][i]&mask)==0) cnt++;

        long c1=0,c2=cnt;
        for(i=1;i<=n;i++){
            if(mask&v[s][i]) v[d][++c2]=v[s][i];
            else             v[d][++c1]=v[s][i];
        }

        useful = false;
        for(i=1;i<=n;i++){
            if(v[s][i]!=v[d][i]){
                useful = true;
                break;
            }
        }

        if(useful){
            for(i=1;i<=n;i++) printf("%ld ",v[d][i]);
            printf("\n");
        }

        s^=1;d^=1;
    }

    return 0;
}
