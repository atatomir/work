#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>
#include <cstring>
#include <queue>

using namespace std;

#define eps 0.000001
#define maxN 1000
#define defPas 30

struct Point{
    double x,y;

    void get(){
        scanf("%lf %lf",&x,&y);
    }
    double dist(Point& who){
        return sqrt( (x-who.x)*(x-who.x) + (y-who.y)*(y-who.y) );
    }
    bool couple(Point& who,double lim){
        if( lim+eps > dist(who) ) return true;
        return false;
    }
};

long n,i;
Point sP[maxN],aP[maxN];
double ansMax,ansSum;

//! Cuplaj maxim
long l[maxN],r[maxN];
vector<long> list[maxN];
bool us[maxN];

void makeGraph(double dim){
    long i,j;
    memset(l,0,sizeof(l));
    memset(r,0,sizeof(r));
    for(i=1;i<=n;i++) list[i].clear();

    for(i=1;i<=n;i++)
        for(j=1;j<=n;j++)
            if(sP[i].couple( aP[j],dim )) list[i].push_back(j);
}

bool pairUp(long node){
    if(us[node]) return false;
    us[node] = true;

    for(auto it=list[node].begin();it!=list[node].end();it++){
        if(!r[*it]){
            l[node] = *it;
            r[*it] = node;
            return true;
        }
    }
    for(auto it=list[node].begin();it!=list[node].end();it++){
        if(pairUp(r[*it])){
            l[node] = *it;
            r[*it] = node;
            return true;
        }
    }

    return false;
}

void Cuplaj(){
    long i;
    bool ok;

    ok = true;
    while(ok){
        ok = false;
        memset(us,0,sizeof(us));

        for(i=1;i<=n;i++)
            if(!l[i]) ok |= pairUp(i);
    }
}

bool allGood(){
    for(long i=1;i<=n;i++)
        if(!l[i]) return false;
    return true;
}

//! Cuplaj maxim de cost minim
#define S 0
#define D 900
long F[maxN][maxN],C[maxN][maxN];
double cost[maxN][maxN],cc[maxN];
long prov[maxN];
queue<long> Q;
bool inQueue[maxN];

void makeFGraph(double dim){
    long i,j;
    for(i=1;i<=n;i++) list[i].clear();

    for(i=1;i<=n;i++){
        for(j=1;j<=n;j++){
            if(sP[i].couple( aP[j],dim )) {
                list[i].push_back(j+n);
                list[j+n].push_back(i);
                F[i][j+n]=F[j+n][i]=0;
                C[i][j+n]=1;C[j+n][i]=0;
                cost[i][j+n] = sP[i].dist( aP[j] );
                cost[j+n][i] = -cost[i][j+n];
            }
        }
    }

    for(i=1;i<=n;i++){
        list[S].push_back(i);
        list[i].push_back(S);
        F[S][i]=F[i][S]=0;
        C[S][i]=1;C[i][S]=0;
        cost[S][i] = cost[i][S]=0;
    }
    for(i=n+1;i<=n*2;i++){
        list[D].push_back(i);
        list[i].push_back(D);
        F[D][i]=F[i][D]=0;
        C[D][i]=0;C[i][D]=1;
        cost[D][i] = cost[i][D]=0;
    }

}

bool bellman(){
    memset(prov,0,sizeof(prov));
    memset(cc,0,sizeof(cc));
    memset(inQueue,0,sizeof(inQueue));
    memset(us,0,sizeof(us));
    while(!Q.empty()) Q.pop();

    Q.push(S); prov[S]=-1; us[S]=true; inQueue[S]=true;
    while(!Q.empty()){
        long node = Q.front();Q.pop(); inQueue[node]=false;
        if(node==D) continue;

        for(auto it = list[node].begin();it!=list[node].end();it++){
            double newCost = cc[node] + cost[node][*it];
            if(C[node][*it]==F[node][*it]) continue;
            if(!us[*it] || newCost < cc[*it]){
                prov[*it] = node;
                cc[*it] = newCost;
                us[*it]=true;
                if(!inQueue[*it]){
                    inQueue[*it]=true;
                    Q.push(*it);
                }
            }
        }
    }

    if(!us[D]) return false;
    ansSum += cc[D];
    for(long node = D;node;node=prov[node]){
        F[prov[node]][node]++;
        F[node][prov[node]]--;
    }


    return true;
}

//! si altele

double getAnsMax(){
    double i=0.00,j=1500.00,m;
    long pas = defPas;

    while(pas--){
        m = (i+j)/2.00;
        makeGraph(m);
        Cuplaj();

        if(allGood()) j=m; else i=m;
    }

    return i;
}

int main()
{
    freopen("adapost.in","r",stdin);
    freopen("adapost.out","w",stdout);

    scanf("%ld",&n);
    for(i=1;i<=n;i++) sP[i].get();
    for(i=1;i<=n;i++) aP[i].get();

    ansMax = getAnsMax();
    printf("%.5lf ",ansMax);

    makeFGraph(ansMax+eps*10);
    while(bellman()){}

    printf("%.5lf ",ansSum);

    return 0;
}
