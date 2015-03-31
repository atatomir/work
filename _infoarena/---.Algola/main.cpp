#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

#define maxN 55
#define maxT 105
#define mp make_pair
#define INF 200
#define time tttime

struct Edge{
    long x,y,c;
};

long n,m,i,S,D,hum[maxN],sum,time;
vector<Edge> E;
long C[maxN][maxT][maxN][maxT],F[maxN][maxT][maxN][maxT];
vector<pair<long,long> > list[maxN][maxT];

long flux;
queue<pair<long,long> > Q;
pair<long,long> prov[maxN][maxT];
bool used[maxN][maxT];

void addArc(long n1,long t1,long n2,long t2,long cap){
    list[n1][t1].push_back(mp(n2,t2));
    list[n2][t2].push_back(mp(n1,t1));

    C[n1][t1][n2][t2] = cap;
}

bool BF(){
    memset(used,0,sizeof(used));

    used[S][S] = true; Q.push(mp(S,S));
    while(!Q.empty()){
        pair<long,long> act = Q.front(); Q.pop();
        if(act==mp(D,D)) continue;

        for(long i=0;i<list[act.first][act.second].size();i++){
            pair<long,long> dir = list[act.first][act.second][i];

            if(used[dir.first][dir.second] || F[act.first][act.second][dir.first][dir.second]==C[act.first][act.second][dir.first][dir.second]) continue;
            used[dir.first][dir.second] = true;
            Q.push(mp(dir.first,dir.second));
            prov[dir.first][dir.second] = act;
        }
    }

    if(!used[D][D]) return false;

    for(long i=0;i<list[D][D].size();i++){
        pair<long,long> dir = list[D][D][i];
        if(used[dir.first][dir.second]==false) continue;

        long how = INF; prov[D][D] = dir;
        for(pair<long,long> node = mp(D,D);node!=mp(S,S);node=prov[node.first][node.second]){
            pair<long,long> prv = prov[node.first][node.second];
            how = min(how,C[prv.first][prv.second][node.first][node.second]-
                          F[prv.first][prv.second][node.first][node.second]);
        }
        for(pair<long,long> node = mp(D,D);node!=mp(S,S);node=prov[node.first][node.second]){
            pair<long,long> prv = prov[node.first][node.second];
            F[prv.first][prv.second][node.first][node.second] += how;
            F[node.first][node.second][prv.first][prv.second] -= how;
        }

        flux += how;
    }

    return true;
}

int main()
{
    freopen("algola.in","r",stdin);
    freopen("algola.out","w",stdout);

    scanf("%ld %ld",&n,&m);
    S=0; D=n+1;

    for(i=1;i<=n;i++) {scanf("%ld",&hum[i]); sum+=hum[i];}

    E.resize(m);
    for(i=0;i<m;i++) scanf("%ld %ld %ld",&E[i].x,&E[i].y,&E[i].c);

    for(i=1;i<=n;i++) addArc(S,S,i,0,hum[i]);
    addArc(1,0,D,D,sum);

    if(flux == sum) {printf("%ld",time);return 0;}
    for(time++;;time++){
        for(i=0;i<E.size();i++){
            addArc(E[i].x,time-1,E[i].y,time,E[i].c);
            addArc(E[i].y,time-1,E[i].x,time,E[i].c);
        }
        for(i=1;i<=n;i++) addArc(i,time-1,i,time,INF);
        addArc(1,time,1,time-1,INF);

        for(;BF(););
        if(flux == sum) {printf("%ld",time);return 0;}
    }


    return 0;
}
