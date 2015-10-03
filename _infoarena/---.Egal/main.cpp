#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <unordered_map>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 100011
#define maxSQRT 411

int n, i, x, y;
vector<int> list[maxN];
int key[maxN];

bool us[maxN];
int dim;
int newArb[maxN];
int newKeys[maxN];

vector< pair<int, int> > Q[maxSQRT];
int smen_dim;
int smen_count;

int cnt[maxN];
int best;
int ans_safe[maxN], ans_cnt[maxN];

int getBlock(int x) {
    int blk = x / smen_dim;
    if (x % smen_dim == 0) blk--;
    return blk + 2;
}

void addKey(int k, int& best) {
    cnt[k]++;
    if (cnt[k] == cnt[best]) best = min(k, best);
    if (cnt[k] >  cnt[best]) best = k;
}

void brute(int node, int l, int r) {
    best = 0;
    for(int i = l; i <= r; i++)
        addKey(newKeys[i], best);

    ans_safe[node] = best;
    ans_cnt[node] = cnt[best];

    for(int i = l; i <= r; i++) cnt[newKeys[i]]--;
}

void dfs(int node) {
    us[node] = true;

    int aux = ++dim;
    newArb[dim] = node;
    newKeys[dim] = key[node];

    for (auto to : list[node]) {
        if (us[to]) continue;

        dfs(to);
    }

    if (dim - aux + 1 >= smen_dim)
        Q[ getBlock(aux) ].pb(mp(aux, dim));
    else
        brute(node, aux, dim);
}

bool cmp(const pair<int, int>& a, const pair<int, int>& b){
    return a.second < b.second;
}

void solve_bucket(int id) {
    int start = smen_dim * (id - 1) + 1;
    int i = start;
    int l_best;

    best = 1;
    memset(cnt, 0, sizeof(cnt));

    sort(Q[id].begin(), Q[id].end(), cmp);

    for (auto act : Q[id]) {
        while (i <= act.second) {
            addKey(newKeys[i], best);

            i++;
        }

        l_best = best;
        for (int j = act.first; j < start; j++) {
            addKey(newKeys[j], l_best);
        }

        ans_safe[ newArb[act.first] ] = l_best;
        ans_cnt[ newArb[act.first] ] = cnt[l_best];

        for (int j = act.first; j < start; j++) cnt[newKeys[j]]--;
    }
}

vector<int> aux;
unordered_map<int, int> to;
int from[maxN];
void do_it() {
    int i;

    aux.resize(n);
    for (i = 1; i <= n; i++) aux[i - 1] = key[i];

    sort(aux.begin(), aux.end());
    aux.resize(unique(aux.begin(), aux.end()) - aux.begin());
    for (i = 0; i < aux.size(); i++) {
        to[ aux[i] ] = i + 1;
        from[i + 1] = aux[i];
    }

    for (i = 1; i <= n; i++) key[i] = to[key[i]];
}

int main()
{

    freopen("egal.in","r",stdin);
    freopen("egal.out","w",stdout);

    scanf("%d", &n);
    for (i = 1; i < n; i++) {
        scanf("%d%d", &x, &y);
        list[x].pb(y);
        list[y].pb(x);
    }
    for (i = 1; i <= n; i++) scanf("%d", &key[i]);
    do_it();

    smen_dim = (int)sqrt(n);
    smen_count = (n + smen_dim - 1) / smen_dim;
    dfs(1);

    for (i = 1; i <= smen_count; i++) solve_bucket(i);

    for (i = 1; i <= n; i++) printf("%d %d\n", from[ans_safe[i]], ans_cnt[i]);

    return 0;
}
