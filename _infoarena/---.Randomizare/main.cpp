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

#define maxN 200011

int n, i;
int v[maxN], p[maxN];
bool us[maxN];

vector< vector<int> > ord;
vector<int> aux, sz, last;

int need[maxN];
int ans[maxN];

int cnt;
int mark[maxN];

void dfs(int node) {
    us[node] = true;
    aux.pb(node);

    if (!us[p[node]])
        dfs(p[node]);
}

int gcd(int a, int b) {
    if (a < b) swap(a, b);

    while (b > 0) {
        a %= b;
        swap(a, b);
    }

    return a;
}

void rot(vector<int> data, int cnt) {
    int i, dim;

    dim = data.size();
    for (i = 0; i < cnt; i++) data.pb(data[i]);
    for (i = 0; i < dim; i++)
        ans[ data[i] ] = v[ data[i + cnt] ];
}

int main()
{
    freopen("randomizare.in","r",stdin);
    freopen("randomizare.out","w",stdout);

    scanf("%d", &n); need[0] = -1;
    for (i = 1; i <= n; i++) scanf("%d", &v[i]), need[i] = -1;
    for (i = 1; i <= n; i++) scanf("%d", &p[i]);

    for (i = 1; i <= n; i++) {
        if (us[i]) continue;
        aux.clear();
        dfs(i);
        ord.pb(aux);
        sz.pb(aux.size());
    }

    sort(sz.begin(), sz.end());
    sz.resize(unique(sz.begin(), sz.end()) - sz.begin());

    for (auto &act : ord) {
        int dim = act.size();
        if (need[dim] != -1) {
            rot(act, need[dim]);
            continue;
        }

        cnt = 0;
        for (i = 0; i <= dim; i++) mark[i] = 0;

        //! new dimension
        last.clear();
        for (auto e : sz) {
            int cmmdc = gcd(dim, e);
            last.pb(cmmdc);
        }

        sort(last.begin(), last.end());
        last.resize(unique(last.begin(), last.end()) - last.begin());

        for (auto cmmdc : last) {
            if (cmmdc == 1) continue;
            if (need[cmmdc] == -1) continue;

            cnt++;
            for (i = need[cmmdc]; i < dim; i += cmmdc) mark[i]++;
        }

        pair<int, int> best = mp(-1, -1);
        for (i = 0; i < dim; i++) {
            if (mark[i] != cnt) continue;

            if (best.first == -1) best = mp(v[ act[i] ], i);
            if (best.first > v[ act[i] ]) best = mp(v[ act[i] ], i);
        }

        rot(act, best.second);
        need[dim] = best.second;

        for (auto e : last) need[e] = best.second % e;
    }

    for (i = 1; i <= n; i++) printf("%d ", ans[i]);


    return 0;
}
