#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define inf (1LL << 60)
#define maxN 1000011
#define sdim 15

struct aib {
    int dim;
    vector<int> data;

    void init(int _dim) {
        dim = _dim;
        data = vector<int>(dim + 10, 0);
    }

    int zrs(int x) {
        return (x ^ (x - 1)) & x;
    }

    void add(int pos, int v) {
        while (pos <= dim) {
            data[pos] += v;
            pos += zrs(pos);
        }
    }

    int sum(int pos) {
        int ans = 0;

        while (pos) {
            ans += data[pos];
            pos -= zrs(pos);
        }

        return ans;
    }
};

int n, m, i, nodes;
char river[maxN][sdim];

int dad[maxN];
ll dist_dad[maxN];
vector< pair<int, ll> > list[maxN];

int prov[maxN];
bool is_end[maxN];
ll leng[maxN];
ll to_root[maxN];

int cnt;
int wh_l[maxN], wh_r[maxN];
bool blocked[maxN];
aib work, help;

vector< pair<ll, int> > R; // rivers
vector< pair<ll, int> > B; // blocked
int now_dead;

int answer[maxN];



void decomposite(int node, ll dist) {
    pair<ll, int> best = mp(inf, -1);
    to_root[node] = dist;

    wh_l[node] = wh_r[node] = ++cnt;

    if (list[node].empty()) return; // leaf

    //! get the smallest path
    for (auto to : list[node]) {
        decomposite(to.first, dist + to.second);
        leng[to.first] += to.second;

        best = min(best, mp(leng[to.first], to.first));
    }

    leng[node] = best.first;
    prov[node] = best.second;

    for (auto to : list[node]) {
        if (to.first == best.second) continue;
        is_end[to.first] = true;
    }

    wh_r[node] = cnt;
}

void block_node(int node) {
    int aux;

    if (work.sum(wh_l[node])) {
        aux = work.sum(wh_l[node]);

        blocked[aux] = false;
        work.add(wh_l[aux], -aux);
        work.add(wh_r[aux] + 1, +aux);

        help.add(wh_l[aux], -1);
        now_dead--;
    }

    if (help.sum(wh_r[node]) - help.sum(wh_l[node] - 1)) return;


    blocked[node] = true;
    work.add(wh_l[node], +node);
    work.add(wh_r[node] + 1, -node);
    now_dead++;

    help.add(wh_l[node], +1);
}



int main()
{
    freopen("test.in","r",stdin);

    scanf("%d%d\n", &n, &m);
    for (i = 1; i <= n; i++) {
        scanf("%s%d%lld\n", river[i] + 1, &dad[i], &dist_dad[i]);

        if (dad[i] != 0) dad[i] += n;
        list[dad[i]].pb(mp(i, dist_dad[i]));
    }

    for (i = 1; i <= m; i++) {
        scanf("%d%lld", &dad[n + i], &dist_dad[n + i]);

        if (dad[n + i] != 0) dad[n + i] += n;
        list[ dad[n + i] ].pb(mp(n + i, dist_dad[n + i]));
    }

    nodes = n + m;
    decomposite(0, 0);

    for (i = 1; i <= n; i++) R.pb(mp(to_root[i], i));
    for (i = 0; i <= nodes; i++) B.pb(mp(leng[i], i));


    sort(B.begin(), B.end());
    sort(R.begin(), R.end());
    reverse(R.begin(), R.end());

    work.init(nodes + 5);
    help.init(nodes + 5);
    dad[0] = 0;

    for (auto act : R) {
        int node = act.second;
        ll limit = act.first;

        while (!B.empty()) {
            if (B.back().first <= limit) break;

            block_node(B.back().second);
            B.pop_back();
        }

        answer[ node ] = now_dead + 1 - work.sum(wh_l[node]);
    }


    for (i = 1; i <= n; i++)
        printf("%s %d\n", river[i] + 1, answer[i]);

    return 0;
}
