#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>
#include <map>
#include <stack>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 15011
#define maxM 100011

struct edge {
    int x, y, col;

    int get_from(int _x) {
        if (x == _x) return y;
        return x;
    }
};

int t, ti;
int i, n, m;
bool used[maxM];
edge E[maxM];
vector<int> list[maxN];

vector<int> added, wh[maxN];
int aux_col[maxN];
priority_queue< pair<int, int> > H;

map<int, int> paired[maxN];
vector<int> ans;

stack< pair<int, int> > S;
vector< pair<int, int> > aux[maxN];


void pair_them(int node) {
    added.clear();
    paired[node].clear();

    for (auto to : list[node])
        aux_col[ E[to].col ]++, added.pb(E[to].col), wh[E[to].col].pb(to);

    sort(added.begin(), added.end());
    added.resize(unique(added.begin(), added.end()) - added.begin());

    while (!H.empty()) H.pop();
    for (auto e : added)
        H.push(mp(aux_col[e], e));

    while (!H.empty()) {
        auto bg = H.top(); H.pop();
        auto sm = H.top(); H.pop();

        int c1 = bg.second;
        int c2 = sm.second;

        paired[node][ wh[c1].back() ] = wh[c2].back();
        paired[node][ wh[c2].back() ] = wh[c1].back();
        wh[c1].pop_back(); aux_col[c1]--;
        wh[c2].pop_back(); aux_col[c2]--;

        if (aux_col[c1] > 0) H.push(mp(aux_col[c1], c1));
        if (aux_col[c2] > 0) H.push(mp(aux_col[c2], c2));
    }

}

void solve2(int node, int from) {
    int le, ri, toto, c1, c2, pp;
    bool found;
    int edge_to = paired[node][from];
    int to = E[edge_to].get_from(node);

    used[from] = true;
    S.push(mp(node, from));
    aux[node].pb(mp(0, 0));

    while (!S.empty()) {
        node = S.top().first;
        from = S.top().second;

        if (aux[node].back() == mp(0, 0)) {
            edge_to = paired[node][from];
            to = E[edge_to].get_from(node);

            aux[node].pop_back(), aux[node].pb(mp(E[from].col, E[edge_to].col));

            if (!used[edge_to]) {
                used[edge_to] = true;

                S.push(mp(to, edge_to));
                aux[to].pb(mp(0, 0));

                continue;
            }
        }

        le = aux[node].back().first;
        ri = aux[node].back().second;

        found = false;
        for (int i = 0; i < list[node].size(); i++) {
            int e = list[node][i];

            if (used[e]) {
                list[node][i] = list[node].back();
                list[node].pop_back();
                i--;
                continue;
            }

            pp = paired[node][e];
            c1 = E[e].col;
            c2 = E[pp].col;

            if (c1 == le || c2 == ri) swap(e, pp), swap(c1, c2);
            if (c1 == le || c2 == ri)
                cerr << "err", exit(101);

            used[e] = true;
            aux[node].back().second = c2;

            toto = E[e].get_from(node);
            aux[toto].pb(mp(0, 0));
            S.push(mp(toto, e));
            found = true;
            break;
        }

        if (found) continue;
        aux[node].pop_back();
        S.pop();
        ans.pb(node);
    }

}

int main()
{
    freopen("ulei.in","r",stdin);
    freopen("ulei.out","w",stdout);

    scanf("%d", &t);
    for (ti = 1; ti <= t; ti++) {
        scanf("%d%d", &n, &m);

        for (i = 1; i <= n; i++) list[i].clear();
        for (i = 1; i <= m; i++) {
            scanf("%d%d%d", &E[i].x, &E[i].y, &E[i].col);
            list[E[i].x].pb(i);
            list[E[i].y].pb(i);
        }

        for (i = 1; i <= n; i++)
            random_shuffle(list[i].begin(), list[i].end());

        for (i = 1; i <= n; i++)
            pair_them(i);

        int R = 1;
        if (m >= 20001) R = 20001;

        memset(used, 0, sizeof(used));
        used[R] = true;
        int n1 = E[R].x;
        int n2 = E[R].y;

        ans.clear();
        solve2(n2, R);
        ans.pb(n1);

        if (ans.size() != m + 1) exit(102);

        for (auto e : ans) printf("%d ", e);
        printf("\n");
    }


    return 0;
}
