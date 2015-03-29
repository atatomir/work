#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

#define maxN 211
#define INF 2000000000

long n,m,i,j,ans;
long a[maxN][maxN],sum[maxN][maxN];
long UR[maxN][maxN],UL[maxN][maxN],LR[maxN][maxN];

void Show(){
    for(long i=1;i<=n;i++){
        for(j=1;j<=m;j++) cerr << a[i][j] << ' ';
        cerr << '\n';
    }
}

void TryNow(){
    long i,j,k;
    long tmp[maxN];

    memset(tmp,0,sizeof(tmp));

    //! sume pe coloane
    for(i=1;i<=n;i++)
        for(j=1;j<=m;j++)
            sum[i][j] = sum[i-1][j]+a[i][j];

    //! init
    for(i=1;i<=n;i++)
        for(j=1;j<=m;j++) UL[i][j]=UR[i][j]=-INF;
    for(i=1;i<=n;i++)
        for(j=i;j<=n;j++) LR[i][j]=-INF;

    //! from Up-Left
    for(i=1;i<=n;i++){
        for(j=i;j<=n;j++){
            for(k=1;k<=m;k++){
                tmp[k] = sum[j][k]-sum[i-1][k];
                if(tmp[k-1]>0) tmp[k] += tmp[k-1];
                UL[j][k] = max(UL[j][k],tmp[k]);
            }
        }
    }
    for(i=1;i<=n;i++){
        for(j=1;j<=m;j++) {
            if(i>1) UL[i][j] = max(UL[i][j],UL[i-1][j]);
            if(j>1) UL[i][j] = max(UL[i][j],UL[i][j-1]);
        }
    }

    //! from Up-Right
    for(i=1;i<=n;i++){
        for(j=i;j<=n;j++){
            for(k=m;k;k--){
                tmp[k] = sum[j][k]-sum[i-1][k];
                if(tmp[k+1]>0) tmp[k] += tmp[k+1];
                UR[j][k] = max(UR[j][k],tmp[k]);
            }
        }
    }
    for(i=1;i<=n;i++){
        for(j=m;j;j--) {
            if(i>1)UR[i][j] = max(UR[i][j],UR[i-1][j]);
            if(j<m)UR[i][j] = max(UR[i][j],UR[i][j+1]);
        }
    }

    //! Left-Right
    for(i=1;i<=n;i++){
        for(j=i;j<=n;j++){
            for(k=1;k<=m;k++) tmp[k] = sum[j][k] - sum[i-1][k];
            for(k=1;k<=m;k++){
                if(tmp[k-1]>0) tmp[k] += tmp[k-1];
                LR[i][j] = max(LR[i][j],tmp[k]);
            }

            if(i!=j)LR[i][j] = max(LR[i][j],LR[i][j-1]);
        }
    }
    for(j=n;j;j--)
        for(i=j-1;i;i--) LR[i][j] = max(LR[i][j],LR[i+1][j]);


    //!!!!!!!!!! First case : three lines
    for(i=1;i<=n-2;i++){
        for(j=i+1;j<=n-1;j++){
            long how = LR[1][i]+LR[i+1][j]+LR[j+1][n];
            ans = max(ans,how);
        }
    }

    //!!!!!!!!!! Second case : one line and two squares
    for(i=1;i<n;i++){
        for(j=1;j<m;j++){
            long how = UL[i][j] + UR[i][j+1] + LR[i+1][n];
            ans = max(ans,how);
        }
    }

}

void Rotate(){
    long tmp[maxN][maxN],i,j;
    for(i=1;i<=n;i++)
        for(j=1;j<=m;j++) tmp[i][j] = a[i][j];

    for(i=1;i<=n;i++)
        for(j=1;j<=m;j++)
            a[j][n-i+1] = tmp[i][j];

    swap(n,m);
}

int main()
{
    freopen("treid.in","r",stdin);
    freopen("treid.out","w",stdout);

    scanf("%ld %ld",&n,&m);
    for(i=1;i<=n;i++)
        for(j=1;j<=m;j++)
            scanf("%ld",&a[i][j]);

    ans = -INF;

    TryNow();
        Rotate(); //Show(); cerr << '\n';
    TryNow();
        Rotate(); //Show(); cerr << '\n';
    TryNow();
        Rotate(); //Show(); cerr << '\n';
    TryNow();

    printf("%ld",ans);

    return 0;
}
