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

//#define debug(x) ;
#define debug(x) cerr << #x << " = " << x << "\n";

ostream& operator<<(ostream& cerr, vector<ll> aux) {
    cerr << "[";
    for (auto e : aux) cerr << e << ' ';
    cerr << "]";
    return cerr;
}

int t, ti;
int n, i, j, tp, last;
vector<int> v, w;
vector<bool> us;
vector< pair<int, int> > moves;
vector<int> bads, ord;

void exec(int x, int y) {
    moves.pb(mp(x, y));
    swap(v[x], v[y]);
    swap(v[n - 1 - x], v[n - 1 - y]);
}

void dfs(int node) {
    us[node] = true;
    ord.pb(node);
    if (v[node] != w[node]) tp ^= 1, last = node;
    if (!us[w[node]])
        dfs(w[node]);
}

void solve_cycle() {
    int i;

    reverse(ord.begin(), ord.end());
    for (i = 0; i + 1 < ord.size(); i++) {
        int x = ord[i];
        int y = ord[i + 1];

        if (v[y] < v[n - y - 1])
            exec(x, y);
        else
            exec(x, n - y - 1);
    }
}

int solve() {
    int i, bad = 0;
    int cycles = 0, bad_cycles = 0;

    moves.clear();
    bads.clear();

    for (i = 0; i < n / 2; i++) {
        if (v[i] != n - 1 - v[n - i - 1])
            return -1;
        if (v[i] > v[n - i - 1]) bad++;
    }

    if (bad & 1) return -1;

    w.resize(n / 2);
    for (i = 0; i < n / 2; i++) 
        w[i] = min(v[i], v[n - 1 - i]);
    us = vector<bool>(n / 2, false);


    for (i = 0; i < n / 2; i++) {
        if (us[i]) continue;
        tp = 0;
        ord.clear();
        dfs(i);
        if (tp) bad_cycles++, bads.pb(last);
        cycles++;
    }

    for (i = 0; i < bads.size(); i += 2)
        exec(bads[i], n - 1 - bads[i + 1]);

    us = vector<bool>(n / 2, false);
    for (i = 0; i < n / 2; i++)
        w[i] = min(v[i], v[n - 1 - i]);

    for (i = 0; i < n / 2; i++) {
        if (us[i]) continue;
        tp = 0;
        ord.clear();
        dfs(i);
        solve_cycle();
    }


    return n / 2 - cycles + bad_cycles;
}

bool check() {
    for (int i = 0; i < n; i++)
        if (v[i] != i)
            return false;
    return true;
}

int main()
{
    freope("test.in","r",stdin);

    scanf("%d", &t);
    for (ti = 1; ti <= t; ti++) {
        scanf("%d", &n);
        v.resize(n);
        for (auto& e: v) scanf("%d", &e), e--;
        
        int sol = solve();
        if (sol == -1)
            printf("-1\n");
        else {
            printf("%d %d\n", sol, sol);
            for (auto e : moves)
                printf("%d %d\n", e.first + 1, e.second + 1);

            //cerr << check() << '\n';
        }
    }


    return 0;
}
