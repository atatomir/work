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

vector<ll> ended;
vector<ll> useful;

// wrong_ended - nodes on path that could be ends
// incomplete - incomplete rivers
aib wrong_ended, incomplete;
int answer[maxN];


int get_pos(int v) {
    return upper_bound(useful.begin(), useful.end(), v) - useful.begin();
}

void decomposite(int node, ll dist) {
    pair<ll, int> best = mp(inf, -1);
    useful.pb(dist);

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
}

void solve(int node, ll dist) {
    if (is_end[node])
        wrong_ended.add( get_pos(leng[node]), +1 );

    if (0 < node && node <= n) {
        //! solve query

        int same = 0;
        same += upper_bound(ended.begin(), ended.end(), dist) - ended.begin();
        same -= wrong_ended.sum( get_pos(dist) );
        same += incomplete.sum( get_pos(dist) );

        answer[node] = n - same;
    }

    for (auto to : list[node]) {
        if (to.first != prov[node])
            incomplete.add( get_pos(leng[ prov[node] ]), +1);

        solve(to.first, dist + to.second);

        if (to.first != prov[node])
            incomplete.add( get_pos(leng[ prov[node] ]), -1);
    }


    if (is_end[node])
        wrong_ended.add( get_pos(leng[node]), -1 );
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

    for (i = 0; i <= nodes; i++) {
        useful.pb(leng[i]);
        if (is_end[i]) ended.pb(leng[i]);
    }
    sort(ended.begin(), ended.end());

    sort(useful.begin(), useful.end());
    useful.resize(unique(useful.begin(), useful.end()) - useful.begin());

    wrong_ended.init(useful.size());
    incomplete.init(useful.size());

    solve(0, 0);
    for (i = 1; i <= n; i++)
        printf("%s %d\n", river[i] + 1, answer[i]);

    return 0;
}
