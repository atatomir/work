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

#define maxN 1000011

ll limit = 1LL << 51;

struct frac {
    ll a, b;

    bool operator<(const frac& who) {
        return a * who.b < b * who.a;
    }
};

ll n, i, x, y, bg;
vector<ll> list[maxN];
ll X[maxN];
frac ans;

vector<int> ord;
bool useful[maxN];
vector<frac> aux;

ll dp[maxN];


ll cmmdc(ll a, ll b) {
    if (a < b) swap(a, b);

    while (b > 0) {
        a %= b;
        swap(a, b);
    }

    return a;
}

void print_sol() {
    ll d = cmmdc(ans.a, ans.b);
    ans.a /= d;
    ans.b /= d;

    printf("%lld/%lld", ans.a, ans.b);

    exit(0);
}

void dfs(int node, int root, frac act) {
    static frac aux;
    if (act < ans) ans = act;

    for (auto to : list[node]) {
        if (to == root) continue;
        if (limit / act.a < X[to]) continue;

        aux = {act.a * X[to], act.b + 1};
        dfs(to, node, aux);
    }
}

void solve_brute() {
    int i;

    limit = (1LL << 30) * 1024 * 10;

    ans = {X[1], 1};
    for (i = 1; i <= n; i++)
        dfs(i, 0, {X[i], 1});

    print_sol();
    exit(0);
}

void dfs_ord(int node, int root) {
    ord.pb(node);

    for (auto to : list[node])
        if (to != root)
            dfs_ord(to, node);
}

void solve_line() {
    int i, j;

    ans = {X[1], 1};

    for (i = 1; i <= n; i++) {
        if (list[i].size() > 2)
            return;
        if (list[i].size() == 1)
            bg = i;
    }

    dfs_ord(bg, 0);
    useful[0] = true;
    for (i = 1; i < ord.size(); i++)
        if (X[ord[i - 1]] != 1)
            useful[i] = true;

    aux.clear();
    for (i = 0; i < ord.size(); i++) {
        int id = ord[i];

        if (useful[i]) aux.pb({1, 0});
        for (j = 0; j < aux.size(); j++) {
            if (limit / aux[j].a < X[id]) {
                aux[j] = aux.back();
                aux.pop_back();
                j--;
                continue;
            }

            aux[j].a *= X[id];
            aux[j].b++;

            if (aux[j] < ans) ans = aux[j];
        }
    }

    print_sol();
    exit(0);
}

void dfs_solve(int node, int root) {
    vector<ll> aux;
    aux.clear();

    for (int to : list[node]) {
        if (to == root) continue;
        dfs_solve(to, node);
        aux.pb(dp[to]);
    }

    if (X[node] == 1) {
        // ala bala
        if (aux.size() == 0) {
            dp[node] = 1;
        } else {
            dp[node] = 1 + *max_element(aux.begin(), aux.end());
        }

        frac now = {1, dp[node]};
        if (now < ans)
            ans = now;

        // portocala

        if (aux.size() >= 2) {
            int pos = max_element(aux.begin(), aux.end()) - aux.begin();
            swap(aux[aux.size() - 1], aux[pos]);

            ll v = aux.back();
            aux.pop_back();

            pos = max_element(aux.begin(), aux.end()) - aux.begin();
            swap(aux[aux.size() - 1], aux[pos]);

            v += aux.back() + 1;

            now = {1, v};
            if (now < ans)
                ans = now;
        }
    } else {
        dp[node] = 0;
    }


}

void solve() {
    int i;

    ans = {X[1], 1};
    for (i = 2; i <= n; i++) if (X[i] < ans.a) ans = {X[i], 1};

    dfs_solve(1, 0);
    print_sol();
}

int main()
{
    //freopen("test.in","r",stdin);

    scanf("%lld", &n);
    for (i = 1; i < n; i++) {
        scanf("%d%d", &x, &y);
        list[x].pb(y);
        list[y].pb(x);
    }
    for (i = 1; i <= n; i++) scanf("%lld", &X[i]);

    if (n <= 1000) solve_brute();
    solve_line();

    solve();

    return 0;
}
