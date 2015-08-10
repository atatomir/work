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

#define maxN 1000011
#define news (26*26)
#define lett (26)
#define S 799
#define D 800
#define maxCnt (D+17)
#define INF (1e8)
#define code(a,b) (lett+a*26+b)

int n,i,j,m,p1,p2,allFlow;
char s[maxN];
int howNews[lett][lett];
int howLett[lett];
char c1,c2;
vector<int> ids[lett][lett];

int C[maxCnt][maxCnt];
int F[maxCnt][maxCnt];
vector<int> list[maxCnt];
bool us[maxCnt];
int prov[maxCnt];
queue<int> Q;

vector<int> wh[lett];

void addEdge(int x,int y,int cap){
    list[x].pb(y); list[y].pb(x);
    C[x][y]=cap; C[y][x]=0; //! arc de la x la y
    F[x][y]=F[y][x]=0;
}

bool Flux(){
    memset(us,0,sizeof(us));
    memset(prov,0,sizeof(prov));
    while(!Q.empty()) Q.pop();

    Q.push(S); us[S]=true;
    while(!Q.empty()){
        int node = Q.front(); Q.pop();
        if(node==D) continue;

        foreach(list[node]){
            if(us[*it] || F[node][*it]==C[node][*it]) continue;
            us[*it] = true; prov[*it] = node;
            Q.push(*it);
        }
    }

    if(!us[D]) return false;
    foreach(list[D]){
        if(!us[*it]) continue;

        prov[D] = *it;
        int Flow = INF;

        for(int node=D;node!=S;node=prov[node])
            Flow = min(Flow,C[ prov[node] ][node] - F[ prov[node] ][node]);
        for(int node=D;node!=S;node=prov[node]) {
            F[ prov[node] ][node] += Flow;
            F[node][ prov[node] ] -= Flow;
        }

        allFlow += Flow;
    }


    return true;
}

int main()
{
    freopen("teroristi.in","r",stdin);
    freopen("teroristi.out","w",stdout);

    scanf("%d%d\n",&n,&m);
    scanf("%s\n",s+1);
    fordef(i,1,n) howLett[ s[i]-'a' ]++;
    fordef(i,1,m){
        scanf("%c %c\n",&c1,&c2);
        if(c1>c2) swap(c1,c2);
        howNews[c1-'a'][c2-'a']++;
        ids[c1-'a'][c2-'a'].pb(i);
    }

    fordef(i,0,25) addEdge(S,i,howLett[i]);
    fordef(i,0,25){
        p1=p2=0; j=26;
        while(j<news+lett){
            if(i==p1 || i==p2) addEdge(i,j, INF );

            p2++; if(p2==26) { p1++; p2=0; }
            j++;
        }
    }
    p1=p2=0;
    fordef(i,lett,news+lett-1){
        addEdge(i,D, howNews[p1][p2] );
        p2++; if(p2==26) { p1++; p2=0; }
    }

    while( Flux() ) ;


    fordef(i,0,25){
        p1=0;p2=0;j=lett;
        while(j<news){
            for(int aux=1;aux<=F[i][j];aux++) {
                int elem = ids[p1][p2][ ids[p1][p2].size()-1 ];
                ids[p1][p2].pop_back();
                wh[i].pb( elem );
            }

            p2++; if(p2==26) {p1++;p2=0;}
            j++;
        }
    }

    fordef(i,1,n){
        char ch = s[i];
        int elem = wh[ ch-'a' ][ wh[ ch-'a' ].size()-1 ];
        wh[ ch-'a' ].pop_back();

        printf("%d ",elem);
    }


    return 0;
}
