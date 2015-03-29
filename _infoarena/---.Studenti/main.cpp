#include <iostream>
#include <cstdio>

using namespace std;

#define maxN 311

struct stud{
    long long h,g;
};

long long n,i,j,k,hMax,gMax,c1,c2,c3;
stud S[maxN];
long long G[3],H[3],ans;

int main()
{
    freopen("studenti.in","r",stdin);
    freopen("studenti.out","w",stdout);

    scanf("%lld",&n); gMax = -1; hMax = -1;
    for(i=1;i<=n;i++) {
        scanf("%lld %lld",&S[i].g,&S[i].h);
        gMax = max(gMax,S[i].g);
        hMax = max(hMax,S[i].h);
    }

    ans = 1LL<<60;

    //! Case 1

    for(i=1;i<n;i++){
        for(j=i+1;j<=n;j++){
            long long val = (gMax+S[i].g+S[j].g)*(hMax+S[i].h+S[j].h);
            ans = min(ans,val);
        }
    }

    //! Case 2

    G[0] = gMax;
    H[1] = hMax;

    for(i=1;i<=n;i++){
        H[0] = S[i].h;
        for(j=1;j<=n;j++){
            G[1] = S[j].g;

            G[2]=H[2]=-1; c1=0;c2=0;c3=0;
            for(k=1;k<=n;k++){
                if(S[k].h <= H[0] && S[k].g <= G[1]) c2++;
                if(S[k].h <= H[0]) {c1++;continue;}
                if(S[k].g <= G[1]) {c2++;continue;}

                G[2] = max(G[2],S[k].g);
                H[2] = max(H[2],S[k].h); c3++;
            }

            if(c3==0){
                for(k=1;k<=n;k++){
                    long long val;
                    if(S[k].h <= H[0] && S[k].g <= G[1]){
                        if(c1>1&&c2>1){
                            val = (G[0]+G[1]+S[k].g)*(H[0]+H[1]+S[k].h);
                            ans = min(ans,val);
                        }
                    } else
                    if(S[k].h <= H[0]){
                        if(c1>1){
                            val = (G[0]+G[1]+S[k].g)*(H[0]+H[1]+S[k].h);
                            ans = min(ans,val);
                        }
                    } else {
                        if(c2>1){
                            val = (G[0]+G[1]+S[k].g)*(H[0]+H[1]+S[k].h);
                            ans = min(ans,val);
                        }
                    }

                }
            } else{
                long long val = (G[0]+G[1]+G[2])*(H[0]*H[1]*H[2]);
                ans = min(ans,val);
            }

        }
    }

    printf("%lld",ans);

    return 0;
}
