#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>

using namespace std;

#define foreach(V) for(auto it=V.begin();it!=V.end();it++)
#define fordef(it,a,b) for(it=a;it<=b;it++)
#define mp make_pair
#define pb push_back
#define ll long long
#define pa(a,b) pair< a,b >

#define maxN 1024

int n,m,i,x,y,steps,S;
vector< pair<int,double> > list[maxN];
double cost,l,r,mid;
int gr[maxN];

queue<int> Q;
bool inQueue[maxN];
int how[maxN];
double dist[maxN];

void makeGraph(){
    S = n+1; list[S].clear();

    fordef(i,1,n)
        if(!gr[i]) list[S].pb(mp(i,0.00));

    if(list[S].empty()) S = n;
}

bool check(double def){
    memset(inQueue,0,sizeof(inQueue));
    memset(how,0,sizeof(how));
    memset(dist,0,sizeof(dist));
    while(!Q.empty()) Q.pop();

    inQueue[S]=true; how[S]=1;Q.push(S);
    while(!Q.empty()){
        int node = Q.front(); Q.pop();
        inQueue[node]=false;

        foreach(list[node]){
            pair<int,double> act = *it;
            if(!how[act.first] || dist[act.first]>dist[node]+act.second-def){
                if( ++how[act.first] == n ) return true;
                if(!inQueue[act.first]){
                    inQueue[act.first]=true;
                    Q.push(act.first);
                }
                dist[act.first] = dist[node]+act.second-def;
            }
        }
    }
    return false;
}

int main()
{
    freopen("ciclu.in","r",stdin);
    freopen("ciclu.out","w",stdout);

    scanf("%d%d",&n,&m);
    fordef(i,1,m){
        scanf("%d%d%lf",&x,&y,&cost);
        list[x].pb(mp(y,cost));
        gr[y]++;
    }

    makeGraph();
    l = 0.00; r = 100000.00; steps = 25;
    while(steps--){
        mid = (l+r)/2.00;
        if( check(mid) )
            r = mid;
        else
            l = mid;
    }

    printf("%.2lf",(l+r)/2.00);

    return 0;
}
