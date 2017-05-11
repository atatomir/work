#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <cassert>
using namespace std;

#define pb push_back
#define mp make_pair
#define ll long long

#define maxN 400011
#define mod 1000000007


int n, l, q, i;
int dad[maxN], Q[maxN];
vector<int> list[maxN];
int s[maxN], nxt[maxN];
int ans[maxN];

int bonus;
int up[maxN];
vector<int>* down[maxN];

void add(int& a, int b) {
    a += b;
    if (a >= mod) a -= mod;
}

int get(vector<int>* v, int pos) {
    if (pos == l + 1) return 1;
    if (l - pos < v->size())
        return (*v)[l - pos];
    return 0;
}

void add_to_vector(vector<int>*v, int pos) {

    if (l - pos < v->size()) {
        if (pos != l)
            add((*v)[l - pos], (*v)[l - pos - 1]);
        else
            add((*v)[l - pos], 1);
        return;
    }

    if (l - pos == v->size()) {
        if (pos != l)
            v->pb(v->back());
        else
            v->pb(1);

        return;
    }


}

void dfs(int node) {
    //! add leaf
    if (list[node].empty()) {
        if (s[node] == l) add(ans[bonus + node], mod - up[l - 1]);
        if (nxt[node] == l) add(ans[bonus +node], up[l - 1]);

        down[node] = new vector<int>;
        down[node]->clear();
        if (s[node] == l) down[node]->pb(1);

        return;
    }

    //! solve sons
    pair<int, int> best = {-1, 0};
    add(up[nxt[node]], up[nxt[node] - 1]);

    for (auto to : list[node]) {
        dfs(to);
        best = max(best, mp((int)down[to]->size(), to));
    }

    add(up[nxt[node]], mod - up[nxt[node] - 1]);

    //! merge down
    down[node] = down[best.second];
    for (auto to : list[node]) {
        if (to == best.second) continue;
        for (int i = 0; i < down[to]->size(); i++)
            add((*down[node])[i], (*down[to])[i]);
    }

    // compute changes
    if (s[node] == l) {
        add(ans[bonus + node], mod - up[l - 1]);
    } else {
        ans[bonus + node] += mod;
        ans[bonus + node] -= (1LL * up[s[node] - 1] * get(down[node], s[node] + 1)) % mod;
        ans[bonus + node] %= mod;
    }

    if (nxt[node] == l) {
        add(ans[bonus + node], up[l - 1]);
    } else {
        ans[bonus + node] += (1LL * up[nxt[node] - 1] * get(down[node], nxt[node] + 1)) % mod;
        ans[bonus + node] %= mod;
    }

    //! add actual position
    add_to_vector(down[node], s[node]);
}

void solve_bucket(int _bonus) {
    int i;

    bonus = _bonus;
    for (i = 1; i <= n; i++) nxt[i] = max(1, Q[bonus + i]);

    up[0] = 1;
    dfs(1);

    if (down[1]->size() == l)
        ans[bonus] = (*down[1])[l - 1];
    else
        ans[bonus] = 0;

    for (i = 1; i <= n; i++) add(ans[bonus + i], ans[bonus + i - 1]), s[i] = nxt[i];
}

int main()
{
    freopen("meow.in", "r", stdin);
    freopen("meow.out", "w", stdout);

    cin >> n >> l >> q;
    for (i = 2; i <= n; i++) cin >> dad[i], dad[i]++, list[dad[i]].pb(i);
    for (i = 1; i <= n; i++) cin >> s[i];
    for (i = 1; i <= q; i++) cin >> Q[i];

    for (i = 1; i <= q; i += n)
        solve_bucket(i - 1);

    ll sol = 0;
    for (i = 1; i <= q; i++) {
        sol += 1LL * i * ans[i];
        sol %= mod;
        //cerr << ans[i] << '\n';
    }

    cout << sol;

    return 0;
}
