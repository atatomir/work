#include <iostream>
#include <cstdio>

using namespace std;

#define maxN 200

long n,m,ns,ms,i,j,dim;
long ans[maxN][maxN];
long t,ti;

bool rl,rc;
long op,val;

int main()
{
    freopen("origami.in","r",stdin);
    freopen("origami.out","w",stdout);

    scanf("%ld%ld",&n,&t); m = n;
    ns = 1; ms = 1;

    for(i=1;i<=n;i++)
        for(j=1;j<=n;j++) ans[i][j] = 1;

    for(ti=1;ti<=t;ti++){
        scanf("%ld %ld",&op,&val);
        long rez = val;
        if(op == 1){
            dim = m-ms+1;
            if(rc) val = dim - val;

            if(val <= dim/2){

                for(i=1;i<=val;i++){
                    for(j=ns;j<=n;j++){
                        ans[j][m-val-i+1] += ans[j][m-val+i];
                    }
                }
                m -= val;
            } else {
                val = dim-val;
                //if(rc) rc = false; else rc = true;

                for(i=1;i<=val;i++){
                    for(j=ns;j<=n;j++){
                        ans[j][ms+val+i-1] += ans[j][ms+val-i];
                    }
                }
                ms += val;
            }

            if(rez > dim/2)
                if(rc) rc = false; else rc = true;
        } else {
            dim = n-ns+1;
            if(rl) val = dim - val;

            if(val <= dim/2){

                for(i=1;i<=val;i++){
                    for(j=ms;j<=m;j++){
                        ans[n-val-i+1][j] += ans[n-val+i][j];
                    }
                }
                n -= val;
            } else {
                val = dim - val;
                //if(rl) rl = false; else rl = true;

                for(i=1;i<=val;i++){
                    for(j=ms;j<=m;j++){
                        ans[ns+val+i-1][j] += ans[ns+val-i][j];
                    }
                }
                ns += val;
            }

            if(rez >dim/2)
                    if(rl) rl = false; else rl = true;
        }
    }

    long maxim = 0;
    for(i=ns;i<=n;i++)
        for(j=ms;j<=m;j++)
            maxim = max(maxim,ans[i][j]);

    printf("%ld %ld %ld",n-ns+1,m-ms+1,maxim);

    return 0;
}
