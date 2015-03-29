#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

#define dir first
#define cost second
#define maxN 267
#define pb push_back
#define mp make_pair
#define eps 0.0000000001

typedef pair<long,long> mPair;

long n,m,i,j,x,y,c,node,k,l;
vector<mPair> list[maxN];
double ec[maxN][maxN];
double ans[maxN];

void Gauss(){
    i=j=1;
    while(i<=n&&j<=n){
        for(k=i;k<=n;k++)
            if(ec[k][j]<-eps||ec[k][j]>eps) break;
        if(k>n){j++; continue;}
        if(k!=i){
            for(l=1;l<=n+1;l++) {double tmp=ec[i][l];ec[i][l]=ec[k][l];ec[k][l]=tmp;}
        }
        for(k=j+1;k<=n+1;k++) ec[i][k] /= ec[i][j]; ec[i][j] = 1.00;
        for(k=i+1;k<=n;k++){
            for(l=j+1;l<=n+1;l++) ec[k][l] -= ec[i][l]*ec[k][j];
            ec[k][j] = 0;
        }

        i++;j++;
    }

    for(i=n;i;i--){
        for(j=1;j<=n;j++){
            if(ec[i][j]>-eps&&ec[i][j]<eps) continue;

            ans[j] = ec[i][n+1];
            for(l=j+1;l<=n;l++) ans[j] -= ec[i][l]*ans[l];

            break;
        }
    }
}

int main()
{
    freopen("tunel.in","r",stdin);
    freopen("tunel.out","w",stdout);

    scanf("%ld %ld",&n,&m);
    for(i=1;i<=m;i++){
        scanf("%ld %ld %ld",&x,&y,&c);
        list[x].pb(mp(y,c));
        list[y].pb(mp(x,c));
    }

    for(node=1;node<=n;node++){
        if(list[node].size()==0 || node==n){
            ec[node][node] = 1.00;
            continue;
        }

        double tmp = 1.00/list[node].size();
        ec[node][node] = 1.00;
        for(j = 0;j<list[node].size();j++){
            long newNode = list[node][j].dir;
            long newCost = list[node][j].cost;

            ec[node][newNode] -= tmp;
            ec[node][n+1] += tmp*newCost;
        }
    }

    Gauss();
    printf("%.5f",ans[1]);

    return 0;
}
