#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 100011
#define maxM 250011
#define maxLog 19

int data[maxLog][maxN<<2];
class RangeMinimumQuery {
    public:
        void init(int _dim,int *_from,int *_aux) {
            dim = _dim;
            from = _from;
            aux = _aux;

            aux[1] = 0;
            for (int i = 1; i <= dim; i++) {
                aux[i] = aux[i-1];
                if (i >= (1 << (aux[i]+1))) aux[i]++;
            }

            for (int i = 1; i <= dim; i++) data[0][i] = from[i];
            for (int actLog = 1; actLog <= aux[dim]; actLog++) {
                int limit = dim - (1 << actLog) + 1;
                int def = 1 << (actLog-1);
                for (int i = 1; i <= limit; i++)
                    data[actLog][i] = min(data[actLog-1][i],data[actLog-1][ i + def ]);
            }
        }

        int getMin(int l,int r) {
            int how = r-l+1;
            int actLog = aux[how];

            return min( data[actLog][l], data[actLog][r - (1 << actLog) + 1 ] );
        }

    private:
        int dim;
        int *aux;
        int *from;
};

struct Edge {
    int x,y;
    int cost,id;

    void read(int _id) {
        scanf("%d%d%d",&x,&y,&cost);
        x++; y++;
        id = _id;
    }
    Edge Reverse() {
        Edge aux = *this;
        swap(aux.x, aux.y);
        return aux;
    }

    bool operator<(const Edge& who)const {
        return cost < who.cost;
    }
};

int n,m,i;
Edge aux;
vector< Edge > list[maxN];
vector< Edge > other;
int ans[maxM];

bool us[maxN];
int lvl[maxN];
int id[maxN];
int nextUp[maxN];
int seq[maxN<<2],dim;
int where[maxN];

RangeMinimumQuery RMQ;
int rmq_aux[maxN<<2];

void dfs(int node) {
    us[node] = true;
    seq[++dim] = lvl[node];
    where[node] = dim;

    for (auto e:list[node]) {
        int to = e.y;
        int id_ = e.id;

        if (us[to]) continue;

        lvl[to] = lvl[node] + 1;
        id[to] = id_;
        nextUp[to] = node;

        dfs(to);
        seq[++dim] = lvl[node];
    }
}

int getNext(int node) {
    if (!us[ nextUp[node] ]) return nextUp[node];
    nextUp[node] = getNext( nextUp[node] );
    return nextUp[node];
}

void setEdges(int node,int lvlLimit,int actId) {
    if (us[node]) node = getNext(node);
    while (lvl[node] > lvlLimit) {
        ans[ id[node] ] = actId;
        us[node] = true;

        node = getNext(node);
    }
}

int main()
{
    freopen("arb4.in","r",stdin);
    freopen("arb4.out","w",stdout);

    scanf("%d%d",&n,&m);
    for (i = 1; i < n; i++) {
        aux.read(i);

        list[aux.x].pb(aux);
        list[aux.y].pb(aux.Reverse());
    }
    for (i = n; i <= m; i++) {
        aux.read(i);

        other.pb(aux);
    }

    lvl[1] = 1;
    dfs(1);
    RMQ.init(dim,seq,rmq_aux);
    memset(us,0,sizeof(us));

    sort(other.begin(),other.end());
    for (auto actEdge:other) {
        int xx = actEdge.x;
        int yy = actEdge.y;
        int myId = actEdge.id;

        if (where[xx] > where[yy]) swap(xx,yy);
        int lvlLimit = RMQ.getMin(where[xx],where[yy]);

        setEdges(xx,lvlLimit,myId);
        setEdges(yy,lvlLimit,myId);
    }

    for (i = 1; i < n; i++) {
        printf("%d\n",ans[i]-1);
    }

    return 0;
}
